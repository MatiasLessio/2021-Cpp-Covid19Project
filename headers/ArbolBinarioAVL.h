#ifndef U05_ARBOL_ARBOL_ARBOLBINARIOAVL_H_
#define U05_ARBOL_ARBOL_ARBOLBINARIOAVL_H_

#include "./NodoArbolAVL.h"

template <class T>
class ArbolBinarioAVL
{
protected:
  NodoArbolAVL<T> *root;

public:
  ArbolBinarioAVL();

  void put(T data);

  T search(T data);

  void remove(T data);

  void preorder();

  void inorder();

  void postorder();

  ~ArbolBinarioAVL();

  bool esVacio();

  int getBalance()
  {
    return getBalance(root);
  }

private:
  T search(T data, NodoArbolAVL<T> *r);
  void preorder(NodoArbolAVL<T> *r);
  void inorder(NodoArbolAVL<T> *r);
  void postorder(NodoArbolAVL<T> *r);

  int max(int a, int b);
  int calculateHeight(NodoArbolAVL<T> *r);
  int getBalance(NodoArbolAVL<T> *r);
  NodoArbolAVL<T> *rotacionDerecha(NodoArbolAVL<T> *y);
  NodoArbolAVL<T> *rotacionIzquierda(NodoArbolAVL<T> *x);
  NodoArbolAVL<T> *put(T data, NodoArbolAVL<T> *r);
  NodoArbolAVL<T> *remove(T data, NodoArbolAVL<T> *r);

  NodoArbolAVL<T> *findMin(NodoArbolAVL<T> *r);
  int stringAinteger(string stringDate);
};

/**
 * Constructor del Arbol
 * @tparam K Clave por la cual va a ordenar el árbol
 * @tparam T Valor guardado por el árbol
 */
template <class T>
ArbolBinarioAVL<T>::ArbolBinarioAVL() { root = nullptr; }

/**
 * Destructor del Arbol
 */
template <class T>
ArbolBinarioAVL<T>::~ArbolBinarioAVL() {}

/**
 * Busca un dato en el árbol. Si no esta el dato en el árbol
 * tira una excepción
 * @param clave Valor a buscar
 * @return el valor buscado
 */
template <class T>
T ArbolBinarioAVL<T>::search(T data)
{
  return search(data, root);
}

template <class T>
T ArbolBinarioAVL<T>::search(T data, NodoArbolAVL<T> *r)
{
  if (r == nullptr)
  {
    throw 404;
  }

  if (r->getData() == data)
  {
    return r->getData();
  }

  if (r->getData() > data)
  {
    return search(data, r->getLeft());
  }
  else
  {
    return search(data, r->getRight());
  }
}

/**
 * Agrega un dato al árbol
 * @param clave Clave para agregar el dato
 * @param dato Dato a agregar
 */
template <class T>
void ArbolBinarioAVL<T>::put(T data) { root = put(data, root); }

template<class T> 
int ArbolBinarioAVL<T>::stringAinteger(string stringDate) {
    string intDate;
    int num=stringDate.size();
    for(int i=0; i < num ; i++){
         int aux = stringDate[i];
        if(aux >= 48 && aux <=57){
            intDate += stringDate[i];
        }
    }
    return stoi(intDate);
}

template <class T>
NodoArbolAVL<T> *ArbolBinarioAVL<T>::put(T data, NodoArbolAVL<T> *r)
{
  //1. Realizar Insercion normal
  if (r == nullptr)
  {
    return new NodoArbolAVL<T>(data);
  }
  
  if (r->getClave() >= stringAinteger(data[13]))
  {
    r->setLeft(put(data, r->getLeft()));
  }
  else
  {
    r->setRight(put(data, r->getRight()));
  }

  //2. Actualizar altura de este nodo padre
  r->setHeight(max(calculateHeight(r->getLeft()), calculateHeight(r->getRight())) + 1);


  //3. Obtener el factor de balance de este nodo padre
  // y chequear si este nodo se desbalanceo
  int balance = getBalance(r);

  //Quedo desbalanceado II: corresponde una rot Der
  if (balance > 1 && stringAinteger(data[13]) <= r->getLeft()->getClave())
  {
    return rotacionDerecha(r);
  }

  //Quedo desbalanceado ID: corresponde una rot Izq Der
  if (balance > 1 && stringAinteger(data[13]) > r->getLeft()->getClave())
  {
    r->setLeft(rotacionIzquierda(r->getLeft()));
    return rotacionDerecha(r);
  }

  //Quedo desbalanceado DD: corresponde una rot Izq
  if (balance < -1 && stringAinteger(data[13]) >= r->getRight()->getClave())
  {
    return rotacionIzquierda(r);
  }

  //Quedo desbalanceado DI: corresponde una rot Der Izq
  if (balance < -1 && stringAinteger(data[13]) <= r->getRight()->getClave())
  {
    
    r->setRight(rotacionDerecha(r->getRight()));
    return rotacionIzquierda(r);
  }
  return r;
}

