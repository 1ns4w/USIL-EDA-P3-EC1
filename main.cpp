#include <iostream>
#include "bst.h"
#include "type.h"
//by jose terrones
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


  cout << "Iterator Descendente..." << endl;

  bst.Iterator_descendente();

  cout << endl<< "Iterator Ascendente..." << endl;

  bst.Iterator_ascend();

  cout<<endl<< "Inorder ..." << endl;
  bst.Inorder();
  cout<<endl << "Preorder ..." << endl;
  bst.Preorder();
  cout<<endl << "Postorder ..." << endl;
  bst.Postorder();

  cout <<endl<< "Preorder 2d ..." << endl;
  bst.Preorder2d();
  cout<< endl << "Inorder en 2d ..." << endl;
  bst.Inorder2d();
  cout << endl<< "Postorder en 2d ..." << endl;
  bst.Postorder2d();

  bst.Borrar(100);
  cout <<  "" << endl;

  cout<< endl<< "Se borro el dato 100..." << endl;
  cout<< "Para comprobar q se borro el dato..." << endl;
  //se usa Inorder para ver si se elimino el dato
  cout<<endl << "Inorden ..." << endl;
  bst.Inorder();
  /*
  cout << "Imprimir BFS..." << endl;
  bst.BFS();
  */
}
