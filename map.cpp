#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include "map.h"
#include "resource.h"

using namespace std;

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
			fhi1[t1][t2] = ((rand()/(double)RAND_MAX)*2-1) * max_fhi;
			fhi2[t1][t2] = ((rand()/(double)RAND_MAX)*2-1) * max_fhi;
		}
}

void map :: value(double x, double y, resource& rr)
{
	for(int t1=0; t1<num_resource; t1++)
	{
		rr.list[t1] = 0;
		for(int t2=0; t2<num_cp; t2++)
			rr.list[t1] += A[t2][t1]*(1+sin(kx1[t2][t1]*x+ky1[t2][t1]*y+fhi1[t2][t1])*cos(ky2[t2][t1]*y-kx2[t2][t1]*x+fhi2[t2][t1]));
	}
}

void map :: save(ofstream& out)
{
	out<<"num_resource "<<num_resource<<endl;
	out<<"num_copy "<<num_cp<<endl;
	out<<"begin_parameter "<<endl;
	for(int t1=0; t1<num_cp; t1++)
	{
		for(int t2=0; t2<num_resource; t2++)
			out<<A[t1][t2]<<'\t'<<kx1[t1][t2]<<'\t'<<ky1[t1][t2]<<'\t'<<kx2[t1][t2]<<'\t'<<ky2[t1][t2]<<'\t'<<fhi1[t1][t2]<<'\t'<<fhi2[t1][t2]<<endl;
		out<<endl;
	}
}

void map :: load(ifstream& in)
{
	string tmp;
	in>>tmp>>num_resource;
	in>>tmp>>num_cp;
	A    = new double*[num_cp];
	kx1  = new double*[num_cp];
	ky1  = new double*[num_cp];
	kx2  = new double*[num_cp];
	ky2  = new double*[num_cp];
	fhi1 = new double*[num_cp];
	fhi2 = new double*[num_cp];
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
	in>>tmp;
	for(int t1=0; t1<num_cp; t1++)
	for(int t2=0; t2<num_resource; t2++)
		in>>A[t1][t2]>>kx1[t1][t2]>>ky1[t1][t2]>>kx2[t1][t2]>>ky2[t1][t2]>>fhi1[t1][t2]>>fhi2[t1][t2];
}

void map :: print()
{
	for(int t1=0; t1<num_resource; t1++)
		for(int t2=0; t2<num_cp; t2++)
			cout<<A[t2][t1]<<'\t'<<kx1[t2][t1]<<'\t'<<ky1[t2][t1]<<'\t'<<fhi1[t2][t1]<<'\t'<<ky2[t2][t1]<<'\t'<<kx2[t2][t1]<<'\t'<<fhi2[t2][t1]<<endl;
}
