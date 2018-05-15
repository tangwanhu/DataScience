file_name ={'GA7822', 'GA7746'};
%file_name ={'GA7726', 'GA7822'};

%read file1
m = 0;
%file1 = '/home/wlku/Desktop/ben_stanton_data/run804_KZ862/GA7726_readcount_per_7822_7726_peaks.txt';
%file2 = '/home/wlku/Desktop/ben_stanton_data/run804_KZ862/GA7822_readcount_per_7822_7726_peaks.txt';
%file1 = '/home/wlku/Desktop/ben_stanton_data/run804_KZ862/GA7822_readcount_per_7822_7746_peaks.txt';
%file2 = '/home/wlku/Desktop/ben_stanton_data/run804_KZ862/GA7746_readcount_per_7822_7746_peaks.txt';
file1 = '/home/wlku/Desktop/ben_stanton_data/run804_KZ862/GA7822_readcount_per_7822_7746_peaks_2.txt';
file2 = '/home/wlku/Desktop/ben_stanton_data/run804_KZ862/GA7746_readcount_per_7822_7746_peaks_2.txt';


ft = fopen(file1,'r');
while~feof(ft)
    a = fscanf(ft, '%s', 5);
    m  = m +1;
end;
fclose(ft);
m = m-1;

chr1 = cell([m ,1]);
peak_ss1 = zeros(m, 1);
peak_es1 = zeros(m, 1);
tag_num1 = zeros(m, 1);

ft = fopen(file1,'r');
tic
for i = 1:m
    a = fscanf(ft, '%s', 1);
    chr1(i) = cellstr(a);
    a = fscanf(ft, '%d', 1);
    peak_ss1(i) = fscanf(ft, '%d', 1);
    peak_es1(i) = fscanf(ft, '%d', 1);
    tag_num1(i) = fscanf(ft, '%d', 1);
    toc
end;
fclose(ft);
%==========================================================================
% Read file 2
%==========================================================================
m = 0;
ft = fopen(file2,'r');
while~feof(ft)
    a = fscanf(ft, '%s', 5);
    m  = m +1;
end;
fclose(ft);
m = m-1;

chr2 = cell([m ,1]);
peak_ss2 = zeros(m, 1);
peak_es2 = zeros(m, 1);
tag_num2 = zeros(m, 1);

ft = fopen(file2,'r');
tic
for i = 1:m
    a = fscanf(ft, '%s', 1);
    chr2(i) = cellstr(a);
    a = fscanf(ft, '%d', 1);
    peak_ss2(i) = fscanf(ft, '%d', 1);
    peak_es2(i) = fscanf(ft, '%d', 1);
    tag_num2(i) = fscanf(ft, '%d', 1);
    toc
end;
fclose(ft);
%======================================================================
%
%======================================================================
m1 = max(size(chr1));
m2 = max(size(chr2));

new_name1 = cell([m1 ,1]);
new_name2 = cell([m2 ,1]);
for i =1:m1
    new_name1(i) = cellstr(strcat(char(chr1(i)), '_', num2str(peak_ss1(i)), '_', num2str(peak_es1(i))));
end;
for i =1:m2
    new_name2(i) = cellstr(strcat(char(chr2(i)), '_', num2str(peak_ss2(i)), '_', num2str(peak_es2(i))));
end;



%fn = strcat(char(file_name(1)),'_', char(file_name(2)),'_readcount_at_two_combined_peaks.txt');
fn = strcat(char(file_name(1)),'_', char(file_name(2)),'_readcount_at_two_combined_peaks_2.txt');
totalfile = strcat('/home/wlku/Desktop/ben_stanton_data/run804_KZ862/', fn);
fp= fopen(totalfile, 'w');
fprintf(fp, '%s\t %s\t %s\n', 'Symbol', char(file_name(1)), char(file_name(2)));
for j = 1:m1-1
    fprintf(fp, '%s\t %d\t %d\n', char(new_name1(j)), tag_num1(j), tag_num2(j));
end;
fclose(fp);


