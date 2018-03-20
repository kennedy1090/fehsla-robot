clc; clear; close all;
Info = csvread('LOG007.TXT');
Time = Info(:, 1);
X = Info(:, 2);
Y = Info(:,3);
Angle = Info(:,4);
Vx = Info(:,5);
Vy = Info(:,6);
Estx = Info(:,7);
Esty = Info(:,8);
Travel = Info(:,9);
TrX = cos(Travel);
TrY = sin(Travel);

%set the window style to normal
set(0,'DefaultFigureWindowStyle','normal')

%read in image of the course 
%this image file must be in the same folder as the script
img = imread('Exploration_03_Course_Image.png');

%set course axes ranges
x_min = 0;
x_max = 72;
y_min = 0;
y_max = 36;

%open MATLAB figure with course image at set location on screen
hFig = figure(1);
set(hFig, 'Position', [150 150 879 478])
imagesc([x_min x_max], [y_min y_max], flipud(fliplr(img)));
set(gca,'xdir','reverse')
set(gca,'ydir','normal')
set(gca, 'YAxisLocation','right')
set(hFig, 'Resize','off')
hold on
destX = 25.8;
destY = 21.5;
tolerance = 1;
r = rectangle('Position', [destY-tolerance, destX-tolerance, 2*tolerance, 2*tolerance])
set(r, 'EdgeColor', 'green');

act = quiver(Y, X, Vy, Vx);
act2 = quiver(Y, X, TrY, TrX);
set(act, 'Color', 'red');
set(act2, 'Color', 'blue');
est = quiver(Esty, Estx, Vy, Vx);
est2 = quiver(Esty, Estx, TrY, TrX);
set(est, 'Color', 'red');
set(est2, 'Color', 'blue');
scatter(Y, X);
scatter(Esty, Estx, 'filled');
hold off