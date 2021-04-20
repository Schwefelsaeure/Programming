class AddProjectIdToProjectSummaries < ActiveRecord::Migration
  def change
    add_column :project_summaries, :project_id, :integer
  end
end
