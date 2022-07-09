#ifndef _NODO_
#define _NODO_
#include<math.h>
#include<iostream>
using namespace std;

class Nodo{
    private:
        int *key; //claves
        Nodo **child;
        bool leaf;
        int n; // para saber cuantas claves hay en el nodo
    public:
        Nodo();
        Nodo(int);
        //setters
        void setLeaf(bool);
        void setN();
        void setKey(int);
        //getters
        int* getKey();
        int getN();
        Nodo *getChild(Nodo*,int);

        //funciones
        void findNodo(Nodo*,int,int,Nodo*,Nodo*);
        void splitChild(Nodo*,int,Nodo*,Nodo*);
        ~Nodo();

};

Nodo::Nodo(int tamanhoFrame){
    key = new int[tamanhoFrame+1];//cantidad de claves --------- +1
    for(int i=0;i<tamanhoFrame;i++){
        key[i]=NULL;
    }
    leaf = true;
    n=0;
    child= new Nodo*[tamanhoFrame+1]; //cantidad de punteros
    for(int i=0;i<=tamanhoFrame;i++){
        child[i]=nullptr;
    }
}

//Setters
void Nodo::setLeaf(bool opc){
    this->leaf = opc;
}

void Nodo::setN(){
    this->n++;
}

void Nodo::setKey(int data){
    this->key[n+1]= data;
    n++;
}

//Getters
int* Nodo::getKey(){
    return this->key;
}

int Nodo::getN(){
    return this->n;
}

Nodo* Nodo::getChild(Nodo *node_active,int i){
    return node_active->child[i];
}

//Funciones
void Nodo::findNodo(Nodo *node_active,int data,int t,Nodo *root,Nodo *anterior){ //void
    //si es una hoja
    if(node_active->leaf){
        int i=t; //cantidad de frames
        //pasar por las claves hasta que el valor no sea nulo
        while(!node_active->key[i-1]){
            i--;
            //cout<< i <<endl;
        }
        //Si el valor es mayor que el que esta en la parte extema derecha, le inserta a la derecha
        while(node_active->key[i-1]>data && i!=0){
            node_active->key[i]=node_active->key[i-1]; // ejem: 1 3 5 [] e insertar el 2= 1 2 3 5
            i--;
        }
        //se inserta en lugar respectivo
        node_active->key[i]=data;
        node_active->n +=1;
    }

    //si no es una hoja el root
    else{
        int i=0;
        //
        while(i<node_active->n && data>node_active->key[i]){ //en vez de root: node_active
            i++;
        }
        //child[i]->findNodo(this->child[i],data,t,root);
        findNodo(node_active->child[i],data,t,root,node_active);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    //se pone el +1 pra igualara la cantidad de claves y frames
    //para poder insertar un elemento más a la lista y ocurra el overflow
    
    if(node_active->n == t+1){
        //en caso de que aun se la raiz
        /*
        if(node_active == root){
            //Nodo *temp = new Nodo(t);
            //temp->leaf = false;
            //temp->child[0] = node_active;
            //temp->splitChild(node_active,t);
            //return temp;
            //ocurre el overflow arreglar
            splitChild(node_active,t);
        }
        else{
            node_active->splitChild(node_active,t);
        }
        */

        splitChild(node_active,t,root,anterior);
    }
    //return root;
    
}

void Nodo::splitChild(Nodo *fullNodo, int t,Nodo *root,Nodo *anterior){
    Nodo *rightNodo = new Nodo(t);
    Nodo *leftNodo = new Nodo(t);
    fullNodo->leaf = false;
    fullNodo->child[0] = leftNodo;
    fullNodo->child[1] = rightNodo;
    int i_right=0;// i_left=0; 
    int move_up=(t-1)/2; //1
    int n_fullNodo=fullNodo->n; //num de claves 5
    //int carry= fullNodo->key[move_up],i_child=0;
    float val1= ceil(float(t)/2); //que valor es la que ira en el nodo padre
    int walk_chil= val1; // arreglar  2
    //pasa los valores al Nodo hijo derecho
    //insertar en el nodo derecho
    for(int i= move_up+1;i<n_fullNodo;i++){// 5
        rightNodo->key[i_right]=fullNodo->key[i]; //
        fullNodo->key[i]= NULL;
        i_right++;
        fullNodo->n = (fullNodo->n)-1; // disminuye el num de claves
        rightNodo->n = (rightNodo->n)+1; //aumenta en 1 el n, cantidad de claves
    }

    //insertar en el nodo izquierdo
    for(int i= 0;i<=move_up;i++){//
        leftNodo->key[i]=fullNodo->key[i]; //
        fullNodo->key[i]= NULL;
        fullNodo->n = (fullNodo->n)-1; // disminuye el num de claves
        leftNodo->n = (leftNodo->n)+1; //aumenta en 1 el n, cantidad de claves
    }
    //volvemos a insertar el menor valor del nodo derecho en su padre
    fullNodo->key[0]=rightNodo->key[0];
    fullNodo->n = (fullNodo->n)+1;

    //Si el Nodo que nosotros estamos dividiendo tiene hijos 
    //revisar detalladamente
    if(fullNodo != root){
        int i=t;
        while(!anterior->key[i-1]){
            i--;
        }
        //Si el valor es mayor que el que esta en la parte extema derecha, le inserta a la derecha
        while(anterior->key[i-1]>fullNodo->key[0] && i!=0){
            anterior->key[i]=anterior->key[i-1]; // ejem: 1 3 5 [] e insertar el 2= 1 2 3 5
            anterior->child[i+1]=anterior->child[i];  
            //anterior->child[i]=rightNodo;           ////en otra parte
            i--;
        }
        //se inserta en lugar respectivo
        anterior->key[i]=fullNodo->key[0];
        anterior->n +=1;
        //anterior->child[anterior->n]=anterior->child[1];
        anterior->child[i+1]=rightNodo;
        anterior->child[i]=leftNodo;
        /*
        for(int i=anterior->n-1;i>=0;i--){ // 2 do 4
            anterior->child[i]=fullNodo->child[i];
        }
        */
        delete fullNodo;
    }
    /*
    if(fullNodo->leaf == false){
        for(int i=walk_chil;i<=t;i++){ // 2 do 4
            rightNodo->child[i_child]=fullNodo->child[i];
            i_child++;
        }
        rightNodo->leaf= fullNodo->leaf;
    }
    */
    
   /*
    int hold=t-1;//3
    //Trata de unicar el nodo derecho en el nodo root, solocionar
    while(fullNodo->child[hold]!=fullNodo){//
        child[hold+1]=child[hold];
        hold--;
    }
    fullNodo->child[hold+1]=rightNodo;
    int j=t-1; //3
    while(!key[j-1] && j!=0){
        j--;
    }
    //si el valor antes de la clave es mayor que los datos, empujelo haci la derecha
    while(key[j-1]>carry && j!=0){
        key[j]=key[j-1];
        j--;
    }
    //inserta el valor en el respectivo lugar en el Nodo
    key[j]=carry;
    n++;
    fullNodo->n= (fullNodo->n)-1;
    */
}

Nodo::~Nodo(){

}

#endif
