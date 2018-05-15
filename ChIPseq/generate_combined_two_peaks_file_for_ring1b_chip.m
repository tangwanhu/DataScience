% testing
%fp = fopen('/home/wlku/Desktop/ben_stanton_data/run804_KZ862/GA7822_GA7726_macs_peaks_combined_peaks_sorted_combined.txt', 'r')
%m = 0;
%while~feof(fp)
%	a = fscanf(fp, '%s', 5);
%	m = m + 1;
%end;
%fclose(fp);
%m = m - 1;

%chr = cell([m, 1]);
%chr_index = zeros(m,1);
%peak_ss = zeros(m, 1);
%peak_es = zeros(m, 1);
%peak_pos = zeros(m, 1);
%fp = fopen('/home/wlku/Desktop/ben_stanton_data/run804_KZ862/GA7822_GA7726_macs_peaks_combined_peaks_sorted_combined.txt', 'r');
%tic
%for i = 1:m
%%while ~feof(fp)
%    a = fscanf(fp, '%s', 1);
%    b = fscanf(fp, '%d', 1);
%    c = fscanf(fp, '%d', 1);
%    d = fscanf(fp, '%d', 1);
%    e = fscanf(fp, '%d', 1);
%    chr(i) = cellstr(a);
%    chr_index(i) = b;
%    peak_ss(i) = c;
%    peak_es(i) = d;
%    peak_pos(i) = e;
%    toc
%end;
%fclose(fp);

%=========================================================================
%=========================================================================

%fp = fopen('/home/wlku/Desktop/ben_stanton_data/run804_KZ862/GA7822_GA7726_macs_peaks_combined_peaks_sorted.txt','r');
fp = fopen('/home/wlku/Desktop/ben_stanton_data/run804_KZ862/GA7746_GA7822_macs_peaks_combined_peaks_sorted.txt','r');

m = 0;
while~feof(fp)
	a = fscanf(fp, '%s', 5);
	m = m + 1;
end;
fclose(fp);
m = m - 1;

chr = cell([m, 1]);
chr_index = zeros(m,1);
peak_ss = zeros(m, 1);
peak_es = zeros(m, 1);
peak_pos = zeros(m, 1);

%fp = fopen('/home/wlku/Desktop/ben_stanton_data/run798_KZ850/J1_chip_rybp_macs_combined_peaks_sorted.txt','r');
%fp = fopen('/home/wlku/Desktop/ben_stanton_data/run804_KZ862/Ring1b_chip_macs_peaks_combined_peaks_sorted.txt','r');
%fp = fopen('/home/wlku/Desktop/ben_stanton_data/run798_KZ850_temp/J1_chip_rybp_macs_peaks_with_input_combined_peaks_sorted.txt','r');

%fp = fopen('/home/wlku/Desktop/ben_stanton_data/run804_KZ862/GA7822_GA7726_macs_peaks_combined_peaks_sorted.txt','r');
fp = fopen('/home/wlku/Desktop/ben_stanton_data/run804_KZ862/GA7746_GA7822_macs_peaks_combined_peaks_sorted.txt','r');
tic
for i = 1:m
%while ~feof(fp)
    a = fscanf(fp, '%s', 1);
    b = fscanf(fp, '%d', 1);
    c = fscanf(fp, '%d', 1);
    d = fscanf(fp, '%d', 1);
    e = fscanf(fp, '%d', 1);
    chr(i) = cellstr(a);
    chr_index(i) = b;
    peak_ss(i) = c;
    peak_es(i) = d;
    peak_pos(i) = e;
    toc
end;
fclose(fp);

clus = zeros(1, max(size(chr)));
m = 0;
tic
for i = 1: max(size(chr))-1 
    clus(i) = m;
    if(chr_index(i)==chr_index(i+1))
        if(peak_ss(i+1)-peak_es(i)>200)
            m = m + 1;
        end;
    else
        m = m + 1;
    end;
    toc
end;
if (peak_ss(max(size(chr)))- peak_es(max(size(chr))-1)>200)
    m = m + 1;
end;

clus(max(size(chr))) = m;

uni_clus = unique(clus);
%ft = fopen('/home/wlku/Desktop/ben_stanton_data/run798_KZ850_temp/J1_chip_rybp_macs_peaks_with_input_combined_peaks_sorted_combined.txt','w');
%ft = fopen('/home/wlku/Desktop/ben_stanton_data/run804_KZ862/Ring1b_chip_macs_peaks_combined_peaks_sorted_combined.txt','w');

%ft = fopen('/home/wlku/Desktop/ben_stanton_data/run804_KZ862/GA7822_GA7726_macs_peaks_combined_peaks_sorted_combined.txt','w');
ft = fopen('/home/wlku/Desktop/ben_stanton_data/run804_KZ862/GA7746_GA7822_macs_peaks_combined_peaks_sorted_combined_200.txt','w');

for i = 1:max(size(uni_clus))
    q = find(clus== uni_clus(i));
    q_min = min(q);
    q_max = max(q);
    fprintf(ft,'%s\t %d\t %d\t %d\t %d\n', char(chr(q_min)), chr_index(q_min), peak_ss(q_min), peak_es(q_max), floor((peak_ss(q_min)+peak_es(q_max))/2));
    
end; 
fclose(ft);
