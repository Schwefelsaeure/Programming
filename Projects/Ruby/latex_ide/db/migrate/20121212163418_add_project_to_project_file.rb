class AddProjectToProjectFile < ActiveRecord::Migration
  def change
    add_column :project_files, :project_id, :integer
  end
end
