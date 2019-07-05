///////////////////////////////////////////////////////////////
// DEM_IN2B -- demonstrates derivation with ctor initializa- //
//             tion sequences and derived assignment with    //
// Ver 1.1     explicit invocation of base assignment        //
///////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

class base {

  public:

  // virtual constructors not allowed - not inherited
    base(void);
    base(const base &);
    virtual ~base(void);

  // virtual operator= not needed as operator= is not inherited
    base& operator= (const base& b);

  private:
    int data;
};

class derived : public base {

  public:
    derived(void);
    derived(const derived &);
    derived(const base &);  // normally don't want to do this
    ~derived(void);
    derived& operator= (const derived& b);

  private:
    int moredata;
};


//----< void constructor >-------------------------------------

base::base(void)   { cout << "  base void constructor called\n"; }


//----< copy constructor >-------------------------------------

base::base(const base &b) : data(b.data) {
  cout << "  base copy constructor called\n";
}

//----< destructor >-------------------------------------------

base::~base(void)  { cout << "  base destructor called\n"; }


//----< assignment >-------------------------------------------

base& base::operator= (const base& b) {
  if(this == &b) return *this;
  data = b.data;
  cout << "  base operator= called\n"; return *this;
}

//

//----< void constructor >-------------------------------------

derived::derived(void) {
  cout << "  derived void constructor called\n";
}

//----< copy constructor >-------------------------------------

//  Processing:
//    derived copy explicitly calls base copy as initialization

derived::derived(const derived &d) : base(d), moredata(d.moredata) {
  cout << "  derived copy constructor called\n";
}

//----< destructor >-------------------------------------------

derived::~derived(void) {
  cout << "  derived destructor called\n";
}

//----< assignment >-------------------------------------------

//  Processing:
//    derived assignment does not call base assignment operator
//    unless you specifically ask it to.  This examples works
//    even if base has only compiler generated default assignment.

derived& derived::operator= (const derived& d) {
  if(this == &d) return *this;
  cout << "  derived operator= called\n";

// cast to base assignment to assign base components
  ((base&) *this) = d;

// now assign derived components
  moredata = d.moredata;
  return *this;
}

//----< show and tell >----------------------------------------

void message(char *s) {
  cout << endl << s << " executable statement of main\n";
}

/**/

void main() {

  message("1st");	base b1;
  message("2nd");	base b2 = b1;
  message("3rd");	b1 = b2;

  message("4th");	derived d1;
  message("5th");	derived d2 = d1;
  message("6th");	d1 = d2;

//                      d2 = b1;
//      won't compile without a base to derived promotion ctor

  message("7th");	b1 = d2;
  message("no more");
}

// Note:
// Now both the major problems, observed in dem_inh2.cpp, have been
// fixed.
// - Here, the derived copy constructor explicitly initializes
//   the base object in the initialization sequence, along with
//   the derived data element - this is the right way to do both.
// - The assignment of one derived object to another now works
//   because the derived assignment operator explicitly calls the
//   base assignment operator.
