class ProjectSummary < ActiveRecord::Base
  attr_accessible :log, :pdf

  belongs_to :project

  def read_log_file
    File.open(log, "rb") { |f| f.read }
  rescue
    t("messages.no_log")
  end
end
