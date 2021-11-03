#ifndef U05_ARBOL_ARBOL_NODOARBOLAVL_H_
#define U05_ARBOL_ARBOL_NODOARBOLAVL_H_

#include <string.h>
#include "./case.h"

using namespace std;

template <class T>
class NodoArbolAVL
{
private:
  T data;
  NodoArbolAVL *left, *right;
  int height;

  int stringAinteger(string stringDate);

public:
  NodoArbolAVL()
  {
    left = nullptr;
    right = nullptr;
    height=1;
  }

  NodoArbolAVL(T d)
  {
    data = d;
    left = nullptr;
    right = nullptr;
    height = 1;
  }

  T getData() const
  {
    return data;
  }

  void setData(T d)
  {
    this->data = d;
  }

  int getClave(){
    return stringAinteger(data[13]);
  }

  NodoArbolAVL *getRight() const
  {
    return right;
  }

  void setRight(NodoArbolAVL *r)
  {
    this->right = r;
  }
  NodoArbolAVL *getLeft() const
  {
    return left;
  }

  void setLeft(NodoArbolAVL *l)
  {
    this->left = l;
  }

  int getHeight(){
    return height;
  }

  void setHeight(int h){
    height = h;
  }

  void print(){
         
    int columnas[] = {0, 2, 3, 12, 13,  14, 17, 20}; //columnas importantes 
    int numColumnas = sizeof(columnas) / sizeof(columnas[0]);
    
    for (int i = 0; i < numColumnas; i++){
      cout << data[columnas[i]] << "\t";
    }
    cout << endl;
  }

};

template<class T> 
int NodoArbolAVL<T>::stringAinteger(string stringDate) {
    string intDate;
    int num=stringDate.size();
    for(int i=0; i < num ; i++){
         int aux = stringDate[i];
        if(aux >= 48 && aux <=57){
            intDate  += stringDate[i];
        }
    }
    return stoi(intDate);
}


#endif // U05_ARBOL_ARBOL_NODOARBOLAVL_H_
