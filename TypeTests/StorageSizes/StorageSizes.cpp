// StorageSizes.cpp

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
//#include <iomanip>
#include <fstream>
#include <sstream>
#include <memory>

void showSize(const std::string& typeName, size_t size, size_t fieldSize = 28)
{
  long int save = std::cout.flags();
  std::cout << "\n  " << std::left << std::setw(fieldSize) << "sizeof(" + typeName + "): " << std::right << std::setw(4) << size;
  if (size > 1)
    std::cout << " bytes";
  else
    std::cout << " byte";
  std::cout.flags(save);
}

int main()
{
  std::cout << "\n  Testing Storage Sizes for Common C++ Types";
  std::cout << "\n ============================================\n";

  bool pred = true;
  size_t boolSz = sizeof(bool);
  showSize("bool", boolSz);

  size_t nullptrSz = sizeof(nullptr_t);
  showSize("nullptr_t", nullptrSz);

  std::cout << "\n\n  ---- integers -----------------------------------";
  
  size_t shortintSz = sizeof(short int);
  showSize("short int", shortintSz);

  size_t intSz = sizeof(int);
  showSize("int", intSz);

  size_t longintSz = sizeof(long);
  showSize("long int", longintSz);

  size_t longlongintSz = sizeof(long long int);
  showSize("long long int", longlongintSz);

  size_t unsignedintSz = sizeof(unsigned int);
  showSize("unsigned int", unsignedintSz);

  size_t constintSz = sizeof(const int);
  showSize("const int", constintSz);

  size_t volatileintSz = sizeof(volatile int);
  showSize("volatile int", volatileintSz);

  static int staticInt = 0;
  size_t staticintSz = sizeof(staticInt);
  showSize("static int", staticintSz);

  std::cout << "\n\n  ---- chars --------------------------------------";

  size_t charSz = sizeof(char);
  showSize("char", charSz);

  size_t unsignedcharSz = sizeof(unsigned char);
  showSize("unsigned char", unsignedcharSz);

  size_t wchar_tSz = sizeof(wchar_t);
  showSize("wchar_t", wchar_tSz);

  size_t char16_tSz = sizeof(char16_t);
  showSize("char16_t", char16_tSz);

  size_t char32_tSz = sizeof(char32_t);
  showSize("char32_t", char32_tSz);

  std::cout << "\n\n  ---- floats -------------------------------------";

  size_t floatSz = sizeof(float);
  showSize("float", floatSz);

  size_t doubleSz = sizeof(double);
  showSize("double", doubleSz);

  size_t longdoubleSz = sizeof(long double);
  showSize("long double", longdoubleSz);

  std::cout << "\n\n  ---- pointers -----------------------------------";

  size_t ptrvoidSz = sizeof(void*);
  showSize("void*", ptrvoidSz);

  size_t ptrintSz = sizeof(int*);
  showSize("int*", ptrintSz);

  size_t ptrptrvoidSz = sizeof(void**);
  showSize("void**", ptrptrvoidSz);

  std::cout << "\n\n  ---- arrays -------------------------------------";

  size_t arrayint1Sz = sizeof(int[1]);
  showSize("int[1]", arrayint1Sz);

  size_t arrayint4Sz = sizeof(int[4]);
  showSize("int[4]", arrayint4Sz);

  size_t arraydouble1Sz = sizeof(double[1]);
  showSize("double[1]", arraydouble1Sz);

  std::cout << "\n\n  ---- structs and classes ------------------------";

  struct {} structEmpty;
  size_t emptystructSz = sizeof(structEmpty);
  showSize("struct {}", emptystructSz,32);

  struct { int a; double d; } structIntDouble;
  size_t structintdoubleSz = sizeof(structIntDouble);
  showSize("struct w/ int, double", structintdoubleSz, 32);

  class {} classEmpty;
  size_t emptyclassSz = sizeof(classEmpty);
  showSize("class {}", emptyclassSz, 32);

  class virtualClass { virtual ~virtualClass() {}; };
  size_t virtualClassSz = sizeof(virtualClass);
  showSize("class w/ virtual dtor", virtualClassSz, 32);

  std::cout << "\n\n  ---- selected library types ---------------------";

  std::unique_ptr<int> upInt = std::make_unique<int>(2);
  size_t upIntSz = sizeof(upInt);
  showSize("std::unique_ptr<int> = \"std::make_unique<int>(2)\"", upIntSz, 68);

  std::shared_ptr<double> spDbl = std::make_shared<double>(2.5);
  size_t spDblSz = sizeof(spDbl);
  showSize("std::shared_ptr<double> = \"std::make_shared<double>(2.5)\"", spDblSz, 68);

  std::string emptystr = "";
  size_t emptyStrSz = sizeof(emptystr);
  showSize("std::string = \"\"", emptyStrSz, 68);

  std::string str = "abc";
  size_t strSz = sizeof(str);
  showSize("std::string = \"abc\"", strSz, 68);

  std::vector<int> emptyVecInt;
  size_t emptyvecintSz = sizeof(std::vector<int>);
  showSize("std::vector<int>", emptyvecintSz, 68);

  std::vector<int> vecInt{ 1, 2, 3 };
  size_t vecintSz = sizeof(vecInt);
  showSize("std::vector<int> { 1, 2, 3 }", vecintSz, 68);

  std::unordered_map<std::string, std::string> emptyUnOrdMap;
  size_t emptyUnOrdMapSz = sizeof(emptyUnOrdMap);
  showSize("std::unordered_map<std::string, std::string>", emptyUnOrdMapSz, 68);

  std::unordered_map<std::string, std::string> unOrdMap{ {"one", "1" }, {"two", "2" }, {"three", "3" } };
  size_t unOrdMapSz = sizeof(unOrdMap);
  showSize("std::unordered_map<std::string, std::string> {...}", unOrdMapSz, 68);

  size_t stdCoutSz = sizeof(std::cout);
  showSize("std::cout", stdCoutSz, 68);

  size_t stdStrBufSz = sizeof(std::streambuf);
  showSize("std::streambuf", stdStrBufSz, 68);

  size_t stdOFSSz = sizeof(std::ofstream);
  showSize("std::ofstream", stdOFSSz, 68);

  size_t stdFlBufSz = sizeof(std::filebuf);
  showSize("std::filebuf", stdFlBufSz, 68);

  size_t stdOSSSz = sizeof(std::ostringstream);
  showSize("std::ostringstream", stdOSSSz, 68);

  size_t stdSBufSz = sizeof(std::stringbuf);
  showSize("std::stringbuf", stdSBufSz, 68);

  std::cout << "\n\n";
}