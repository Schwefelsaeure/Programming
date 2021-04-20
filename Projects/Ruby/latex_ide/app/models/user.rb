class User < ActiveRecord::Base
  after_create :create_user_directory

  has_secure_password
  attr_accessible :email, :password, :password_confirmation
  
  validates :email,
    format: /^([^@\s]+)@((?:[-a-z0-9]+\.)+[a-z]{2,})$/i,
    uniqueness: true

  has_many :projects
  
  private

  def create_user_directory
    logger.debug("Creating user directory: #{user_directory}")
    if File.directory?(user_directory)
      logger.warn("User directory already exists!")
    else
      Dir.mkdir(user_directory)
      logger.debug("Created user directory.")
    end
  end

  def user_directory
    File.join(USERS_DIRECTORY, id.to_s)
  end
end
