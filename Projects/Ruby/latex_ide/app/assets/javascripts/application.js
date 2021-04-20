// This is a manifest file that'll be compiled into application.js, which will include all the files
// listed below.
//
// Any JavaScript/Coffee file within this directory, lib/assets/javascripts, vendor/assets/javascripts,
// or vendor/assets/javascripts of plugins, if any, can be referenced here using a relative path.
//
// It's not advisable to add code directly here, but if you do, it'll appear at the bottom of the
// the compiled file.
//
// WARNING: THE FIRST BLANK LINE MARKS THE END OF WHAT'S TO BE PROCESSED, ANY BLANK LINE SHOULD
// GO AFTER THE REQUIRES BELOW.
//
//= require jquery
//= require jquery_ujs
//= require jquery-ui
//= require_tree .

$(function() {
	// Activate jQuery UI widgets.
	$("#accordion_projects").accordion({
		collapsible: true,
		autoHeight: false, 
		active: false
	});

	$("#accordion_ide").accordion({
		collapsible: true,
		autoHeight: false
	});

	$("#tabs_ide").tabs();

	// Activate "my" upload button.
	$("div#files").each(function(index, element) {
		upload_button = $(this).find("#file_upload_button");
		file_field = $(this).find("#file_field");
		submit = $(this).find("#submit");

		upload_button.click(function() {
			file_field.click();
		});

		file_field.change(function() {
			filename = file_field.val();

			if(filename.length > 0)
			submit.click();
		});
	});
});
