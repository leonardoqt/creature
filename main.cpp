#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "include.h"

using namespace std;

int main()
{
	srand(time(0));
//	srand(0);
	// initial param
	int ll = 300;
	int num_k = 4;
	int num_ptn = 20;
	int digit = 3;
	int num_organ = 90000;
	int len_gene = 9;
	int num_resource = 2;
	int num_creature_opt = 1000;
	int num_creature = num_creature_opt;
	int num_creature_next;
	// code
	code_dna cd1;
	code_ptn cp1;
	code_organ co1;
	// creature
	creature *being, *being_next;
	// born rate
	double *weight=nullptr;		// use living_advantage to calculate, propotional to (current-min+1)
	double weight_sum;
	int *num_born=nullptr;
	double max_la, min_la;
	// for map
	double A = 500, k1 = 0.004, k2 = 0.001, fhi = 3.14;
	int num_cp = 4;
	map m1;
	// for move
	int move_max = 10000;
	// for generation
	int gen_max = 400;
	// for load/save
	int ini_from_file = 0;

	ifstream in_cd;
	ifstream in_cp;
	ifstream in_co;
	ifstream in_dna;
	ifstream in_map;
	ofstream out_cd;
	ofstream out_cp;
	ofstream out_co;
	ofstream out_dna;
	ofstream out_map;

	cin>>ini_from_file;
	if (ini_from_file)
	{
		in_cd.open("code_dna.dat");
		in_cp.open("code_ptn.dat");
		in_co.open("code_organ.dat");
		in_dna.open("dna.dat");
		in_map.open("map.dat");

		cd1.load(in_cd);
		cp1.load(in_cp);
		co1.load(in_co);
		m1.load(in_map);
	}
	else
	{
		out_cd.open("code_dna.dat");
		out_cp.open("code_ptn.dat");
		out_co.open("code_organ.dat");
		out_dna.open("dna.dat");
		out_map.open("map.dat");

		cd1.init(num_k,num_ptn,digit);
		cp1.init(num_ptn, num_organ, len_gene);
		co1.init(num_organ, num_resource);
		m1.init(num_resource, num_cp, A, k1, k2, fhi);

		cd1.save(out_cd);
		cp1.save(out_cp);
		co1.save(out_co);
		m1.save(out_map);
	}

	// prepare for creatures
	being = new creature[num_creature];
	for(int t1=0; t1<num_creature; t1++)
	{
		being[t1].init(m1.num_resource,&cd1,&cp1,&co1);
		if (ini_from_file)
			being[t1].load_dna(in_dna);
		else
		{
			being[t1].dna_init(ll);
			being[t1].save_dna(out_dna);
		}
		being[t1].translate();
	}
	if (!ini_from_file)
		out_dna.close();
	out_dna.open("dna_last.dat");

	// the trip of one generation
	for(int t1=0; t1<num_creature; t1++)
	{
		for(int t2=0; t2<move_max; t2++)
			being[t1].travel(m1);
		being[t1].surviving();
//		cout<<being[t1].x<<'\t'<<being[t1].y<<endl;
	}
//	cout<<endl;

	for (int num_gen=0; num_gen<gen_max; num_gen++)
	{
		// get next generation
		if (weight != nullptr)
			delete[] weight;
		if (num_born != nullptr)
			delete[] num_born;
		weight = new double[num_creature];
		num_born = new int[num_creature];
		max_la = -1e10;
		min_la = 1e10;
		for(int t1=0; t1<num_creature; t1++)
		{
			if(being[t1].living_advantage > max_la)
				max_la = being[t1].living_advantage;
			if(being[t1].living_advantage < min_la)
				min_la = being[t1].living_advantage;
		}
		weight_sum = 0;
		for(int t1=0; t1<num_creature; t1++)
		{
			weight[t1] = being[t1].living_advantage - min_la+1;
			weight_sum += weight[t1];
		}
		for(int t1=0; t1<num_creature; t1++)
		{
			weight[t1] = weight[t1]/weight_sum*num_creature_opt;
		}
		for(int t1=0; t1<num_creature; t1++)
		{
			num_born[t1] = (int) weight[t1];
			if((rand()/(double)RAND_MAX) < weight[t1]-num_born[t1])
				num_born[t1]++;
		}
		// ready to spawn next generation
		num_creature_next = 0;
		for(int t1=0; t1<num_creature; t1++)
			num_creature_next += num_born[t1];
		being_next = new creature[num_creature_next];
		for(int t1=0,ind=0; t1<num_creature; t1++)
		{
			for(int t2=0; t2<num_born[t1]; t2++)
			{
				being[t1].spawn(being_next[ind]);
				ind++;
			}
		}
		// kill previous generation
		delete[] being;
		being = being_next;
		num_creature = num_creature_next;
	
		// test of new travel
		for(int t1=0; t1<num_creature; t1++)
		{
			for(int t2=0; t2<1000; t2++)
				being[t1].travel(m1);
			being[t1].surviving();
			cout<<being[t1].x<<'\t'<<being[t1].y<<'\t'<<num_gen<<endl;
		}
	}
	for(int t1=0; t1<num_creature; t1++)
		being[t1].save_dna(out_dna);
	return 0;
}
