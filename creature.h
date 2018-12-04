#ifndef CREATURE
#define CREATHRE

#include "class.h"
#include "dna.h"
#include "ptn.h"
#include "organ.h"
#include "resource.h"
#include "map.h"

class creature
{
private :
	dna dna0;
	ptn ptn0;
	organ organ0;
	int num_r;	// types of resource
	code_dna *cd;
	code_ptn *cp;
	code_organ *co;
	// define status/function of the creature
	double x,y;
	resource s_range, s_acc, s_num;
	resource m_acc, m_eff;
	resource c_c_cap, c_p_cap;
	resource cost, harm;
	resource stock, damage;
public :
	void init(int num_resource, code_dna&, code_ptn&, code_organ&);
	void dna_init(int length);
	void translate();
	void travel(map& map0);
	void print();
};
#endif
