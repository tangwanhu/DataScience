#include<iostream>
#include<fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>
#include <math.h>
#include <string>

using namespace std;

int main(int argc, char* args[]) {
        if( argc != 4){
                cout<<"USAGE: ./haha \t pathname \t input file\t outfile\n";
                return 0;
        }

	string pathname = args[1];
        string filein = args[2];
        string fileout = args[3];

	string inputf;
	string outputf;

	inputf = pathname + filein;
        outputf = pathname + fileout;
	
	time_t rawtime;
	ifstream ft;
	ofstream fp;
	
	int peak_start, peak_end, peak_loc, chromo_index = 0;
	int peak_start_2, peak_end_2, peak_loc_2, chromo_index_2;
	int k = 0;	
	string chromo;
	string chromo_2;	
	size_t result;	
	//Chip-seq location which have been mapped by bowtie2	
	//ft.open("/home/wlku/Desktop/ben_stanton_data/run789/GA7219_macs_peaks_2.txt");
	//ft.open("/home/wlku/Desktop/ben_stanton_data/brg_binding/Brg_J1_chip_peaks_2.txt");
	//ft.open("/home/wlku/Desktop/ben_stanton_data/run792/GA7826_macs_peaks_2.txt");
	//ft.open("/home/wlku/Desktop/chipseq_analysis/run605_KZ355/GA4906_macs_peaks_2_filter_tss.txt");
	//ft.open("/home/wlku/Desktop/ben_stanton_data/stat3_binding/STAT3_chip_peaks_2.txt");
	//ft.open("/home/wlku/Desktop/ben_stanton_data/hg18_enhancer/K562_h3k4me1_hg18_peaks_3.txt");
	//ft.open("/home/wlku/Desktop/ben_stanton_data/run798_KZ850/GA7705_macs_nonunique_peaks_2.txt");
	//ft.open("/home/wlku/Desktop/ben_stanton_data/run798_KZ850_temp/GA7703_macs_with_input_peaks_2.txt");
	//ft.open("/home/wlku/Desktop/ben_stanton_data/run804_KZ862/GA7822_macs_peaks_2.txt");
	ft.open(inputf.c_str());

	//Output file
	//fp.open("/home/wlku/Desktop/ben_stanton_data/run789/GA7219_macs_peaks_with_peak_pos.txt");	
	//fp.open("/home/wlku/Desktop/ben_stanton_data/brg_binding/Brg_J1_chip_peaks_with_peak_pos.txt");
	//fp.open("/home/wlku/Desktop/ben_stanton_data/run792/GA7826_macs_peaks_with_peak_pos.txt");
	//fp.open("/home/wlku/Desktop/chipseq_analysis/run605_KZ355/GA4906_macs_peaks_with_peak_pos_filter_tss.txt");
	//fp.open("/home/wlku/Desktop/ben_stanton_data/stat3_binding/STAT3_chip_peaks_with_peak_pos.txt");
	//fp.open("/home/wlku/Desktop/ben_stanton_data/hg18_enhancer/K562_h3k4me1_hg18_peaks_with_peak_pos.txt");
	//fp.open("/home/wlku/Desktop/ben_stanton_data/run798_KZ850/GA7705_macs_nonunique_peaks_with_peak_pos.txt");
	//fp.open("/home/wlku/Desktop/ben_stanton_data/run798_KZ850_temp/GA7703_macs_with_input_peaks_with_peak_pos.txt");
	//fp.open("/home/wlku/Desktop/ben_stanton_data/run804_KZ862/GA7822_macs_peaks_with_peak_pos.txt");
	fp.open(outputf.c_str());

   //GA7545_macs_peaks.xls
   //GA7726_macs_peaks.xls
   //GA7738_macs_peaks.xls
   //GA7739_macs_peaks.xls
   //GA7744_macs_peaks.xls
   //GA7745_macs_peaks.xls
   //GA7746_macs_peaks.xls
   //GA7747_macs_peaks.xls
   //GA7748_macs_peaks.xls
   //GA7749_macs_peaks.xls
   //GA7750_macs_peaks.xls
   //GA7822_macs_peaks.xls
		
	while (!ft.eof())
	{	
		if (k==0)
		{		
			ft>>chromo>>peak_start>>peak_end;
			ft>>chromo_2>>peak_start_2>>peak_end_2;
		}					
		else if(k>0)
		{
			ft>>chromo_2>>peak_start_2>>peak_end_2;
		}

		if(peak_start>peak_end)
		{
			peak_loc = peak_start + floor((double)(peak_end-peak_start)/2.0);
		}
		else if (peak_end>peak_start)
		{
			peak_loc = peak_end + floor((double)(peak_start-peak_end)/2.0);
		}
		
		if(chromo.compare(chromo_2)==0)
		{
			fp<<chromo<<"\t"<<chromo_index<<"\t"<<peak_start<<"\t"<<peak_end<<"\t"<<peak_loc<<endl;					
			chromo = chromo_2;
			peak_start = peak_start_2;
			peak_end = peak_end_2;			
		}
		else
		{
			fp<<chromo<<"\t"<<chromo_index<<"\t"<<peak_start<<"\t"<<peak_end<<"\t"<<peak_loc<<endl;	
			chromo = chromo_2;
			peak_start = peak_start_2;
			peak_end = peak_end_2;			
			chromo_index = chromo_index + 1;
		}
		
			
		k = k + 1;
	}
	fp<<chromo_2<<"\t"<<chromo_index<<"\t"<<peak_start_2<<"\t"<<peak_end_2<<"\t"<<peak_loc<<endl;	
	ft.close();
	fp.close();
}	
	
