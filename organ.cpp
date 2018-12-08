#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include "organ.h"
#include "ptn.h"

using namespace std;

organ :: organ()
{
	chain = nullptr;
	rate = nullptr;
}

organ :: ~organ()
{
	if (chain != nullptr)
		delete[] chain;
	if (rate != nullptr)
		delete[] rate;
}

void organ :: translate(ptn& ptn0, code_ptn& code)
{
	int dis_min, dis_current;
	int ind_min;
	if (chain != nullptr)
		delete [] chain;
	if (rate != nullptr)
		delete [] rate;

	num_organ = ptn0.length / code.num_digit;
	chain = new int [num_organ];
	rate = new double [num_organ];

	// find each organ using "distance"
	for(int t1=0; t1<num_organ; t1++)
	{
		// for each possible organ in code, find dis
		dis_min = code.num_ptn*code.num_digit;
		ind_min = -1;
		for(int t2=0; t2<code.num_organ; t2++)
		{
			// calculate distance
			dis_current = 0;
			for(int t3=0; t3<code.num_digit; t3++)
				if (ptn0.chain[t1*code.num_digit+t3] == code.code[t2][t3])
					dis_current -= code.num_ptn;
				else
					dis_current += abs(ptn0.chain[t1*code.num_digit+t3] - code.code[t2][t3]);
			if (dis_current < dis_min)
			{
				dis_min = dis_current;
				ind_min = t2;
			}
		}
		chain[t1] = ind_min;
		rate[t1] = 0;
		for(int t2=0; t2<code.num_digit; t2++)
			if (ptn0.chain[t1*code.num_digit+t2] != code.code[chain[t1]][t2])
				rate[t1] += 1;
		rate[t1] = 1 - rate[t1] / (code.num_digit+1);
	}
}


void organ :: print_chain()
{
	cout<<"Print organ info:"<<endl;
	for(int t1=0; t1<num_organ; t1++)
		cout<<chain[t1]<<'\t'<<rate[t1]<<endl;
}


//===========================sensor========================
void sensor :: init(int nn)
{
	double base_cost, base_harm;
	double rarity = pow((rand()+1)/(double)RAND_MAX,4);
	int t1;
	cost.init(nn);
	harm.init(nn);
	type = rand()%nn;
	range = rarity*100 + (1-rarity)*((rand()+1)/(double)RAND_MAX)*100;			// 0-100
	num_check = (int)(rarity*10) + (int)((1-rarity)*(rand()%10)) + 1;			// 1-10
	acc = rarity + (1-rarity)*((rand()+1)/(double)RAND_MAX);						// 0-1
	// range influence base cost and harm
	// num_check influence base cost
	// acc influence base harm
	// each organ only need and sufer from one
	base_cost = range*0.25 + num_check*2.5;
	base_harm = range*0.25 + acc * 25;
	t1 = rand()%nn;
	cost.list[t1] = base_cost + (rand()+1)/(double)RAND_MAX * (100-base_cost);
	t1 = rand()%nn;
	harm.list[t1] = base_harm + (rand()+1)/(double)RAND_MAX * (100-base_harm);
}

void sensor :: print()
{
	cout<<"Print sensor:--------------"<<endl;
	cout<<"Type: "<<type<<endl;
	cout<<"Range: "<<range<<endl;
	cout<<"Check times: "<<num_check<<endl;
	cout<<"Accuracy: "<<acc*100<<"%"<<endl;
	cout<<"Cost: ";
	cost.print();
	cout<<"Harm: ";
	harm.print();
}

//=========================mover============================
void mover :: init(int nn)
{
	double base_cost, base_harm;
	double rarity = pow((rand()+1)/(double)RAND_MAX,4);
	int t1;
	cost.init(nn);
	harm.init(nn);
	type = rand()%nn;
	acc = rarity + (1-rarity)*((rand()+1)/(double)RAND_MAX);
	eff = rarity + (1-rarity)*((rand()+1)/(double)RAND_MAX);
	base_cost = eff * 50;
	base_harm = acc * 50;
	t1 = rand()%nn;
	cost.list[t1] = base_cost + (rand()+1)/(double)RAND_MAX * (100-base_cost);
	t1 = rand()%nn;
	harm.list[t1] = base_harm + (rand()+1)/(double)RAND_MAX * (100-base_harm);
}

void mover :: print()
{
	cout<<"Print mover:--------------"<<endl;
	cout<<"Type: "<<type<<endl;
	cout<<"Accuracy: "<<acc*100<<"%"<<endl;
	cout<<"Efficiency: "<<eff*100<<"%"<<endl;
	cout<<"Cost: ";
	cost.print();
	cout<<"Harm: ";
	harm.print();
}

