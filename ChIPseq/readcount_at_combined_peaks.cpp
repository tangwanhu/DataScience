#include<iostream>
#include<fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <ctime>
#include <math.h>
#include <string>
#include <algorithm>

using namespace std;

int main(int argc, char* args[]) {
        if( argc != 6){
                cout<<"USAGE: ./haha \t pathname \t input file\t outfile\n";
                return 0;
        }

	string pathname = args[1];
        string filein = args[2];
        string fileout = args[3];
	string filein2 = args[4];
 	int shifting = atoi(args[5]);

	string inputf;
	string inputf2;
	string outputf;

	inputf = pathname + filein;
        outputf = pathname + fileout;
	inputf2 = pathname + filein2;

	time_t rawtime;
	ifstream fp;
	ifstream ft;
 	ofstream fout;
		
	vector<int> read_count, enpos_v, enss_v, enes_v;
	vector<string> enchromo_v;	
	int enpos_size;
	int test = 0, go_ss = 0;
	int en_ss, en_es, en_pos, en_sa, en_sb, en_num, a, i, j, n = 0, k = 0, kk = 0, testtest = 0;
	int en_cindex;
	int en_min, en_max;
	int ff1, ff2, ff3; 
	double gene_length, total_gene = 0.0;	
	
	double total_read, peak_num_en = 0.0;
	double tag_den;
	int ik;	

	int ss_chip, es_chip, ss_chip_2, es_chip_2;
	int macpeak_pos, macpeak_pos_2, cindex, cindex_2;		
	int chipseq_pos, chipseq_pos_2, s2, s2_2;
	string strand_chip, strand_chip_2;
	string chromo, chromo_chip, chromo_chip_2;
	string en_chromo;
	string s1, s1_2;
	string path1, inputfile, inputall, outputfile;
	string infilename;
	//string fname1[] = {"GA7744", "GA7745", "GA7738", "GA7739", "GA7746", "GA7747", "GA7748", "GA7749", "GA7750", "GA7545"};
	//string fname1[] = {"GA7547"};
	string fname1[] = {"GA7727"};
	//string fname2[] = {"GA7822", "GA7726"};
	//string fname2[] = {"GA7546"};
	string fname2[] = {"GA7726"}; 
	size_t result;
	

	//path1 = "/home/wlku/chipseq_analysis/maplot/maplot_enhancer/";
	//path1 = "/home/wlku/ben_stanton_data/run789/";
	//path1 = "/home/wlku/ben_stanton_data/run792/";
	//path1 = "/home/wlku/ben_stanton_data/brg_binding/";	
	//path1 = "/v/bisb1a/kuw/wlku/ben_stanton_data/run798_KZ850_temp/";
	//ff1 = 0; //0-9 string fname1
	//ff2 = 0; //0,1 string fanme2
	//ff3 = 1; // 0, 1 compute tag_den for 2 files
	//path1 = "/v/bisb1a/kuw/wlku/ben_stanton_data/run804_KZ862/";
	//path1 = "/v/bisb1a/kuw/wlku/ben_stanton_data/brg_ko_ring1b_chip/";
	
	//infilename = path1 + fname1[ff1]+string("_")+fname2[ff2]+string("_macs_peaks_combined_peaks_sorted_combined_0b.txt");
	//infilename = path1 + fname1[ff1]+string("_")+fname2[ff2]+string("_macs_peaks_combined_peaks_sorted_combined_0b_b.txt");

	//if(ff3==0)
	//{
	//	//outputfile = path1 + fname2[ff2]+string("_readcount_per_")+fname2[ff2]+string("_")+fname1[ff1]+string("_peaks_2.txt");
	//	outputfile = path1 + fname2[ff2]+string("_readcount_per_")+fname2[ff2]+string("_")+fname1[ff1]+string("_peaks_2b.txt");
	//}
	//else if(ff3 ==1)
	//{
		//outputfile = path1+fname1[ff1]+string("_readcount_per_")+fname2[ff2]+string("_")+fname1[ff1]+string("_peaks_2.txt");
	//	outputfile = path1+fname1[ff1]+string("_readcount_per_")+fname2[ff2]+string("_")+fname1[ff1]+string("_peaks_2b.txt");
	//}
	//outputfile = "/v/bisb1a/kuw/wlku/ben_stanton_data/run804_KZ862/GA7822_readcount_per_7726_7545_peaks_2.txt";
	//outputfile = "/v/bisb1a/kuw/wlku/ben_stanton_data/run804_KZ862/GA7746_readcount_per_7726_7545_peaks_2.txt";



	//if(ff2==0 && ff3 ==0)
	//{
	//	//inputfile = "GA7822_mouse_Brg_EtOH_Ring1b_0_0_mapq10_noDup_with_chippos_sort.txt";
	//	inputfile = "GA7726_Brg_EtOH_Ring1b_mm9_0_0_mapq10_noDup_with_chippos_sort.txt";
	//	//inputfile = "GA7546_ACAGTG_ChIP-seq_mouse_Brg_ethanol_Ring1b_rep2_0_0_mapq10_noDup_with_chippos_sort.txt";

	//}

	//cout<<endl;
	//cout<<fname1[ff1]<<"\t"<<fname2[ff2]<<endl;
	//cout<<endl;
	cout<<inputf2<<endl;
	cout<<endl;
	cout<<inputf<<endl;
	cout<<endl;
	cout<<outputf<<endl;
	cout<<endl;

	//inputall = path1 + inputfile;
	ft.open(inputf.c_str());

	ik = 0;
	total_read = 0.0;
	while(!ft.eof())
	{
		total_read = total_read + 1.0;
		ft>>chromo_chip>>cindex>>ss_chip>>es_chip>>chipseq_pos>>s1>>s2>>strand_chip;
	}
	ft.close();
	cout<<"total_read is equal to\t"<< total_read<<endl;

	ft.open(inputf.c_str());

	while(!ft.eof())	
	{	
		ik = ik + 1;
		if(kk==0)
		{
			ft>>chromo_chip>>cindex>>ss_chip>>es_chip>>chipseq_pos>>s1>>s2>>strand_chip;
			ft>>chromo_chip_2>>cindex_2>>ss_chip_2>>es_chip_2>>chipseq_pos_2>>s1_2>>s2_2>>strand_chip_2;
			//--------------------------------------------------------------
			//fp.open("/home/wlku/Desktop/chipseq_analysis/run605_KZ355/GA4906_macs_peaks_with_peak_pos_sorted.txt");

			//fp.open("/home/wlku/chipseq_analysis/maplot/maplot_enhancer/GA4906_macs_peaks_with_peak_pos_sorted.txt");
			//fp.open("/v/bisb1a/kuw/wlku/ben_stanton_data/run792/GA7822_macs_peaks_with_peak_pos_sorted.txt");
			//fp.open("/v/bisb1a/kuw/wlku/ben_stanton_data/run798_KZ850_temp/J1_chip_rybp_macs_peaks_with_input_combined_peaks_sorted_combined.txt");
			//fp.open("/v/bisb1a/kuw/wlku/ben_stanton_data/run804_KZ862/GA7822_GA7726_macs_peaks_combined_peaks_sorted_combined.txt");
			//fp.open("/v/bisb1a/kuw/wlku/ben_stanton_data/run804_KZ862/GA7746_GA7822_macs_peaks_combined_peaks_sorted_combined.txt");
			
			//fp.open("/v/bisb1a/kuw/wlku/ben_stanton_data/run804_KZ862/GA7746_GA7822_macs_peaks_combined_peaks_sorted_combined_200.txt");
			//fp.open("/v/bisb1a/kuw/wlku/ben_stanton_data/run804_KZ862/GA7747_GA7726_macs_peaks_combined_peaks_sorted_combined_200.txt");
			fp.open(inputf2.c_str());


			while(!fp.eof())
			{								
				fp>>en_chromo>>en_cindex>>en_ss>>en_es>>en_pos;					
	
				if(en_chromo.compare(chromo_chip)==0)
				{	
					enchromo_v.push_back(en_chromo);
					enss_v.push_back(en_ss);
					enes_v.push_back(en_es);
					enpos_v.push_back(en_pos);
					read_count.push_back(0);
				}

			}
			
			enpos_size = enpos_v.size();			
			fp.close();
		}	
		else if(kk > 0)
		{
			ft>>chromo_chip_2>>cindex_2>>ss_chip_2>>es_chip_2>>chipseq_pos_2>>s1_2>>s2_2>>strand_chip_2;
		}
		
		//==================================================================  
		// Compare each chipseq tag to Enhancer
		//==================================================================	
		n = 0;	
		go_ss = 0;
		while(go_ss==0 && n<enpos_size)						
		{	
			
			//if(chipseq_pos>= (enpos_v[n] -1500) && chipseq_pos <= (enpos_v[n]+1500))
			if(chipseq_pos>= (enss_v[n] -shifting) && chipseq_pos <= (enes_v[n]+shifting))
			{
				read_count[n] = read_count[n] + 1;
			}							
			n = n + 1;							
		}
		//============================================================================
		if(ft.eof())
		{
			//fout.open("/home/wlku/Desktop/chipseq_analysis/maplot/maplot_enhancer/GA6624_tags_per_enhancer.txt", ios::app);
			fout.open(outputf.c_str(), ios::app);
				
			for(j=0;j<enpos_size;j++)
			{
				//tag_den = (double) read_count[j]/(total_read);
				//tag_den = (double) log2((double) read_count[j]/(3.0*total_read));
				tag_den = read_count[j];
				//fout<<enchromo_v[j]<<"\t"<<test<<"\t"<<enpos_v[j]<<"\t"<<tag_den<<endl;
				fout<<enchromo_v[j]<<"\t"<<test<<"\t"<<enss_v[j]<<"\t"<<enes_v[j]<<"\t"<<tag_den<<endl;
				//fout<<enchromo_v[j]<<"\t"<<enss_v[j]<<"\t"<<enes_v[j]<<"\t"<<tag_den<<endl;
			}
			fout.close();
			test = test + 1;
		}

		//---------------------------------------------------------
		if(chromo_chip.compare(chromo_chip_2)!=0)
		{	
			//fout.open("/home/wlku/Desktop/chipseq_analysis/maplot/maplot_enhancer/GA6624_tags_per_enhancer.txt", ios::app);
			fout.open(outputf.c_str(), ios::app);	

			cout<<chromo_chip<<"\t"<<chromo_chip_2<<endl;

			for(j=0;j<enpos_size;j++)
			{
				//tag_den = (double) read_count[j]/(total_read);
				//tag_den = (double) log2((double) read_count[j]/(total_read));
				tag_den = read_count[j];
				//fout<<enchromo_v[j]<<"\t"<<test<<"\t"<<enpos_v[j]<<"\t"<<tag_den<<endl;
				fout<<enchromo_v[j]<<"\t"<<test<<"\t"<<enss_v[j]<<"\t"<<enes_v[j]<<"\t"<<tag_den<<endl;
				//fout<<enchromo_v[j]<<"\t"<<enss_v[j]<<"\t"<<enes_v[j]<<"\t"<<tag_den<<endl;
			}
			fout.close();
			test = test + 1;	
				
			//fp.open("/home/wlku/Desktop/chipseq_analysis/run605_KZ355/GA4906_macs_peaks_with_peak_pos_sorted.txt");
			//fp.open("/home/wlku/chipseq_analysis/maplot/maplot_enhancer/GA4906_macs_peaks_with_peak_pos_sorted.txt");
			//fp.open("/v/bisb1a/kuw/wlku/ben_stanton_data/run792/GA7822_macs_peaks_with_peak_pos_sorted.txt");			
			//fp.open("/v/bisb1a/kuw/wlku/ben_stanton_data/run798_KZ850_temp/J1_chip_rybp_macs_peaks_with_input_combined_peaks_sorted_combined.txt");
			//fp.open("/v/bisb1a/kuw/wlku/ben_stanton_data/run804_KZ862/GA7822_GA7726_macs_peaks_combined_peaks_sorted_combined.txt");
			//fp.open("/v/bisb1a/kuw/wlku/ben_stanton_data/run804_KZ862/GA7746_GA7822_macs_peaks_combined_peaks_sorted_combined.txt");
			
			//fp.open("/v/bisb1a/kuw/wlku/ben_stanton_data/run804_KZ862/GA7746_GA7822_macs_peaks_combined_peaks_sorted_combined_200.txt");
			//fp.open("/v/bisb1a/kuw/wlku/ben_stanton_data/run804_KZ862/GA7747_GA7726_macs_peaks_combined_peaks_sorted_combined_200.txt");
			fp.open(inputf2.c_str());
			
			enpos_v.clear();
			read_count.clear();
			enchromo_v.clear();
			enss_v.clear();
			enes_v.clear();

			while(!fp.eof())
			{										
				fp>>en_chromo>>en_cindex>>en_ss>>en_es>>en_pos;							
				if(en_chromo.compare(chromo_chip_2)==0)
				{	
					enchromo_v.push_back(en_chromo);
					enss_v.push_back(en_ss);
					enes_v.push_back(en_es);
					enpos_v.push_back(en_pos);
					read_count.push_back(0);
				}
			}

			enpos_size = enpos_v.size();			
			fp.close();	
			
		}
		//------------------------------------------------------------------------
		chromo_chip = chromo_chip_2;
		chipseq_pos = chipseq_pos_2;		
		ss_chip = ss_chip_2;
		es_chip = es_chip_2;		
		kk = kk + 1;
		
		if(floor(ik/10000)*10000==ik)
		{
			//cout<<enpos_size<<"\t"<<ik/10000<<endl;
		}	
	}	
	
	ft.close();
	enchromo_v.clear();
	enss_v.clear();
	enes_v.clear();
	enpos_v.clear();
	read_count.clear();
	cout<<"total_read is equal to\t"<< total_read<<endl;
//=================================================================================
}	

