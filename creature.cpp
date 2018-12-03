#include <iostream>
#include "creature.h"

using namespace std;

void creature :: init(int num_resource, code_dna& cdd, code_ptn& cpp, code_organ& coo)
{
	num_r = num_resource;
	cd = &cdd;
	cp = &cpp;
	co = &coo;
	s_range.init(num_r);
	s_acc.init(num_r);
	s_num.init(num_r);
	m_acc.init(num_r);
	m_eff.init(num_r);
	c_c_cap.init(num_r);
	c_p_cap.init(num_r);
	cost.init(num_r);
	harm.init(num_r);
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
			s_num.list[t1] = s_range.list[t1] / s_range_max.list[t1] / s_acc_max.list[t1] + 1;
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
