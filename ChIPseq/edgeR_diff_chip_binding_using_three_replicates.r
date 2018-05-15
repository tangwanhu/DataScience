
library("edgeR")
x <- read.delim("/home/kuw/Dropbox/Kairong/run915_KZ1159/run915_KZ1159_edgeR_input_file_2.txt",row.names="Symbol")
#x <- read.delim("/home/kuw/Dropbox/Kairong/run915_KZ1160/run915_KZ1160_KZ1038_edgeR_input_file_2.txt",row.names="Symbol")


group <- factor(c(1,1,2,2))
y <- DGEList(counts=x,group=group)
y <- calcNormFactors(y)
y <- estimateCommonDisp(y)
y <- estimateTagwiseDisp(y)
et <- exactTest(y)
topTags(et,n=dim(et)[1])$table->CMP
cbind(x[row.names(CMP),],CMP)->AL

write.table(AL,file="/home/kuw/Dropbox/Kairong/run915_KZ1159/run915_KZ1159_WT_K_gene_Count_FDR_at_gene_2.xls",sep="\t",quote=FALSE,row.names=TRUE)
#write.table(AL,file="/home/kuw/Dropbox/Kairong/run915_KZ1160/run915_KZ1160_KZ1038_WT_K_gene_Count_FDR_at_gene_2.xls",sep="\t",quote=FALSE,row.names=TRUE)



