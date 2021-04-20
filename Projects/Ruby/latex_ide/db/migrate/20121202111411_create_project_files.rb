class CreateProjectFiles < ActiveRecord::Migration
  def change
    create_table :project_files do |t|
      t.string :name
      t.string :location
      t.float :size
      t.string :content_type
      t.text :comment

      t.timestamps
    end
  end
end
