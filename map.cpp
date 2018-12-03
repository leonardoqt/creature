#include <cstdlib>
#include <cmath>
#include "map.h"
#include "resource.h"

void map :: init(int num_res, int cp, double max_A, double max_k1, double max_k2, double max_fhi)
{
	num_resource = num_res;
	num_cp = cp;
	A    = new double*[cp];
	kx1  = new double*[cp];
	ky1  = new double*[cp];
	kx2  = new double*[cp];
	ky2  = new double*[cp];
	fhi1 = new double*[cp];
	fhi2 = new double*[cp];
	for(int t1=0; t1<num_cp; t1++)
	{
		A[t1]    = new double[num_resource];
		kx1[t1]  = new double[num_resource];
		ky1[t1]  = new double[num_resource];
		kx2[t1]  = new double[num_resource];
		ky2[t1]  = new double[num_resource];
		fhi1[t1] = new double[num_resource];
		fhi2[t1] = new double[num_resource];
	}
	for(int t1=0; t1<num_cp; t1++)
		for(int t2=0; t2<num_resource; t2++)
		{
			A[t1][t2] = max_A/2 + rand()/(double)RAND_MAX * (max_A/2);
			kx1[t1][t2] = ((rand()/(double)RAND_MAX)*2-1) * max_k1;
			ky1[t1][t2] = ((rand()/(double)RAND_MAX)*2-1) * max_k2;
			kx2[t1][t2] = ((rand()/(double)RAND_MAX)*2-1) * max_k2;
			ky2[t1][t2] = ((rand()/(double)RAND_MAX)*2-1) * max_k1;
			fhi1[t1][t2] = ((rand()/(double)RAND_MAX)*2-1) * max_k2;
			fhi2[t1][t2] = ((rand()/(double)RAND_MAX)*2-1) * max_k1;
		}
}

void map :: value(double x, double y, resource& rr)
{
	for(int t1=0; t1<num_resource; t1++)
	{
		rr.list[t1] = 0;
		for(int t2=0; t2<num_cp; t2++)
			rr.list[t2] += A[t2][t1]*sin(kx1[t2][t1]*x+ky1[t2][t1]*y+fhi1[t2][t1])*cos(ky2[t2][t1]*y-kx2[t2][t1]*x+fhi2[t2][t1]);
	}
}
