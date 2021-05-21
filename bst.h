#ifndef __BST_H__ 
#define __BST_H__  

#include <iostream> 
#include <cassert>
#include <vector>
#include "type.h" 

using namespace std;

//Trabajado por Kevin De Lama y Diego Maizo

template <typename T>
class CBinaryTree
{
    struct Node
    {
      T data;//Maizo
      Node *m_pChild[2];
      Node *m_pParentNode;
      Node(const T &_data, Node *pParentNode, Node *pLeft=nullptr, Node *pRight=nullptr) //Maizo agregado const
        : data(_data)
      {   m_pChild[0] = pLeft;  m_pChild[1] = pRight;  m_pParentNode = pParentNode; }
      T getData()             { return data; } //Maizo
      void setData (T &_data) { data=_data; }  //Maizo
      Node *getParent()       { return m_pParentNode; }
    };
public:
    class Iterator
    { 
          Node *m_pNode;
          Node *getNode() { return m_pNode;  }
          void setNode(Node *pNode) { m_pNode = pNode;  }
      public:    
          Iterator(Node *pNode=nullptr): m_pNode(pNode) {};
          //Iterator (Iterator &other) : m_pNode(other.getNode())  {}
          T operator *() { assert(getNode() != nullptr); return getNode()->getData(); }
          Iterator operator++();
          Iterator operator--();
          bool operator==(Iterator &other)  {return getNode() == other.getNode(); }
          bool operator!=(Iterator &other)  {return getNode()!=other.getNode(); }
    };
    Iterator begin()
    {
      Node *pNode = getRoot();
      while(pNode->m_pChild[0])
        pNode = pNode->m_pChild[0];
      return Iterator(pNode);
    }
    Iterator end()  { return Iterator(nullptr); }

    Iterator rend()
    {
      Node *pNode = getRoot();
      while(pNode->m_pChild[1])
        pNode = pNode->m_pChild[1];
      return Iterator(pNode);
    }

    Iterator rbegin()
    { return Iterator(nullptr); }

private:
    Node *m_pRoot = nullptr;
    Node *getRoot() { return m_pRoot; }
public:
    CBinaryTree() {}
    
    void insert(const T &dato) 
    {   internal_insert(m_pRoot, nullptr, dato);   }

    void print1()
    { PostOrden(m_pRoot, 0, 1,cout); }
    
    void print2()
    { PreOrden(m_pRoot, 1, 0,cout);  }

    void print3()
    { InOrden(m_pRoot, 0, 1,cout);}

    void print4()
    { printBFS(m_pRoot); }

    void printEliminar(const T &dato)
    { eliminarNode(m_pRoot, dato);}

    bool printSearch(T &dato) 
    { search(m_pRoot, dato);}

private:
    void internal_insert(Node *&rParentPointer, Node *rParentNode, const T &dato); 
    void InOrden(Node *rParent, size_t c1, size_t c2, ostream &os);
    void PreOrden(Node *rParent, size_t c1, size_t c2, ostream &os);
    void PostOrden(Node *rParent, size_t c1, size_t c2, ostream &os);

    void Nivel (Node *rParent, T lvl);// Niveles
    T altura (Node *rParent);//Niveles
    void printBFS (Node *rParent);// Print Niveles
    
    bool search(Node *rParent, T &dato);//Delete
    Node *nodeMenor(Node *rParent);//Delete
    Node *eliminarNode(Node *rParent,const T &dato);//Print Delete 
};

template <typename T>
void CBinaryTree<T>::internal_insert(Node *&rParentPointer, Node *rParentNode, const T &dato) // kevin de lama y Maizo agregado const
{
  if(!rParentPointer)
  {   rParentPointer = new Node(dato, rParentNode);
      return;
  }
  internal_insert(rParentPointer->m_pChild[ dato > rParentPointer->getData() ], rParentPointer, dato);
}

template <typename T>
void CBinaryTree<T>::InOrden(Node *rParent, size_t c1, size_t c2, ostream &os)
{
  if(rParent)
  {
    InOrden(rParent->m_pChild[c1], c1, c2, os);
    os << rParent->getData() << endl;
    InOrden(rParent->m_pChild[c2], c1, c2, os);
  }
}

