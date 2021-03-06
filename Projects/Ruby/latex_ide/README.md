# README

This application represents a simple LaTeX IDE (editor and compiler).

A user can create projects (simple folders) and upload files to a project. Binary and text files are allowed to upload. The text files can be edited with a simple editor and compiled to a PDF afterwards.

Necessary programs to run this application:

- 7z: to create a ZIP archive of a project
- pdflatex: to create a PDF file.

**Be careful:** Don't run this application in a productive environment because there still exists some critical security issues in "app/models/project_file.rb". Renaming is not secure (i.e. relative paths) and a TEX-Source files can include files outside own user directory via "\input{relative path}". 

## Getting Started

1. `sudo apt install ruby libgmp-dev`
2. `gem install --install-dir .gem -g`
3. `rails server`
