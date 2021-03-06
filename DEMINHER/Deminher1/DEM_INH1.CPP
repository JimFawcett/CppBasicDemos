///////////////////////////////////////////////////////////////
//  DEM_INH1.CPP -- demonstrates derivation without derived  //
//                  constructors, destructor, operator=()    //
///////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

class base {
  public:
    base(void);
    base(const base &);

  // always use virtual destructors for any class
  // which may be the base for inheritance

    virtual ~base(void);
    base& operator= (const base& b);
};

class derived : public base {
  private:
    int  x;
    char y;
};


//----< void constructor >-------------------------------------

base::base(void)   { cout << "  base void constructor called\n"; }


//----< copy constructor >-------------------------------------

base::base(const base &) {
  cout << "  base copy constructor called\n";
}


//----< destructor >-------------------------------------------

base::~base(void)  { cout << "  base destructor called\n"; }


//----< assignment >-------------------------------------------

base& base::operator= (const base& b) {
  if(this == &b) return *this;
  cout << "  base operator= called\n"; return *this;
}


//-------------------------------------------------------------

void message(char *s) {
       cout << endl << s << " executable statement of main\n";
}
/**/

void main() {

  message("1st");  	base b1;
  message("2nd");  	base b2 = b1;
  message("3rd");  	b1 = b2;

  message("4th");  	derived d1;
  message("5th");  	derived d2 = d1;
  message("6th");  	d1 = d2;

//                      d2 = b1;
//       won't compile without a b1 promotion constructor
//       e.g., base is not a derived

  message("7th");  	b1 = d2;

//       however, derived is a base, so this works

  message("no more");
}

// Note:
// - derived class objects can be void constructed, copy constructed
//   assigned and destroyed even though the derived class has no
//   member functions and does not inherit any from the base class.
// - each of these operations is supplied in default form by the
//   compiler
// - default construction, assignment, and destruction is done member-
//   wise, that is, each of the members of the derived class is
//   individually initialized, assigned, and destroyed
