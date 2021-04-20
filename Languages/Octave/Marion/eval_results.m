%% clean up

clear;
close all;
clc;
dbstop if error;

%% paths

path = 'output/';
files = dir([path 'basic_1_chicken_gnm1*']);
output_file_name = 'postvis.trajectories';
n_peds = 200; 

%% read data and eval


for iped = 1: n_peds   
    
    for ifile = 1:length(files)
        fprintf('Status: %.3f%% \n', (length(files)*iped + ifile) / (n_peds * length(files)))
        file_name_i = [path files(ifile).name '\' output_file_name];
        data = dlmread(file_name_i,' ', 1, 0);
        ped_id = data(:,2);
        
        x = data(:,3);
        y = data(:,4);
        
        idx = find(ped_id == iped);
        x_ped = x(idx);
        y_ped = y(idx);
        
        if ifile == 1
            % first is taken as a reference 
            x_ped_ref = x_ped; 
            y_ped_ref = y_ped; 
        else
            % find minimum length
            len_x = min(length(x_ped), length(x_ped_ref)); 
            
            error_x(ifile, iped) = max(x_ped_ref(1:len_x) - x_ped(1:len_x)); 
            error_y(ifile, iped) = max(y_ped_ref(1:len_x) - y_ped(1:len_x)); 
%             if error_y(ifile, iped) > 8
%                figure(); 
%                plot(x_ped_ref, y_ped_ref, '.b')
%                hold on 
%                plot(x_ped, y_ped,'.:r')
%                legend('Ref (1st run)', ['This run (' num2str(ifile) ')' ])
%             end
        end

    end
end

figure(); 
imagesc(error_x)
xlabel('# file')
ylabel('# ped')
title('x-Direction')
colorbar


figure(); 
imagesc(error_y)
xlabel('# file')
ylabel('# ped')
title('y-Direction')
colorbar

