#ifndef __BST_H__ 
#define __BST_H__  
//by jose terrones
#include <iostream> 
#include <cassert> 
#include <vector>
#include "type.h"

using namespace std;

template <typename T>
class CBinaryTree
{
    struct Node
    {
      T data;
      Node *m_pChild[2];
      Node *m_pParentNode;
      Node(const T &_data, Node *pParentNode, Node *pLeft=nullptr, Node *pRight=nullptr)
        : data(_data)
      {   m_pChild[0] = pLeft;  m_pChild[1] = pRight;  m_pParentNode = pParentNode; }
      T getData()             { return data; } 
      void setData (T &_data) { data=_data; } 
      Node *getParent()       { return m_pParentNode; }
    };
public: //Iterador
    class Iterator
    {
          Node *m_pNode;
          Node *getNode() { return m_pNode;  }
          void setNode(Node *pNode) { m_pNode = pNode;  }
      public:    
          Iterator(Node *pNode=nullptr): m_pNode(pNode) {};
          Iterator(Iterator &other) : m_pNode(other.getNode())  {}
          T operator *() { assert(getNode() != nullptr); return getNode()->getData(); }
          Iterator operator++(); //funcion ascendente
          Iterator operator--(); //funcion decendente
          bool operator==(Iterator &other)  {return getNode() == other.getNode(); }
          bool operator!=(Iterator &other)  {return getNode()!=other.getNode(); }
    };
     //comienzo y fin de iterador descendente
    Iterator begin()
    {
      Node *pNode = getRoot();
      while(pNode->m_pChild[0])
        pNode = pNode->m_pChild[0];
      return Iterator(pNode);
    }
    Iterator end()  { return Iterator(nullptr); }
    //comienzo y fin de iterador ascendente
    Iterator newend()
    {
      Node *pNode = getRoot();
      while(pNode->m_pChild[1])
        pNode = pNode->m_pChild[1];
      return Iterator(pNode);
    }

    Iterator newbegin()  { return Iterator(nullptr); }
private:
    Node *m_pRoot = nullptr;
    Node *getRoot() { return m_pRoot; }
public:
    CBinaryTree() {}
    void insert_old(const T &dato)
    {   
        Node **ppNode = &m_pRoot;
        while(*ppNode != nullptr)      
        { if(dato > (*ppNode)->getData())
            ppNode = &ppNode->m_pChild[1];
          else
            ppNode = &ppNode->m_pChild[0];
        }
        *ppNode = new Node(dato);
    }
    void insert(const T &dato) 
    {   internal_insert(m_pRoot, nullptr, dato);   }

    void Preorder() //funcion PreOrden
    { PreOrden(m_pRoot, 0, 1, "", "",cout);  }
    
    void Postorder() //funcion PostOrden
    { PostOrden(m_pRoot, 1, 0, "", "",cout);  }

    void Inorder() //funcion Inorder
    { InOrden(m_pRoot, 1, 0, "", "",cout); }

    void Preorder2d() //funcion PreOrden en 2d
    { PreOrden2d(m_pRoot, 0, 1," ", cout);  }
    
    void Postorder2d() //funcion PostOrden en 2d
    { PostOrden2d(m_pRoot, 0, 1, " ",cout);  }

    void Inorder2d() //funcion InOrden en ed
    { InOrden2d(m_pRoot, 0, 1, " ",cout); }

    void Borrar(const T &dato) //funcion borrar
    { Deleted(m_pRoot, 0, 1,  dato);}

    void Iterator_descendente() //funcion iterador decendente
    { CBinaryTree<T1>::Iterator iter = begin();
      CBinaryTree<T1>::Iterator iter2 = end();
        for(; iter != iter2; ++(iter)) 
      cout << *iter << endl; 
    }