template <typename T>
void CBinaryTree<T>::PreOrden(Node *rParent, size_t c1, size_t c2, ostream &os)
{
  if(rParent)
  {
    os << rParent->getData() << endl;
    PreOrden(rParent->m_pChild[c2], c1, c2, os);
    PreOrden(rParent->m_pChild[c1], c1, c2, os);
  }
}

template <typename T>
void CBinaryTree<T>::PostOrden(Node *rParent, size_t c1, size_t c2, ostream &os)
{
  if(rParent)
  {
    PostOrden(rParent->m_pChild[c1], c1, c2, os);
    PostOrden(rParent->m_pChild[c2], c1, c2, os);
    os << rParent->getData() << endl;
  }
}
template <typename T>
void CBinaryTree<T>::Nivel(Node *rParent, T lvl)
{
  if (rParent == nullptr)
      return;
  else if (lvl == 0)
      cout << rParent -> getData() << " ";
  else // level > 0  
  {
    Nivel(rParent -> m_pChild[0] , lvl - 1);
    Nivel(rParent -> m_pChild[1] , lvl - 1);
  }
}

template <typename T>
T CBinaryTree<T>::altura(Node *rParent)
{
  if (!rParent)//rParent==nullptr
    return -1;
  else 
  {
    T L_alt =altura (rParent->m_pChild[0]);
    T R_alt =altura (rParent->m_pChild[1]);
    if (L_alt>R_alt)
      return (L_alt+1);
    else 
      return(R_alt+1);
  }
}

template <typename T>
void CBinaryTree<T>::printBFS(Node *rParent)
{
  T h = altura(rParent);
  for (T i=0; i<=h; i++)
    Nivel(rParent, i);
}

template <typename T>
bool CBinaryTree<T>::search(Node *rParent, T &dato)
{
  if (rParent!=nullptr)
  {
    if (rParent->getData()==dato)
    { return true; }
    else
    { return search(rParent->m_pChild[dato > rParent->getData()], dato); }
  }
  return false;
}

template <typename T>
typename CBinaryTree<T>::Node *CBinaryTree<T>::nodeMenor(Node *rParent)
{
Node *curr = rParent; //curr = current

while (curr->m_pChild[0]!=nullptr)
  { curr=curr->m_pChild[0]; }
return curr; 
}

template <typename T>
typename CBinaryTree<T>::Node *CBinaryTree<T>::eliminarNode(Node *rParent,const T &dato){
  if(rParent == nullptr){
    return rParent;
  }
  else if (dato < rParent->getData())
  { rParent->m_pChild[0] = eliminarNode(rParent->m_pChild[0], dato); }

  else if (dato > rParent->getData())
  { rParent->m_pChild[1] = eliminarNode(rParent->m_pChild[1], dato); }

  else
  {
    if(rParent->m_pChild[0] == nullptr){
      Node *temp = rParent->m_pChild[1];
      delete rParent;
      return temp;

    } else if(rParent->m_pChild[1] == nullptr){
      Node *temp = rParent->m_pChild[0];
      delete rParent;
      return temp;

    } else if (rParent->m_pChild[0] == nullptr && rParent->m_pChild[1] == nullptr)
    { return nullptr; }

    Node* temp = nodeMenor(rParent->m_pChild[1]);
    T newDato = temp->getData();
    rParent->setData(newDato);
    rParent->m_pChild[1]=eliminarNode(rParent->m_pChild[1], dato);
  }
  return rParent;
}

//igaules
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

template <typename T>
typename CBinaryTree<T>::Iterator CBinaryTree<T>::Iterator::operator--()
{
    Node *pNode = getNode();
    if(pNode->m_pChild[0]) // Tiene hijo izq?
    {
      pNode = pNode->m_pChild[0];
      while(pNode->m_pChild[1])
        pNode = pNode->m_pChild[1];
      setNode(pNode);
      return *this;
    } else {
      Node *pParent = pNode->getParent();
      while(pParent && pParent->m_pChild[0] == pNode) // Mientras venga por el lado derecho => subir
      { pNode = pParent;
        pParent = pParent->getParent();    }
      if(pParent && pParent->m_pChild[1] == pNode) // Soy el hijo izquierdo
      { setNode(pParent);
      return *this; }
     setNode(nullptr);
    return *this;}
}

#endif  