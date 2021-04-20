class SessionsController < ApplicationController
  def new
  end

  def create
    user = User.find_by_email(params[:email])
    if user && user.authenticate(params[:password])
      session[:user_id] = user.id
      redirect_to projects_path,
        notice: t("messages.new_session")
    else
      flash.now.alert = t("messages.unknown_mail_or_username")
      render "new"
    end
  end

  def destroy
    session[:user_id] = nil
    redirect_to root_path,
      notice: t("messages.destroy_session")
  end
end
