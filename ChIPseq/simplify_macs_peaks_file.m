%fp = fopen('/home/wlku/Desktop/Kairong/Sample_KZ729_GA6901/macs_H3K27ac_no_input_peaks.xls','r');
%ft = fopen('/home/wlku/Desktop/Kairong/Sample_KZ729_GA6901/macs_H3K27ac_no_input_peaks_2.txt', 'w');

path = '/data/kuw/biocore/wlku/Keji/run733/';

%file = dir(strcat(char(path), '*hg18_macs_w_input_peaks*'));
file = dir(strcat(char(path), '*.xls'));


msize = max(size(file));
file_name = cell([max(size(file)), 1]);
for i = 1:msize
    file_name(i) = cellstr(file(i).name);
end;
tic
for j = 1:msize
    k = strsplit(char(file_name(j)), '.xls');
    fp = fopen(strcat(char(path), char(file_name(j))),'r');
    ft = fopen(strcat(char(path), char(k(1)),'_2.txt'), 'w');


    for i = 1:23 %20, 24, 23
        a = fgets(fp);
    end;

    %fprintf(ft, '%s\t %s\t %s\n', 'chr', 'start', 'end'); %(optional)
    m = 0;
    n = 0;
    while~feof(fp)
        a = fscanf(fp, '%s', 1);
        b = fscanf(fp, '%d', 1);
        c = fscanf(fp, '%d', 1);
        d1 = fscanf(fp, '%d', 1);
        d2 = fscanf(fp, '%d', 1);
        d3 = fscanf(fp, '%f', 1);
        d4 = fscanf(fp, '%s', 1);
        d5 = fscanf(fp, '%s', 1);
        d6 = fscanf(fp, '%s', 1); %%%%%%%%%%
        d7 = fscanf(fp, '%s', 1); %%%%%%%%%%
        %if(d4>=80 & d5>=5)
            fprintf(ft, '%s\t %d\t %d\n', a, b, c);
            n = n + 1;
        %end;
        m = m + 1;
    end;
    fclose(fp);
    fclose(ft);
    toc
end;   