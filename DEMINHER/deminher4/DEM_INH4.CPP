///////////////////////////////////////////////////////////////
// DEM_INH4 -- demonstrates member functions with pass by    //
//             reference and pass by value                   //
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
    virtual base  fun1(base b);   // pass by value
    virtual base& fun2(base& b);  // pass by reference

  protected:
    int data;
};

class derived : public base {

  public:
    derived(void);
    derived(const derived &);
    derived(const base &);  // normally don't want to do this
    ~derived(void);
    derived& operator= (const derived& b);
     base fun1(base b);         // redefined func has same signature
    base& fun2(base &b);        // redefined func has same signature
     derived fun3(derived d);   // new function
    derived& fun4(derived &d);  // new function

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

//

//----< assignment >-------------------------------------------

base& base::operator= (const base& b) {
  if(this == &b) return *this;
  data = b.data;
  cout << "  base operator = called\n"; return *this;
}

//----< pass by value >----------------------------------------

base base::fun1(base b) {
  cout << "  base::fun1(base b) called\n";
  base temp; return temp;
}

//----< pass by reference >------------------------------------

base& base::fun2(base &b) {
  cout << "  base::fun2(base &b) called\n";
  return b;
}

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

//

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

//----< pass by value >----------------------------------------

base derived::fun1(base b) {
  cout << "  derived::fun1(base b) called\n";
  data = 0; base temp = *this; return temp;
}

//----< pass by reference >------------------------------------

base& derived::fun2(base &b) {
  cout << "  derived::fun2(base &b) called\n";
  return b;
}

//----< pass by value >----------------------------------------

derived derived::fun3(derived d) {
  cout << "  derived::fun3(derived d) called\n";
  derived temp = d; return temp;
}

//----< pass by reference >------------------------------------

derived& derived::fun4(derived &d) {
  cout << "  derived::fun4(derived &d) called\n";
  return d;
}

//----< show and tell >----------------------------------------

void message(char *s) {
  cout << endl << s << " executable statement of main\n";
}
/**/

void main() {

  message("1st");	base b1;
  message("2nd");	base b2 = b1;
  message("3rd");	b2 = b1.fun1(b1);
  message("4th");	b1 = b2.fun2(b1);

  message("5th");	derived d1;
  message("6th");	derived d2 = d1;
  message("7th"); b2 = d1.fun1(b1);
  cout << "\f\n";
  message("8th"); b2 = d1.fun1(d1);
  message("9th");	b1 = d2.fun2(b2);
  message("10th"); b1 = d2.fun2(d2);
  message("11th"); d1 = d2.fun3(d2);
  message("12th"); d1 = d2.fun4(d2);

// next function call won't compile without a
// base->derived constructor.  We can pass a derived to a base,
// as done above, but can't pass a base to a derived unless it
// is promotable, since the base is not a derived.

//                       d2.fun3(b1);
  message("no more");
}

// Note:
// The moral of this story is that an amazingly large amount of
// copying can result from simple pass by value operations,
// especially with derived class objects.  Look closely at
// statement 11 where rampant pass by value results in 15 sep-
// erate function calls.  Compare that with statement 12 which
// does nearly the same thing, but with pass by reference, result-
// ing in 3 function calls.
