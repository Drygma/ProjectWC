f_nodes = 'nodes.txt';  % parameter 'output_nodes' and f_nodes should point to the same file
f_path = 'path.txt';    % parameter 'output_path' and f_path should point to the same file
delimiterIn = ' ';
headerlinesIn = 1;
A = importdata(f_nodes,delimiterIn,headerlinesIn);
B = importdata(f_path,delimiterIn,headerlinesIn);

network_size = A.data(2, 2);
n_inputs = A.data(2,1);


input_color = [255,0,0]/255;
node_color = [0,0,255]/255;
line_color = [0, 255, 0]/255;
hold on;

my_vertices = [
    0 0 0;
    0 A.data(1,2) 0;
    A.data(1,1) A.data(1,2) 0;
    A.data(1,1) 0 0;
    0 0 A.data(1,3);
    0 A.data(1,2) A.data(1,3);
    A.data(1,1) A.data(1,2) A.data(1,3);
    A.data(1,1) 0 A.data(1,3)
    ];
my_faces = [1 2 3 4; 2 6 7 3; 4 3 7 8; 1 5 8 4; 1 2 6 5; 5 6 7 8];
patch('Vertices', my_vertices, 'Faces', my_faces, 'FaceColor', 'w');
hold off;
alpha(.3);
hold on;
for k = 3:1:n_inputs+2
   x = A.data(k, 1);
   y = A.data(k, 2);
   z = A.data(k, 3);
   plot3(x, y, z, '--bo', 'Color', input_color);
   disp('.');
end

for k = n_inputs+3:1:3+network_size-1
   x = A.data(k, 1);
   y = A.data(k, 2);
   z = A.data(k, 3);
   plot3(x, y, z, '--bo', 'Color', node_color);
   disp('.');
end

num_el = numel(B.data)/2;
for k = 1:1:num_el
   index1 = 3 + B.data(k, 1);
   index2 = 3 + B.data(k, 2);
   P1 = [A.data(index1,1),A.data(index1,2),A.data(index1,3)];
   disp(P1);
   P2 = [A.data(index2,1),A.data(index2,2),A.data(index2,3)];
   disp(P2);
   pts = [P1; P2];
   plot3(pts(:,1), pts(:,2), pts(:,3), 'Color', line_color);
end