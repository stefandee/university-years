#include "mystring.h"

String& String::operator=(String& v)
{
 String x=v;
 if(data)
 {
  delete data;
  data=NULL;
 }
 if(x.data)
 {
  data=(char*)malloc(strlen(x.data)+1);
  strcpy(data,x.data);
 }
 return *this;
}

String operator+(String& s1,String& s2)
{
 char *s;
 s=(char*)malloc(strlen(s1.data)+1+strlen(s2.data));
 strcpy(s,s1.data);
 strcat(s,s2.data);
 return String(s);
}

int operator<=(String& s1,String& s2)
{
 char *s;
 /*
 int l,pos=0;
 l=strlen(s2.data);
 s=(char*)malloc(strlen(s1.data)+1);
 strcpy(s,s1.data);
 for(pos=0;s;pos++)
 {
  if(!strncmp(s,s2.data,l)) return pos;
  s=s+1;
 }
 return -1;*/
 if ((s = strstr(s1.data, s2.data)) != NULL)
 {
    return s-s1.data+1;
 }
 return -1;
}
