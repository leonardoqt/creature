#ifndef RESOURCE
#define RESOURCE

#include "class.h"

class resource
{
private :
	int num;
	double *list;
friend sensor;
friend mover;
friend collector;
friend map;
friend creature;
public :
	resource();
	~resource();
	void init(int nn);
	void print();
};
#endif
