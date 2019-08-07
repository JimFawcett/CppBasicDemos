#ifndef SOLDIERS_H
#define SOLDIERS_H
/////////////////////////////////////////////////////////////////////////////////
// Soldiers.h - demonstrates inheritance                                       //  
//                                                                             //
// Jim Fawcett, Summer Short Course, Su2016                                    //
/////////////////////////////////////////////////////////////////////////////////
/*
 * Illustrates flexability afforded by polymorphic substitution.  
 * The global show function accepts a reference to any instance with 
 * class derived from Soldier, e.g., Officer, Sergeant, or Private.  
 * It then dynamically dispatches to the appropriate functions 
 * Soldier::salute() and Soldier::equipment().
*/
#include <string>
#include <vector>
#include <iostream>
#include "Utilities.h"

class Gear
{
public:
  using Name = std::string;

  Gear(const Name& name);
  ~Gear();
  Name name();
protected:
  Name name_;
};

class Person
{
public:
  using Name = std::string;

  Person(const Name& name);
  void eat();
  void sleep();
  Name name();
  virtual ~Person();
protected:
  Name name_;
};

class Soldier : public Person
{
public:
  using Equipment = std::vector<Gear>;
  using Rank = std::string;

  Soldier(const Name& name, const Rank& rank="private");
  virtual void salute() = 0;
  Rank rank() { return rank_; }
  void add(const Gear& gear);
  Equipment& equipment();
private:
  Equipment equip_;
  Rank rank_;
};

class Officer : public Soldier
{
public:
  Officer(const Name& name, const Rank& rank="Captain");
  virtual void salute();
};

class Sergeant : public Soldier
{
public:
  Sergeant(const Name& name);
  virtual void salute();
};

class Private : public Soldier
{
public:
  Private(const Name& name);
  virtual void salute();
};

void show(Soldier& s);

#endif
