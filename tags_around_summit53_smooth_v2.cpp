	//============================================================================
// Name        : HC2AZ.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "UCSCBEDOperator.h"
#include "expression.h"

using namespace std;

int PROMOTERUPLEN = 2000;
int PROMOTERDOWNLEN = 2000;
int MININTRESTREGIONLEN = 0;
int SHIFT = 0;

int main(int argc, char* args[]) {

	if( argc < 10){
            cout<<"Usage: tags_around_summit53_smooth file_names_file "
            		"input_option input_file upL downL shift out_put input_sense_strand_only[y/n] bp_in_smooth\n";
            cout<<"input_option: 1 bed3 the middle of the regions will be chosen as sumit\n";
            cout<<"input_option: 2 macs XLS\n";
            cout<<"input_option: 3 SICCERSummary\n";
            cout<<"input_option: 4 fimmo txt\n";
            cout<<"input_option: 5 ucsc_genes.txt(TSS will be extracted)\n";
            cout<<"input_option: 6 BED4\n";
            cout<<"file_names_file: contain filenames of bed3, \n"
            		"\t if itself is not a bed3 file\n ";
            return 0;
    }//*/

	map<Str, vector<BED3> > regions;
	map<Str, set<BED3> > _regions;
	int opt = atoi(args[2]);
	int upL = atoi(args[4]);
	int dnL = atoi(args[5]);
	int shift = atoi(args[6]);

	if( opt == 1){
		BEDFrmFile( Str(args[3]), _regions, 0);
		for( map<Str, set<BED3> >::iterator chrIt = _regions.begin(); chrIt != _regions.end(); ++chrIt ){
			for(  set<BED3>::iterator bIt = chrIt->second.begin(); bIt != chrIt->second.end(); ++bIt ){
				BED3 b = *bIt;
				b.sumit = (bIt->start + bIt->end)/2;
				regions[b.chrom].push_back( b);
			}
		}
	}else if( opt == 2 ){
		BEDFrmMACSXLS( Str(args[3]), _regions, 0, true);
		for( map<Str, set<BED3> >::iterator chrIt = _regions.begin(); chrIt != _regions.end(); ++chrIt ){
			for(  set<BED3>::iterator bIt = chrIt->second.begin(); bIt != chrIt->second.end(); ++bIt ){
				regions[bIt->chrom].push_back( *bIt);
			}
		}
	}else if( opt == 3 ){
		BEDFrmSICCERSummary( Str(args[3]), _regions, 0);
		for( map<Str, set<BED3> >::iterator chrIt = _regions.begin(); chrIt != _regions.end(); ++chrIt ){
			for(  set<BED3>::iterator bIt = chrIt->second.begin(); bIt != chrIt->second.end(); ++bIt ){
				BED3 b = *bIt;
				b.sumit = (bIt->start + bIt->end)/2;
				regions[b.chrom].push_back( b);
			}
		}
	}else if( opt == 4 ){
		_regions = BEDFrmFIMO(Str(args[3]));
		for( map<Str, set<BED3> >::iterator chrIt = _regions.begin(); chrIt != _regions.end(); ++chrIt ){
			for(  set<BED3>::iterator bIt = chrIt->second.begin(); bIt != chrIt->second.end(); ++bIt ){
				BED3 b = *bIt;
				b.sumit = (bIt->start + bIt->end)/2;
				if( Str(args[8]) == "y" ){
					if( b.strand == "+")
					regions[b.chrom].push_back( b);
				}else{
					regions[b.chrom].push_back( b);
				}

			}
		}
	}else if( opt == 5){
		cout<<"From UCSC genes annotation\n";
		map<Str, set<UCSC, UCSC::sortByTxStart> > chr_genes;
		UCSCGenesFrmFile(Str(args[3]), chr_genes);
		for( map<Str, set<UCSC, UCSC::sortByTxStart> >::iterator chrIt = chr_genes.begin(); chrIt != chr_genes.end(); ++chrIt ){
			for(  set<UCSC, UCSC::sortByTxStart>::iterator gIt = chrIt->second.begin(); gIt != chrIt->second.end(); ++gIt ){
				BED3 b;
				b.chrom = gIt->chrom;
				b.start = gIt->TSS - 1000;
				b.end = gIt->TSS + 1000;
				b.sumit = gIt->TSS;
				b.strand  = gIt->strand;
				if( Str(args[8]) == "y" ){
					if( b.strand == "+")
						regions[b.chrom].push_back( b);
				}else{
					regions[b.chrom].push_back( b);
				}
			}
		}
	}else if( opt == 6){
		map<Str, set<BED4> > _regions;
		BEDFrmFile( Str(args[3]), _regions, 0);
		for( map<Str, set<BED4> >::iterator chrIt = _regions.begin(); chrIt != _regions.end(); ++chrIt ){
			for(  set<BED4>::iterator bIt = chrIt->second.begin(); bIt != chrIt->second.end(); ++bIt ){
				BED3 b;
				b.chrom = bIt->chrom;
				b.start = bIt->start;
				b.end = bIt->end;
				b.strand = bIt->strand;
				b.sumit = (bIt->start + bIt->end)/2;
				regions[b.chrom].push_back( b);
			}
		}
	}else{
		cout<<"option ERR\n";
		exit(1);
	}

	Str file_names(args[1]);
	Str tag ="ncus";
	double tagN = 0;
	if( file_names.find(".bed") == std::string::npos ){
		ifstream in(file_names.data());
		while( !in.eof() ){
			Str line;
			in >>line;
			if( !line.empty() ){
				cout<<line<<endl;
				//if( line.find("chr1-")!=std::string::npos)
					tagN += smoothed_counts_in_islands(regions,
							line, tag, shift, upL, dnL );
			}
		}
	}else{
		cout<<file_names<<endl;
		tagN += smoothed_counts_in_islands(regions, file_names, tag, shift, upL, dnL );
		cout<<"process "<<file_names<<" completed\n";
	}
	cout<<"total tags: "<<tagN<<endl;
	cout<<"out 5 and 3 density ...\n";
	ofstream out5(Str(Str(args[7])+"5").data());
	ofstream out3(Str(Str(args[7])+"3").data());
	for( map<Str, vector<BED3> >::iterator chrIt = regions.begin(); chrIt != regions.end(); ++chrIt ){
		for( vector<BED3>::iterator bIt = chrIt->second.begin(); bIt != chrIt->second.end(); ++bIt ){
			out5<<bIt->chrom<<":"<<bIt->start<<"-"<<bIt->end<<'\t'<<bIt->sumit;
			out3<<bIt->chrom<<":"<<bIt->start<<"-"<<bIt->end<<'\t'<<bIt->sumit;
			for( int i = 0; i < bIt->readCountsOn[tag+"5"].size(); ++i ){
				out5<<'\t'<<bIt->readCountsOn[tag+"5"][i];
			}
			for( int i = 0; i < bIt->readCountsOn[tag+"3"].size(); ++i ){
				out3<<'\t'<<bIt->readCountsOn[tag+"3"][i];
			}
			out5<<endl;
			out3<<endl;
		}
	}
	out5.close();
	out3.close();
	cout<<"Done\n";
	//*/

	map<Str, vector<BED3> > islands5 = set2vector(BEDFrmtags_around_summit( Str(args[7])+"5"));
	map<Str, vector<BED3> > islands3 = set2vector(BEDFrmtags_around_summit( Str(args[7])+"3"));
	vector<double> nucs5( upL+dnL, 0), nucs3( upL+dnL, 0);
	for( map<Str, vector<BED3> >::iterator chrIt = islands5.begin(); chrIt != islands5.end(); ++chrIt ){
		for( vector<BED3>::iterator bIt = chrIt->second.begin(); bIt != chrIt->second.end(); ++bIt ){
			for( int i = 0; i < bIt->readCountsOn[Str(args[7])+"5"].size(); ++i ){
				nucs5[i] += bIt->readCountsOn[Str(args[7])+"5"][i];
			}
		}
	}
	for( map<Str, vector<BED3> >::iterator chrIt = islands3.begin(); chrIt != islands3.end(); ++chrIt ){
		for( vector<BED3>::iterator bIt = chrIt->second.begin(); bIt != chrIt->second.end(); ++bIt ){
			for( int i = 0; i < bIt->readCountsOn[Str(args[7])+"3"].size(); ++i ){
				nucs3[i] += bIt->readCountsOn[Str(args[7])+"3"][i];
			}
		}
	}
	int N = getSize( islands5 );
	ofstream out53(Str(Str(args[7])+"53ave").data());
	out53<<"\tpos\tnucs\tgrp\n";
	int NN = 0;
	int step = atoi(args[9]);
	cout<<"smooth window size "<<step<<endl;
	for( int i = 0; i < nucs5.size()-step; ++i ){
		double score = 0;
		for( int j = 0; j < step; ++j ){
			score += nucs5[i+j] + nucs3[i+j];
		}
		out53<<(++NN)<<'\t'<<(i+step/2)<<'\t'<<score/step/N*1000000/tagN<<'\t'<<args[7]<<'5'<<endl;
	}
	out53.close();

	ofstream out15(Str(Str(args[7])+"5ave").data());
	out15<<"\tpos\tnucs\tgrp\n";
	NN = 0;
	for( int i = 0; i < nucs5.size()-step; ++i ){
		double score = 0;
		for( int j = 0; j < step; ++j ){
			score += nucs5[i+j];
		}
		out15<<(++NN)<<'\t'<<(i+step/2)<<'\t'<<score/step/N<<'\t'<<args[7]<<'5'<<endl;
	}
	out15.close();
	ofstream out13(Str(Str(args[7])+"3ave").data());
	out13<<"\tpos\tnucs\tgrp\n";
	NN = 0;
	for( int i = 0; i < nucs3.size()-step; ++i ){
		double score = 0;
		for( int j = 0; j < step; ++j ){
			score += nucs3[i+j];
		}
		out13<<(++NN)<<'\t'<<(i+step/2)<<'\t'<<score/step/N<<'\t'<<args[7]<<'3'<<endl;
	}
	out13.close();//*/
	return 0;
}

