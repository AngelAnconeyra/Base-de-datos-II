#ifndef _BTREE_
#define _BTREE_
#include "Nodo.h"
#include<iostream>
using namespace std;

class BTree{
    private:
        Nodo *root;
        int t; //cantidad de frames
    public:
        BTree();
        BTree(int);
        //Setters

        //Getters
        int getT();

        //Funciones
        void insert(int);
        void buscarRango(int,int);
        void buscarRango(Nodo *,int,int);
        void erase(int);
        void imprimir();
        void imprimir(Nodo*,int);
        void imprimirHojas();
        ~BTree();
};

BTree::BTree(){

}

BTree::BTree(int tamanhoFrame){
    this->root= nullptr;
    this->t= tamanhoFrame;
}

//Setters

//Getters
int BTree::getT(){
    return t;
}

//Funciones
void BTree::insert(int data){
    Nodo *nuevo= new Nodo(t);
    if(!this->root){
        this->root = nuevo;
        this->root->setLeaf(true);
        //this->root->setKey(data);
        this->root->getKey()[root->getN()]= data;
        this->root->setN();
    }
    else{
        root->findNodo(root,data,t,root,root);
    }
}

void BTree::buscarRango(int L,int R){
    Nodo *aux=root;
    buscarRango(aux,L,R);
}

void BTree::buscarRango(Nodo* aux,int L,int R){
    int i=t;
    if(aux->getLeaf()){
        int j=0;
        while(aux->getKey()[j]<L && j<aux->getN()){
            j++;
        }
        do{
            for(int k=j;k<aux->getN();k++){
                if(aux->getKey()[k]<=R){
                    cout<< aux->getKey()[k] <<" ";
                }
                else{
                    return;
                }
            }
            j=0;
            aux = aux->getChild(aux,t);
        } while (aux !=nullptr);
    }
    else{
        while(!aux->getKey()[i-1]){
            i--;
        }
        //Si el valor es mayor que el que esta en la parte extema derecha, le inserta a la derecha
        while(aux->getKey()[i-1]>L && i!=0){
            i--;
        }
        buscarRango(aux->getChild(aux,i),L,R);
    }
}

void BTree::erase(int data){
    if(!this->root){
        cout<<"\nBTree vacio\n";
    }
    else{
        root->erase(root,data,t,root,0,root,0);
    }
}

void BTree::imprimir(){
    if(!this->root){
        cout<<"\nVacio\n";
    }
    else{
        imprimir(root,0);
    }
}

void BTree::imprimir(Nodo *aux,int i){
    cout<<endl;
    cout<<i<<": ";
    for(int j=0;j<aux->getN();j++){
        cout<<aux->getKey()[j]<<" ";
    }
    for(int j=0;j<=aux->getN();j++){
        if(aux->getChild(aux,j)!= nullptr){
            imprimir(aux->getChild(aux,j),i+1);
            i++;
        }
    }
}

void BTree::imprimirHojas(){
    Nodo *aux=root;
    while (aux->getLeaf()!=true){
        aux = aux->getChild(aux,0);
    }
    //cout<< "pasa\n";
    do{
        for(int i=0;i<aux->getN();i++){
            cout<< aux->getKey()[i] <<" ";
        }
        cout<<endl;
        aux = aux->getChild(aux,t);
    } while (aux !=nullptr);

    
}

BTree::~BTree(){

}

#endif
