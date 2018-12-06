#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "include.h"

using namespace std;

int main()
{
	// for map
	double A = 500, k1 = 0.04, k2 = 0.01, fhi = 3.14;
	int num_cp = 4;
	map m1;
	resource rr;
	ifstream in_map;
	ofstream out_map;

	in_map.open("map.dat");
	out_map.open("res_map.dat");
	m1.load(in_map);
	rr.init(m1.num_resource);


	for(int x=-1000; x<=1000; x+=50)
	for(int y=-1000; y<=1000; y+=50)
	{
		m1.value(x,y,rr);
		out_map<<x<<'\t'<<y<<'\t';
		out_map<<rr<<endl;
	}
	return 0;
}
