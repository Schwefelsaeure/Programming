class ProjectsController < ApplicationController
  before_filter :require_login, :set_current_page_as_reload_address
  before_filter :redirect_if_no_project, except: [:index, :new, :create]

  def index
    @projects = current_user.projects
  end

  def show
  end

  def new
    @project = current_user.projects.build
  end

  def create
    @project = current_user.projects.build(params[:project])
    if @project.save
      redirect_to projects_path,
        notice: t("messages.new_project")
    else
      render "new"
    end
  end

  def edit
  end

  def update
    if @project.update_attributes(params[:project])
      redirect_to projects_path,
        notice: t("messages.edit_project")
    else
      render "edit"
    end
  end

  def destroy
    @project.destroy
    redirect_to projects_path,
      notice: t("messages.delete_project")
  end

  def download
    zipped_project = @project.zip
    send_file zipped_project,
      filename: @project.name,
      type: :zip
    # Don't delete ZIP file. ZIP file will only be updated next time user
    # downloads the project. Saves CPU time for large projects.
  end

  private

  def redirect_if_no_project
    @project = current_user.projects.find(params[:id])
  rescue
    redirect_to projects_path,
      alert: t("messages.no_project")
  end
end
