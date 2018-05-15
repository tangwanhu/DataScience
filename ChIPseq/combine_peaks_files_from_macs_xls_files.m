uni_chr={'chr1','chr10','chr11','chr12','chr13','chr14','chr15','chr16','chr17','chr18','chr19','chr2','chr3','chr4','chr5','chr6','chr7','chr8','chr9','chrX', 'chrY', 'chr20', 'chr21', 'chr22', 'chr23'};

path1 = '/data/kuw/biocore/wlku/Kairong/zhangyi_data/';
files = {'GA8162_shLuc_H2AZ_mm9_macs_w_input_peaks.xls','GA8163_shLuc_H2AZ_mm9_macs_w_input_peaks.xls','GA8170_shOsr1_H2AZ_mm9_macs_w_input_peaks.xls','GA8171_shOsr1_H2AZ_mm9_macs_w_input_peaks.xls'};
outfile = 'GA8162_GA8163_GA8170_GA8171_macs_w_input_peaks_tag_gt10_peaks_800_1500_with_peak_pos.txt';
ft = fopen(strcat(char(path1), char(outfile)),'w');
tic
for kkk =1:4
    
    fp = fopen(strcat(char(path1), char(files(kkk))),'r');

    for i = 1:24 %20, 24
        a = fgets(fp);
    end;
    m = 0;
    while~feof(fp)
        a = fscanf(fp, '%s', 1);
        b = fscanf(fp, '%d', 1);
        c = fscanf(fp, '%d', 1);
        d1 = fscanf(fp, '%d', 1);
        d2 = fscanf(fp, '%d', 1);
        d3 = fscanf(fp, '%d', 1);
        d4 = fscanf(fp, '%f', 1);
        d5 = fscanf(fp, '%f', 1);
        d6 = fscanf(fp, '%f', 1); %%%%%%%%%%
        m = m + 1;
    end;
    fclose(fp);
    m = m - 1;

    chr = cell([m,1]);
    peak_ss = zeros(m, 1);
    peak_es = zeros(m, 1);
    peak_len = zeros(m, 1);
    peak_summit = zeros(m ,1);
    peak_tag = zeros(m, 1);
    peak_pval = zeros(m, 1);
    peak_fc = zeros(m, 1);
    peak_fdr = zeros(m, 1);

    fp = fopen(strcat(char(path1), char(files(kkk))),'r');
    for i = 1:24 %20, 24
        a = fgets(fp);
    end;
    for i = 1:m
        a = fscanf(fp, '%s', 1);
        chr(i) = cellstr(a);
        peak_ss(i) = fscanf(fp, '%d', 1);
        peak_es(i) = fscanf(fp, '%d', 1);
        peak_len(i) = fscanf(fp, '%d', 1);
        peak_summit(i) = fscanf(fp, '%d', 1);
        peak_tag(i) = fscanf(fp, '%d', 1);
        peak_pval(i) = fscanf(fp, '%f', 1);
        peak_fc(i) = fscanf(fp, '%f', 1);
        peak_fdr(i) = fscanf(fp, '%f', 1);
    end;    
    fclose(fp);
    
    q = find(peak_tag<10 | (peak_len<800 | peak_len>1500));
    chr(q) = [];
    peak_ss(q) = [];
    peak_es(q) = [];
    peak_len(q) = [];
    peak_summit(q) = [];
    peak_tag(q) = [];
    peak_pval(q) = [];
    peak_fc(q) = [];
    peak_fdr(q) = [];
    
    peak_sumpos = peak_ss + peak_summit;
    
    for i =1:max(size(chr))
        chr_index = find(strcmp(uni_chr, chr(i))==1);
        fprintf(ft, '%s\t %d\t %d\t %d\t %d\n', char(chr(i)), chr_index-1, peak_ss(i), peak_es(i), peak_summit(i));        
        %fprintf(ft, '%s\t %d\t %d\t %d\t %d\n', char(chr(i)), chr_index-1, peak_sumpos(i)-400, peak_sumpos(i)+400, peak_sumpos(i));        
   
    end;
    toc
end;   

