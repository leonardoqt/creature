#ifndef DNA
#define DNA

#include "class.h"
#include <fstream>

class dna
{
private :
	int length;
	int num_k;
	int *chain;
friend code_dna;
friend ptn;
friend creature;
public :
	dna();
	~dna();
	void init(int num, int ll);
	dna& operator=(const dna& );
	void mutate(int num);

	void save(std::ofstream & out);
	void load(std::ifstream & in);
	void print_chain();
};

class code_dna
{
private :
	int num_k;
	int num_ptn;
	int num_digit;
	int num_code;
	int * code;
friend dna;
friend ptn;
friend creature;
public :
	void init(int kk, int ptn, int digit);

	void save(std::ofstream & out);
	void load(std::ifstream & in);
	void print_code();
};

#endif
