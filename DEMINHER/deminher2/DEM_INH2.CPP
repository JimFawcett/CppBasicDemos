///////////////////////////////////////////////////////////////
// DEM_INH2 -- demonstrates derivation with derived          //
//             constructors, destructor, and operator=()     //
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
    ~derived(void);
    derived& operator= (const derived& b);
  private:
    int moredata;
};


//---- implementations ----------------------------------------

base::base(void)   { cout << "  base void constructor called\n"; }

//-------------------------------------------------------------

base::base(const base &b) {
  data = b.data; cout << "  base copy constructor called\n";
}

//-------------------------------------------------------------

base::~base(void)  { cout << "  base destructor called\n"; }

//-------------------------------------------------------------

base& base::operator= (const base& b) {
  if(this == &b) return *this;
  cout << "  base operator= called\n"; 
  data = b.data; return *this;
}

//

//-------------------------------------------------------------

derived::derived(void) {
  cout << "  derived void constructor called\n"; }

//---- serious problem here - no initialization ---------------

derived::derived(const derived &d) {
  moredata = d.moredata;
  cout << "  derived copy constructor called\n";
}

//-------------------------------------------------------------

derived::~derived(void) { cout << "  derived destructor called\n"; }

//---- another serious problem here - no base assignment ------

derived& derived::operator= (const derived& b) {
  if(this == &b) return *this;
  moredata = b.moredata;
  cout << "  derived operator= called\n"; return *this;
}

//-------------------------------------------------------------

void message(char *s) {
  cout << endl << s << " executable statement of main\n";
}
/**/

void main() {  //----------------------------------------------

  message("1st");	base b1;
  message("2nd");	base b2 = b1;
  message("3rd");	b1 = b2;

  message("4th");	derived d1;
  message("5th");	derived d2 = d1;
  message("6th");	d1 = d2;

//                      d2 = b1;
//        won't compile without a b1 promotion constructor

  message("7th");	b1 = d2;
  message("no more");
}

// Note:
// There are two major problems here:
// - The derived constructor constructor has compiler generated code
//   to call a base constructor - unfortunately it's the base void
//   constructor, not the base copy constructor as you would have
//   expected, so the base element did not get copied.
// - The derived assignment operator was called, but the compiler did
//   not generate code to call the base assignment, as you might have
//   supposed in view of the way constructors work.
//
// We show in the next demo how to take care of both of these problems.
