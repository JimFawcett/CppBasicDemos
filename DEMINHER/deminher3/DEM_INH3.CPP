
///////////////////////////////////////////////////////////////
// DEM_INH3 -- demonstrates derivation with base to derived  //
//             promotion constructor                         //
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

//----< base to derived promotion constructor >----------------

//  this weird promotion makes assigning bases to deriveds a
//  valid operation - probably not to sensible for most classes

derived::derived(const base &b) : base(b), moredata(0) {
  cout << "  base to derived promotion constructor called\n";
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

  message("7th");       d2 = b1;
//         now compiles because there is a way to build
//         a derived object from base object

  message("8th");	b1 = d2;
  message("no more");
}

// Note:
// Now the assignment of base to derived works because there is
// a way to build a derived object from a base.  When the compiler
// encounters the 7th statement in main() it observes the assign-
// ment type mismatch and finds a way to resolve it - by calling
// the base to derived constructor to build a temporary derived
// object from the base object on the right.  The temporary then
// gets assigned to the derived on the left.
//
// Note the destruction of the derived temporary at the end of the
// 7th statement.

