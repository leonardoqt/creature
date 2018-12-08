#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include "creature.h"

using namespace std;

void creature :: init(int num_resource, code_dna* cdd, code_ptn* cpp, code_organ* coo)
{
	num_r = num_resource;
	cd = cdd;
	cp = cpp;
	co = coo;
	s_range.init(num_r);
	s_acc.init(num_r);
	s_num.init(num_r);
	m_acc.init(num_r);
	m_eff.init(num_r);
	c_c_cap.init(num_r);
	c_p_cap.init(num_r);
	cost.init(num_r);
	harm.init(num_r);
	stock.init(num_r);
	damage.init(num_r);
	// right now set default value for x,y to be zero
	//x = y = 0;
	// now set it between -100 and 100
	x = (rand()/(double)RAND_MAX*2-1)*100;
	y = (rand()/(double)RAND_MAX*2-1)*100;
} 

void creature :: dna_init(int length)
{
	dna0.init(cd->num_k,length);
}

void creature :: translate()
{
	resource s_range_max, s_acc_max;
	int ind;
	sensor *ps;
	mover *pm;
	collector *pc;
	double rr;	// rate from organ
	ptn0.translate(dna0,*cd);
	organ0.translate(ptn0,*cp);
	// may need more when introducing status;
	// Initialize status
	for(int t1=0; t1<num_r; t1++)
	{
		s_range.list[t1] = 0;
		s_acc.list[t1] = 0;
		s_num.list[t1] = 0;
		m_acc.list[t1] = 1;
		m_eff.list[t1] = 1;
		c_c_cap.list[t1] = 0;
		c_p_cap.list[t1] = 0;
		cost.list[t1] = 0;
		harm.list[t1] = 0;
	}
	// accumulate change
	s_range_max.init(num_r);
	s_acc_max.init(num_r);
	for(int t1=0; t1<organ0.num_organ; t1++)
	{
		// sensor
		if(organ0.chain[t1] < co->num_sensor)
		{
			ind = organ0.chain[t1];
			rr = organ0.rate[t1];
			ps = &(co->ss[ind]);
			s_range.list[ps->type] += ps->range * ps->acc * ps->num_check * rr*rr*rr;
			if (s_range_max.list[ps->type] < ps->range*rr)
				s_range_max.list[ps->type] = ps->range*rr;
			if (s_acc_max.list[ps->type] < ps->acc*rr)
				s_acc_max.list[ps->type] = ps->acc*rr;
			for(int t2=0; t2<num_r; t2++)
			{
				cost.list[t2] += ps->cost.list[t2]/rr;
				harm.list[t2] += ps->harm.list[t2]*rr;
			}
		}
		// mover
		else if (organ0.chain[t1] < co->num_sensor+co->num_mover)
		{
			ind = organ0.chain[t1] - co->num_sensor;
			rr = organ0.rate[t1];
			pm = &(co->mm[ind]);
			m_acc.list[pm->type] *= (1-pm->acc*rr);
			m_eff.list[pm->type] *= (1-pm->eff*rr);
			for(int t2=0; t2<num_r; t2++)
			{
				cost.list[t2] += pm->cost.list[t2]/rr;
				harm.list[t2] += pm->harm.list[t2]*rr;
			}
		}
		// collector
		else
		{
			ind = organ0.chain[t1] - co->num_sensor - co->num_mover;
			rr = organ0.rate[t1];
			pc = &(co->cc[ind]);
			if (pc->c_p == 1)
				c_c_cap.list[pc->type] += pc->cap*rr;
			else if (pc->c_p == -1)
				c_p_cap.list[pc->type] += pc->cap*rr;
			for(int t2=0; t2<num_r; t2++)
			{
				cost.list[t2] += pc->cost.list[t2]/rr;
				harm.list[t2] += pc->harm.list[t2]*rr;
			}
		}
	}
	// finalize status
	for(int t1=0; t1<num_r; t1++)
	{
		// for sensor
		if (s_range_max.list[t1]*s_acc_max.list[t1] > 0)
		{
			s_num.list[t1] = s_range.list[t1] / s_range_max.list[t1] / s_acc_max.list[t1];
			s_range.list[t1] = s_range_max.list[t1];
			s_acc.list[t1] = s_acc_max.list[t1];
		}
		else
		{
			s_num.list[t1] = 0;
			s_range.list[t1] = 0;
			s_acc.list[t1] = 0;
		}
		// for mover
		m_acc.list[t1] = 1 - m_acc.list[t1];
		m_eff.list[t1] = 1 - m_eff.list[t1];
	}
}

