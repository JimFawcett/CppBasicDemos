/////////////////////////////////////////////////////////////////////
// Lambdas.cpp - demonstrate lambda capture                        //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2015       //
/////////////////////////////////////////////////////////////////////
/*
 * When compiled a lambda definition is translated into a functor
 * with operator() defining the code of the lambda.  Any referenced 
 * data from the local scope becomes member data of the functor and 
 * gets passed around with the lambda.
 *
 * Lambdas are defined like this:
 * 1. [=] (arguments) 
 *    { code to execute may include names of local data as well as arguments };
 *    The [=] means that local data, like i below, are captured by value.
 * 2. [&] (arguments)
 *    { code to execute may include names of local data as well as arguments };
 *    The [&] means that local data is captured by reference so must be in
 *    scope when the lambda executes.
 * 3. [localVar1, &localVar2] (arguments)
 *    { code to execute includes localVar1 by value and localVar2 by reference }
 */

#include <functional>
#include <iostream>
#include <sstream>

//----< create a lambda and bind to a std::function >----------------
/*
 * Lambda copies captured values, e.g., [=]
 */
std::function<std::string()> CreateLambda1(int i)
{
  // this std function converts an integer to a string

  std::function<std::string()> f = [=]()
  {
    std::ostringstream convert;
    convert << i;                      // lambda captures value of i
    return convert.str();
  };
  return f;
}

//----< create a lambda and bind to a std::function >----------------
/*
 * Lambda copies captured values, e.g., []
 */
std::function<std::string(int)> CreateLambda2()
{
  // this std function converts an integer to a string

  std::function<std::string(int)> f = [](int i)
  {
    std::ostringstream convert;
    convert << i;                      // lambda captures value of i
    return convert.str();
  };
  return f;
}

//----< create a lambda and bind to a std::function >----------------
/*
 * Lambda captures a reference to i and the value of j, e.g., [&i, j]
 */
std::function<std::string()> CreateLambda3(int& i)
{
  // this std function converts integers to a string

  int j = 40;

  std::function<std::string()> f = [&i, j]()
  {
    std::ostringstream convert;
    convert << i + j;                      // lambda captures reference to
    return convert.str();                  // external i - would be an error
  };                                       // if i was passed by value to
  return f;                                // CreateLambda3(int i)
}

//----< create a lambda and bind to a std::function >----------------
/*
 * Lambda captures a reference to i that will become invalid when
 * returning from invocation and a copy of j which will be valid, 
 * e.g., [&i, j]
 */
std::function<std::string()> CreateLambda4()
{
  // this std function converts integers to a string

  int i = 2;
  int j = 40;

  std::function<std::string()> f = [&i, j]()
  {
    std::ostringstream convert;
    convert << i + j;           // error here - will return invalid reference
    return convert.str();       // to temporary value of i along with valid
  };                            // copy of j, e.g., [&i, j]
  return f;
}

//----< demonstration of lambda operation >--------------------------

int main()
{
  std::cout << "\n  Demonstrating Lambda Capture";
  std::cout << "\n ==============================";

  std::function<std::string()> f = CreateLambda1(42);

  std::cout << "\n  The meaning of life is \"" << f() << "\"";

  std::function<std::string(int)> g = CreateLambda2();

  std::cout << "\n  The meaning of life is still \"" << g(42) << "\"";

  int i = 2;
  std::function<std::string()> h = CreateLambda3(i);

  std::cout << "\n  Again, the meaning of life is still \"" << h() << "\"";

  std::function<std::string()> error = CreateLambda4();

  std::cout << "\n  the meaning of life is not \"" << error() << "\"";

  std::cout << "\n\n  So long, Douglas Adams, and thanks for all the fish!\n\n";
}