# usage: Rscript matrix_minus.R matrix_1 out_file
args = commandArgs(TRUE);
a <- read.table(args[1])
a_ave<-sum(a)/length(a[1,])/length(a[,1])
c <-(a-a_ave)
write.table(c, args[2], sep='\t')

