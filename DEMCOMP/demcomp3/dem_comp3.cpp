//////////////////////////////////////////////////////////////////
//  DEM_COMP3.CPP - demonstrates composition                    //
//                  initialization of arrays                    //
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
    composer(int x);
    virtual ~composer(void);
    composer& operator=(const composer& a);
    friend ostream& operator<<(ostream& ostrm, const composer& a);

  private:

    composed in1;
    composed in2;
};


//----< void constructor >-------------------------------------

composed::composed(void) {
  cout << "  composed void constructor called\n";
}

//----< copy constructor >-------------------------------------

composed::composed(const composed& b) : data(b.data) {
  cout << "  composed copy constructor called\n";
}

//

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
  if(this == &b) return *this;
  cout << "  composed operator= called\n";
  data = b.data;
  return *this;
}

//----< insertion >--------------------------------------------

ostream& operator<<(ostream& ostrm, const composed& b) {
  ostrm << b.data; return ostrm;
}

//----< void constructor >-------------------------------------

composer::composer(void) {
  cout << "  composer void constructor called\n";
}

//----< copy constructor >-------------------------------------

//  note initialization - it's more efficient

composer::composer(const composer &a) : in1(a.in1), in2(a.in2) {
  cout << "  composer copy constructor called\n";
}

//----< promotion constructor with initialization >------------

composer::composer(int size1, int size2) : in1(size1), in2(size2) {
  cout << "  composer(int,int) constructor called\n";
  cout << "    set in1 = " << in1 << endl;
  cout << "    set in2 = " << in2 << endl;
}

//----< promotion constructor taking only one argument >-------

composer::composer(int oneSize) : in1(oneSize), in2(oneSize) {
  cout << " composer(int) constructor called\n";
  cout << "   set in1 = " << in1 << endl;
  cout << "   set in2 = " << in2 << endl;
}

//

//----< destructor >-------------------------------------------

composer::~composer(void) {
  cout << "  composer destructor called\n";
}

//----< assignment >-------------------------------------------

composer& composer::operator=(const composer &a) {
  if(this == &a) return *this;
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

  message("1st");  	composer outer1;
  message("2nd");  	composer outer2(6,4);
  cout << "\f\n";
  message("3rd");       composer outer3[2];
  message("4th");   composer array[4] = { composer(), composer(7,-2), outer2 };
  message("5th");   composer();
  message("no more");
}

// in statement 4:
//   we defined an array of four elements and initialized
//   just the first three elements using default, promotion,
//   and copy constructors

//   the initialization uses explicit calls to the promotion
//   ctors composer(int,int) and composer().

//   the C++ language guarantees that any unitialized elements
//   are constructed using a void ctor for the array element