void creature :: travel(map& map0)
{
	double x_max,y_max,res_max;
	double x_tmp,y_tmp,res_tmp;
	double x_add,y_add;
	resource rr_tmp;
	rr_tmp.init(num_r);
	// loop for each type of resource
	for(int t1=0; t1<num_r; t1++)
	{
		// use sensor to search for most resource-abundent place
		map0.value(x,y,rr_tmp);
		res_max = rr_tmp.list[t1]*s_acc.list[t1]+(rand()/(double)RAND_MAX)*rr_tmp.list[t1]*(1-s_acc.list[t1]);
//		res_max = 0;
		x_max = 0;
		y_max = 0;
		for(int t2=0; t2<s_num.list[t1]; t2++)
		{
			// generate random search site
			x_add = (rand()/(double)RAND_MAX*2-1)*s_range.list[t1];
			y_add = (rand()/(double)RAND_MAX*2-1)*s_range.list[t1];
			while(sqrt(x_add*x_add+y_add*y_add) > s_range.list[t1])
			{
				x_add = (rand()/(double)RAND_MAX*2-1)*s_range.list[t1];
				y_add = (rand()/(double)RAND_MAX*2-1)*s_range.list[t1];
			}
			// get new xy
			x_tmp = x+x_add;
			y_tmp = y+y_add;
			// find value
			map0.value(x_tmp,y_tmp,rr_tmp);
			res_tmp = rr_tmp.list[t1]*s_acc.list[t1]+(rand()/(double)RAND_MAX)*rr_tmp.list[t1]*(1-s_acc.list[t1]);
			// greedy
			if(res_max < res_tmp)
			{
				res_max = res_tmp;
				x_max = x_add;
				y_max = y_add;
			}
		}
		// move itself to the place
		x_add = x_max*m_acc.list[t1]+(rand()/(double)RAND_MAX)*x_max*(1-m_acc.list[t1]);
		y_add = y_max*m_acc.list[t1]+(rand()/(double)RAND_MAX)*y_max*(1-m_acc.list[t1]);
		x = x + x_add*m_eff.list[t1];
		y = y + y_add*m_eff.list[t1];

		// take resource, suffer damage
		map0.value(x,y,rr_tmp);
		// collect current resource
		if (c_c_cap.list[t1] > rr_tmp.list[t1])
			stock.list[t1] += rr_tmp.list[t1];
		else
			stock.list[t1] += c_c_cap.list[t1];
		for(int t2=0; t2<num_r; t2++)
		{
			// cost resource as long as move
			stock.list[t2] -= cost.list[t2]/num_r;
			// damage is the remaining after guarded by c_p_cap
			if (c_p_cap.list[t2] < rr_tmp.list[t2])
				damage.list[t2] += rr_tmp.list[t2] - c_p_cap.list[t2];
		}
	}
//	for(int t1=0; t1<num_r; t1++)
//		cout<<stock.list[t1]<<'\t'<<damage.list[t1]<<'\t';
//	cout<<endl;
}

void creature :: surviving()
{
//	double max_living_chance = 1e10;
	double basic_chance = 0.01;
	living_advantage = 0;
	mutation_chance = 1;
	for(int t1=0; t1<num_r; t1++)
	{
		if (cost.list[t1] > 0)
			living_advantage += stock.list[t1] / cost.list[t1];
//		else
//			living_advantage += max_living_chance;
		mutation_chance += log(1+damage.list[t1])/log(10);
	}
	mutation_chance *= basic_chance;
}

void creature :: spawn(creature& baby)
{
	baby.init(num_r,cd,cp,co);
	baby.dna0 = dna0;
	baby.dna0.mutate(mutation_chance);
	baby.translate();
	baby.x = x;
	baby.y = y;
}

void creature :: save_dna(ofstream& out)
{
	dna0.save(out);
}

void creature :: load_dna(ifstream& in)
{
	dna0.load(in);
}

void creature :: print()
{
//	dna0.print_chain();
//	ptn0.print_chain();
//	organ0.print_chain();
//	cout<<endl;
	cout<<"Final search range: ----------"<<endl;
	s_range.print();
	cout<<"Final search accuracy: ----------"<<endl;
	s_acc.print();
	cout<<"Final check times: ---------"<<endl;
	s_num.print();
	cout<<endl;
	cout<<"Final move accuracy: ------------"<<endl;
	m_acc.print();
	cout<<"Final move boost: --------------"<<endl;
	m_eff.print();
	cout<<endl;
	cout<<"Final collector: ------------"<<endl;
	c_c_cap.print();
	cout<<"Final protector: ------------"<<endl;
	c_p_cap.print();
	cout<<endl;
	cout<<"Final cost: -------------"<<endl;
	cost.print();
	cout<<"Final harm: -------------"<<endl;
	harm.print();
}
