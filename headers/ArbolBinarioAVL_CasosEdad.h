#ifndef U05_ARBOL_ARBOL_ArbolBinarioAVL_CasosEdad_H_
#define U05_ARBOL_ARBOL_ArbolBinarioAVL_CasosEdad_H_

#include "./NodoArbolAVL_CasosEdad.h"

template <class T>
class ArbolBinarioAVL_CasosEdad{

protected:

  NodoArbolAVL_CasosEdad<T> *root;

public:
  ArbolBinarioAVL_CasosEdad();

  void put(T data);

  T search(T data);

  void remove(T data);

  void inorder();

  ~ArbolBinarioAVL_CasosEdad();

  bool esVacio();

  int getBalance(){
    return getBalance(root);
  }

private:
  T search(T data, NodoArbolAVL_CasosEdad<T> *r);

  void inorder(NodoArbolAVL_CasosEdad<T> *r);


  int max(int a, int b);
  int calculateHeight(NodoArbolAVL_CasosEdad<T> *r);
  int getBalance(NodoArbolAVL_CasosEdad<T> *r);
  NodoArbolAVL_CasosEdad<T> *rotacionDerecha(NodoArbolAVL_CasosEdad<T> *y);
  NodoArbolAVL_CasosEdad<T> *rotacionIzquierda(NodoArbolAVL_CasosEdad<T> *x);
  NodoArbolAVL_CasosEdad<T> *put(T data, NodoArbolAVL_CasosEdad<T> *r);
  NodoArbolAVL_CasosEdad<T> *remove(T data, NodoArbolAVL_CasosEdad<T> *r);

  NodoArbolAVL_CasosEdad<T> *findMin(NodoArbolAVL_CasosEdad<T> *r);
  
};

/**
 * Constructor del Arbol
 * @tparam K Clave por la cual va a ordenar el árbol
 * @tparam T Valor guardado por el árbol
 */
template <class T>
ArbolBinarioAVL_CasosEdad<T>::ArbolBinarioAVL_CasosEdad() { root = nullptr; }

/**
 * Destructor del Arbol
 */
template <class T>
ArbolBinarioAVL_CasosEdad<T>::~ArbolBinarioAVL_CasosEdad() {}

/**
 * Busca un dato en el árbol. Si no esta el dato en el árbol
 * tira una excepción
 * @param clave Valor a buscar
 * @return el valor buscado
 */
template <class T>
T ArbolBinarioAVL_CasosEdad<T>::search(T data){

  return search(data, root);
}

template <class T>
T ArbolBinarioAVL_CasosEdad<T>::search(T data, NodoArbolAVL_CasosEdad<T> *r){

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
void ArbolBinarioAVL_CasosEdad<T>::put(T data) { root = put(data, root); }

template <class T>
NodoArbolAVL_CasosEdad<T> *ArbolBinarioAVL_CasosEdad<T>::put(T data, NodoArbolAVL_CasosEdad<T> *r){

//1. Realizar Insercion normal
  if (r == nullptr) {
  
    return new NodoArbolAVL_CasosEdad<T>(data);
  }
  if (r->getClave() >= stoi(data[17])){
  
    r->setLeft(put(data, r->getLeft()));
  } else{
    r->setRight(put(data, r->getRight()));
  }
  
  //2. Actualizar altura de este nodo padre
  r->setHeight(max(calculateHeight(r->getLeft()), calculateHeight(r->getRight())) + 1);

  //3. Obtener el factor de balance de este nodo padre
  // y chequear si este nodo se desbalanceo
  int balance = getBalance(r);

  //Quedo desbalanceado II: corresponde una rot Der
  if (balance > 1 && stoi(data[17]) <= r->getLeft()->getClave()){
    return rotacionDerecha(r);
  }

  //Quedo desbalanceado ID: corresponde una rot Izq Der
  if (balance > 1 && stoi(data[17]) > r->getLeft()->getClave()) {
    r->setLeft(rotacionIzquierda(r->getLeft()));
    return rotacionDerecha(r);
  }

  //Quedo desbalanceado DD: corresponde una rot Izq
  if (balance < -1 && stoi(data[17]) >= r->getRight()->getClave()){
    return rotacionIzquierda(r);
  }

  //Quedo desbalanceado DI: corresponde una rot Der Izq
  if (balance < -1 && stoi(data[17]) <= r->getRight()->getClave()){
    r->setRight(rotacionDerecha(r->getRight()));
    return rotacionIzquierda(r);
  }
  return r;
}

template <class T>
NodoArbolAVL_CasosEdad<T> *ArbolBinarioAVL_CasosEdad<T>::findMin(NodoArbolAVL_CasosEdad<T> *r){

  {
    NodoArbolAVL_CasosEdad<T> *ret = r;
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
bool ArbolBinarioAVL_CasosEdad<T>::esVacio() { return root == nullptr; }



/**
 * Recorre un árbol en orden
 */
template <class T>
void ArbolBinarioAVL_CasosEdad<T>::inorder(){

  inorder(root);
  std::cout << std::endl;
}

template <class T>
void ArbolBinarioAVL_CasosEdad<T>::inorder(NodoArbolAVL_CasosEdad<T> *r){

  if (r == nullptr){
  
    return;
  }

  inorder(r->getLeft());
  r->print();
  inorder(r->getRight());
}



template <class T>
int ArbolBinarioAVL_CasosEdad<T>::max(int a, int b)
{
  return (a > b) ? a : b;
}

template <class T>
int ArbolBinarioAVL_CasosEdad<T>::calculateHeight(NodoArbolAVL_CasosEdad<T> *r){

  if (r == nullptr){
  
    return 0;
  }
  else
    return r->getHeight();
}
template <class T>
int ArbolBinarioAVL_CasosEdad<T>::getBalance(NodoArbolAVL_CasosEdad<T> *r){

  if (r == nullptr){
  
    return 0;
  }
  return calculateHeight(r->getLeft()) - calculateHeight(r->getRight());
}
template <class T>
NodoArbolAVL_CasosEdad<T> *ArbolBinarioAVL_CasosEdad<T>::rotacionDerecha(NodoArbolAVL_CasosEdad<T> *y){

  NodoArbolAVL_CasosEdad<T> *x = y->getLeft();
  NodoArbolAVL_CasosEdad<T> *T2 = x->getRight();

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
NodoArbolAVL_CasosEdad<T> *ArbolBinarioAVL_CasosEdad<T>::rotacionIzquierda(NodoArbolAVL_CasosEdad<T> *x){

  NodoArbolAVL_CasosEdad<T> *y = x->getRight();
  NodoArbolAVL_CasosEdad<T> *T2 = y->getLeft();

  //Rotacion
  y->setLeft(x);
  x->setRight(T2);

  //Atualizar alturas
  x->setHeight(max(calculateHeight(x->getLeft()), calculateHeight(x->getRight())) + 1);
  y->setHeight(max(calculateHeight(y->getLeft()), calculateHeight(y->getRight())) + 1);

  //Devolver la nueva raiz
  return y;
}

#endif // U05_ARBOL_ARBOL_ArbolBinarioAVL_CasosEdad_H_
