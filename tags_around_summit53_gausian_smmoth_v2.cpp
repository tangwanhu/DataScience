//============================================================================
// Name        : HC2AZ.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "UCSCBEDOperator.h"
#include "expression.h"
#include "Nucs.h"

using namespace std;

int PROMOTERUPLEN = 2500;
int PROMOTERDOWNLEN = 2500;
int MININTRESTREGIONLEN = 0;
int SHIFT = 0;

int main(int argc, char* args[]) {

	if( argc != 12){
            cout<<"Usage: tags_around_summit53_gausian_smmoth_v2 bed_file "
            		"input_option input_file upL dwnL shift out_put_tag generate_graph[y/n] chr chrlen_file pair(y/n)\n";
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
	Str in_f = Str(args[1]);
	int opt = atoi(args[2]);
	int upL = atoi(args[4]);
	int dnL = atoi(args[5]);
	int shift = atoi(args[6]);
	Str out_tag = Str(args[7]);
	bool begraph= Str(args[8]) == "y";
	Str chr = Str(args[9]);
	Str chrlen_f = Str(args[10]);
	bool pair = Str(args[11]) == "y";

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

	for( map<Str, vector<BED3> >::iterator chrIt = regions.begin(); chrIt != regions.end(); ++chrIt ){
		for( vector<BED3>::iterator bIt = chrIt->second.begin(); bIt != chrIt->second.end(); ++bIt ){
			int m = (bIt->start+bIt->end)/2;
			if( bIt->strand == "+"){
				bIt->start = m - upL;
				bIt->end = m + dnL;
			}else{
				bIt->start = m - dnL;
				bIt->end = m + upL;
			}
		}
	}
	ofstream out((out_tag+chr).data());

	Nucs nucs(chrlen_f, chr);
	if( pair )
		nucs.init_from_double(in_f);
	else
		nucs.init_from_single(in_f, shift);
	nucs.gausian_thrshld(50000);
	nucs.assignDensity2BEDs( regions, out_tag);
	if(begraph)
		nucs.get_graph_file(out_tag+chr+".graph");
	for( map<Str, vector<BED3> >::iterator chrIt = regions.begin(); chrIt != regions.end(); ++chrIt ){
		for( vector<BED3>::iterator bIt = chrIt->second.begin(); bIt != chrIt->second.end(); ++bIt ){
			if( bIt->chrom == chr ){
				map<Str, vector<double>  >::iterator dIt = bIt->gaussianDensityOn.find(out_tag);
				map<Str, vector<double>  >::iterator dthrIt = bIt->gaussianDensityOn.find(out_tag+"thrshld");
				if( dIt != bIt->gaussianDensityOn.end() && dthrIt != bIt->gaussianDensityOn.end()){
					out<<bIt->chrom<<":"<<bIt->start<<"-"<<bIt->end;
					vector<double> d = dIt->second;
					vector<double> dthr = dthrIt->second;
					int step = 10;
					for( int i = 0; i < d.size() - step; i += step ){
						double sum = 0;
						for( int j = 0; j < step; ++j){
							sum += d[i+j] - dthr[i+j];
						}
						out<<'\t'<<sum/step;//(sum > 0 ? sum/step: 0);
					}
					out<<endl;
				}
			}
		}
	}
	out.close();

	return 0;
}
