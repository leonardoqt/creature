#ifndef PTN
#define PTN

#include "class.h"
#include <fstream>

class ptn
{
private:
	int length;
	int num_k;
	int * chain;
friend organ;
friend creature;
public:
	ptn();
	~ptn();
	void translate(dna&, code_dna&);

	void print_chain();
};

class code_ptn
{
private:
	int num_ptn;
	int num_organ;
	int num_digit;
	int ** code;	// code_ptn is translated using similarity
friend organ;
friend creature;
public :
	void init(int n_p, int n_organ, int n_digit);

	void save(std::ofstream& out);
	void load(std::ifstream& in);

	void print_code();
};

#endif
