#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "include.h"

using namespace std;

int main()
{
	int num_creature;
	// code
	code_dna cd1;
	code_ptn cp1;
	code_organ co1;
	// creature
	creature *being;
	// for map
	map m1;
	// file
	ifstream in_cd;
	ifstream in_cp;
	ifstream in_co;
	ifstream in_dna;
	ifstream in_map;

	in_cd.open("code_dna.dat");
	in_cp.open("code_ptn.dat");
	in_co.open("code_organ.dat");
	in_dna.open("dna.dat");
	in_map.open("map.dat");
	cd1.load(in_cd);
	cp1.load(in_cp);
	co1.load(in_co);
	m1.load(in_map);

	cin>>num_creature;
	being = new creature[num_creature];

	for(int t1=0; t1<num_creature; t1++)
	{
		cout<<t1<<"============================================"<<endl;
		// prepare for creatures
		being[t1].init(m1.num_resource,&cd1,&cp1,&co1);
		being[t1].load_dna(in_dna);
		being[t1].translate();
		being[t1].print();
	}
	return 0;
}
