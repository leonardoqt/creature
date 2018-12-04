#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "include.h"

using namespace std;

int main()
{
	srand(time(0));
//	srand(0);
	int ll = 300;
	int num_k = 4;
	int num_ptn = 20;
	int digit = 3;
	int num_organ = 90000;
	int len_gene = 9;
	int num_resource = 2;
	code_dna cd1;
	code_ptn cp1;
	code_organ co1;
	creature being[3];
	int ini_from_file = 0;

	ifstream in_cd;
	ifstream in_cp;
	ifstream in_co;
	ofstream out_cd;
	ofstream out_cp;
	ofstream out_co;

	cin>>ini_from_file;
	if (ini_from_file)
	{
		in_cd.open("code_dna.dat");
		in_cp.open("code_ptn.dat");
		in_co.open("code_organ.dat");

		cd1.load(in_cd);
		cp1.load(in_cp);
		co1.load(in_co);
	}
	else
	{
		out_cd.open("code_dna.dat");
		out_cp.open("code_ptn.dat");
		out_co.open("code_organ.dat");

		cd1.init(num_k,num_ptn,digit);
		cp1.init(num_ptn, num_organ, len_gene);
		co1.init(num_organ, num_resource);

		cd1.save(out_cd);
		cp1.save(out_cp);
		co1.save(out_co);
	}

	for(int t1=0; t1<3; t1++)
	{
		being[t1].init(num_resource,&cd1,&cp1,&co1);
		being[t1].dna_init(ll);
		being[t1].translate();
	}
	being[0].print();

	double A = 500, k1 = 0.04, k2 = 0.01, fhi = 3.14;
	int num_cp = 4;
	map m1;
	m1.init(num_resource, num_cp, A, k1, k2, fhi);
	for(int t1=0; t1<100; t1++)
	{
//		cout<<t1<<'\t';
		being[0].travel(m1);
	}

//print map
/*
	double A = 200, k1 = 0.04, k2 = 0.01, fhi = 3.14;
	int num_res = 1;
	int num_cp = 4;
	map m1;
	resource r1;

	m1.init(num_res, num_cp, A, k1, k2, fhi);
	r1.init(num_res);

	for(int t1=-700; t1<=700; t1+=10)
	for(int t2=-700; t2<=700; t2+=10)
	{
		m1.value(t1,t2,r1);
		cout<<t1<<'\t'<<t2<<'\t';
		r1.print();
	}
*/
}
