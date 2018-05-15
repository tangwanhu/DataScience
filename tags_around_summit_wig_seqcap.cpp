
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

int PROMOTERUPLEN = 2500;
int PROMOTERDOWNLEN = 2500;
int MININTRESTREGIONLEN = 0;
int SHIFT = 0;


vector<double> gausian_smooth(vector<double>& tag_raw, vector<double> dis_p, int window){
        int sz = tag_raw.size();
        int lB = window/2;
        int uB = sz - window/2;
        vector<double> tag_smooth = vector<double>(sz, 0);
        for( int i = lB; i < uB; ++i){
                if( tag_raw[i] > 0){
                        for( int j = -lB; j < lB; ++j ){
                                tag_smooth[i+j] += tag_raw[i]*dis_p[_abs(j)];
                        }
                }
        }
	return tag_smooth;
}

int main(int argc, char* args[]) {
	if( argc != 4){
		cout<<"tags_around_summit_wig_seqcap wig peaks output\n";
		cout<<"peaks: bed4 or bed3\n";
		cout<<"1kb up and 1kb down, 20-bp wnd sz, log2 scale ouput\n";
		return 0;
	}

	map<Str, pair<int, int> > probs;
	probs["chr1"] = make_pair(150000000, 160000000);
	probs["chr6"] = make_pair(30000000, 40000000);

	map<Str, vector<double> > graphs;
	graphs["chr1"] = vector<double >((probs["chr1"].second-probs["chr1"].first) );
	graphs["chr6"] = vector<double >((probs["chr6"].second-probs["chr6"].first) );

	int NN = 0;
    map<Str, set<BED3> > isld;
    ifstream in1( args[2] );
    while( !in1.eof() ){
            BED3 b;
            in1>>b.chrom>>b.start>>b.end;
            getline( in1, b.strand);
            if( b.strand.find("-") != std::string::npos ){
                    b.strand = "-";
            }else{
                    b.strand = "+";
            }
            if( !b.chrom.empty() ){
            	++NN;
            	b.island_score = ++NN;
            	if( b.chrom == "chr1" && b.start > probs["chr1"].first && b.end < probs["chr1"].second )
            		isld[b.chrom].insert(b);
            	if( b.chrom == "chr6" && b.start > probs["chr6"].first && b.end < probs["chr6"].second )
               		isld[b.chrom].insert(b);
            }
    }
    in1.close();
    cout<<"# peaks in regions "<<getSize(isld)<<endl;

	map<Str, int> ptn_n;
	ifstream in(args[1]);
	Str chrom;
	int base = 0;
	int stp = 0;
	int span = 0;
	int index = 0;
	int startPos = 0;
	int endPos = 0;
	while( !in.eof() ){
		Str line;
		in>>line;
		if(line.find("fixedStep") != std::string::npos ){
			Str _base, _stp, _span;
			in>>chrom>>_base>>_stp>>_span;
			chrom = chrom.substr(chrom.find("=")+1);
			base = atoi(_base.substr(_base.find("=")+1).data());
			stp = atoi(_stp.substr(_stp.find("=")+1).data());
			span = atoi(_span.substr(_span.find("=")+1).data());
			startPos = probs[chrom].first;
			endPos = probs[chrom].second;
			index = 0;
			cout<<chrom<<"\t"<<startPos<<"\t"<<endPos<<"\t"<<base<<"\t"<<stp<<"\t"<<span<<endl;
		}else{
			int beg = index*stp;
			if( base+beg > startPos && base+beg+span<endPos ){
				for( int i = 0; i < span; ++i ){
					graphs[chrom][base+beg-startPos+i]=atof(line.data());
				}
			}
			++index;
		}
	}
	in.close();

	int step = 10;
	vector<double > profile(2000,0);
	vector<pair<double, pair<Str, vector<double> > > > score_id_vect;
	for( map<Str, vector<double> >::iterator it = graphs.begin(); it != graphs.end(); ++it ){
		map<Str, pair<int, int> >::iterator pIt = probs.find(it->first);
		if( pIt != probs.end() ){
			int beg = pIt->second.first;
			int end = probs[it->first].second;
			vector<double > gp = it->second;
			map<Str, set<BED3> >::iterator isldIt = isld.find(it->first);
			if( isldIt != isld.end() ){
				for( set<BED3>::const_iterator bIt = isldIt->second.begin(); bIt != isldIt->second.end(); ++bIt ){
					int pos = (bIt->start + bIt->end)/2;
					if( pos - beg > profile.size()/2 && pos + profile.size()/2 < end ){
						vector<double> dens;
						if( bIt->strand == "+"){
							for( int i = 0; i < profile.size(); ++i ){
								profile[i] += gp[pos - profile.size()/2 - beg + i];
								dens.push_back(gp[pos - profile.size()/2 - beg + i]);
							}
						}else{
							for( int i = 0; i < profile.size(); ++i ){
								profile[profile.size()-1-i] += gp[pos - profile.size()/2 - beg + i];
								dens.push_back(gp[pos - profile.size()/2 - beg + i]);
							}
						}
						pair<Str, vector<double> > id_vect;
						id_vect.first = bIt->chrom+":"+convert2String(bIt->start)+"-"+convert2String(bIt->end);
						int step = 20;
						for( int i = 0; i < dens.size() - step; i += step ){
							double sum = 0;
							for( int j = 0; j < step; ++j ){
								sum += dens[i+j];
							}
							id_vect.second.push_back(sum/step);
						}
						score_id_vect.push_back(make_pair(bIt->island_score, id_vect));
					}
				}
			}
		}
	}
	sort( score_id_vect.begin(), score_id_vect.end() );
	ofstream out1((Str(args[3])+".mtx").data());
	for( int i = 0; i < score_id_vect.size(); ++i ){
		pair<Str, vector<double> > id_vect = score_id_vect[i].second;
		out1<<id_vect.first;
		for( int k = 0; k < id_vect.second.size(); ++k ){
			out1<<"\t"<<id_vect.second[k];
		}
		out1<<endl;
	}
	out1.close();//*/
	ofstream out((Str(args[3])+".prf").data());
	out<<"\tpos\tden\n";
	for( int i = 0; i < profile.size(); ++i ){
		out<<(i+1)<<"\t"<<(i+1)<<"\t"<<profile[i]<<endl;
	}
	out.close();

	return 0;
}

//*/
