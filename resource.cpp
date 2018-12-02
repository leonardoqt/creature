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

void resource :: print()
{
	for(int t1=0; t1<num; t1++)
		cout<<list[t1]<<'\t';
	cout<<endl;
}
