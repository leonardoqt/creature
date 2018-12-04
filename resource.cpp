#include <iostream>
#include "resource.h"

using namespace std;
resource :: resource()
{
	num = 0;
	list = nullptr;
}

resource :: ~resource()
{
	if (list != nullptr)
		delete[] list;
}

void resource  :: init(int nn)
{
	num = nn;
	list = new double[nn];
	for(int t1=0; t1<nn; t1++)
		list[t1] = 0;
}

void resource :: clean()
{
	for(int t1=0; t1<num; t1++)
		list[t1] = 0;
}

ofstream& operator<<(ofstream& out, resource& A)
{
	for(int t1=0; t1<A.num; t1++)
		out<<A.list[t1]<<'\t';
	return out;
}

ifstream& operator>>(ifstream& in, resource& A)
{
	for(int t1=0; t1<A.num; t1++)
		in>>A.list[t1];
	return in;
}

void resource :: print()
{
	for(int t1=0; t1<num; t1++)
		cout<<list[t1]<<'\t';
	cout<<endl;
}
