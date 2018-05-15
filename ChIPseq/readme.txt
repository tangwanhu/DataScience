wes
#mm9
vi /home/wes/jksrc/kent/src/hg/makeDb/trackDb/mouse/mm9/trackDb.ra

cd /home/wes/jksrc/kent/src/hg/makeDb/trackDb/
make alpha DBS='mm9'
cd /data/goldenPath/mm9/customtracks/WKu

stranz
scp *.graph wes@165.112.111.61:/data/goldenPath/mm9/customtracks/WKu
vi script
./script

pwd:kzlab!123


mysql -u root -p
use mm9
select * from grp;
insert into grp values ('CHiT','Chi Tian',2.000,0);
#delete from grp WHERE name='Kinases';
#replace into grp values ('Kinases','Kinases',1.0021);
exit

#hg18
mkdir /data/goldenPath/hg18/customtracks/KuW
vi /home/wes/jksrc/kent/src/hg/makeDb/trackDb/human/hg18/trackDb.ra

cd /home/wes/jksrc/kent/src/hg/makeDb/trackDb/
make alpha DBS='hg18'
cd /data/goldenPath/hg18/customtracks/KuW

========================================================================
1) Compute rpkm and count for rna-seq
========================================================================

a) (/home/wlku/Desktop/rnaseq_analysis) (an example:)  python rpkmforgenes.py -i ./rna_dnase/GA8476-EL4-Dnase+nrdN_4RD-seq_0_0_mapq10.bed -readcount -a mm9_ucsc_ref_gene.txt -o ./rna_dnase/GA8476_pkm_output.txt -fulltranscript -rmnameoverlap

b) run filter_duplicate_gene.cpp

c) run analyze_log_log_plot_rna_2.m



========================================================================
2) Separate the mixed reads into RNA and Dnase by using primer.
========================================================================

1) run script_extract_reads_with_primer_in_fastq


==============================================================================
3) Distribution of spike in data at TSS (mouse)
==============================================================================

a1) Run /home/wlku/Desktop/kairong/generate_sort_cpp.m(transfer output to biowulf)
a2) Run /data/kuw/biocore/wlku/Keji/sort_cpp (mm9)

b1) Run /home/wlku/Desktop/kairong/generate_quantify_cpp.m(transfer output to biowulf)
b2) Run /data/kuw/biocore/wlku/Keji/quantify_cpp (for both hg18 and mm9)

c1) Run /home/wlku/Desktop/kairong/generate_script_sort.m(transfer output to biowulf)
c2) Run  /data/kuw/biocore/wlku/Keji/script_sort


d1) Run generate_script_chipden_dis_at_tss.m
d2) Run kuw@biocoreserver1.nhlbi.nih.gov:/v/bisb1a/kuw/wlku/kairong/script_chipden_dis_at_tss

e) Run /home/wlku/Desktop/kairong/analyze_chip_den_dis_at_tss.m
