/////////////////////////////////////////////////////////////////
// GraphWalkDemo.cpp - Demonstrate how to walk graph           //
//                                                             //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2014   //
/////////////////////////////////////////////////////////////////
/*
 * This demo displays several graph traversal strategies.
 *
 * Note:
 * To accumulate data acquired during graph Walk:
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
#include <iostream>

class Node
{
public:
  using sPtr = std::shared_ptr < Node >;

  Node(const std::string& name) : name_(name) { }
  void addChild(sPtr pNode) { children_.push_back(pNode); }
  std::vector<sPtr>& children() { return children_; }
  std::string& name() { return name_; }
  bool visited() { return visited_; }
  void visited(bool v) {
    visited_ = v;
  }
private:
  std::string name_;
  bool visited_ = false;
  std::vector<sPtr> children_;
};

using sPtr = std::shared_ptr < Node > ;

//----< recursive left-to-right Depth First Search >-------------------------
/*
 *  Good candidate for XmlDocument search operations
 */
void DFS_r_ltr(sPtr pNode)
{
  pNode->visited(true);
  std::cout << "\n  " << pNode->name();
  for (auto pChild : pNode->children()) {
    if (!pChild->visited())
      DFS_r_ltr(pChild);
  }
}

//----< recursive left-to-right, bottom-to-top Depth First Search >----------

void DFS_r_ltrbtt(sPtr pNode)
{
  pNode->visited(true);
  for (auto pChild : pNode->children()) {
    if (!pChild->visited())
      DFS_r_ltrbtt(pChild);
  }
  std::cout << "\n  " << pNode->name();
}

//----< recursive right-to-left Depth First Search >-------------------------

void DFS_r_rtl(sPtr pNode)
{
  pNode->visited(true);
  std::cout << "\n  " << pNode->name();
  size_t numChildren = pNode->children().size();
  for (size_t i = 0; i < numChildren; ++i) {
    sPtr child = pNode->children()[numChildren - i - 1];
    if (!child->visited())
      DFS_r_rtl(pNode->children()[numChildren - i - 1]);
  }
}

//----< stack-based right-to-left Depth First Search >-----------------------
/*
*  Good candidate for XmlDocument search operations
*/
void DFS_s_rtl(sPtr pNode)
{
  std::stack<sPtr> nodeStack;
  pNode->visited(true);
  nodeStack.push(pNode);
  while (nodeStack.size() > 0)
  {
    sPtr pCurrentNode = nodeStack.top();
    nodeStack.pop();
    std::cout << "\n  " << pCurrentNode->name();
    for (auto pChild : pCurrentNode->children()) {
      if (!pChild->visited()) {
        pChild->visited(true);
        nodeStack.push(pChild);
      }
    }
  }
}

//----< stack-based left-to-right Depth First Search >-----------------------

void DFS_s_ltr(sPtr pNode)
{
  std::stack<sPtr> nodeStack;
  pNode->visited(true);
  nodeStack.push(pNode);
  while (nodeStack.size() > 0)
  {
    sPtr pCurrentNode = nodeStack.top();
    nodeStack.pop();
    std::cout << "\n  " << pCurrentNode->name();
    size_t numChildren = pCurrentNode->children().size();
    for (size_t i = 0; i < numChildren; ++i) {
      sPtr child = pCurrentNode->children()[numChildren - i - 1];
      if (!child->visited()) {
        child->visited(true);
        nodeStack.push(pCurrentNode->children()[numChildren - i - 1]);
      }
    }
  }
}

//----< queue-based left-to-right Breadth First Search >---------------------
/*
 *   Breadth first search has the same variations as shown
 *   above for Depth First Search.  I'll leave it up to you
 *   to explore those if you wish.
 */
void BFSq(sPtr pNode)
{
  std::queue<sPtr> nodeQueue;
  pNode->visited(true);
  nodeQueue.push(pNode);
  while (nodeQueue.size() > 0)
  {
    sPtr pCurrentNode = nodeQueue.front();
    nodeQueue.pop();
    std::cout << "\n  " << pCurrentNode->name();
    for (auto pChild : pCurrentNode->children()) {
      if (!pChild->visited()) {
        pChild->visited(true);
        nodeQueue.push(pChild);
      }
    }
  }
}
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
//----< demonstration >------------------------------------------------------

int main()
{
  title("Demonstrate Graph Traversal Strategies", '=');
  putLine();

  // build ad hoc graph
  /*
               +----- root -------+
               |                  |
               V                  V
             child1 ----------> child2 -----------+
               |  ^                |              |
               |  |                |              |
               |  +-------+        |              |
               V          |        V              V
          grandChild11    +--- grandChild21   grandChild22
               |
               V
        greadGrandChild11
  */
 
  sPtr pRoot = sPtr(new Node("root"));
  sPtr pChild1 = sPtr(new Node("child1"));
  pRoot->addChild(pChild1);
  sPtr pChild2 = sPtr(new Node("child2"));
  pRoot->addChild(pChild2);
  sPtr pGrandChild11 = sPtr(new Node("grandChild11"));
  pChild1->addChild(pGrandChild11);
  pChild1->addChild(pChild2);
  sPtr pGreatGrandChild11 = sPtr(new Node("greatGrandChild11"));
  pGrandChild11->addChild(pGreatGrandChild11);
  sPtr pGrandChild21 = sPtr(new Node("grandChild21"));
  pGrandChild21->addChild(pChild1);
  pChild2->addChild(pGrandChild21);
  sPtr pGrandChild22 = sPtr(new Node("grandChild22"));
  pChild2->addChild(pGrandChild22);

  // now start walking

  title("Recursive left-to-right Depth First Search");
  DFS_r_ltr(pRoot);
  putLine();
  pRoot->visited(false);
  pChild1->visited(false);
  pChild2->visited(false);
  pGrandChild11->visited(false);
  pGrandChild21->visited(false);
  pGrandChild22->visited(false);
  pGreatGrandChild11->visited(false);

  title("Recursive bottom-to-top Depth First Search");
  DFS_r_ltrbtt(pRoot);
  putLine();
  pRoot->visited(false);
  pChild1->visited(false);
  pChild2->visited(false);
  pGrandChild11->visited(false);
  pGrandChild21->visited(false);
  pGrandChild22->visited(false);
  pGreatGrandChild11->visited(false);

  title("Recursive right-to-left Depth First Search");
  DFS_r_rtl(pRoot);
  putLine();
  pRoot->visited(false);
  pChild1->visited(false);
  pChild2->visited(false);
  pGrandChild11->visited(false);
  pGrandChild21->visited(false);
  pGrandChild22->visited(false);
  pGreatGrandChild11->visited(false);

  title("Stack based right-to-left Depth First Search");
  DFS_s_rtl(pRoot);
  putLine();
  pRoot->visited(false);
  pChild1->visited(false);
  pChild2->visited(false);
  pGrandChild11->visited(false);
  pGrandChild21->visited(false);
  pGrandChild22->visited(false);
  pGreatGrandChild11->visited(false);

  title("Stack based left-to-right Depth First Search");
  DFS_s_ltr(pRoot);
  putLine();
  pRoot->visited(false);
  pChild1->visited(false);
  pChild2->visited(false);
  pGrandChild11->visited(false);
  pGrandChild21->visited(false);
  pGrandChild22->visited(false);
  pGreatGrandChild11->visited(false);

  title("Queue based Breadth First Search");
  BFSq(pRoot);
  putLine(2);
}