#include <iostream.h>
#include <values.h>
#include "myint.h"

void Integer::printOn()
{
 cout << data;
}

Integer operator+(Integer& i1,Integer& i2)
{
 return Integer(i1.data+i2.data);
}

Integer operator-(Integer& i1,Integer& i2)
{
 return Integer(i1.data-i2.data);
}

Integer operator*(Integer& i1,Integer& i2)
{
 return Integer(i1.data*i2.data);
}

Integer operator/(Integer& i1,Integer& i2)
{
 if(i2.data)return Integer(i1.data/i2.data);
 else return Integer(MAXINT);
}
