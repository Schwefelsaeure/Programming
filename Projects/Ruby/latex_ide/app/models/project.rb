require "fileutils"

class Project < ActiveRecord::Base
  after_create :create_project_directory
  after_destroy :delete_project_directory

  attr_accessible :description, :name
  validates :name, presence: true

  belongs_to :user
  has_many :project_files
  belongs_to :project_summary

  def zip
    if File.directory?(project_directory)
      input = project_directory
      output = input + ".zip"
      zip_command = "7z a -tzip #{output} #{input}"
      output if system(zip_command)
    end
  end

  def project_directory
    File.join(USERS_DIRECTORY, user_id.to_s, id.to_s)
  end

  private

  def create_project_directory
    logger.debug("Creating project directory: #{project_directory}")
    if File.directory?(project_directory)
      logger.warn("Project directory already exists!")
    else
      Dir.mkdir(project_directory)
      logger.debug("Created project directory.")
    end
  end

  def delete_project_directory
    logger.debug("Deleting project directory: #{project_directory}")
    if File.directory?(project_directory)
      FileUtils.rm_rf(project_directory)
      logger.debug("Deleted project directory.")
    else
      logger.warn("Project directory does not exist!")
    end
  end
end
