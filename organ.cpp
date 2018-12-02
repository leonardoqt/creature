#include <iostream>
#include <cstdlib>
#include "organ.h"
#include "ptn.h"

using namespace std;

organ :: organ()
{
	chain = nullptr;
	rate = nullptr;
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

