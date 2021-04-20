require 'test_helper'

class IdeControllerTest < ActionController::TestCase
  test "should get edit_project" do
    get :edit_project
    assert_response :success
  end

  test "should get edit_file" do
    get :edit_file
    assert_response :success
  end

end
