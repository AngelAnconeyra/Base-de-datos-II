#ifndef _D_LINKED_LIST_
#define _D_LINKED_LIST_
#include "Nodo.h"
#include "iostream"
using namespace std;
template<typename T>
class Double_Linked_List{
    private:
        Nodo<T> *head;
        int size;
    public:
        Double_Linked_List();
        void push_back(T);
        bool buscar(T);
        int get_size();
        ~Double_Linked_List();
};

template<typename T>
Double_Linked_List<T>::Double_Linked_List(){
    this->head = nullptr;
    this->size = 0;
}

template<typename T>
void Double_Linked_List<T>::push_back(T dato){
    Nodo<T> *nuevo = new Nodo<T>(dato);
    if(!this->head){
        this->head = nuevo;
        head->set_sig(nuevo);
        head->set_ant(nuevo);
    }else{
        Nodo<T> *aux = this->head;
        aux->set_ant(nuevo);
        nuevo->set_sig(aux);
        for(int i=1;i<size;++i){
            aux = aux->get_sig();
        }
        aux->set_sig(nuevo);
        nuevo->set_ant(aux);
    }
    size++;
}

template<typename T>
bool Double_Linked_List<T>::buscar(T dato){
    if(!head){
        return false;
    }
    else{
        Nodo<T> *tmp = head;
        for(int i=0;i<size;i++){
            if(tmp->get_dato() == dato){
                return true;
            }
            tmp = tmp->get_sig();
        }
        return false;
    }
}

template<typename T>
int Double_Linked_List<T>::get_size(){
    return this->size;
}

template<typename T>
Double_Linked_List<T>::~Double_Linked_List(){
    while(this->size){
        this->pop_back();
    }
    delete head;
}

#endif
