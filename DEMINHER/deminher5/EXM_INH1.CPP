// EXM_INH1.CPP - polymorphism example for class
//                Jim Fawcett

#include <iostream.h>

class base {
  public:
    void fun1(void) { cout << "this is b::fun1()\n"; }
    void fun2(void) { cout << "this is b::fun2()\n"; }
    void fun3(void) { cout << "this is b::fun3()\n"; }
    virtual void fun4(void) { cout << "this is b::fun4()\n"; }
};

class deri:public base {
  public:
    void fun2(void) { cout << "this is d::fun2()\n"; }
    void fun3(int x) { cout << "this is d::fun3(x)\n"; }
    void fun4(void) { cout << "this is d::fun4()\n"; }
    void fun5(void) { cout << "this is d::fun5()\n"; }
};

void message(char* s) { cout << endl << s << "    "; }

void main () {
  cout << "\n\ndemonstrating various flavors of redefinition\n\n";
  int x=1;
  base bObj;  base* basePtrTo_bObj = &bObj;
  deri dObj;  deri* deriPtrTo_dObj = &dObj;
              base* basePtrTo_dObj = &dObj;

  message("\nbase bObj;"); message("base* basePtrTo_bObj = &bObj");
  message("\nderi dObj;"); message("deri* deriPtrTo_dObj = &dObj");
  message("\n          "); message("base* basePtrTo_dObj = &dObj");
  cout << endl << endl;
  message("basePtrTo_bObj -> fun1();");   basePtrTo_bObj -> fun1();
  message("basePtrTo_bObj -> fun2();");   basePtrTo_bObj -> fun2();
  message("basePtrTo_bObj -> fun3();");   basePtrTo_bObj -> fun3();
  message("basePtrTo_bObj -> fun4();");   basePtrTo_bObj -> fun4();
  cout << "\nbasePtrTo_bObj -> fun5();"
          "  won't compile - not a member\n";
  cout << endl;
  message("deriPtrTo_dObj -> fun1();");   deriPtrTo_dObj -> fun1();
  message("deriPtrTo_dObj -> fun2();");   deriPtrTo_dObj -> fun2();
  cout << "\nderiPtrTo_dObj -> fun3();"
          "  won't compile - too few parameters\n";
  message("deriPtrTo_dObj ->fun3(x);");  deriPtrTo_dObj -> fun3(x);
  message("deriPtrTo_dObj -> fun4();");   deriPtrTo_dObj -> fun4();
  message("deriPtrTo_dObj -> fun5();");   deriPtrTo_dObj -> fun5();
  cout << endl;
  message("basePtrTo_dObj -> fun1();");   basePtrTo_dObj -> fun1();
  message("basePtrTo_dObj -> fun2();");   basePtrTo_dObj -> fun2();
  message("basePtrTo_dObj -> fun3();");   basePtrTo_dObj -> fun3();
  cout << "\nbasePtrTo_dObj -> fun3(x);"
          " won't compile - extra parameter\n";
  message("basePtrTo_dObj -> fun4();");   basePtrTo_dObj -> fun4();
  cout << "\nbasePtrTo_dObj -> fun5();"
          "  won't compile - not member of base\n";
}