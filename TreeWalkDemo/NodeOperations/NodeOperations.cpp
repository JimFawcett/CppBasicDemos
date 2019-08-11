/////////////////////////////////////////////////////////////////
// NodeOperations.cpp - Demonstrate how to operate on each     //
//                      node of an m-ary tree                  //
//                                                             //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2014   //
/////////////////////////////////////////////////////////////////
/*
* This demo displays several node operation strategies.
* Any of them will work for XmlDocument operations.
*
* Note:
* To accumulate data acquired during Tree Walk:
* - recursive call methods require data storage to be defined
*   outside method, e.g., member data in class that defines
*   the recursive walk, or by passing as a parameter.
* - stack and queue based walks can define local data for
*   accumulation because you never leave the starting scope
*   until the search completes.
*/
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <memory>
#include <functional>
#include <iostream>

/////////////////////////////////////////////////////////////////////////////
// Define tree node - used to wire up ad hoc tree

class Node
{
public:
  using sPtr = std::shared_ptr < Node >;

  Node(const std::string& name) : name_(name) { }
  void addChild(sPtr pNode) { children_.push_back(pNode); }
  std::vector<sPtr>& children() { return children_; }
  std::string& name() { return name_; }
private:
  std::string name_;
  std::vector<sPtr> children_;
};

/////////////////////////////////////////////////////////////////////////////
// Depth First Search
// - First works for functors and lambdas, second for functions

using sPtr = std::shared_ptr < Node >;

//----< recursive left-to-right Depth First Search >-------------------------
/*
 *  Good candidate for XmlDocument operations
 */
template<typename CallObj>
void DFS1(sPtr pNode, CallObj& co)
{
  co(pNode);
  for (auto pChild : pNode->children())
    DFS1(pChild, co);
}

//----< recursive left-to-right Depth First Search >-------------------------
/*
 *  If the callable object is a function and we need to accumulate
 *  state while walking the tree we will have to pass a state argument.
 */
template<typename State, typename CallObj>
void DFS2(sPtr pNode, State& st, CallObj& co)
{
  co(pNode, st);
  for (auto pChild : pNode->children())
    DFS2(pChild, st, co);
}
/////////////////////////////////////////////////////////////////////////////
// Callable objects

//----< operation global function >------------------------------------------

struct State
{
  State() : count(0) {}
  void show()
  {
    std::cout << "\n  count = " << count;
    std::cout << "\n  node name list:";
    for (auto item : names)
      std::cout << "\n    " << item;
    std::cout << "\n";
  }
  size_t count;
  std::vector<std::string> names;
};

void functionOper(sPtr pNode, State& st)
{
  ++st.count;  // number of nodes visited
  st.names.push_back(pNode->name());
}
//----< operation functor >--------------------------------------------------

class functorOper
{
public:
  functorOper() : count_(0) {}
  size_t& count() { return count_; }
  std::vector<std::string> names() { return names_; }

  void operator()(sPtr pNode)
  {
    ++count_;
    names_.push_back(pNode->name());
  }
  void show()
  {
    std::cout << "\n  count = " << count();
    std::cout << "\n  node name list:";
    for (auto item : names())
      std::cout << "\n    " << item;
    std::cout << "\n";
  }
private:
  size_t count_;
  std::vector<std::string> names_;
};

/////////////////////////////////////////////////////////////////////////////
// Demonstration

//----< utilities >----------------------------------------------------------

void title(const std::string& t, char underline = '-')
{
  std::cout << "\n  " << t;
  std::cout << "\n " << std::string(t.size() + 2, underline);
}

void putLine(size_t lines = 1)
{
  for (size_t i = 0; i < lines; ++i)
    std::cout << "\n";
}

int main()
{
  title("Demonstrating Node Operations with Callable Objects");
  putLine();

  // build ad hoc tree

  sPtr pRoot = sPtr(new Node("root"));
  sPtr pChild1 = sPtr(new Node("child1"));
  pRoot->addChild(pChild1);
  sPtr pChild2 = sPtr(new Node("child2"));
  pRoot->addChild(pChild2);
  sPtr pGrandChild11 = sPtr(new Node("grandChild11"));
  pChild1->addChild(pGrandChild11);
  sPtr pGreatGrandChild11 = sPtr(new Node("greatGrandChild11"));
  pGrandChild11->addChild(pGreatGrandChild11);
  sPtr pGrandChild21 = sPtr(new Node("grandChild21"));
  pChild2->addChild(pGrandChild21);
  sPtr pGrandChild22 = sPtr(new Node("grandChild22"));
  pChild2->addChild(pGrandChild22);

  // now start walking

  title("Operate on each tree node with function - have to pass state");
  State st;
  DFS2(pRoot, st, functionOper);
  st.show();

  title("Operate on each tree node with functor - functor carries state");
  functorOper fo;
  DFS1(pRoot, fo);
  fo.show();

  title("Operate on each tree node with lambda - lambda captures state");
  size_t count = 0;
  std::vector<std::string> names;
  std::function<void(sPtr)> f =
    [&count, &names](sPtr pNode) { ++count; names.push_back(pNode->name()); };
  
  DFS1(pRoot, f);
  
  [count, names]()
  {
    std::cout << "\n  count = " << count;
    std::cout << "\n  node name list:";
    for (auto item : names)
      std::cout << "\n    " << item;
    putLine();
  }();

  putLine(2);
}