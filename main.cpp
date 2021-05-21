#include <iostream>
#include <vector>
#include "bst.h"
#include "type.h"

//Realizado por Kevin De Lama y Diego Maizo

using namespace std;

int main()
{
  CBinaryTree<T1> bst;
  T1 dato, borrar;
  
  bst.insert(50);
  bst.insert(30);
  bst.insert(70);
  bst.insert(90);
  bst.insert(10);
  bst.insert(40);
  bst.insert(100);
  bst.insert(80);

  cout<<"Print iterator Ascendente"<<endl;
  CBinaryTree<T1>::Iterator iter = bst.begin();
  CBinaryTree<T1>::Iterator iter2 = bst.end();
  for(; iter != iter2; ++(iter))
    cout << *iter << endl;


  
  cout<<"Print iterator Descendente"<<endl;
  CBinaryTree<T1>::Iterator iter3 = bst.rbegin();
  CBinaryTree<T1>::Iterator iter4 = bst.rend();
  for(; iter4 != iter3; --(iter4))
    cout << *iter4 << endl; 

  cout << "PostOrder..."<<endl;
  bst.print1();

  cout << "PreOrder..."<<endl;
  bst.print2();

  cout <<"InOrder..."<<endl;
  bst.print3();

  cout <<"Print Nivel (BFS)"<<endl; 
  bst.print4();

  cout<<"\nIngrese un numero para eliminarlo"<<endl;
  cin>>borrar;

  if(bst.printSearch(borrar))
  {
    bst.printEliminar(borrar);
    cout<<"El numero: "<<borrar<<" ha sido eliminado"<<endl;
    bst.print3();//In order
    bst.print4();//Niveles
  }else{
    cout<<"No se encuentra el numero: "<<borrar<<" en el arbol"<<endl;
  }

  cout<<"\nIngrese un numero para buscarlo"<<endl;
  cin>>dato;

  if(bst.printSearch(dato))
  {
    cout<<"El numero buscado es: "<<dato<<endl;
  }else{
    cout<<"No se encuentra el numero: "<<dato<<" en el arbol"<<endl;
  }
  
  return 0;
}
