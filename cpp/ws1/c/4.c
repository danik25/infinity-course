typedef struct  Person
{
   int age;
}Person;

typedef struct  List
{
   Person person;
}List;

void *foo(List *ll, int key, int age);



void *ll_find(List* ll, int key)
{
   ;
}
int main(void)
{
   List *ll;
   int key = 0;
   int age = 10;

   foo(ll, key, age);
}

void *foo(List *ll, int key, int age)
{
       void *vv = ll_find(ll, key);
       Person *p = (person*)ll;
       p->age = age;
}

/* static_cast<Person*>(vv); */