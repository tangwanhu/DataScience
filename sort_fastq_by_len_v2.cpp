
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

int main(int argc, char* args[]) {
	if( argc != 5 ){
		cout<<"sort_fastq_by_len_v2 fastq label minLen maxLen\n";
		return 0;
	}
	int minL = atoi(args[3]);
	int maxL = atoi(args[4]);
	Str label(args[2]);
	vector<pair<Str, Str> > id_fastq = readInFast(Str(args[1]));

	vector<pair<int, pair<Str, Str> > > len_seq;
	for( vector<pair<Str, Str> >::iterator it = id_fastq.begin(); it != id_fastq.end(); ++it ){
		len_seq.push_back(make_pair(it->second.size(), *it));
	}

	sort( len_seq.begin(), len_seq.end(), std::greater<pair<int, pair<Str, Str> > >() );

	ofstream out(Str(Str(args[1])+"_sort_"+convert2String(minL)+"_"+convert2String(maxL)).data());
	int N = 0;
	for( vector<pair<int, pair<Str, Str> > >::iterator it = len_seq.begin(); it != len_seq.end(); ++it ){
		if( it->second.second.size() > minL && it->second.second.size() < maxL ){
			out<<">"<<label<<"_"<<convert2String(++N)<<endl;
			out<<it->second.second<<endl;
		}
	}
	out.close();

	return 0;
}


//*/
