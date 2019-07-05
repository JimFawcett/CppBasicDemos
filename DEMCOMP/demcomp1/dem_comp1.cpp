///////////////////////////////////////////////////////////////
//  DEM_COMP1.CPP - demonstrates composition,                //
//                  compiler generated copy constructor and  //
//                  compiler generated assignment operator   //
///////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

class composed {

  public:

    composed(void);
    composed(const composed& b);
    composed(int x);
    virtual ~composed(void);
    composed& operator= (const composed& b);
    friend ostream& operator<<(ostream& ostrm, composed& b);

  private:

    int data;
};

class composer {

  public:

    composer(void);
    composer(int x1, int x2);
  // no copy constructor defined yet
  // no operator=() defined yet
  // no destructor defined

  private:

    composed in1;    //  can't initialize as shown below
    composed in2;    //    composed in2(5);   compile error
                     //    composed in2 = 5;     "      "
};
//

//----< void constructor >-------------------------------------

composed::composed(void) { cout << "  composed void constructor called\n"; }

//----< copy constructor >-------------------------------------

composed::composed(const composed& b) : data(b.data) {    // note initialization
  cout << "  composed copy constructor called\n";
}

//----< promotion constructor >--------------------------------

composed::composed(int x) : data(x) {   // note initialization
  cout << "  composed(int) constructor called\n";
  cout << "    set data = " << data << "\n";
}

//----< destructor >-------------------------------------------

composed::~composed(void) { cout << "  composed destructor called\n"; }

//----< assignment >-------------------------------------------

composed& composed::operator= (const composed& b) {
  if(this == &b) return *this;
  cout << "  composed operator= called\n";
  data = b.data;
  return *this;
}

//----< insertion >--------------------------------------------

ostream& operator<<(ostream& ostrm, composed& b) {
  ostrm << b.data; return ostrm;
}

//----< void constructor >-------------------------------------

composer::composer(void) { cout << "  composer void constructor called\n"; }
  // no operator= defined yet
  // no copy constructor defined for composer

//----< promotion constructor with initialization >------------

composer::composer(int size1, int size2) : in1(size1), in2(size2) {
  cout << "  composer(int,int) constructor called\n";
  cout << "    set in1 = " << in1 << endl;
  cout << "    set in2 = " << in2 << endl;
}

// no destructor defined for composer

//----< annunciator >------------------------------------------

void message(char *s) {
  cout << endl << s << " executable statement of main\n";
}
/**/

void main() {  //----------------------------------------------

  message("1st");  	composed inner1;
  message("2nd");  	composed inner2 = inner1;
  message("3rd");  	inner1 = inner2;

  message("4th");  	composer outer1;
  message("5th");  	composer outer2(6,4);
  message("6th");       composer outer3 = outer1;   // no copy ctor
  message("7th");  	    outer3 = outer2;            // no assignment oper
  message("no more");
}

//  in 6th statement a compiler generated copy ctor does element
//             by element copy of composer's data - first inner1 then inner2

//  in 7th statement a compiler generated assignment operator does
//             element by element assignment

//  first two destructions are inner1 and inner2

//  now composed dtors are called by compiler generated composer dtor
//    next two are outer1's data elements
//    next two are outer2's data elements
//    last two are outer3's data elements
