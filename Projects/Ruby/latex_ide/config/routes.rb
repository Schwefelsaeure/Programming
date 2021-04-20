LatexIde::Application.routes.draw do
  get "ide/:project/:file/edit" => "ide#edit_file", as: "edit_file_in_ide"
  post "ide/:project/:file/compile/" => "ide#compile", as: "compile_file_in_ide"
  get "ide/:project/pdf" => "ide#pdf", as: "pdf_project"

  resources :projects
  get "projects/:id/download/" => "projects#download", as: "download_project"

  get "project_files/:project/new" => "project_files#new", as: "new_project_file"
  post "project_files/:project/upload" => "project_files#upload", as: "upload_project_file"
  get "project_files/:project/:file/edit" => "project_files#edit", as: "edit_project_file"
  post "project_files/:project/:file/edit" => "project_files#update", as: "update_project_file"
  delete "project_files/:project/:file/delete" => "project_files#delete", as: "delete_project_file"

  resources :users, only: [:new, :create]

  get "login" => "sessions#new", as: "login"
  post "sessions" => "sessions#create", as: "sessions"
  delete "logout" => "sessions#destroy", as: "logout"

  root to: "pages#home"

  # The priority is based upon order of creation:
  # first created -> highest priority.

  # Sample of regular route:
  #   match 'products/:id' => 'catalog#view'
  # Keep in mind you can assign values other than :controller and :action

  # Sample of named route:
  #   match 'products/:id/purchase' => 'catalog#purchase', :as => :purchase
  # This route can be invoked with purchase_url(:id => product.id)

  # Sample resource route (maps HTTP verbs to controller actions automatically):
  #   resources :products

  # Sample resource route with options:
  #   resources :products do
  #     member do
  #       get 'short'
  #       post 'toggle'
  #     end
  #
  #     collection do
  #       get 'sold'
  #     end
  #   end

  # Sample resource route with sub-resources:
  #   resources :products do
  #     resources :comments, :sales
  #     resource :seller
  #   end

  # Sample resource route with more complex sub-resources
  #   resources :products do
  #     resources :comments
  #     resources :sales do
  #       get 'recent', :on => :collection
  #     end
  #   end

  # Sample resource route within a namespace:
  #   namespace :admin do
  #     # Directs /admin/products/* to Admin::ProductsController
  #     # (app/controllers/admin/products_controller.rb)
  #     resources :products
  #   end

  # You can have the root of your site routed with "root"
  # just remember to delete public/index.html.
  # root :to => 'welcome#index'

  # See how all your routes lay out with "rake routes"

  # This is a legacy wild controller route that's not recommended for RESTful applications.
  # Note: This route will make all actions in every controller accessible via GET requests.
  # match ':controller(/:action(/:id))(.:format)'
end
