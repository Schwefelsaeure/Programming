# Be sure to restart your server when you modify this file.

# Directory where to store all user folders.
USERS_DIRECTORY = File.join(".", "public", "users")
Dir.mkdir(USERS_DIRECTORY) unless File.directory?(USERS_DIRECTORY)