template <class T>
NodoArbolAVL<T> *ArbolBinarioAVL<T>::findMin(NodoArbolAVL<T> *r)
{
  {
    NodoArbolAVL<T> *ret = r;
    while (ret->getLeft() != nullptr)
      ret = ret->getLeft();

    return ret;
  }
}

/**
 * Informa si un árbol esta vacío
 * @return
 */
template <class T>
bool ArbolBinarioAVL<T>::esVacio() { return root == nullptr; }

/**
 * Recorre un árbol en preorden
 */
template <class T>
void ArbolBinarioAVL<T>::preorder()
{
  preorder(root);
  std::cout << std::endl;
}

template <class T>
void ArbolBinarioAVL<T>::preorder(NodoArbolAVL<T> *r)
{
  if (r == nullptr)
  {
    return;
  }

  std::cout << r->getData() << " ";
  preorder(r->getLeft());
  preorder(r->getRight());
}

/**
 * Recorre un árbol en orden
 */
template <class T>
void ArbolBinarioAVL<T>::inorder()
{
  inorder(root);
  std::cout << std::endl;
}

template <class T>
void ArbolBinarioAVL<T>::inorder(NodoArbolAVL<T> *r)
{
  if (r == nullptr)
  {
    return;
  }

  inorder(r->getLeft());
  r->print();
  inorder(r->getRight());
}

/**
 * Recorre un árbol en postorden
 */
template <class T>
void ArbolBinarioAVL<T>::postorder()
{
  postorder(root);
  std::cout << std::endl;
}

template <class T>
void ArbolBinarioAVL<T>::postorder(NodoArbolAVL<T> *r)
{
  if (r == nullptr)
  {
    return;
  }

  postorder(r->getLeft());
  postorder(r->getRight());
  std::cout << r->getData() << " ";
}


template <class T>
int ArbolBinarioAVL<T>::max(int a, int b)
{
  return (a > b) ? a : b;
}

template <class T>
int ArbolBinarioAVL<T>::calculateHeight(NodoArbolAVL<T> *r)
{
  if (r == nullptr)
  {
    return 0;
  }
  else
    return r->getHeight();
}
template <class T>
int ArbolBinarioAVL<T>::getBalance(NodoArbolAVL<T> *r)
{
  if (r == nullptr)
  {
    return 0;
  }
  return calculateHeight(r->getLeft()) - calculateHeight(r->getRight());
}
template <class T>
NodoArbolAVL<T> *ArbolBinarioAVL<T>::rotacionDerecha(NodoArbolAVL<T> *y)
{
  NodoArbolAVL<T> *x = y->getLeft();
  NodoArbolAVL<T> *T2 = x->getRight();

  //Rotacion
  x->setRight(y);
  y->setLeft(T2);

  //Actualizar alturas
  y->setHeight(max(calculateHeight(y->getLeft()), calculateHeight(y->getRight())) + 1);
  x->setHeight(max(calculateHeight(x->getLeft()), calculateHeight(x->getRight())) + 1);

  //Devolver la nueva raiz;
  return x;
}

template <class T>
NodoArbolAVL<T> *ArbolBinarioAVL<T>::rotacionIzquierda(NodoArbolAVL<T> *x)
{
  NodoArbolAVL<T> *y = x->getRight();
  NodoArbolAVL<T> *T2 = y->getLeft();

  //Rotacion
  y->setLeft(x);
  x->setRight(T2);

  //Atualizar alturas
  x->setHeight(max(calculateHeight(x->getLeft()), calculateHeight(x->getRight())) + 1);
  y->setHeight(max(calculateHeight(y->getLeft()), calculateHeight(y->getRight())) + 1);

  //Devolver la nueva raiz
  return y;
}

#endif // U05_ARBOL_ARBOL_ARBOLBINARIOAVL_H_
