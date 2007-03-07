#include "Resource.h"

Resource::Resource(string n)
{
	resourceName = n;
	amount = 0;
}

Resource::Resource(string n, int a)
{
	resourceName = n;
	amount = a;
}

