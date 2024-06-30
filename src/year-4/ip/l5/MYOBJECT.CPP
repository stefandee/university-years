#include <string.h>
#include "myobject.h"

int operator==(Object& o1, Object& o2)
{
 return (!strcmp(o1.nameOf(),o2.nameOf())&&o1.isEqual(o2));
}

int operator!=(Object& o1, Object& o2)
{
 return (strcmp(o1.nameOf(),o2.nameOf()) || !o1.isEqual(o2));
}
