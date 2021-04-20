module ProjectsHelper
  def back_to_projects
    content_tag(:p,
                link_to(t("links.your_projects"), projects_path),
                class: "subNavigation")
  end
end
