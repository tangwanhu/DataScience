# usage: Rscript run_edgeR.R in_file out_file
library(edgeR)
library(limma)
args = commandArgs(TRUE);
raw.data <- read.delim(args[1])
d <- raw.data[, 2:5]# with replicates
rownames(d) <- raw.data[, 1]
group <- c(rep("WT", 2), rep("KD", 2))#with replicates
d <- DGEList(counts = d, group = group)
cpm.d <- cpm(d)
d <- d[ rowSums(cpm.d > 1) >=2, ]#at least two with RPKM > 3, with replicates
d <- calcNormFactors(d)
getPriorN(d)
system.time(d <- estimateTagwiseDisp(d, prop.used=0.5, grid.length = 500))
de.tgw <- exactTest(d)
write.table(topTags(de.tgw, n = length(d$counts[,1]))$table, args[2])
