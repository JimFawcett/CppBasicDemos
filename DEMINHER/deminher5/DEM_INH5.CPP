///////////////////////////////////////////////////////////////
// DEM_INH5 -- demonstrates polymorphism through pointers    //
//             and references to virtual member functions    //
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
    virtual base& fun1(base& b);

  protected:
    int data;
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
  cout << "  base operator = called\n"; return *this;
}

//----< pass by reference >------------------------------------

base& base::fun1(base &b) {
  cout << "  base::fun1(base &b) called\n";
  return b;
}

//

class derived : public base {

  public:
    derived(void);
    derived(const derived &);
    ~derived(void);
    derived& operator= (const derived& b);
     base& fun1(base &b);        // redefined func has same signature
  derived& fun2(derived &d);     // new function

  private:
    int moredata;
};

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
  cout << "  derived operator = called\n";

// cast to base assignment to assign base components
  ((base&) *this) = d;

// now assign derived components
  moredata = d.moredata;
  return *this;
}

//

//----< pass by reference >------------------------------------

base& derived::fun1(base &b) {
  cout << "  derived::fun1(base &b) called\n";
  return b;
}

//----< pass by reference >------------------------------------

derived& derived::fun2(derived &d) {
  cout << "  derived::fun2(derived &d) called\n";
  return d;
}

//----< show and tell >----------------------------------------

void message(char *s) {
  cout << endl << s << " executable statement of main\n";
}

void main() {

  message("1st");	      base b1; base *bpbo=&b1; base &brbo=b1;
  message("2nd");       base b2;
  message("3rd");       bpbo->fun1(b2);
  message("4th");       brbo.fun1(b2);

//   won't compile      bpbo->fun2(b1);
//  unknown to base     brbo.fun2(b1);

// polymorphic calls, e.g., derived redefined functions
// called through base class pointers and refs
  message("5th");	      derived d1; base *bpdo=&d1; base &brdo=d1;
  message("6th");	      bpdo->fun1(b2);
  message("7th");       brdo.fun1(b2);

// can call derived functions through derived pointers and refs
// but this doesn't polymorphism
  message("8th");       derived *dpdo=&d1; derived &drdo=d1;
  message("9th");	      dpdo->fun1(b2);
  message("10th");	    drdo.fun1(b2);
  message("11th");	    dpdo->fun2(d1);
  message("12th");      drdo.fun2(d1);

// compile error        derived *dpbo=&b1; derived &drbo=b1;
//   can't set derived ptr to base object
//   can't set derived ref to base object
// so these won't       dpdo->fun1(b2);
// work either    	    drdo.fun1(b2);

  message("no more");
}

//

// Note:
// The power of polymorphism is due to the way it decouples clients
// from derived class components.  The client needs to know the base
// class protocol but does not need to know the details that disting-
// uish one derived object from another.  In fact, the client may not
// even know it deals with anything other than base class objects.
