class CreateProjectSummaries < ActiveRecord::Migration
  def change
    create_table :project_summaries do |t|
      t.string :log
      t.string :pdf

      t.timestamps
    end
  end
end
