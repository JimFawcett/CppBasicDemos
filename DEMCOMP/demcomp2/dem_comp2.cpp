//////////////////////////////////////////////////////////////////
//  DEM_COMP2.CPP - demonstrates composition                    //
//                  knows how to copy, assign, and destroy      //
//                  uses inefficient copy ctor design           //
//////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

class composed {

  public:

    composed(void);
    composed(const composed& b);
    composed(int x);
    virtual ~composed(void);
    composed& operator= (const composed& b);
    friend ostream& operator<<(ostream& ostrm, const composed& b);

  private:

    int data;
};

class composer {

  public:

    composer(void);
    composer(const composer &a);
    composer(int x1, int x2);
    virtual ~composer(void);
    composer& operator=(const composer& a);
    friend ostream& operator<<(ostream& ostrm, const composer& a);

  private:

    composed in1;
    composed in2;
};
//

//----< void constructor >-------------------------------------

composed::composed(void) {
  cout << "  composed void constructor called\n";
}

//----< copy constructor >-------------------------------------

composed::composed(const composed& b) : data(b.data) {
  cout << "  composed copy constructor called\n";
}

//----< promotion constructor >--------------------------------

composed::composed(int x) : data(x) {
  cout << "  composed(int) constructor called\n";
  cout << "    set data = " << data << "\n";
}

//----< destructor >-------------------------------------------

composed::~composed(void) {
  cout << "  composed destructor called\n";
}

//----< assignment >-------------------------------------------

composed& composed::operator= (const composed& b) {
  if(this==&b) return *this;
  cout << "  composed operator= called\n";
  data = b.data;
  return *this;
}

//----< insertion >--------------------------------------------

ostream& operator<<(ostream& ostrm, const composed& b) {
  ostrm << b.data; return ostrm;
}

//
//----< void constructor >-------------------------------------

composer::composer(void) {
  cout << "  composer void constructor called\n";
}

//----< copy constructor >-------------------------------------

// this copy method is not efficient - see dem_ag2b

composer::composer(const composer &a) {
  cout << "  composer copy constructor called\n";
  in1 = a.in1;
  in2 = a.in2;
}

//----< promotion constructor with initialization >------------

composer::composer(int size1, int size2) : in1(size1), in2(size2) {
  cout << "  composer(int,int) constructor called\n";
  cout << "    set in1 = " << in1 << endl;
  cout << "    set in2 = " << in2 << endl;
}

//----< destructor >-------------------------------------------

composer::~composer(void) {
  cout << "  composer destructor called\n";
}

//----< assignment >-------------------------------------------

composer& composer::operator=(const composer &a) {
  if(this==&a) return *this;
  cout << "  composer operator= called\n";
  in1 = a.in1;
  in2 = a.in2;
  return *this;
}

//----< annunciator >------------------------------------------

void message(char *s) {
  cout << endl << s << " executable statement of main\n";
}

void main() {  //----------------------------------------------

  message("1st");  	composed inner1;
  message("2nd");  	composed inner2 = inner1;
  message("3rd");  	inner1 = inner2;

  message("4th");  	composer outer1;
  message("5th");  	composer outer2(6,4);
  message("6th");     composer outer3 = outer1;
  message("7th");  	outer3 = outer2;
  message("no more");
}

//

//  now, composer has a copy ctor, assignment oper, and a dtor
//       - we see them being called in 6th statement, 7th
//         statement, and in the destruction sequence

//  one issue of note here:
//    if you compare composer source code for copy ctor and
//    annunciations you will see that when composer does a copy
//    construction it's elements are first constructed with
//    void ctor, then assigned with composed operator=()

//  there is a better way - see dem_comp2b