    void Iterator_ascend() //funcion iterador ascendente
    { CBinaryTree<T1>::Iterator iter = newend();
      CBinaryTree<T1>::Iterator iter2 = newbegin();
        for(; iter != iter2; --(iter)) 
      cout << *iter << endl; 
    }
    /* //se avanzo la funcion BFS
    void BFS()
    { LvlOrdenBFS(m_pRoot); }
    */
    
private:
    void internal_insert(Node *&rParentPointer, Node *rParentNode, const T &dato); 
    void InOrden(Node *rParent, size_t c1, size_t c2, string space, string flecha, ostream &os);
    void PreOrden(Node *rParent, size_t c1, size_t c2, string space, string flecha, ostream &os);
    void PostOrden(Node *rParent, size_t c1, size_t c2, string space, string flecha, ostream &os);
    void InOrden2d(Node *rParent, size_t c1, size_t c2, string espacio,  ostream &os);
    void PreOrden2d(Node *rParent, size_t c1, size_t c2, string espacio,  ostream &os);
    void PostOrden2d(Node *rParent, size_t c1, size_t c2, string espacio,  ostream &os);
    Node *ElMenor(Node *rParent, size_t c1, size_t c2);//parte de borrar
    Node *Deleted(Node *rParent, size_t c1, size_t c2,const T &dato);//parte de borrar
    /* //se avanzo la funcion BFS
    void GivenLvl(Node *rParent, size_t c1, size_t c2, string space, T &lvl,  ostream &os); //parte de BFS
    void LvlOrdenBFS(Node *rParent); //parte de BFS
    */
};

template <typename T>
void CBinaryTree<T>::internal_insert(Node *&rParentPointer, Node *rParentNode, const T &dato)
{
  if(!rParentPointer)
  {   rParentPointer = new Node(dato, rParentNode);
      return;
  }
  internal_insert(rParentPointer->m_pChild[ dato > rParentPointer->getData() ], rParentPointer, dato);
}

template <typename T>
void CBinaryTree<T>::InOrden(Node *pNode, size_t c1, size_t c2, string space, string flecha, ostream &os)
{
  if(pNode)
  {
    InOrden(pNode->m_pChild[c1], c1, c2, space+"  ", "/", os);
    os << space <<flecha<< pNode->getData();
    if( pNode->getParent() )
      os << "(" << pNode->getParent()->getData() << ")";
    else
      os << "(*)";
    os << endl;
    InOrden(pNode->m_pChild[c2], c1, c2, space+"  ", "\\", os);
  }
}

template <typename T>
void CBinaryTree<T>::PreOrden(Node *rParent, size_t c1, size_t c2, string space, string flecha, ostream &os)
{
  if(rParent)
  {
    os << space <<flecha<< rParent->getData() << endl;
    PreOrden(rParent->m_pChild[c1], c1, c2, space+"  ", "/", os);
    PreOrden(rParent->m_pChild[c2], c1, c2, space+"  ", "\\", os);
  }
}


template <typename T>
void CBinaryTree<T>::PostOrden(Node *rParent, size_t c1, size_t c2, string space, string flecha, ostream &os)
{
  if(rParent)
  {
    PostOrden(rParent->m_pChild[c1], c1, c2, space+"  ", "/", os);
    PostOrden(rParent->m_pChild[c2], c1, c2, space+"  ", "\\", os);
    os << space <<flecha<< rParent->getData() << endl;
  }
}

template <typename T>
void CBinaryTree<T>::PreOrden2d(Node *rParent, size_t c1, size_t c2, string espacio, ostream &os)
{
  if(rParent)
  {
    os << rParent->getData()<< espacio;
    PreOrden2d(rParent->m_pChild[c1], c1, c2, espacio,  os);
    PreOrden2d(rParent->m_pChild[c2], c1, c2, espacio,  os);
  }
}

template <typename T>
void CBinaryTree<T>::InOrden2d(Node *rParent, size_t c1, size_t c2, string espacio, ostream &os)
{
  if(rParent)
  {
    InOrden2d(rParent->m_pChild[c1], c1, c2, espacio,  os);
    os << rParent->getData()<< espacio;
    InOrden2d(rParent->m_pChild[c2], c1, c2, espacio,  os);
  }
}

template <typename T>
void CBinaryTree<T>::PostOrden2d(Node *rParent, size_t c1, size_t c2, string espacio, ostream &os)
{
  if(rParent)
  {
    PostOrden2d(rParent->m_pChild[c1], c1, c2, espacio,  os);
    PostOrden2d(rParent->m_pChild[c2], c1, c2, espacio,  os);
    os << rParent->getData()<< espacio;
  }
}


