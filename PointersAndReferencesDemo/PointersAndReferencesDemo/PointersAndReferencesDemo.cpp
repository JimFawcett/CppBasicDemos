/////////////////////////////////////////////////////////////////////
// PointersAndReferencesDemo.cpp - simple demo defining and        // 
//                                 using pointers and references   //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2019       //
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

// define a simple user defined type, Demo

class Demo {
public:
  std::string say()
  {
    return "instance of Demo class here";
  }
};

// define a Global (unbound) function that executes demonstration

void PtrsAndRefsDemo()
{
  std::cout << "\n  Demonstrating Pointers";
  std::cout << "\n ------------------------";

  // A pointer refers to a specific memory location, 
  // holding a specific type.

  // define a "throw-away" formatter

  std::string preface = "\n  ";

  // instances of primitive data types and a user defined type

  int intPrimitive = 3;
  double doublePrimitive = 3.1415927;
  Demo demo;

  // T* pT = &t says that pT points to the memory location of t
  // & in an expression is an operator that returns a memory location

  int* pInt = &intPrimitive;
  double* pDouble = &doublePrimitive;
  Demo* pDemo = &demo;

  // display, on the console, the contents pointed to

  std::cout << preface << *pInt;
  std::cout << preface << *pDouble;
  
  // invoke Demo::say() method

  std::cout << preface << pDemo->say();
  std::cout << preface << (*pDemo).say();

  std::cout << "\n";

  // define a lambda that acts like a local function

  auto lambda = [&]() {
  
    std::cout << "\n  Demonstrating C++ References";
    std::cout << "\n ------------------------------";

    int& rInt = *pInt;
    double& rDouble = *pDouble;
    Demo& rDemo = demo;

    std::cout << preface << rInt;
    std::cout << preface << rDouble;
    std::cout << preface << rDemo.say();

    std::cout << "\n\n";
  };
  
  // invoke the lambda like it was a function

  lambda();
}

int main()
{
  PtrsAndRefsDemo();
}
