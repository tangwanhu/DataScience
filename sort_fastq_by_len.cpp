
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
	if( argc != 2 ){
		cout<<"sort_fastq_by_len fastq\n";
		return 0;
	}

	vector<pair<Str, Str> > id_fastq = readInFast(Str(args[1]));

	vector<pair<int, pair<Str, Str> > > len_seq;
	for( vector<pair<Str, Str> >::iterator it = id_fastq.begin(); it != id_fastq.end(); ++it ){
		len_seq.push_back(make_pair(it->second.size(), *it));
	}

	sort( len_seq.begin(), len_seq.end(), std::greater<pair<int, pair<Str, Str> > >() );

	ofstream out(Str(Str(args[1])+"_sort.txt").data());
	for( vector<pair<int, pair<Str, Str> > >::iterator it = len_seq.begin(); it != len_seq.end(); ++it ){
		out<<">"<<it->second.first<<endl;
		out<<it->second.second<<endl;
	}
	out.close();

	return 0;
}


//*/
