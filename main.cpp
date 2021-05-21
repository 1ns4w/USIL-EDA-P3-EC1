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

  cout << "Ascendente iterator ..." << endl;
  bst.visitNodeAscIterador();

  cout << "Descendente iterator ..." << endl;
  bst.visitNodeDescIterador();

  // bst.test();
  bst.remove(10);
  bst.remove(30);
  bst.remove(50);
  bst.remove(40);

  cout << "Pre-Order:" << endl;
  bst.VisitNodesPreOrden();
  cout << "In-Order:" << endl;
  bst.VisitNodesAsc();
  cout << "Post-Order:" << endl;
  bst.VisitNodesPostOrden();

  cout << "recorrido BFS:" << endl;
  bst.recorridoBFS();

  cout << "recorrido DFS:" << endl;
  bst.recorridoDFS();
}