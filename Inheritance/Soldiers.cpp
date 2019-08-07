/////////////////////////////////////////////////////////////////////////////////
// Soldiers.cpp - demonstrates inheritance                                     //  
//                                                                             //
// Jim Fawcett, Summer Short Course, Su2016                                    //
/////////////////////////////////////////////////////////////////////////////////
/*
*  Illustrates flexability afforded by polymorphic substitution.
*  The global show function accepts a reference to any instance with
*  class derived from Soldier, e.g., Officer, Sergeant, or Private.
*  It then dynamically dispatches to the appropriate functions
*  Soldier::salute() and Soldier::equipment().
*/
#include "Soldiers.h"

Gear::Gear(const Name& name) : name_(name) {}

Gear::~Gear() {}

Gear::Name Gear::name() { return name_; }

Person::Person(const Name& name) : name_(name) {}

void Person::eat()
{
  std::cout << "\n  " << name() << " eating";
}

void Person::sleep()
{
  std::cout << "\n  " << name() << " sleeping";
}

Person::Name Person::name() { return name_; }

Person::~Person() {}

Soldier::Soldier(const Name& name, const Rank& rank) : Person(name), rank_(rank) {}

void Soldier::add(const Gear& gear)
{
  equip_.push_back(gear);
}

Soldier::Equipment& Soldier::equipment()
{
  return equip_;
}

Officer::Officer(const Name& name, const Rank& rank) : Soldier(name, rank) {}

void Officer::salute()
{
  std::cout << "\n  casual salute";
}

Sergeant::Sergeant(const Name& name) : Soldier(name, "Sergeant") {}

void Sergeant::salute()
{
  std::cout << "\n  default salute";
}

Private::Private(const Name& name) : Soldier(name) {}

void Private::salute()
{
  std::cout << "\n  snappy salute";
}
//----< global function accepts any Soldier object >-------

void show(Soldier& s)
{
  s.salute();
  std::cout << "\n  Sir, my name is " << s.rank() << " " << s.name();
  for (auto eq : s.equipment())
    std::cout << "\n    inspecting " << eq.name();
  if (s.equipment().size() == 0)
    std::cout << "\n    Sorry sir, I forgot my equipment";
}

int main()
{
  Officer off("Frank");
  off.add(Gear("45 Caliber Pistol"));

  Sergeant sgt("Sam");
  sgt.add(Gear("m16 carbine"));

  Private pvt1("George");
  pvt1.add(Gear("m16 carbine"));
  pvt1.add(Gear("40lb backpack"));

  Private pvt2("Charlie");
  pvt2.add(Gear("m16 carbine"));
  pvt2.add(Gear("mortar"));

  Private pvt3("Slacker");

  Utilities::title("chow time");
  off.eat();
  sgt.eat();
  pvt1.eat();
  pvt2.eat();
  pvt3.eat();
  Utilities::putLine();

  Utilities::title("inspection");
  std::cout << "\n  " << off.rank() << " " << off.name() << " inspecting his 1st squad";
  show(sgt);
  show(pvt1);
  show(pvt2);
  show(pvt3);
  std::cout << "\n\n";
}
