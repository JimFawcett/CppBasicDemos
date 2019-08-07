/////////////////////////////////////////////////////////////////////////
// Utilities.cpp - helper functions for GettingStartedExamples         //  
//                                                                     //
// Jim Fawcett, Summer Short Course, Su2016                            //
/////////////////////////////////////////////////////////////////////////
/*
* Found in: Handouts\ShortCourse\Repository\GettingStartedExamples
*
*/
#include "Utilities.h"
#include <iostream>

void Utilities::title(const std::string& msg, char underline)
{
  std::cout << "\n  " << msg;
  std::cout << "\n " << std::string(msg.size() + 2, underline).c_str();
}

void Utilities::putLine() { std::cout << "\n"; }

#ifdef TEST_UTILITIES // defined in Project > Properties > C/C++ > Preprocessor 

int main()
{
  Utilities::title("Testing Utilities");
}

#endif


