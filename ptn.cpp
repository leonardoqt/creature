#include <iostream>
#include <cstdlib>
#include "ptn.h"
#include "dna.h"

using namespace std;

ptn :: ptn()
{
	chain = nullptr;
}

ptn :: ~ptn()
{
	if (chain != nullptr)
		delete[] chain;
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
	cout<<"Print protein sequence:"<<endl;
	for(int t1=0; t1<length; t1++)
		cout<<chain[t1]<<' ';
	cout<<endl;
}

//======================================================

void code_ptn :: init(int n_p, int n_organ, int n_digit)
{
	num_ptn = n_p;
	num_organ = n_organ;
	num_digit = n_digit;
	code = new int*[num_organ];
	for(int t1=0; t1<num_organ; t1++)
		code[t1] = new int[num_digit];

	for(int t1=0; t1<num_organ; t1++)
		for(int t2=0; t2<num_digit; t2++)
			code[t1][t2] = rand()%num_ptn;
}

void code_ptn :: print_code()
{
	cout<<"Print protein to organ sequence:"<<endl;
	for(int t1=0; t1<num_organ; t1++)
	{
		for(int t2=0; t2<num_digit; t2++)
			cout<<code[t1][t2]<<'\t';
		cout<<endl;
	}
}
