
%dir ='brg_ko_ring1b_chip/'; %run808_KZ870/
%dir ='run798_KZ850/'; %run808_KZ870/
%dir ='a53_ko_ring1b_chip/'; %run808_KZ870/
dir = '/data/kuw/biocore/wlku/dingyi/run872_KZ1019/';


ga_a = {'GA8901'}; % GA77548
ga_b = {'GA8902'}; % GA77549
ga_c = {'GA8903'}; % GA77550
ga_d = {'GA8904'}; % GA77551


%GA7844_readcount_per_G784E_peaks.txt
%GA7845_readcount_per_K785R_peaks.txt
%GA7846_readcount_per_Y860H_peaks.txt
%GA7847_readcount_per_E861K_peaks.txt
%GA7848_readcount_per_E882K_peaks.txt
%GA7849_readcount_per_R885H_peaks.txt


%file_name2 ='sicer'; % run808_KZ870
%file_name2 ='a53_ko_ring1b_chip'; % run808_KZ870
file_name2 ='R885H'; % run808_KZ870

fn = strcat(char(file_name2),'_readcount_at_four_combined_peaks_2.txt');

for iga = 1:1
    for igb = 1:1
        
        clear filen_name chr1 peak_ss1 peak_es1 tag_num1 new_name1;
        clear chr2 peak_ss2 peak_es2 tag_num2 new_name2;

        file_name ={char(ga_a(iga)), char(ga_b(iga)), char(ga_c(iga)), char(ga_d(iga))};
        
        %file_name2 ='brg_ko_ring1b_chip'; % run808_KZ870
        
        %read file1
        m = 0;
        %file1 = '/home/wlku/Desktop/ben_stanton_data/run804_KZ862/GA7726_readcount_per_7822_7726_peaks.txt';
        %file2 = '/home/wlku/Desktop/ben_stanton_data/run804_KZ862/GA7822_readcount_per_7822_7726_peaks.txt';
        %file1 = '/home/wlku/Desktop/ben_stanton_data/run804_KZ862/GA7822_readcount_per_7822_7746_peaks.txt';
        %file2 = '/home/wlku/Desktop/ben_stanton_data/run804_KZ862/GA7746_readcount_per_7822_7746_peaks.txt';

        %file1 = strcat('/home/wlku/Desktop/ben_stanton_data/brg_ko_ring1b_chip/',char(ga_b(igb)),'_readcount_per_',char(ga_b(igb)),'_',char(ga_a(iga)),'_peaks_2.txt');
        %file2 = strcat('/home/wlku/Desktop/ben_stanton_data/brg_ko_ring1b_chip/',char(ga_a(iga)),'_readcount_per_',char(ga_b(igb)),'_',char(ga_a(iga)),'_peaks_2.txt');

        %file1 = strcat('/home/wlku/Desktop/ben_stanton_data/brg_ko_ring1b_chip/',char(ga_b(igb)),'_readcount_per_',char(ga_b(igb)),'_',char(ga_a(iga)),'_peaks_2b.txt');
        %file2 = strcat('/home/wlku/Desktop/ben_stanton_data/brg_ko_ring1b_chip/',char(ga_a(iga)),'_readcount_per_',char(ga_b(igb)),'_',char(ga_a(iga)),'_peaks_2b.txt');
        
        %file1 = strcat('/home/wlku/Desktop/ben_stanton_data/', char(dir), char(ga_a(iga)),'_readcount_per_',char(file_name2),'_peaks_2.txt');
        %file2 = strcat('/home/wlku/Desktop/ben_stanton_data/', char(dir), char(ga_b(iga)),'_readcount_per_',char(file_name2),'_peaks_2.txt');
        %file3 = strcat('/home/wlku/Desktop/ben_stanton_data/', char(dir), char(ga_c(iga)),'_readcount_per_',char(file_name2),'_peaks_2.txt');
        %file4 = strcat('/home/wlku/Desktop/ben_stanton_data/', char(dir), char(ga_d(iga)),'_readcount_per_',char(file_name2),'_peaks_2.txt');
        
        file1 = strcat('/home/wlku/Desktop/ben_stanton_data/', char(dir), char(ga_a(iga)),'_readcount_per_',char(file_name2),'_peaks.txt');
        file2 = strcat('/home/wlku/Desktop/ben_stanton_data/', char(dir), char(ga_b(iga)),'_readcount_per_',char(file_name2),'_peaks.txt');
        file3 = strcat('/home/wlku/Desktop/ben_stanton_data/', char(dir), char(ga_c(iga)),'_readcount_per_',char(file_name2),'_peaks.txt');
        file4 = strcat('/home/wlku/Desktop/ben_stanton_data/', char(dir), char(ga_d(iga)),'_readcount_per_',char(file_name2),'_peaks.txt');
        
        
        display(file1);
        display(file2);
        
        ft = fopen(file1,'r');
        tic
        while~feof(ft)
            a = fscanf(ft, '%s', 5);
            m  = m +1;
            toc
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
        %===================================================================       
        % read file 3
        %======================================================================
         m = 0;
        ft = fopen(file3,'r');
        while~feof(ft)
            a = fscanf(ft, '%s', 5);
            m  = m +1;
        end;
        fclose(ft);
        m = m-1;

        chr3 = cell([m ,1]);
        peak_ss3 = zeros(m, 1);
        peak_es3= zeros(m, 1);
        tag_num3 = zeros(m, 1);

        ft = fopen(file3,'r');
        tic
        for i = 1:m
            a = fscanf(ft, '%s', 1);
            chr3(i) = cellstr(a);
            a = fscanf(ft, '%d', 1);
            peak_ss3(i) = fscanf(ft, '%d', 1);
            peak_es3(i) = fscanf(ft, '%d', 1);
            tag_num3(i) = fscanf(ft, '%d', 1);
            toc
        end;
        fclose(ft);
         %===================================================================       
        % read file 4
        %======================================================================
         m = 0;
        ft = fopen(file4,'r');
        while~feof(ft)
            a = fscanf(ft, '%s', 5);
            m  = m +1;
        end;
        fclose(ft);
        m = m-1;

        chr3 = cell([m ,1]);
        peak_ss4 = zeros(m, 1);
        peak_es4 = zeros(m, 1);
        tag_num4 = zeros(m, 1);

        ft = fopen(file4,'r');
        tic
        for i = 1:m
            a = fscanf(ft, '%s', 1);
            chr4(i) = cellstr(a);
            a = fscanf(ft, '%d', 1);
            peak_ss4(i) = fscanf(ft, '%d', 1);
            peak_es4(i) = fscanf(ft, '%d', 1);
            tag_num4(i) = fscanf(ft, '%d', 1);
            toc
        end;
        fclose(ft);
        
        
        %=================================================================
        %
        %=================================================================
        
        
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
        %fn = strcat(char(file_name(1)),'_', char(file_name(2)),'_readcount_at_two_combined_peaks_2.txt');
        %fn = strcat(char(file_name(1)),'_', char(file_name(2)),'_readcount_at_two_combined_peaks_2b.txt');
        %fn = strcat(char(file_name(1)),'_', char(file_name(2)),'_readcount_at_two_combined_peaks_2.txt');
        %fn = strcat(char(file_name2),'_readcount_at_four_combined_peaks_2.txt');
        clear chr1 chr2 chr3 chr4 peak_ss1 peak_ss2 peak_ss3 peak_ss4 peak_es1 peak_es2 peak_es3 peak_es4;
        [a, b]= unique(new_name1);
        
        totalfile = strcat('/home/wlku/Desktop/ben_stanton_data/',char(dir), fn);
        fp= fopen(totalfile, 'w');
        fprintf(fp, '%s\t %s\t %s\t %s\t %s\n', 'Symbol', char(file_name(1)), char(file_name(2)), char(file_name(3)), char(file_name(4)));
        tic
        for j = 1:max(size(a))
            fprintf(fp, '%s\t %d\t %d\t %d\t %d\n', char(new_name1(b(j))), tag_num1(b(j)), tag_num2(b(j)), tag_num3(b(j)), tag_num4(b(j)));
            toc
        end;
        fclose(fp);    
    end;
end;

clear;