//========================collector=========================
void collector :: init(int nn)
{
	double base_cost, base_harm;
	double rarity = pow((rand()+1)/(double)RAND_MAX,4);
	int t1;
	cost.init(nn);
	harm.init(nn);
	type = rand()%nn;
	c_p = (rand()%2)*2-1;
	cap = (rarity + (1-rarity)*((rand()+1)/(double)RAND_MAX)) * 5000;
	base_cost = base_harm = cap / 20;
	t1 = rand()%nn;
	cost.list[t1] = base_cost + (rand()+1)/(double)RAND_MAX * (100-base_cost);
	t1 = rand()%nn;
	harm.list[t1] = base_harm + (rand()+1)/(double)RAND_MAX * (100-base_harm);
}

void collector :: print()
{
	cout<<"Print collector:--------------"<<endl;
	cout<<"Type: "<<type<<endl;
	cout<<"C or P: "<<c_p<<endl;
	cout<<"Effect: "<<cap<<endl;
	cout<<"Cost: ";
	cost.print();
	cout<<"Harm: ";
	harm.print();
}

//==========================code_organ========================
void code_organ :: init(int num, int num_signal)
{
	num_resource = num_signal;
	num_organ = num;
	num_sensor = num_mover = num / 3;
	num_collector = num_organ - num_sensor - num_mover;
	ss = new sensor[num_sensor];
	mm = new mover[num_mover];
	cc = new collector[num_collector];
	for(int t1=0; t1<num_sensor; t1++)
		ss[t1].init(num_signal);
	for(int t1=0; t1<num_mover; t1++)
		mm[t1].init(num_signal);
	for(int t1=0; t1<num_collector; t1++)
		cc[t1].init(num_signal);
}

void code_organ :: save(ofstream& out)
{
	out<<"num_resource "<<num_resource<<endl;
	out<<"num_organ "<<num_organ<<endl;
	out<<"num_sensor "<<num_sensor<<endl;
	out<<"num_mover "<<num_mover<<endl;
	out<<"num_collector "<<num_collector<<endl;
	out<<"begin_code"<<endl;
	for(int t1=0; t1<num_sensor; t1++)
	{
		out<<"sensor_"<<t1<<'_'<<t1<<endl;
		out<<ss[t1].type<<'\t'<<ss[t1].range<<'\t'<<ss[t1].num_check<<'\t'<<ss[t1].acc<<endl;
		out<<ss[t1].cost<<endl;
		out<<ss[t1].harm<<endl;
	}
	for(int t1=0; t1<num_mover; t1++)
	{
		out<<"mover_"<<t1<<'_'<<t1+num_sensor<<endl;
		out<<mm[t1].type<<'\t'<<mm[t1].acc<<'\t'<<mm[t1].eff<<endl;
		out<<mm[t1].cost<<endl;
		out<<mm[t1].harm<<endl;
	}
	for(int t1=0; t1<num_collector; t1++)
	{
		out<<"collector_"<<t1<<'_'<<t1+num_sensor+num_mover<<endl;
		out<<cc[t1].type<<'\t'<<cc[t1].c_p<<'\t'<<cc[t1].cap<<endl;
		out<<cc[t1].cost<<endl;
		out<<cc[t1].harm<<endl;
	}
}

void code_organ :: load(ifstream& in)
{
	string tmp;
	in>>tmp>>num_resource;
	in>>tmp>>num_organ;
	in>>tmp>>num_sensor;
	in>>tmp>>num_mover;
	in>>tmp>>num_collector;
	ss = new sensor[num_sensor];
	mm = new mover[num_mover];
	cc = new collector[num_collector];
	for(int t1=0; t1<num_sensor; t1++)
		ss[t1].init(num_resource);
	for(int t1=0; t1<num_mover; t1++)
		mm[t1].init(num_resource);
	for(int t1=0; t1<num_collector; t1++)
		cc[t1].init(num_resource);
	in>>tmp;
	for(int t1=0; t1<num_sensor; t1++)
	{
		in>>tmp;
		in>>ss[t1].type>>ss[t1].range>>ss[t1].num_check>>ss[t1].acc;
		in>>ss[t1].cost;
		in>>ss[t1].harm;
	}
	for(int t1=0; t1<num_mover; t1++)
	{
		in>>tmp;
		in>>mm[t1].type>>mm[t1].acc>>mm[t1].eff;
		in>>mm[t1].cost;
		in>>mm[t1].harm;
	}
	for(int t1=0; t1<num_collector; t1++)
	{
		in>>tmp;
		in>>cc[t1].type>>cc[t1].c_p>>cc[t1].cap;
		in>>cc[t1].cost;
		in>>cc[t1].harm;
	}
}

void code_organ :: print()
{
	cout<<"Sensor: ========================="<<endl;
	for(int t1=0; t1<num_sensor; t1++)
		ss[t1].print();
	cout<<"Mover: ========================="<<endl;
	for(int t1=0; t1<num_sensor; t1++)
		mm[t1].print();
	cout<<"Collector: ========================="<<endl;
	for(int t1=0; t1<num_sensor; t1++)
		cc[t1].print();
}
