#library("edgeR")
#x <- read.delim("/home/wlku/Desktop/ben_stanton_data/run808_KZ870/run808_KZ870_readcount_at_four_combined_peaks_2.txt",row.names="Symbol")


#group <- factor(c(1,1,2,2))
#dge <- DGEList(counts=x,group=group)
#Norm <- calcNormFactors(dge)
#Norm$common.dispersion <-estimateCommonDisp(dge)
#et <- exactTest(Norm)

#topTags(et,n=dim(et)[1])$table->CMP
#cbind(x[row.names(CMP),],CMP)->AL
#write.table(AL,file="/home/wlku/Desktop/ben_stanton_data/run808_KZ870/run808_KZ870_Count_FDR_at_four_combined_peaks_2.xls",sep="\t",quote=FALSE,row.names=TRUE)


library("edgeR")
x <- read.delim("/data/kuw/biocore/wlku/Kairong/run886_KZ1038_wanjun/KZ1038_ILC2_WT_K_gene_readcount.txt",row.names="Symbol")


group <- factor(c(1,1,2,2))
y <- DGEList(counts=x,group=group)
y <- calcNormFactors(y)
y <- estimateCommonDisp(y)
y <- estimateTagwiseDisp(y)
et <- exactTest(y)
topTags(et,n=dim(et)[1])$table->CMP
cbind(x[row.names(CMP),],CMP)->AL

write.table(AL,file="/data/kuw/biocore/wlku/Kairong/run886_KZ1038_wanjun/KZ1038_ILC2_WT_K_gene_Count_FDR_at_gene.xls",sep="\t",quote=FALSE,row.names=TRUE)


