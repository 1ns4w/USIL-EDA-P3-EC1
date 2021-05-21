#ifndef __BST_H__ //Maizo Diego
#define __BST_H__  //kevin de lama

#include <iostream> //Maizo
#include <vector>
#include "type.h" //Maizo

using namespace std;

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
      bool isRightChild() {
        return m_pParentNode &&
          m_pParentNode->m_pChild[1] &&
          m_pParentNode->m_pChild[1]->getData()==data;
      }
      T getData()             { return data; } //Maizo
      void setData (T &_data) { data=_data; }
      void setParent (Node *pParentNode) { m_pParentNode=pParentNode; }
      Node *getParent()       { return m_pParentNode; }
    };


  public:
    class Iterator {
      Node *m_pNode;
      Node *getNode() { return m_pNode;  }
      void setNode(Node *pNode) { m_pNode = pNode;  }
  public:    
      Iterator(Node *pNode=nullptr): m_pNode(pNode) {};
      Iterator(Iterator &other) : m_pNode(other.getNode())  {}
      T operator *() { assert(getNode() != nullptr); return getNode()->getData(); }
      T data() {  return getNode()->getData(); }
      Iterator operator++();
      Iterator operator--();
      bool operator==(Iterator &other)  {return getNode() == other.getNode(); }
      bool operator!=(Iterator &other)  {return !(*this == other); }
      bool empty() {
        return getNode() == nullptr;
      }
    };
  private:
    int cantidad = 0;

    Node *beginNode(Node *pNode) {
      while(pNode->m_pChild[0])
        pNode = pNode->m_pChild[0];
      return pNode;
    }
    Iterator begin()
    {
      Node *pNode = beginNode(m_pRoot);
      return Iterator(pNode);
    }

    Node *lastNode(Node *pNode) {
      // Node *pNode = getRoot();
      while(pNode->m_pChild[1])
        pNode = pNode->m_pChild[1];
      return pNode;
    }

    Iterator last()
    {
      Node *pNode = lastNode(m_pRoot);
      return Iterator(pNode);
    }
  private:
    Node *m_pRoot = nullptr;
    Node *getRoot() { return m_pRoot; }
  void printNodeData (Node *n, string label = "", string notF = "Not found", string fin = "\n") {
    if (n) {
      cout << label << n->getData() << fin;
    } else {
      cout << notF << fin;
    }
  }

  void printNodeAllData(Node *node) {
    printNodeData(node, "node: ", "No node");
    if (node) {
      printNodeData(node->m_pChild[0], "node->m_pChild[0]: ", "No node->m_pChild[0]");
      printNodeData(node->m_pChild[1], "node->m_pChild[1]: ", "No node->m_pChild[1]");
      printNodeData(node->getParent(), "NodeParent: ", "No NodeParent");
    }
    cout << "end node ------;" << endl;
  }
public:
  void test() {
    vector<int> numbers {2, 4, 6, 8};
    numbers[5];
  }

  void remove(const T valor, bool debug = false) {
    Node *n = find(valor);
    if (!n) return;
    Node *newNode = nullptr;
    Node *parent = n->getParent();
    if (debug) printNodeData(n, "n: ", "No n");
    if (n->m_pChild[0] && n->m_pChild[1]) {
      newNode =  lastNode(n->m_pChild[0]);
      Node *newNodeParent = newNode->getParent();
        // printNodeAllData(newNode);
      if (newNode->isRightChild()) {
        newNodeParent->m_pChild[1] = newNode->m_pChild[0];
        if (newNodeParent->m_pChild[1]) newNodeParent->m_pChild[1]->setParent(newNodeParent);
      } else {
        newNode->m_pChild[1] = n->m_pChild[1];
        if (newNode->m_pChild[1]) newNode->m_pChild[1]->setParent(newNode);
      }
    } else if (n->m_pChild[1]) {
      // if (debug) printNodeAllData(n->m_pChild[1]);
      newNode = n->m_pChild[1];
    } else {
      newNode = n->m_pChild[0];
    }
    if (newNode) {
      if (parent) {
        parent->m_pChild[n->isRightChild()] = newNode;
      } else {
        for(int i=0;i<2;++i) {
          if (!n->m_pChild[i] || n->m_pChild[i]->getData()!=newNode->getData()) newNode->m_pChild[i] = n->m_pChild[i];
          if (newNode->m_pChild[i]) newNode->m_pChild[i]->setParent(newNode);
        }
      }
      newNode->setParent(parent);
      if (debug) printNodeAllData(newNode);
      if (debug) printNodeAllData(newNode->getParent());
    } else if (n->m_pParentNode) {
      n->m_pParentNode->m_pChild[n->isRightChild()] = nullptr;
      if (debug) printNodeAllData(n);
      if (debug) printNodeAllData(n->m_pParentNode);
    }
    n->m_pChild[1] = nullptr;
    n->m_pChild[0] = nullptr;
    n->m_pParentNode = nullptr;
    // printNodeAllData(newNode->m_pChild[0]);
    if (n->getData() == m_pRoot->getData()) {
      m_pRoot=newNode;
      if (debug) printNodeAllData(m_pRoot);
    }
    n = nullptr;
    cantidad--;
  }
  
  Node *find(const T valor) {
    return findAny(m_pRoot, valor);
  }

  Node *findAny(Node *nParent, const T valor) {
    // printNodeData(nParent, "Root: ", "No root");
    while (nParent != nullptr && nParent->getData()!=valor) {
      nParent = nParent->m_pChild[nParent->getData()<valor];
      // printNodeData(nParent, "next: ", "No next");
    }
    return nParent;
  }
    CBinaryTree() {}
    void insert_old(const T &dato) //Maizo agregado const
    {   
      cantidad++;
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
    {   internal_insert(m_pRoot, nullptr, dato);   }

    void VisitNodesAsc()
    { InOrden(m_pRoot, 0, 1, "", "",cout);  }
    
    void VisitNodesDesc()
    { InOrden(m_pRoot, 1, 0, "", "",cout);  }

    void VisitNodesPostOrden()
    { PostOrden(m_pRoot, 0, 1, "", "",cout);  }

    void VisitNodesPreOrden()
    { PreOrden(m_pRoot, 0, 1, "", "",cout);  }
    
    void visitNodeAscIterador() {
      Iterator iter = begin();
      // cout << iter << endl;
      InOrderGenIterator(iter, true);
    }
    
    void visitNodeDescIterador() {
      Iterator iter = last();
      InOrderGenIterator(iter, false);
    }
    void recorridoBFS() {
      int pos = 0;
      int colaCant = 0;
      Node *cola[1000000] ;
      cola[colaCant++] = getRoot();
      Node *current = nullptr;
      while (!!(current = cola[pos])) {
        // printNodeData(current, "BFS: ");
        for (int i=0; i<2; ++i) {
          if (current->m_pChild[i]) {
            cola[colaCant++] = current->m_pChild[i];
          }
        }
        printNodeData(current);
        pos++; 
      }
    }

    void recorridoBFSNode (Node *parent) {
      
    }

    void recorridoDFS ( ) {
      recorridoDFSNode(m_pRoot);
    }

    void recorridoDFSNode (Node *parent) {
      printNodeData(parent);
      for (int i=0; i<2; ++i) {
        if (parent->m_pChild[i]) {
          recorridoDFSNode(parent->m_pChild[i]);
        }
      }
    }


private:
    void internal_insert(Node *&rParentPointer, Node *rParentNode,const T &dato); //Maizo agregado const
    void InOrden(Node *rParent, size_t c1, size_t c2, string space, string flecha, ostream &os);
    void PreOrden(Node *rParent, size_t c1, size_t c2, string space, string flecha, ostream &os);
    void PostOrden(Node *rParent, size_t c1, size_t c2, string space, string flecha, ostream &os);

    void InOrderGenIterator(Iterator iter, bool asc=true/* , string space, string flecha, ostream &os */) {
      for(; !iter.empty(); asc ? ++iter : --iter)
        cout << iter.data() << endl;
    }
};

