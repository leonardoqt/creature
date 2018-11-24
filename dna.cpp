#include <cstdlib>
#include <iostream>
#include "dna.h"

using namespace std;

dna :: dna()
{
	length = 0;
	num_k = 0;
	chain = nullptr;
}

dna :: ~dna()
{
	if (chain != nullptr)
		delete[] chain;
}

void dna :: init(int num, int ll)
{	
	num_k = num;
	length = ll;
	chain = new int[length];
	for(int t1=0; t1<length; t1++)
		chain[t1] = rand()%num_k;
}

dna& dna :: operator=(const dna& B)
{
	if (chain != nullptr)
		delete[] chain;
	length = B.length;
	num_k = B.num_k;
	chain = new int[length];
	for (int t1=0; t1<length; t1++)
		chain[t1] = B.chain[t1];
	return (*this);
}

void dna :: mutate(int num)
{
	int ind;
	for(int t1=0; t1<num; t1++)
	{
		ind = rand()%length;
		chain[ind] = rand()%num_k;
	}
}

void dna :: print_chain()
{
	for (int t1=0; t1<length; t1++)
		cout<<chain[t1]<<' ';
	cout<<endl;
}


//=========================code_dna==============================
void code_dna :: init(int kk, int ptn, int digit)
{
	num_k = kk;
	num_ptn = ptn;
	num_digit = digit;
	num_code = 1;
	for(int t1=0; t1<num_digit; t1++)
		num_code *= num_k;
	code = new int[num_code];
	for(int t1=0; t1<num_code; t1++)
		code[t1] = rand()%num_ptn;
}

void code_dna :: print_code()
{
	for (int t1=0; t1<num_code; t1++)
		cout<<t1<<":\t"<<code[t1]<<endl;
}