#ifndef ORGAN
#define ORGAN

#include "class.h"
#include "resource.h"

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
// could have IFF that works differently.
private :
	int type;
	// range of sense
	double range;
	// how many points check in the range
	int num_check;
	// accuracy of signal value
	double acc;
	resource cost;
	resource harm;
public :
	void init(int nn); 	// number of total type of signals
	void print();
};

class mover
{
// each mover reacts to the result of a single signal.
// mover for IFF can be different.
private :
	int type;
	// how accurate value transfer from sensor to mover
	double acc;		// for multiple mover, final acc = 1-Pi(1-acc)
	// how close to move to max value
	double eff;		// same to eff
	resource cost;
	resource harm;
public :
	void init(int nn);
	void print();
};

class collector
{
// collector and protector together, each organ has requirements/vulnerability for certain signals (simulate resources and poison)
// the sum represents total requirements/vulnerability
// for multiple collector, take the sum as for
private :
	int type;
	int c_p;	// c: 1,collector; p: -1,protector
	// threshold of collect, protect;
	double cap;
	resource cost;
	resource harm;
public :
	void init(int nn);
	void print();
};

class code_organ
{
// this code map organ index to organ type(sensor, mover, etc), and basic function value, since it is complicated, sensor and mover will be defiend above
// this code generate list of all organs
private :
	int num_organ;
	int num_sensor;
	int num_mover;
	int num_collector;
	sensor *ss;
	mover *mm;
	collector *cc;
friend creature;
public :
	void init(int num, int num_signal);
	void print();
};

#endif
