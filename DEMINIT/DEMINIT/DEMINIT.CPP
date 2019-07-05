

///////////////////////////////////////////////////////////////
//  deminit.cpp - demonstrate initialization of various      //
//                types of data members                      //
///////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS  // here to allow us to demo buffer overrun

#include <iostream>    // cout, <<, >>
#include <cstdlib>     // exit()
#include <string>      // strlen(), strcpy()

//////////////////////////////////////////////////////
//  class Y objects used only as data member of X   //
//////////////////////////////////////////////////////

class Y {

  public:
    Y(int n=0)          { intMem = n;               }
    operator int ()     { return intMem;            }
    Y& operator=(int n) { intMem = n; return *this; }

  private:
    int intMem;
};


//////////////////////////////////////////////////////
//  class X demonstrates use of built-in types,     //
//  pointers, and references as data members        //
//////////////////////////////////////////////////////

class X {

  public:
    X(const X &x);
    X(int n, const char *str, Y &y);
    X& operator=(const X &x);

    const char* Str() { return ptrMem; }
            int Int() { return intMem; }
             Y& Ref() { return refMem; }
  private:
     int intMem;                   // built-in type
    char *ptrMem;                  // pointer to heap allocation
       Y &refMem;                  // reference to external object
    void alloc(const char *s);     // private function
};

//

////////////////////////////////////////
//   definition of member X members   //
////////////////////////////////////////


//----< private helper function >------------------------------

void X::alloc(const char *s) {

  ptrMem = new char[strlen(s)+1];  // calls killJob on failure
  strcpy(ptrMem,s);                // if we overrun allocation
}

//----< copy constructor >-------------------------------------

X::X(const X &x) : intMem(x.intMem), refMem(x.refMem) {

  alloc(x.ptrMem);
}

//----< constructor with value arguments >---------------------

X::X(int n, const char *s, Y &y) : intMem(n), refMem(y) {

  alloc(s);
}

//----< assignment >-------------------------------------------

X& X::operator=(const X &x) {

  if(this == &x) return *this;
  delete [] ptrMem;
  alloc(x.ptrMem);
  intMem = x.intMem;
  refMem = x.refMem;  // this changes the external object
                      // so don't do this unless that's what
                      // you and the object's owner both want
  return *this;
}

//

#include <new.h>   // set_new_handler

//----< private global function - announces errors >-----------

static void killJob() {

  std::cout << "\n  memory alloc failure\n"; exit(1);
}


//----< test stub >--------------------------------------------

int main(int, char *argv[]) {

  std::cout << "\n"
       << "-------------------------------------------------------\n"
       << " demonstrating member objects, pointers and references \n"
       << "-------------------------------------------------------\n";

  set_new_handler(killJob);

  Y y1(10);
  X x1(20,"this is a string",y1);

  std::cout << "\n  y1 object member: " << y1 << std::endl;
  std::cout <<   "  x1 object members:" << std::endl
            <<   "    Int(): " << x1.Int() << std::endl
            <<   "    Str(): " << x1.Str() << std::endl
            <<   "    Ref(): " << x1.Ref() << std::endl;

  Y y2(15);
  X x2(30,argv[0],y2);

  std::cout << "\n  y2 object member: " << y2 << std::endl;
  std::cout <<   "  x2 object members:" << std::endl
            <<   "    Int(): " << x2.Int() << std::endl
            <<   "    Str(): " << x2.Str() << std::endl
            <<   "    Ref(): " << x2.Ref() << std::endl;

  x1 = x2;

  std::cout << "\n  after assignment, x1 = x2:" << std::endl;
  std::cout << "\n  y1 object member: " << y1 << std::endl;
  std::cout <<   "  x1 object members:" << std::endl
            <<   "    Int(): " << x1.Int() << std::endl
            <<   "    Str(): " << x1.Str() << std::endl
            <<   "    Ref(): " << x1.Ref() << std::endl;


  std::cout << "\n  Paused to show output.  Press any key then enter to continue: ";
  char ch;
  std::cin >> ch;

///////////////////////////////////////////////////////////////
//  this part illustrates invocation of new handler, e.g.,   //
//  function killJob()                                       //
///////////////////////////////////////////////////////////////

  char *junk;
  int count = 0;
  const int big = 100000;

  while(1) {
    junk = new char[big];   // repeated allocation causes memory leak
                            // used to demonstrate error handling;
    std::cout << "\n  allocation #" << ++count;
  }
  return 0;
}