template <typename T>
void CBinaryTree<T>::internal_insert(Node *&rParentPointer, Node *rParentNode, const T &dato) // kevin de lama y Maizo agregado const
{
  if(!rParentPointer)
  {   rParentPointer = new Node(dato, rParentNode);
      cantidad++;
      return;
  }
  internal_insert(rParentPointer->m_pChild[ dato > rParentPointer->getData() ], rParentPointer, dato);
}

template <typename T>
void CBinaryTree<T>::InOrden(Node *rParent, size_t c1, size_t c2, string space, string flecha, ostream &os)
{
  if(rParent)
  {
    InOrden(rParent->m_pChild[c1], c1, c2, space+"  ", "/", os);
    os << space <<flecha<< rParent->getData() << endl;
    InOrden(rParent->m_pChild[c2], c1, c2, space+"  ", "\\", os);
  }
}

template <typename T>
void CBinaryTree<T>::PreOrden(Node *rParent, size_t c1, size_t c2, string space, string flecha, ostream &os)
{
  // printNodeData(rParent);
  // printNodeData(rParent->m_pChild[0]->m_pChild[0]);
  // printNodeData(rParent->m_pChild[0]->m_pChild[1]);
  // // printNodeData(rParent->m_pChild[c2]);
  // return;
  if(rParent)
  {
    os << space <<flecha<< rParent->getData() << endl;
    PreOrden(rParent->m_pChild[c1], c1, c2, space+"  ", "/", os);
    PreOrden(rParent->m_pChild[c2], c1, c2, space+"  ", "\\", os);
  }
}

template <typename T>
// PostOrden
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
typename CBinaryTree<T>::Iterator CBinaryTree<T>::Iterator::operator++() {
  Node *pNode = getNode();
  if(pNode->m_pChild[1]) // Tiene hijo derecho?
  {
    pNode = pNode->m_pChild[1];
    while(pNode->m_pChild[0])
      pNode = pNode->m_pChild[0];
    setNode(pNode);
    return *this;
  }
  Node *pParent = pNode->getParent();
  // cout << pParent->getData() << " ";
  while(pParent && pParent->m_pChild[1] == pNode) // Mientras venga por el lado derecho => subir
  {
    pNode = pParent;
    pParent = pParent->getParent();
  }
  if(pParent && pParent->m_pChild[0] == pNode) // Soy el hijo izquierdo
  { setNode(pParent);
    return *this;
  }
  setNode(nullptr);
  return *this;
}

template <typename T>
typename CBinaryTree<T>::Iterator CBinaryTree<T>::Iterator::operator--() {
  Node *pNode = getNode();
  if(pNode->m_pChild[0]) // Tiene hijo derecho?
  {
    pNode = pNode->m_pChild[0];
    while(pNode->m_pChild[1])
      pNode = pNode->m_pChild[1];
    setNode(pNode);
    return *this;
  }
  Node *pParent = pNode->getParent();
  while(pParent && pParent->m_pChild[0] == pNode) // Mientras venga por el lado derecho => subir
  {
    pNode = pParent;
    pParent = pParent->getParent();
  }
  if(pParent && pParent->m_pChild[1] == pNode) // Soy el hijo izquierdo
  { setNode(pParent);
    return *this;
  }
  setNode(nullptr);
  return *this;
}

#endif //Maizo Diego  