%path1 = '/home/wlku/Desktop/Kairong/zhangyi_data/';
%path2 = '/home/wlku/Desktop/Kairong/';
%path3 = '/v/bisb1a/kuw/wlku/Kairong/zhangyi_data/';
%path1 = '/data/kuw/biocore/wlku/Keji/run861_KZ1007/';
%path2 =  '/data/kuw/biocore/wlku/Keji/';
%path3 =  '/data/kuw/biocore/wlku/Keji/run861_KZ1007/';

%path1 = '/data/kuw/biocore/wlku/Keji/run858_KZ980/';
%path2 =  '/data/kuw/biocore/wlku/Keji/';
%path3 =  '/data/kuw/biocore/wlku/Keji/run858_KZ980/';
%path1 = '/data/kuw/biocore/wlku/Keji/run864_KZ1008/';
%path2 =  '/data/kuw/biocore/wlku/Keji/';
%path3 =  '/data/kuw/biocore/wlku/Keji/run864_KZ1008/';
%path1 = '/data/kuw/biocore/wlku/Keji/run865_KZ1009/';
%path2 =  '/data/kuw/biocore/wlku/Keji/';
%path3 =  '/data/kuw/biocore/wlku/Keji/run865_KZ1009/';
%path1 = '/data/kuw/biocore/wlku/Keji/run883_KZ1047/';
%path2 =  '/data/kuw/biocore/wlku/Keji/';
%path3 =  '/data/kuw/biocore/wlku/Keji/run883_KZ1047/';

%path1 = '/data/kuw/biocore/wlku/Keji/run865_KZ1012/';
%path2 = '/data/kuw/biocore/wlku/Keji/';
%path3 = '/data/kuw/biocore/wlku/Keji/run865_KZ1012/';

%path1 = '/data/kuw/biocore/wlku/dingyi/run877_KZ1030_KZ1031/';
%path2 = '/data/kuw/biocore/wlku/dingyi/';
%path3 = '/data/kuw/biocore/wlku/dingyi/run877_KZ1030_KZ1031/';

%path1 = '/data/kuw/biocore/wlku/single_dnase/run705_KZ606_KZ607/';
%path2 = '/data/kuw/biocore/wlku/single_dnase/';
%path3 = '/data/kuw/biocore/wlku/single_dnase/run705_KZ606_KZ607/';

%path1 = '/data/kuw/biocore/wlku/Keji/run888_KZ1055/';
%path2 = '/data/kuw/biocore/wlku/Keji/';
%path3 = '/data/kuw/biocore/wlku/Keji/run888_KZ1055/';

%path1 = '/data/kuw/biocore/wlku/Keji/run895_KZ1074/';
%path2 = '/data/kuw/biocore/wlku/Keji/';
%path3 = '/data/kuw/biocore/wlku/Keji/run895_KZ1074/';

path1 = '/data/kuw/biocore/wlku/Keji/run904_KZ1124/data/';
path2 = '/data/kuw/biocore/wlku/Keji/';
path3 = '/data/kuw/biocore/wlku/Keji/run904_KZ1124/data/';

fileend = '_with_chippos.bed';
fileend2 = '_with_chippos_quantify_chromo.bed';
fileend3 = '_with_chippos_sort.txt';

listing = dir(strcat(char(path1), '*100.bed'));
msize = max(size(listing));
filename = cell([msize, 1]);

for i = 1:msize
    filename(i) = cellstr(listing(i).name);
end;

fp = fopen(strcat(char(path2), 'script_sort'), 'w');


for i = 1:msize
    fprintf(fp, '%s ', 'sort');
    fprintf(fp, '%s ', '-k2,2');
    fprintf(fp, '%s', '-k5g,5');
    c = strsplit(char(filename(i)),'.bed');
    fprintf(fp, '%s', strcat('<', char(path3), char(c(1)), char(fileend2), '>'));
    fprintf(fp, '%s', strcat(char(path3), char(c(1)), char(fileend3)));
    fprintf(fp,'\n');
    fprintf(fp,'\n');
end;
fclose(fp);
