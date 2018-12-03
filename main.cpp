#include <iostream>
#include <cstdlib>
#include <ctime>
#include "include.h"

using namespace std;

int main()
{
	srand(time(0));
/*
	int ll = 1000;
	int num_k = 4;
	int num_ptn = 20;
	int digit = 3;
	int num_organ = 50;
	int len_gene = 9;
	int num_resource = 4;
	dna g1, g2;
	code_dna cd1;
	ptn p1;
	code_ptn cp1;
	organ o1;
	code_organ cg1;
	map m1;

	g1.init(num_k, ll);
	cd1.init(num_k,num_ptn,digit);
	cp1.init(num_ptn, num_organ, len_gene);
	cg1.init(num_organ, num_resource);

//	g1.print_chain();
	p1.translate(g1,cd1);
	o1.translate(p1,cp1);
//	p1.print_chain();
//	cp1.print_code();
//	o1.print_chain();
	cg1.print();
*/	

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

}
