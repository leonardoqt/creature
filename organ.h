#ifndef ORGAN
#define ORGAN

#include "class.h"

class organ
{
private :
	int num_organ;
	int * chain;
	double * rate;
public :
	organ();
	void translate(ptn&, code_ptn&);

	void print_chain();
};

class sensor
{
// each sensor has a type that only sense a certain signal, but all sensors could share the same type.
// could have IFF that work differently.
};

class mover
{
// each mover reacts to the result of a single signal.
// mover for IFF can be different.
};

class code_organ
{
// this code map organ index to organ type(sensor, mover, etc), and basic function value, since it is complicated, sensor and mover will be defiend above
private :
};

#endif
