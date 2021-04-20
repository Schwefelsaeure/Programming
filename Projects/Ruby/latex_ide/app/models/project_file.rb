class ProjectFile < ActiveRecord::Base
  attr_accessible :comment, :content_type, :location, :name, :project_id, :size

  after_destroy :delete_file_from_filesystem

  validates :location, uniqueness: true

  belongs_to :project

  def self.save(upload, project)
    filename =  upload.original_filename
    location = File.join(project.project_directory, filename)

    logger.debug("Saving file: #{location}")
    File.open(location, "wb") { |f| f.write(upload.read) }
    logger.debug("Saved file.")

    self.add_to_database(upload, project)
  end

  def is_text_file?
    /^text\/$*/ === content_type
  end

  def read_text_file
    File.open(location, "rb") { |f| f.read }
  end

  def update_text_file(new_text)
    if is_text_file?
      File.open(location, "wb") { |f| f.write(new_text) }
    end
  end

  def compile?
    input = name
    latex_command = "pdflatex -halt-on-error -interaction nonstopmode -jobname #{name} #{input}"

    logger.debug("Compiling...")
    logger.debug(latex_command)

    no_error = Dir.chdir(project.project_directory) do
      system(latex_command)
    end
    create_project_summary

    logger.debug("Compiled without errors: #{no_error.to_s}")

    no_error
  end

  def rename(new_name)
    errors.add(:name, "can not be empty") if new_name.empty?
    errors.add(:name, "must be different from old name") if new_name == name

    if errors.empty?
      old_location = location
      new_location = File.join(project.project_directory, new_name)

      if update_attributes(location: new_location, name: new_name)
        logger.debug("Renaming file #{old_location} to #{new_location}...")
        FileUtils.mv(old_location, new_location)
        logger.debug("Renamed file.")
      end
    end
  end

  private

  def self.add_to_database(upload, project)
    content_type = upload.content_type
    filename =  upload.original_filename
    location = File.join(project.project_directory, filename)
    size = File.size?(location)

    ProjectFile.create(content_type: content_type, location: location, name: filename, size: size, project_id: project.id)
  end
  
  def delete_file_from_filesystem
    if File.exists?(location)
      File.delete(location)
    end
  end

  def create_project_summary
    log_name = name + ".log"
    pdf_name = name + ".pdf"

    log_location = File.join(project.project_directory, log_name)
    pdf_location = File.join(project.project_directory, pdf_name)

    project_summary = project.project_summary
    project_summary ||= ProjectSummary.new

    project_summary.project_id = project.id

    if File.exist?(log_location)
      project_summary.log = log_location
    else
      project_summary.log = nil
      logger.warn("Cannot find log file for project file #{name}.")
    end

    if File.exist?(pdf_location)
      project_summary.pdf = pdf_location
    else
      project_summary.pdf = nil
      logger.warn("Cannot file pdf file for project file #{name}.")
    end

    project_summary.save

    project.project_summary_id = project_summary.id
    project.save
  end
end
