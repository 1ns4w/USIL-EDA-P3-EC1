#ifndef __BST_H__ //Maizo Diego
#define __BST_H__  //kevin de lama

#include <iostream> //Maizo
#include "type.h" //Maizo

using namespace std;

template <typename T>
class CBinaryTree
{
    struct Node
    {
      T data;//Maizo
      Node *m_pChild[2];
      Node(const T &_data, Node *pLeft=nullptr, Node *pRight=nullptr) //Maizo agregado const
        : data(_data)
      {   m_pChild[0] = pLeft;  m_pChild[1] = pRight;   }
      T getData()             { return data; } //Maizo
      void setData (T &_data) { data=_data; }  //Maizo
    };

    Node *m_pRoot = nullptr;
public:
    CBinaryTree() {}
    void insert_old(const T &dato) //Maizo agregado const
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
    void insert(const T &dato) //Maizo agregado const
    {   internal_insert(m_pRoot, dato);   }

    void VisitNodesAsc()
    { internalVisitNodes(m_pRoot, 0, 1, "", "",cout);  }
    
    void VisitNodesDesc()
    { internalVisitNodes(m_pRoot, 1, 0, "", "",cout);  }
    
private:
    void internal_insert(Node *&rParent,const T &dato); //Maizo agregado const
    void InOrden(Node *rParent, size_t c1, size_t c2, string space, string flecha, ostream &os);
    void PreOrden(Node *rParent, size_t c1, size_t c2, string space, string flecha, ostream &os);
    void PostOrden(Node *rParent, size_t c1, size_t c2, string space, string flecha, ostream &os);
};

template <typename T>
void CBinaryTree<T>::internal_insert(Node *&rParent, const T &dato) // kevin de lama y Maizo agregado const
{
  if(!rParent)
  {   rParent = new Node(dato);
      return;
  }
  internal_insert(rParent->m_pChild[ dato > rParent->getData() ], dato);
}

template <typename T>
void CBinaryTree<T>::InOrden(Node *rParent, size_t c1, size_t c2, string space, string flecha, ostream &os)
{
  if(rParent)
  {
    internalVisitNodes(rParent->m_pChild[c1], c1, c2, space+"  ", "/", os);
    os << space <<flecha<< rParent->getData() << endl;
    internalVisitNodes(rParent->m_pChild[c2], c1, c2, space+"  ", "\\", os);
  }
}

template <typename T>
void CBinaryTree<T>::PreOrden(Node *rParent, size_t c1, size_t c2, string space, string flecha, ostream &os)
{
  if(rParent)
  {
    os << space <<flecha<< rParent->getData() << endl;
    internalVisitNodes(rParent->m_pChild[c1], c1, c2, space+"  ", "/", os);
    internalVisitNodes(rParent->m_pChild[c2], c1, c2, space+"  ", "\\", os);
  }
}

template <typename T>
void CBinaryTree<T>::PostOrden(Node *rParent, size_t c1, size_t c2, string space, string flecha, ostream &os)
{
  if(rParent)
  {
    internalVisitNodes(rParent->m_pChild[c1], c1, c2, space+"  ", "/", os);
    internalVisitNodes(rParent->m_pChild[c2], c1, c2, space+"  ", "\\", os);
    os << space <<flecha<< rParent->getData() << endl;
  }
}

#endif //Maizo Diego  