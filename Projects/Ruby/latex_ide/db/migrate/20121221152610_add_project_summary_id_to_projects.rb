class AddProjectSummaryIdToProjects < ActiveRecord::Migration
  def change
    add_column :projects, :project_summary_id, :integer
  end
end
