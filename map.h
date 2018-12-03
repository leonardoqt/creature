#ifndef MAP
#define MAP

#include "class.h"
class map
{
private :
	int num_resource;
// use A*sin(x+k1y+fhi1)*cos(y+k2y+fhi2) + a copy
	int num_cp;
	double **A, **kx1, **ky1, **kx2, **ky2, **fhi1, **fhi2;
public :
	void init(int num_res, int cp, double max_A, double max_k1, double max_k2, double max_fhi);
	void value(double x, double y, resource& rr);

	void print();
};
#endif
