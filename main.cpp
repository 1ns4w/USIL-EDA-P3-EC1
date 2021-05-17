#include <iostream>
#include "bst.h"
#include "type.h"

using namespace std;

int main()
{
  CBinaryTree<T1> bst;
  
  bst.insert(50);
  bst.insert(30);
  bst.insert(70);
  bst.insert(90);
  bst.insert(10);
  bst.insert(40);
  bst.insert(100);

  cout << "Ascendente ..." << endl;
  bst.VisitNodesAsc();
  cout << "Descendente ..." << endl;
  bst.VisitNodesDesc();
}