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
	if( argc != 3){
	     cout<<"USAGE: sicer2bed3 sicer_summary-FDR output\n";
	     return 0;
	   }
	map<Str, set<BED3> > bed3;
	BEDFrmSICCERSummary( Str(args[1]), bed3, 0);

	ofstream out( args[2] );
	for( map<Str, set<BED3> >::iterator chrIt = bed3.begin(); chrIt != bed3.end(); ++chrIt ){
		for( set<BED3>::iterator bIt = chrIt->second.begin(); bIt != chrIt->second.end(); ++bIt ){
			out<<bIt->chrom<<'\t'<<bIt->start<<'\t'<<bIt->end<<endl;
		}
	}
	out.close();

	return 0;
}

