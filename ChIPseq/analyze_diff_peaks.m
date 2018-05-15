
fp = fopen('/data/kuw/biocore/wlku/dingyi/run872_KZ1019/H2AZ_GA8905_GA8908_Count_FDR_at_four_combined_peaks.xls', 'r');
%fp = fopen('/home/wlku/Desktop/ben_stanton_data/run804_KZ862/GA7746_GA7822_Count_FDR.xls', 'r');

a = fscanf(fp, '%s', 8);
m = 0;
while~feof(fp)
    a = fscanf(fp, '%s', 9);
    m = m + 1;
end;
m  = m -1;
fclose(fp);

peak_name1 = cell([m, 1]);
fc1 = zeros(m, 1);
fdr1 = zeros(m ,1);

fp = fopen('/data/kuw/biocore/wlku/dingyi/run872_KZ1019/H2AZ_GA8905_GA8908_Count_FDR_at_four_combined_peaks.xls', 'r');
%fp = fopen('/home/wlku/Desktop/ben_stanton_data/run804_KZ862/GA7746_GA7822_Count_FDR.xls', 'r');

a = fscanf(fp, '%s', 8);
for i= 1:m
    a = fscanf(fp, '%s', 1);
    peak_name1(i) = cellstr(a);
    a = fscanf(fp, '%d', 4);
    fc1(i) = fscanf(fp, '%f', 1);
    a = fscanf(fp, '%f', 2);
    fdr1(i) = fscanf(fp, '%f', 1);
end;
fclose(fp);

q = find(fdr1<0.1 & fc1>0.58);
fp = fopen('/data/kuw/biocore/wlku/dingyi/run872_KZ1019/GA8905_GA8908_fdr_01_fc_15_increased_peaks.txt','w');

for i = 1: max(size(q))
    a = strsplit(char(peak_name1(q(i))),'_');
    fprintf(fp, '%s\t %d\t %d\n', char(a(1)), str2num(char(a(2))), str2num(char(a(3)))); 
end;    
fclose(fp);