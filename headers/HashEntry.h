#ifndef PARCIAL2_HASHENTRY_H
#define PARCIAL2_HASHENTRY_H

template <class K, class T>
class HashEntry
{
private:
    K clave;
    T valor;
    HashEntry<K, T> *next;
public:
    HashEntry(K c, T v){
        clave = c;
        valor = v;
    }
    void setnext(HashEntry<K, T> *Next) {
        next = Next;
    }
    HashEntry<K, T> *getnext() {
        return next;
    }
    K getClave(){
        return clave;
    }
    void setClave(K c){
        clave = c;
    }

    T getValor(){
        return valor;
    }
    void setValor(T v){
        valor = v;
    }
};

#endif // PARCIAL2_HASHENTRY_H
