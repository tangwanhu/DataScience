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

int PROMOTERUPLEN = 5000;
int PROMOTERDOWNLEN = 5000;
int MININTRESTREGIONLEN = 5000;
int SHIFT = 0;

int main(int argc, char* args[]) {
	if( argc != 2 ){
		cout<<"seqlen seg_fasta\n";
		return 0;
	}
	ifstream in(args[1]);
	Str tmp;
	getline( in, tmp );
	int sz = 0;
	while( !in.eof() ){
		getline( in,tmp );
		if( !tmp.empty() ){
			sz += tmp.size();
		}
	}
	cout<<args[1]<<'\t'<<sz<<endl;
	return 0;
}

//*/
