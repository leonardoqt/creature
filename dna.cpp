#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
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

void dna :: mutate(double rate)
{
	for(int t1=0; t1<length; t1++)
		if (rand()/(double)RAND_MAX < rate)
			chain[t1] = rand()%num_k;
}

void dna :: save(ofstream& out)
{
	out<<"DNA_info"<<endl;
	out<<length<<'\t'<<num_k<<endl;
	for(int t1=0; t1<length; t1++)
		out<<chain[t1]<<' ';
	out<<endl;
}

void dna :: load(ifstream& in)
{
	string tmp;
	string label = "DNA_info";
	getline(in,tmp);
	while(tmp.find(label) == string::npos)
		getline(in,tmp);
	in>>length>>num_k;
	if(chain != nullptr)
		delete[] chain;
	chain = new int[length];
	for(int t1=0; t1<length; t1++)
		in>>chain[t1];
}

void dna :: print_chain()
{
	cout<<"Print DNA sequence:"<<endl;
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

void code_dna :: save(ofstream& out)
{
	out<<"num_k "<<num_k<<endl;
	out<<"num_ptn "<<num_ptn<<endl;
	out<<"num_digit "<<num_digit<<endl;
	out<<"num_code "<<num_code<<endl;
	out<<"begin_code "<<endl;
	for(int t1=0; t1<num_code; t1++)
	{
		out<<code[t1]<<'\t';
		if((t1+1)%num_k == 0)
			out<<endl;
	}
}

void code_dna :: load(ifstream& in)
{
	string tmp;
	in>>tmp>>num_k;
	in>>tmp>>num_ptn;
	in>>tmp>>num_digit;
	in>>tmp>>num_code;
	code = new int[num_code];
	in>>tmp;
	for(int t1=0; t1<num_code; t1++)
		in>>code[t1];
}

void code_dna :: print_code()
{
	cout<<"Print DNA to protein code:"<<endl;
	for (int t1=0; t1<num_code; t1++)
		cout<<t1<<":\t"<<code[t1]<<endl;
}
