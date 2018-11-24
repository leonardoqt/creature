#ifndef PTN
#define PTN

#include "class.h"

class ptn
{
private:
	int length;
	int num_k;
	int * chain;
public:
	ptn();
	void translate(dna&, code_dna&);

	void print_chain();
};

#endif