template <typename T>
typename CBinaryTree<T>::Iterator CBinaryTree<T>::Iterator::operator++()
{
    Node *pNode = getNode();
    if(pNode->m_pChild[1]) // Tiene hijo derecho?
    {
      pNode = pNode->m_pChild[1];
      while(pNode->m_pChild[0])
        pNode = pNode->m_pChild[0];
      setNode(pNode);
      return *this;
    } else {
      Node *pParent = pNode->getParent();
      while(pParent && pParent->m_pChild[1] == pNode) // Mientras venga por el lado derecho => subir
      { pNode = pParent;
        pParent = pParent->getParent();    }
      if(pParent && pParent->m_pChild[0] == pNode) // Soy el hijo izquierdo
      { setNode(pParent);
      return *this; }
     setNode(nullptr);
    return *this;}
}

//lado opuesto del operador ++, si era 1 ahora es 0 en m_pChild
template <typename T>
typename CBinaryTree<T>::Iterator CBinaryTree<T>::Iterator::operator--()
{
    Node *pNode = getNode();
    if(pNode->m_pChild[0]) // Tiene hijo izquierdo?
    {
      pNode = pNode->m_pChild[0];
      while(pNode->m_pChild[1])
        pNode = pNode->m_pChild[1];
      setNode(pNode);
      return *this;
    } else {
      Node *pParent = pNode->getParent();
      while(pParent && pParent->m_pChild[0] == pNode) // Mientras venga por el lado izquierdo => subir
      { pNode = pParent;
        pParent = pParent->getParent();    }
      if(pParent && pParent->m_pChild[1] == pNode) // Soy el hijo derecho
      { setNode(pParent);
      return *this; }
     setNode(nullptr);
    return *this;}
}

//determina el menor nodo de la izquierda
template <typename T>
typename CBinaryTree<T>::Node *CBinaryTree<T>::ElMenor(Node *rParent, size_t c1, size_t c2)
{
Node *actual = rParent; 

while (actual->m_pChild[c1]!=nullptr)
  { 
    actual=actual->m_pChild[c1];
  }
return actual; 
}

//funcion para borrar nodos
template <typename T>
typename CBinaryTree<T>::Node *CBinaryTree<T>::Deleted(Node *rParent, size_t c1, size_t c2,const T &dato){
  if(rParent == nullptr)
  {
    return rParent;
  }
  else if (dato < rParent->getData())
  { 
    rParent->m_pChild[c1] = Deleted(rParent->m_pChild[c1],c1,c2, dato);
  }

  else if (dato > rParent->getData())
  { 
    rParent->m_pChild[c2] = Deleted(rParent->m_pChild[c2],c1,c2, dato);
  }

  else
  {
    if(rParent->m_pChild[c1] == nullptr)
    {
      Node *nuevo = rParent->m_pChild[c2];
      delete rParent;
      return nuevo;
    } 
    else if(rParent->m_pChild[c2] == nullptr)
    {
      Node *nuevo = rParent->m_pChild[c1];
      delete rParent;
      return nuevo;
    } 
    else 
    {
      Node* nuevo = ElMenor(rParent->m_pChild[c2],c1,c2);
      T valor_modificado = nuevo->getData();
      rParent->setData(valor_modificado);
      rParent->m_pChild[c2]=Deleted(rParent->m_pChild[c2],c1,c2, dato);
    }
  }
  return rParent;
}
/* //se avanzo la funcion BFS
//imprimir nivel de orden del BFS
template <typename T>
void CBinaryTree<T>::LvlOrdenBFS(Node *rParent)
{
  T1 h = height(rParent);
  for (T i=0; i<=h; i++)
  { GivenLvl(m_pRoot, 0, 1, " ", i, cout);  }
}

template <typename T>
//imprimir la altura
void CBinaryTree<T>::height(Node *rParent, size_t c1, size_t c2, string space, T &lvl,  ostream &os)
{
  if (rParent == nullptr){}

}


template <typename T>
//imprimir el nivel dado
void CBinaryTree<T>::GivenLvl(Node *rParent, size_t c1, size_t c2, string space, T &lvl,  ostream &os)
{
  if (rParent == nullptr)
    return;
  else if (lvl==0)
    os<<rParent->getData()<<space;
  else
  {
    GivenLvl(rParent->m_pChild[c1], lvl-1);
    GivenLvl(rParent->m_pChild[c2], lvl-1);
  }
}
*/
#endif 
