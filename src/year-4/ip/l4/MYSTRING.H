class MyStr {
 char *c;
public:
 int operator <(MyStr);
 int operator >(MyStr);
 int operator ==(MyStr);
 MyStr& operator =(MyStr);
 MyStr(char *s);
 MyStr() { c = NULL; };
 MyStr(MyStr &s) { c = NULL; if (s.c) { c = (char*)malloc(strlen(s.c)+1); strcpy(c, s.c); } };
 ~MyStr();
};

int MyStr::operator<(MyStr s)
{
 return strcmp(c,s.c)<0;
}

int MyStr::operator >(MyStr s)
{
 return strcmp(c,s.c)>0;
}

int MyStr::operator ==(MyStr s)
{
 return strcmp(c,s.c)==0;
}

MyStr& MyStr::operator =(MyStr s)
{
 MyStr aux(s.c);
 if (c) delete c;
 c = (char*) malloc(strlen(aux.c)+1);
 //printf("in egal : %d\n",strlen(aux.c));
 strcpy(c,aux.c);
 return *this;
}

MyStr::MyStr(char *s)
{
 c = (char*)malloc(strlen(s)+1);
 strcpy(c,s);
}

MyStr::~MyStr(void)
{
 delete c;
}

