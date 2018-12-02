#include <cstdlib>
#include <ctime>
#include "include.h"

int main()
{
	srand(time(0));

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
	sensor s1;
	mover m1;
	collector c1;

	g1.init(num_k, ll);
	cd1.init(num_k,num_ptn,digit);
	cp1.init(num_ptn, num_organ, len_gene);

//	g1.print_chain();
	p1.translate(g1,cd1);
	o1.translate(p1,cp1);
//	p1.print_chain();
//	cp1.print_code();
//	o1.print_chain();
	s1.init(num_resource);
	m1.init(num_resource);
	c1.init(num_resource);
	s1.print();
	m1.print();
	c1.print();
}
