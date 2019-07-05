///////////////////////////////////////////////////////////////
//  equiv.cpp - demonstrates syntax equivalences             //
//                                                           //
//  Jim Fawcett, CSE687, Spring 2003                         //
///////////////////////////////////////////////////////////////
//
//  Note that the member function implementations for class X 
//  are non-functional.  All they do is to announce themselves
//  so you can see when they are called.  Thus, assignment has
//  no affect on the assignee's state - not the usual behavior.

#include <iostream>
using namespace std;

class X {
  public:
    X();                              // void ctor
    X(const X &x);                    // copy ctor
    ~X();                             // dtor
    X& operator=(const X &x);         // assignment operator
    void speak(const std::string& s); // member function
  private:
    static int count;                 // this many objects so far    - shared
    int myCount;                      // my place in object sequence - unique
};

int X::count = 0;                     // static data members must be
                                      // initialized this way

//----< void ctor >--------------------------------------------

X::X() : myCount(++count) { cout << "  void ctor of object #" << myCount << "\n"; }

//----< copy ctor - nothing to copy for these objects >--------

X::X(const X &x) : myCount(++count) { cout << "  copy ctor of object #" << myCount << "\n"; }
   
//----< dtor >-------------------------------------------------

X::~X() { cout << "  dtor of object #" << myCount << "\n"; }

//----< assignment - nothing to assign for these objects >-----

X& X::operator=(const X &x) {
  if(this==&x) return *this;
  cout << "  assignment operator\n";
  return *this;
}

//----< display count >----------------------------------------

void X::speak(const std::string& msg) 
{
  cout << "    " << msg.c_str() << " - object #" 
       << myCount << " speaking" << endl;
}

//

//====< test stub >============================================

void main() {

  cout << "\n   demonstration of equivalent syntaxes "
       << "\n  ======================================\n";

//----< 6 different ways of calling void constructor >---------

    X x1;               // void construction calls X();
    x1.speak("x1");

    X().speak("anonymous");        // creating anonomous temporary with void ctor

//  X x2();             // interpreted as a function declaration
//  x2.speak();

    X x3[2];            // void construction calls X() twice
    x3[0].speak("x3[0]");
    x3[1].speak("x3[1]");

    X* ptr = new X;     // void construction calls X();
    ptr->speak("on heap");
    delete ptr;         // destructor calls ~X()
    ptr = new X();
    ptr->speak("on heap again");
    delete ptr;

    ptr = new X[2];     // void construction calls X() twice
    ptr->speak("X[0] on heap");
    (ptr+1)->speak("X[1] on heap");   
    delete [] ptr;      // destructor called on ptr[0] and ptr[1];

//----< 4 different ways of calling copy constructor >---------

    X x4 = x1;          // copy construction calls X(const X &x);
    x4.speak("x4");

    X x5(x1);           //  "        "         "        "
    x5.speak("x5, copy of x1");

    X x6[2] = {x1,x4};  //  "        "         "        "  twice
    x6[0].speak("x6[0], copy of x1");
    x6[1].speak("x6[1], copy of x4");

    ptr = new X(x1);    //  "        "         "        "
    ptr->speak("copy of x1 on heap");
    delete ptr;         // destructor calls ~X()

//  ptr = new X(x1)[2];        // can't copy into heap array this way
//  ptr = new X[2] = {x1,x2};  // this doesn't work either

//----< equivalent ways of calling an operator >---------------

    x5 = x1;            // assignment calls X& operator(const X &x);
    x5.operator=(x1);   //     "        "   "         "

}
