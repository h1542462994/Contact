#include "ContactGroup.h"

bool contactComparerByGroup(Contact* p1, Contact* p2)
{
	return p1->type < p2->type;
}

bool contactComparerByName(Contact* p1, Contact* p2)
{
	return p1->name < p2->name;
}

bool contactComparerByPhone(Contact* p1, Contact* p2)
{
	return p1->phone < p2->phone;
}

bool contactComparerByAddress(Contact* p1, Contact* p2)
{
	return p1->address < p2->address;
}
