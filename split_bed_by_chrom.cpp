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

struct EXPR{
public:
	Str prob;
	double wt, sh, fc, pvalue;
	EXPR(){
		prob = "";
		wt = sh = fc = pvalue = 0;
	}
};

int main(int argc, char* args[]) {
	if( argc != 4 ){
		cout<<"split_bed_by_chrom bed chrlen_file tag\n";
		return 1;
	}
	//name_expr mapping
	map<Str, std::ofstream*> chr_out;
	map<Str, int> chrlen = getChrlen(Str(args[2]));
	for( map<Str, int>::iterator it = chrlen.begin(); it != chrlen.end(); ++it ){
		Str fn = it->first+"_"+Str(args[3])+".bed";
		cout<<fn<<endl;
		chr_out[it->first] = new std::ofstream( fn.data(), std::fstream::app);
	}
	ifstream in(args[1]);
	int N = 0;
	while( !in.eof() ){
		Str chr, oth;
		in>>chr;
		getline( in, oth );
		if( !chr.empty() ){
			map<Str, std::ofstream*>::iterator oIt = chr_out.find(chr);
			if( oIt != chr_out.end()){
				*(oIt->second)<<chr<<'\t'<<oth<<endl;
			}
			if( ++N%5000000 == 0){
				cout<<N<<'\t';
			}
		}
	}
	cout<<endl;
	return 0;
}

