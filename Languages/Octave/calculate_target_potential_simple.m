# Calculate Euclidean distance to a target point.
# Use a discretization to plot the distance as 3D mesh.
source = [ 0 0 ];
target = [ 10 10 ];

min_x = min([source(:,1) target(:,1)]);
max_x = max([source(:,1) target(:,1)]);
min_y = min([source(:,2) target(:,2)]);
max_y = max([source(:,2) target(:,2)]);
discretization = 10;

x = linspace(min_x, max_x, discretization);
y = linspace(min_y, max_y, discretization);

[xx, yy] = meshgrid(x, y);
# Calculate Euclidean distance to "target".
zz = sqrt((xx .- target(1)).^2 + (yy .- target(2)).^2);

meshc(xx, yy, zz);

title(sprintf("Euclidean Distance to Target (%.1f, %.1f)", target(1), target(2)));
xlabel("x");
ylabel("y");
zlabel("z");