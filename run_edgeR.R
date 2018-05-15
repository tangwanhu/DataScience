# usage: Rscript run_edgeR.R in_file out_file
library(edgeR)
library(limma)
args = commandArgs(TRUE);
raw.data <- read.delim(args[1])
d <- raw.data[, 2:5]# with replicates
#d <- raw.data[, c(2,3)]#without replicate
rownames(d) <- raw.data[, 1]
group <- c(rep("WT", 2), rep("TRT", 2))#with replicates
#group <- c("WT","TRT")#without replicate
d <- DGEList(counts = d, group = group)
cpm.d <- cpm(d)
d <- d[ rowSums(cpm.d > 1) >=2, ]#at least two with RPKM > 3, with replicates
#d <- d[ rowSums(cpm.d > 1) >=1, ]#at least 1 with RPKM > 3, without replicate
d <- calcNormFactors(d)
getPriorN(d)
system.time(d <- estimateTagwiseDisp(d, prop.used=0.5, grid.length = 500))
de.tgw <- exactTest(d)
write.table(topTags(de.tgw, n = 60000)$table, args[2])
