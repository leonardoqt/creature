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
	dna g1, g2;
	code_dna c1;
	ptn p1;

	g1.init(num, ll);
	c1.init(num,num_ptn,digit);
	c1.print_code();

	g1.print_chain();
	p1.translate(g1,c1);
	p1.print_chain();
}
