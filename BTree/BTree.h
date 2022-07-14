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
        void imprimir();
        void imprimir(Nodo*,int);
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

void BTree::imprimir(){
    cout<<"pasa\n";
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

BTree::~BTree(){

}

#endif
