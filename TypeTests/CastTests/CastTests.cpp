/////////////////////////////////////////////////////////////////////////
// CastTests.cpp - demo static, const, dynamic, and reinterpret casts  //
//                                                                     //
// Jim Fawcett, Emeritus Teaching Professor, Syracuse University       //
/////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

/*
*  static_cast creates a new instance of a different destination type
*  using information from the source type.
*/
void DemoStatic_cast()
{
  std::cout << "\n  Demonstrating static_cast";
  std::cout << "\n --------------------------------\n";
  
  double d = 3.14159;
  int dtoi = static_cast<int>(d);
  std::cout << "\n  static_cast<int>(3.14159) = " << static_cast<int>(d);
  std::cout << "\n\n";
}
/*
*  const_cast returns the same object with const qualification removed.
*/
void DemoConst_cast()
{
  std::cout << "\n  Demonstrating const_cast";
  std::cout << "\n --------------------------\n";

  const std::string cstr = "a const string";
  std::cout << "\n  cstr = " << cstr;
  
  // create a non-const reference to a const object

  std::string& str = const_cast<std::string&>(cstr);
  str[3] = '3';
  str[4] = '4';
  str[5] = '5';
  std::cout << "\n  str  = " << str;
  std::cout << "\n\n";
}
/*
*  dynamic_cast changes the interface type of a polymorphic object, i.e.,
*  tells compiler to apply a different interface for dispatching calls to 
*  derived object.
*/
void DemoDynamic_cast()
{
  std::cout << "\n  Demonstrating dynamic_cast";
  std::cout << "\n ----------------------------";

  struct IMiddle {
    virtual ~IMiddle() {}
    virtual void MiddleOp() = 0;
  };
  struct ILeft {
    virtual ~ILeft() {}
    virtual void MiddleOp() = 0;
    virtual void LeftOp() = 0;
  };
  struct IRight {
    virtual ~IRight() {}
    virtual void MiddleOp() = 0;
    virtual void RightOp() = 0;
  };
  struct DerivedLeft : public ILeft, IMiddle {
    virtual void MiddleOp() { std::cout << "\n  DerivedLeft::MiddleOp()"; }
    virtual void LeftOp() { std::cout << "\n  DerivedLeft::LeftOp()"; }
  };

  struct DerivedRight : public IMiddle, IRight {
    virtual void MiddleOp() { std::cout << "\n  DerivedRight::MiddleOp()"; }
    virtual void RightOp() { std::cout << "\n  DerivedRight::RightOp()"; }
  };

  std::cout << "\n\n  DerivedLeftOps with ILeft:";
  ILeft* pDL = new DerivedLeft;
  pDL->LeftOp();
  pDL->MiddleOp();
  //pDL->RightOp();

  std::cout << "\n\n  DerivedLeftOps with IMiddle:";
  IMiddle* pMDL = new DerivedLeft;
  //pMDL->LeftOp();
  pMDL->MiddleOp();
  //pMDL->RightOp();

  std::cout << "\n\n  DerivedRightOps with IMiddle:";
  IMiddle* pMDR = new DerivedRight;
  //pMDR->LeftOp();
  pMDR->MiddleOp();
  //pMDR->RightOp();

  std::cout << "\n\n  DerivedRightOps with IRight:";
  IRight* pDR = new DerivedRight;
  //pDR->LeftOp();
  pDR->MiddleOp();
  pDR->RightOp();

  ILeft* pDml = nullptr;
  std::cout << "\n\n  Casting from IMiddle to ILeft with DerivedLeft:";
  pDml = dynamic_cast<ILeft*>(pMDL);
  if (pDml)
  {
    pDml->LeftOp();
    pDml->MiddleOp();
    //pDml->RightOp();
  }
  else
  {
    std::cout << "\n  Cast failed";
  }

  std::cout << "\n\n  Casting from IMiddle to ILeft with DerivedRight:";
  pDml = dynamic_cast<ILeft*>(pMDR);
  if (pDml)
  {
    pDml->LeftOp();
    pDml->MiddleOp();
    //pDml->RightOp();
  }
  else
  {
    std::cout << "\n  Cast failed";
  }

  std::cout << "\n\n  Casting from IMiddle to IRight with DerivedRight:";
  IRight* pDmr = dynamic_cast<IRight*>(pMDR);
  //pDmr->LeftOp();
  pDmr->MiddleOp();
  pDmr->RightOp();

  std::cout << "\n\n  Casting from IRight to IMiddle with DerivedRight:";
  IMiddle* pDrm = dynamic_cast<IMiddle*>(pDmr);
  //pDrm->LeftOp();
  pDrm->MiddleOp();
  //pDrm->RightOp();

  std::cout << "\n\n";
}
/*
*  reinterpret_cast tells compiler to change type rules applied to an object.
*/
void DemoReinterpret_cast()
{
  std::cout << "\n  Demonstrating reinterpret_cast";
  std::cout << "\n --------------------------------\n";
  double d = 3.1415927;
  using byte = unsigned char;
  byte block[8];

  // treat double as if it were an array of chars

  byte* pBlock = reinterpret_cast<byte*>(&d);
  std::wcout << "\n  evaluating bytes in d = 3.1415927\n\n  ";
  for (int i = 0; i < 8; ++i)
  {
    std::wcout << pBlock + i << "  ";
  }

  double retreived = *reinterpret_cast<double*>(pBlock);
  std::wcout.precision(7);
  std::cout << "\n\n  retreived value = " << retreived;
  std::cout << "\n\n";
}
int main()
{
  DemoStatic_cast();
  DemoConst_cast();
  DemoDynamic_cast();
  DemoReinterpret_cast();
  std::cout << "\n  That's all folks\n\n";
}