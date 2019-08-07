#ifndef UTILITIES_H
#define UTILITIES_H
/////////////////////////////////////////////////////////////////////////
// Utilities.h - helper functions for GettingStartedExamples           //  
//                                                                     //
// Jim Fawcett, Summer Short Course, Su2016                            //
/////////////////////////////////////////////////////////////////////////
/*
* Found in: Handouts\ShortCourse\Repository\GettingStartedExamples
*
*/
#include <string>

namespace Utilities
{
  void title(const std::string& msg, char underline = '-');

  void putLine();
}
#endif
