#include <iostream>
#include "ptn.h"
#include "dna.h"

using namespace std;

ptn :: ptn()
{
	chain = nullptr;
}

void ptn :: translate(dna& d1, code_dna& c1)
{
	length = d1.length/c1.num_digit;
	int ind;
	
	if (chain != nullptr)
		delete[] chain;
	chain = new int[length];

	for(int t1=0; t1<length; t1++)
	{
		ind = 0;
		for(int t2=0; t2<c1.num_digit; t2++)
		{
			ind *= c1.num_k;
			ind += d1.chain[t1*c1.num_digit+t2];
		}
		chain[t1] = c1.code[ind];
	}
}

void ptn :: print_chain()
{
	for(int t1=0; t1<length; t1++)
		cout<<chain[t1]<<' ';
	cout<<endl;
}
