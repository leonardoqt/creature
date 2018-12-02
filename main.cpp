#include <cstdlib>
#include <ctime>
#include "include.h"

int main()
{
	srand(time(0));

	int ll = 100;
	int num = 4;
	int num_ptn = 20;
	int digit = 3;
	int num_organ = 10;
	int len_gene = 10;
	dna g1, g2;
	code_dna cd1;
	ptn p1;
	code_ptn cp1;

	g1.init(num, ll);
	cd1.init(num,num_ptn,digit);
	cp1.init(num_ptn, num_organ, len_gene);

	g1.print_chain();
	p1.translate(g1,cd1);
	p1.print_chain();
	g1.mutate(5);
	p1.translate(g1,cd1);
	p1.print_chain();

	cp1.print_code();
}
