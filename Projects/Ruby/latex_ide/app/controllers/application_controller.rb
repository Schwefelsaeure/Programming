class ApplicationController < ActionController::Base
  protect_from_forgery

  private

  def current_user
    if session[:user_id]
      @current_user ||= User.find(session[:user_id])
    end
  end

  def user_signed_in?
    current_user.present?
  end

  def require_login
    unless user_signed_in?
      redirect_to  login_path,
        alert: t("messages.not_signed_in_user")
    end
  end

  def reload_current_page(flash_message)
    current_page = session[:return_to];
    current_page ||= root_path

    redirect_to current_page,
      flash_message
  end

  def set_current_page_as_reload_address
    session[:return_to] = request.fullpath
  end

  helper_method :user_signed_in?, :require_login, :reload_current_page, :set_current_page_as_reload_address
end
