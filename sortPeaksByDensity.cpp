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

int PROMOTERUPLEN = 1000;
int PROMOTERDOWNLEN = 1000;
int MININTRESTREGIONLEN = 0;
int SHIFT = 0;

int main(int argc, char* args[]) {
	if( argc != 7){
		cout<<"sortPeaksByDensity peak_file bed_file upL dwnL output ascend(1/0)\n";
		return 1;
	}

	int upL = atoi(args[3]);
	int dwnL = atoi(args[4]);
	map<Str, set<BED3> > _isld, isld;
	BEDFrmFile( args[1], _isld);
	for( map<Str, set<BED3> >::iterator chrIt = _isld.begin(); chrIt != _isld.end(); ++chrIt ){
		for( set<BED3>::iterator bIt = chrIt->second.begin(); bIt != chrIt->second.end(); ++bIt ){
			BED3 b = *bIt;
			b.start = (bIt->start+bIt->end)/2 - upL;
			b.end = (bIt->start+bIt->end)/2 + dwnL;
			isld[b.chrom].insert(b);
		}
	}
	assignReadCount2Island(isld, args[2], "den");
	vector<pair<double, BED3> > den_bed;
	for( map<Str, set<BED3> >::iterator chrIt = isld.begin(); chrIt != isld.end(); ++chrIt ){
		for( set<BED3>::iterator bIt = chrIt->second.begin(); bIt != chrIt->second.end(); ++bIt ){
			map<Str,double>::const_iterator denIt = bIt->readDensityOn.find("den");
			if( denIt != bIt->readDensityOn.end() ){
				den_bed.push_back(make_pair( denIt->second, *bIt));
			}
		}
	}
	if( Str(args[6]) == "1" ){
		sort( den_bed.begin(), den_bed.end() );
	}else{
		sort( den_bed.begin(), den_bed.end(), std::greater<pair<double, BED3> >() );
	}

	ofstream out(args[5]);
	for( vector<pair<double, BED3> >::iterator it = den_bed.begin(); it != den_bed.end(); ++it ){
		out<<it->second.chrom<<'\t'<<it->second.start<<'\t'<<it->second.end<<endl;
	}
	out.close();

	return 0;
}


//*/
