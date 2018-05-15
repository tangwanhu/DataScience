
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

int main(int argc, char* args[]){
    if( argc != 3 ){
            cout<<"split_bowtie_by_chr chrlen_file\n";
            return 1;
    }

	map<Str, std::ofstream*> chr_out;
	map<Str, int> chrlen = getChrlen(Str(args[2]));
	for( map<Str, int>::iterator it = chrlen.begin(); it != chrlen.end(); ++it ){
		Str fn = it->first+"_"+Str(args[1]);
		chr_out[it->first] = new std::ofstream( fn.data());
	}

	ifstream in(args[1]);
	int n = 0;
	while( !in.eof() ){
		Str id1, str1, chr1, seq1, qual1;
		int pos1;
		in>>id1>>str1>>chr1>>pos1>>seq1;
		getline(in, qual1);
		if( ++n % 10000000 == 0)
			cout<<n<<endl;
		if( !id1.empty()){
			map<Str, std::ofstream*>::iterator oIt = chr_out.find(chr1);
			if( oIt != chr_out.end()){
				*(oIt->second)<<id1<<"\t"<<str1<<"\t"<<chr1<<"\t"<<pos1<<"\t"<<seq1<<qual1<<endl;
			}
		}
	}//*/

	return 0;
}
