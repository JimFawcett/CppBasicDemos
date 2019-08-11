///////////////////////////////////////////////////////////////////////
// Callables.cpp - Executing Callable Objects                        //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Midterm Spring 2016 //
///////////////////////////////////////////////////////////////////////


#include <iostream>
#include "../Utilities/Utilities.h"

// function accepting and executing any callable object

template <class CallObj>
void Executor(CallObj& co)
{
  co();      // invocation of callable object
}
// example callable object - function

void hello()
{
  std::cout << "\n  Hello from hello()";
}
// example callable object - functor

class MyFunctor
{
public:
  MyFunctor(const std::string& msg) : _msg(msg) {}

  void operator()()
  {
    std::cout << "\n  " << _msg.c_str() << " from MyFunctor";
  }
private:
  std::string _msg;
};

// example callable object - lambda

std::string msg("Hi again");
std::function<void()> sfun = [=]() { 
  std::cout << "\n  " << msg.c_str() << " from std::function bound to lambda"; 
};

using namespace Utilities;
using Utils = StringHelper;

int main()
{
  Utils::Title("Demo Executing Callable Objects");

  Executor(hello);
  MyFunctor mf("Hi");
  Executor(mf);
  Executor(sfun);

  // another example callable object

  std::string newMsg = "Hi one more time";
  Executor(
    [=]() { std::cout << "\n  " << newMsg.c_str() << " from lambda"; }
  );

  std::cout << "\n\n";

}