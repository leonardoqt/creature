#ifndef RESOURCE
#define RESOURCE

#include <fstream>
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
	void clean();
	friend std::ofstream& operator<<(std::ofstream&,resource&);
	friend std::ifstream& operator>>(std::ifstream&,resource&);
	void print();
};
#endif
