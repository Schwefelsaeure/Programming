class ProjectFilesController < ApplicationController
  before_filter :require_login
  before_filter :redirect_if_no_file, except: [:upload]

  def new
  end

  def upload
    @project = current_user.projects.find(params[:project])
    if @project
      if ProjectFile.save(params[:file_upload][:upload], @project)
        reload_current_page(notice: t("messages.upload_project_file"))
      else
        flash.now.alert(t("messages.upload_project_file_failed"))
      end
    end
  end

  def edit
  end

  def update
    if @project_file.rename(params[:project_file][:name])
      reload_current_page(notice: t("messages.update_project_file"))
    else
      render "edit"
    end
  end

  def delete
    if @project_file.destroy
      reload_current_page(notice: t("messages.destroy_project_file"))
    else
      flash.now.alert(t("messages.destroy_project_file_failed"))
    end
  end

  private

  def redirect_if_no_file
    @project = current_user.projects.find(params[:project])
    @project_file = @project.project_files.find(params[:file])
  rescue
    reload_current_page(alert: t("messages.no_file"))
  end
end
