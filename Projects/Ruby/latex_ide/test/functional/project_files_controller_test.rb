require 'test_helper'

class ProjectFilesControllerTest < ActionController::TestCase
  test "should get new" do
    get :new
    assert_response :success
  end

  test "should get upload" do
    get :upload
    assert_response :success
  end

  test "should get rename" do
    get :rename
    assert_response :success
  end

  test "should get delete" do
    get :delete
    assert_response :success
  end

end
