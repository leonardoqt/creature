#ifndef CREATURE
#define CREATHRE

#include <fstream>
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
	resource s_range, s_acc, s_num;
	resource m_acc, m_eff;
	resource c_c_cap, c_p_cap;
	resource cost, harm;
	resource stock, damage;
public :
	double x,y;
	// living status
	double living_advantage;	// save stock/cost , sum for all resources, if no need one type of resource, add a very large number
	double mutation_chance;		// use ln(1+damage) to get extra mutation chance, sum up for all resources, base chance is 1%

	void init(int num_resource, code_dna*, code_ptn*, code_organ*);
	void dna_init(int length);
	void translate();
	void travel(map& map0);
	void surviving();
	void spawn(creature& baby);

	void save_dna(std::ofstream& out);
	void load_dna(std::ifstream& in);
	void print();
};
#endif
