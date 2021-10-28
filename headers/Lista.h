#ifndef PARCIAL2_LISTA_H
#define PARCIAL2_LISTA_H
#include "nodo.h"
/**
 * Clase que implementa una Lista Enlasada generica, ya que puede
 * almacenar cualquier tipo de dato T
 * @tparam T cualquier tipo de dato
 */
template <class T> class Lista {
private:
    Nodo<T> *inicio; //Si la lista esta vacia, su puntero de inicio debe apuntar al puntero null
//puntero al nodo de inicio
public:

    Lista();

    Lista(const Lista<T> &li);

    ~Lista();

    bool esVacia();

    int getTamanio();

    void insertar(int pos, T dato);

    void insertarPrimero(T dato);

    void insertarUltimo(T dato);

    void remover(int pos);

    T getDato(int pos);

    void reemplazar(int pos, T dato);

    void vaciar();

    void imprimir();

    void insertAfter2(T oldValue,unsigned int n, T newValue);
};
/**
 * Constructor de la clase Lista
 * @tparam T
 */
template <class T>
Lista<T>::Lista() {
    inicio=nullptr;
}

/**
 * Constructor por copia de la clase Lista
 * @tparam T
 * @param li
 */
template <class T>
Lista<T>::Lista(const Lista<T> &li) {
    inicio = li.inicio;
}

/**
 * Destructor de la clase Lista, se encarga de liberar la memoria de todos los
 * nodos utilizados en la lista
 * @tparam T
 */
template <class T> Lista<T>::~Lista() {}

/**
 * Metodo para saber si la lista esta vacia
 * @tparam T
 * @return true si la lista esta vacia, sino false
 */
template <class T>
bool Lista<T>::esVacia() {
    return inicio==nullptr; // es como if true else false
}

/**
 * Metodo para obtener la cantidad de nodos de la lista
 * @tparam T
 * @return la cantidad de nodos de la lista
 */
template <class T>
int Lista<T>::getTamanio() {
    Nodo<T> *aux = inicio;
    int tam = 0;

    while(aux != nullptr){
        aux= aux-> getSiguiente();
        tam ++;
    }
    return tam;
}

/**
 * Inserta un nodo con el dato en la posicion pos
 * @tparam T
 * @param pos lugar donde será insertado el dato
 * @param dato  dato a insertar
 */
template <class T>
void Lista<T>::insertar(int pos, T dato) {

    Nodo<T> *aux= inicio;
    int posActual = 0;

    Nodo<T> *nuevo = new Nodo<T>;
    nuevo->setDato(dato);

    if(pos==0){
        nuevo->setSiguiente(inicio);
        inicio=nuevo;
        return;
    }

    while(aux != nullptr && posActual < pos - 1){
        aux= aux->getSiguiente();
        posActual++;
    }

    if (aux==nullptr){
        throw 400;
    }

    nuevo->setSiguiente(aux->getSiguiente());
    aux->setSiguiente(nuevo);

}

/**
 * Inserta un nodo con el dato en la primera posicion
 * @tparam T
 * @param dato dato a insertar
 */
template <class T>
void Lista<T>::insertarPrimero(T dato) {

    insertar(0, dato);

}

/**
 * Inserta un nodo con el dato en la ultima posicion
 * @tparam T
 * @param dato dato a insertar
 */
template <class T>
void Lista<T>::insertarUltimo(T dato) {

    Nodo<T> *aux=inicio, *nuevo;
    nuevo= new Nodo<T>;
    nuevo->setDato(dato);

    if(aux==nullptr){
        nuevo->setSiguiente(inicio);
        inicio= nuevo;
        return;
    }

    while (aux->getSiguiente() != nullptr)
    {
        aux=aux->getSiguiente();
    }

    nuevo->setSiguiente(aux->getSiguiente()); //equivalente a nuevo-> setSgiguiente(nulltpr);
    aux->setSiguiente(nuevo);

}

/**
 * Elimina el nodo en la posicion 'pos' de la lista enlasada
 * @tparam T
 * @param pos posicion del nodo a eliminar
 */
template <class T>
void Lista<T>::remover(int pos)
{

    Nodo<T> *aux=inicio, *aBorrar;
    int posActual = 0;

    if(pos==0){
        inicio = inicio->getSiguiente();
        delete aux;
        return;
    }


    while(aux != nullptr && posActual < pos - 1){
        aux= aux->getSiguiente();
        posActual++;
    }

    if (aux==nullptr){
        throw 400;
    }

    aBorrar=aux->getSiguiente();
    aux->setSiguiente(aBorrar->getSiguiente());

    delete aBorrar;
}

/**
 * Obtener el dato del nodo en la posicion pos
 * @tparam T
 * @param pos posicion del dato
 * @return dato almacenado en el nodo
 */
template <class T>
T Lista<T>::getDato(int pos)
{

    Nodo<T> *aux =inicio;
    int posActual =0;

    while(aux != nullptr && posActual < pos){
        aux= aux->getSiguiente();
        posActual++;
    }
    if (aux==nullptr){
        throw 400;
    }
    return aux->getDato();
}

/**
 * Reemplaza el dato almacenado en un nodo por este otro
 * @tparam T
 * @param pos posicion donde se desea reemplazar
 * @param dato nuevo dato a almacenar
 */
template <class T>
void Lista<T>::reemplazar(int pos, T dato)
{
    Nodo<T> *aux =inicio;
    int posActual =0;

    while(aux != nullptr && posActual < pos){
        aux= aux->getSiguiente();
        posActual++;
    }

    if (aux==nullptr){
        throw 400;
    }

    aux->setDato(dato);
}

/**
 * Función que vacia la lista enlazada
 * @tparam T
 */
template <class T>
void Lista<T>::vaciar()
{

    Nodo<T> *aux=inicio, *aBorrar;

    while( aux!= nullptr){
        aBorrar = aux;
        aux = aux->getSiguiente();
        delete aBorrar;
    }

    inicio= nullptr;
}


/**
 * Funcion que imprime la lista enlazada
 * @tparam T
 * */

template<class T>
void Lista <T>::imprimir()
{

    Nodo<T> *aux=inicio;

    while (aux != nullptr){
        std::cout << aux->getDato() << "->";
        aux= aux->getSiguiente();
    }

    std::cout <<"NULL" << std::endl;
}
template<class T> void Lista<T>::insertAfter2(T oldValue, unsigned int n, T newValue) {
    Nodo<T> *look = inicio,*nuevo = nullptr;
    int count = 0;
    if (look == nullptr)
        throw "La lista esta vacia";
    if(look->getDato() == oldValue)
        count++;
    while (look->getSiguiente() != nullptr && count != n) {
        look = look->getSiguiente();

        if(look->getDato() == oldValue) {
            count++;
        }
    }
    if(count == n) {
        nuevo = new Nodo<T>;
        nuevo->setDato(newValue);
        nuevo->setSiguiente(look->getSiguiente());
        look->setSiguiente(nuevo);
    }
    else
        throw "No hay Suficientes instancias oldValue (2)";
}

#endif // PARCIAL2_LISTA_H
