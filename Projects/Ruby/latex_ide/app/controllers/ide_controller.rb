class IdeController < ApplicationController
  before_filter :require_login, :set_current_page_as_reload_address, :redirect_if_no_project
  before_filter :redirect_if_no_file, only: [:edit_file, :compile]

  def edit_file
    @file_content = @file.read_text_file
    @project_summary = ProjectSummary.where(project_id: @project.id).first
    @log_content = @project_summary.read_log_file if @project_summary
  end

  def compile
    @file.update_text_file(params[:editor_content])

    if params[:commit].casecmp("compile") == 0
      if @file.compile?
        redirect_to edit_file_in_ide_path(project: @project.id, file: @file.id),
          notice: t("messages.compile_file")
      else
        redirect_to edit_file_in_ide_path(project: @project.id, file: @file.id),
          alert: t("messages.compile_file_failed")
      end
    else
        redirect_to edit_file_in_ide_path(project: @project.id, file: @file.id),
          notice: t("messages.save_file")
    end
  end

  def pdf
    @project_summary = ProjectSummary.where(project_id: @project.id).first

    if @project_summary && @project_summary.pdf
      send_file @project_summary.pdf,
        filetype: :pdf
    end
  end

  private

  def redirect_if_no_project
    @project = current_user.projects.find(params[:project])
  rescue
    redirect_to root_path,
      alert: t("messages.no_project")
  end

  def redirect_if_no_file
    @file = @project.project_files.find(params[:file])
  rescue
    redirect_to root_path,
      alert: t("messages.no_file")
  end
end
