
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

double get_kappa(Str s, int period ){
	double max = 0;
	//cout<<s<<endl;
	for( int i = 1; i <= period; ++i ){
		Str s1 = s.substr(s.size() - i) + s.substr(0, s.size() - i);
		double sum = 0;
		for( int j = 0; j < s.size(); ++j ){
			if( s[j] == s1[j] )
				sum += 1;
		}
		//cout<<s1<<'\t'<<sum/s.size()<<endl;
		if( sum > max )
			max = sum;
	}
	return max/s.size();
}

int main(int argc, char* args[]) {
	/*get_kappa("AAAAAAAAAAAAAAAAAAAAAATCTATGTT", 15);
	exit(1);//*/
	if( argc != 2 ){
		cout<<"tag_count_bowtie bowtie.map\n";
		return 0;
	}//*/

	set<Str> bowtie;
	ifstream bowtie_in(args[1]);//bowtie map
	int recy = 0, total = 0;
	while( !bowtie_in.eof() ){
		Str tag;
		bowtie_in>>tag>>tag>>tag>>tag>>tag;
		if( !tag.empty() ){
			++total;
			if( get_kappa(tag, tag.size()/2) < 0.8 && bowtie.find(tag) == bowtie.end() ){
				++recy;
			}
			bowtie.insert( tag );
		}
		getline( bowtie_in, tag);
	}
	bowtie_in.close();

	cout<<args[1]<<"\t"<<total<<'\t'<<bowtie.size()<<"\t informless_tag\t"<<recy<<endl;
	return 0;
}


//*/
