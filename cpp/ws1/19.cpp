#include <iostream> //class

struct X
{
    explicit X(); //intiailization function without parameters is named
                // default constructor (often abreviated as: Ctor)

    explicit X(int a_, int b_ = 8); //regular (non default) constructor

    ~X(); //deinitialization function is called destructor (Dtor)

    X(const X& other_); //copy intiailization function is called copy
                        //constructor or CCtor;
    X& operator = ( const X& other_ ); // assignemnt operator

    int m_a;
    int m_b;
};

struct  Y
{
	X m_x;
	int m_i;
    explicit Y();
};


X::X(): m_a(3), m_b(4) //implementation of the default Ctor. why the X::X?
                    //the code after the collon is called an initialization list
{
	std::cout<<"this:" <<this<< "X default Ctor. m_a:" << m_a
	  << " m_b:" << m_b << std::endl;
}

Y::Y(): m_x(), m_i(3) //ex 21
{
    std::cout<<"dani"<<std::endl;
}

X::X(int a_, int b_): m_a(a_), m_b(b_) //implementation of the second Ctor
{
	std::cout<<"this:" <<this<< "X int Ctor. m_a:" << m_a
	  << " m_b:" << m_b << std::endl;
}

X::X(const X& other_): m_a(other_.m_a), m_b(other_.m_b) //implementation of the 
														//copy Ctor
{
	std::cout<<"this:" <<this<< "X copy Ctor. m_a:" << m_a
	  << " m_b:" << m_b << std::endl;
}


X& X::operator=(const X& other_)
{
   m_a= other_.m_a;
   m_b= other_.m_b;
   std::cout<<"this: "<< this <<
       "    X assignment operator. m_a: "<< m_a <<
       " m_b: "<< m_b << std::endl;

   return *this;
}

X:: ~X()
{
   std::cout<<"this: "<< this <<
       "    X Dtor. m_a: "<< m_a <<
       " m_b: "<< m_b << std::endl;
}

int main()
{
   /*X x1;

   X x2(7);
   X* px= new X(x2);
   X x3(9,10);
   X x4(x1);

   x1 = x3;

   delete px;
   px = 0;

   X* xp = new X[10];
   delete []xp;*/

   Y y1;
   /*y1.m_x.m_a = 250;
   y1.m_x.m_b = 750;
   Y y2(y1);
   Y y3;

   y3 = y1;*/
   return 0;
}