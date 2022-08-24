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
        bool getLeaf();
        Nodo *getChild(Nodo*,int);

        //funciones
        void findNodo(Nodo*,int,int,Nodo*,Nodo*);
        void splitChild(Nodo*,int,Nodo*,Nodo*);
        void dividir(Nodo*,int,Nodo*,Nodo*,Nodo*);
        void erase(Nodo*,int,int,Nodo*,int,Nodo*,int);
        ~Nodo();

};

Nodo::Nodo(int tamanhoFrame){
    key = new int[tamanhoFrame+1];//cantidad de claves --------- +1
    for(int i=0;i<tamanhoFrame;i++){
        key[i]=0;
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

bool Nodo::getLeaf(){
    return this->leaf;
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
        while(i<node_active->n && data>node_active->key[i]){ 
            i++;
        }
        findNodo(node_active->child[i],data,t,root,node_active);
    }
    //se pone el +1 pra igualara la cantidad de claves y frames
    //para poder insertar un elemento más a la lista y ocurra el overflow
    if(node_active->n == t+1){
        splitChild(node_active,t,root,anterior);
    }
    
}

void Nodo::splitChild(Nodo *fullNodo, int t,Nodo *root,Nodo *anterior){
    Nodo *rightNodo = new Nodo(t);
    Nodo *leftNodo = new Nodo(t);
    fullNodo->leaf = false;
    int i_right=0; 
    int n_fullNodo=fullNodo->n; //num de claves 
    float val1= ceil(float(t)/2);
    int walk_chil= val1;

    fullNodo->child[0] = leftNodo;
    fullNodo->child[1] = rightNodo;
    //Se conectan los nodos
    leftNodo->child[t] = rightNodo;

    //pasa los valores al Nodo hijo derecho
    //insertar en el nodo derecho
    for(int i= walk_chil;i<n_fullNodo;i++){// 5
        rightNodo->key[i_right]=fullNodo->key[i]; //
        fullNodo->key[i]= 0;
        i_right++;
        fullNodo->n = (fullNodo->n)-1; // disminuye el num de claves
        rightNodo->n = (rightNodo->n)+1; //aumenta en 1 el n, cantidad de claves
    }

    //insertar en el nodo izquierdo
    for(int i= 0;i<walk_chil;i++){//
        leftNodo->key[i]=fullNodo->key[i]; //
        fullNodo->key[i]= 0;
        fullNodo->n = (fullNodo->n)-1; // disminuye el num de claves
        leftNodo->n = (leftNodo->n)+1; //aumenta en 1 el n, cantidad de claves
    }
    //volvemos a insertar el menor valor del nodo derecho en su padre
    fullNodo->key[0]=rightNodo->key[0];
    fullNodo->n = (fullNodo->n)+1;
    //Si el Nodo que nosotros estamos dividiendo no es la raiz
    if(fullNodo != root){
        int i=t; //num claves
        while(!anterior->key[i-1]){
            i--;
        }
        //Si el valor es mayor que el que esta en la parte extema derecha, le inserta a la derecha
        while(anterior->key[i-1]>fullNodo->key[0] && i!=0){
            anterior->key[i]=anterior->key[i-1]; 
            anterior->child[i+1]=anterior->child[i];  
            i--;
        }
        //se inserta en lugar respectivo
        anterior->key[i]=fullNodo->key[0];
        anterior->n +=1;

        //caso en el que el anterior tambien este lleno sus claves
        if(anterior->n==t+1){
            dividir(anterior,t,root,rightNodo,leftNodo);
        }
        else{
            anterior->child[i+1]=rightNodo;
            anterior->child[i]=leftNodo;
            //Para conectar nodos hoja
            if(i == 0){
                rightNodo->child[t] = anterior->child[i+2];
            }
            else{
                anterior->child[i-1]->child[t] = leftNodo;
                rightNodo->child[t] = anterior->child[i+2];
            }
        }
        delete fullNodo;
    }
}

void Nodo::dividir(Nodo* fullNodo,int t,Nodo* root,Nodo* rightN,Nodo* leftN){
    Nodo *rightNodo = new Nodo(t);
    Nodo *leftNodo = new Nodo(t);
    fullNodo->leaf = false;
    int i_right=0;
    int n_fullNodo=fullNodo->n; //num de claves 
    float val1= ceil(float(t)/2);
    int walk_chil= val1; 

    int guardar= fullNodo->key[walk_chil];
    //pasa los valores al Nodo hijo derecho
    //insertar en el nodo derecho
    for(int i= walk_chil+1;i<n_fullNodo;i++){// 5
        rightNodo->key[i_right]=fullNodo->key[i]; //
        fullNodo->key[i]= 0;
        i_right++;
        fullNodo->n = (fullNodo->n)-1; // disminuye el num de claves
        rightNodo->n = (rightNodo->n)+1; //aumenta en 1 el n, cantidad de claves
    }

    //insertar en el nodo izquierdo
    for(int i= 0;i<walk_chil;i++){//
        leftNodo->key[i]=fullNodo->key[i]; //
        fullNodo->key[i]= 0;
        fullNodo->n = (fullNodo->n)-1; // disminuye el num de claves
        leftNodo->n = (leftNodo->n)+1; //aumenta en 1 el n, cantidad de claves
    }
    //volvemos a insertar el menor valor del nodo derecho en su padre
    fullNodo->key[walk_chil] = 0;
    fullNodo->key[0]=guardar;

    //Si tiene hijos y no es una hoja
    if(fullNodo->child[0]!=nullptr && fullNodo->leaf==false){
        //Nodo izquierdo
        for(int i=0;i<=walk_chil;i++){
            leftNodo->child[i]=fullNodo->child[i];
            fullNodo->child[i] = nullptr;
        }
        //Nodo dercho
        int j=0;
        for(int i=walk_chil+1;i<=t;i++){
            rightNodo->child[j]=fullNodo->child[i];
            fullNodo->child[i] = nullptr;
            j++;
        }
        fullNodo->child[0] = leftNodo;
        fullNodo->child[1] = rightNodo;
        rightNodo->leaf = false;
        leftNodo->leaf = false;
    }
    //se inserta los hijo en el nodo derecho
    if(leftN->key[0]>= fullNodo->key[0]){
        int i=t; //cantidad de frames
        //pasar por las claves hasta que el valor no sea nulo
        while(!rightNodo->key[i-1]){
            i--;
        }
        //Si el valor es mayor que el que esta en la parte extema derecha, le inserta a la derecha
        while(rightNodo->key[i-1]>leftN->key[0] && i!=0){
            //rightNodo->child[i+2]=rightNodo->child[i];  
            i--;
        }
        //Para conectar las hojas
        if(i == 0){
            rightN->child[t] = rightNodo->child[i+2];
        }
        else{
            rightNodo->child[i-1]->child[t] = leftN;
            rightN->child[t] = rightNodo->child[i+2];
        }
        //se inserta en lugar respectivo
        rightNodo->child[i] = leftN;
        rightNodo->child[i+1] = rightN;
    }
    //Se insertar en el nodo izquierdo
    else{
        int i=t; //cantidad de frames
        //pasar por las claves hasta que el valor no sea nulo
        while(!leftNodo->key[i-1]){
            i--;
        }
        //Si el valor es mayor que el que esta en la parte extema derecha, le inserta a la derecha
        while(leftNodo->key[i-1]>leftN->key[0] && i!=0){
            //leftNodo->child[i+2]=leftNodo->child[i]; 
            i--;
        }
        //Para conectar las hojas
        if(i == 0){
            rightN->child[t] = rightNodo->child[i+2];
        }
        else{
            leftNodo->child[i-1]->child[t] = leftN;
            rightN->child[t] = leftNodo->child[i+2];
        }
        //se inserta en lugar respectivo
        leftNodo->child[i] = leftN;
        leftNodo->child[i+1] = rightN;
    }
    //Conecta el ultimo hijo del lado derecho del Nodo izquierdo con el hijo del lado izquierdo del nodo derecho
    leftNodo->child[leftNodo->n]->child[t] = rightNodo->child[0];
}

void Nodo::erase(Nodo* node_active,int data,int t,Nodo* anterior,int a,Nodo* guardado,int g){
    if(!node_active->leaf){
        int i=t;
        while(!node_active->key[i-1]){
            i--;
        }
        while(node_active->key[i-1]>data && i!=0){
            i--;
        }
        //En caso de que el numero tambien se encuentre el alguno de los nodos padres
        if(node_active->key[i-1] == data){
            guardado = node_active;
            g= i-1;
        }
        //Busca el nodo hoja donde se encuentra el numero
        erase(node_active->child[i],data,t,node_active,i-1,guardado,g);
    }
    else{
        int i=t;
        while(!node_active->key[i-1]){
            i--;
        }
        while(node_active->key[i-1]>data && i!=0){ 
            i--;
        }
        for(int j=i-1;j<node_active->n-1;j++){
            node_active->key[j] = node_active->key[j+1];
        }
        node_active->key[node_active->n-1] = 0;
        node_active->n--;
        //Si en el nodo anterior tambien se encuentra el numero
        int num = t/2;
        if(i-1 == 0 && anterior->key[a]== data){
            //anterior->key[a] == 0;
            //anterior->n--;
            if(node_active->n < num){
                //si se presta de su hemrano izquierdo
                if(a+1!=0 && anterior->child[a]->n > num){
                    for(int j=node_active->n;j>0;j--){
                        node_active->key[i]= node_active->key[i-1];
                    }
                    node_active->key[0]= anterior->child[a]->key[anterior->child[a]->n-1];
                    node_active->n++;
                    anterior->child[a]->key[anterior->child[a]->n-1]= 0;
                    anterior->child[a]->n--;
                    anterior->key[a] = node_active->key[0];
                }
                else if(anterior->child[a+2]->n > num){
                    node_active->key[node_active->n] = anterior->child[a+2]->key[0];
                    for(int j=0;j<anterior->child[a+2]->n-1;j++){
                        anterior->child[a+2]->key[j] = anterior->child[a+2]->key[j+1];
                    }
                    anterior->child[a+2]->key[anterior->child[a+2]->n-1] = 0;
                    anterior->child[a+2]->n--;
                    node_active->n++;
                    anterior->key[a+1] = anterior->child[a+2]->key[0];
                }
                else{
                    if(a+1!=0){
                        int x=anterior->child[a]->n;
                        for(int j=0;j<node_active->n;j++){
                            anterior->child[a]->key[x]= node_active->key[j];
                            anterior->child[a]->n++;
                            x++;
                        }
                        anterior->child[a]->child[t] = node_active->child[t];
                        delete node_active;
                        for(int j=a;j<anterior->n-1;j++){
                            anterior->key[j] = anterior->key[j+1];
                            anterior->child[j+1] = anterior->child[j+2];
                        }
                        anterior->key[anterior->n-1]=0;
                        anterior->n--;
                        anterior->child[anterior->n]=nullptr;
                    }
                    else{
                        int x=node_active->n;
                        for(int j=0;j<anterior->child[a+2]->n;j++){
                            node_active->key[x]= anterior->child[a+2]->key[j];
                            node_active->n++;
                            x++;
                        }
                        node_active->child[t] = anterior->child[a+2]->child[t];
                        delete anterior->child[a+2]->child[t];
                        for(int j=a+1;j<anterior->n-1;j++){
                            anterior->key[j] = anterior->key[j+1];
                            anterior->child[j+1] = anterior->child[j+2];
                        }
                        anterior->key[anterior->n-1]=0;
                        anterior->n--;
                        anterior->child[anterior->n]=nullptr;
                    }
                }
            }
            else{
                anterior->key[a] = node_active->key[0];
            }
        }
        //Si el nodo donde tambien se encuentra el numero es anterior a su padre, tal vez sua abuelo o bisabuelo
        else if(i-1==0 && anterior!=guardado){
            guardado->key[g] == 0;
            guardado->n--;
        }
        else{
            
        }
    }

}

Nodo::~Nodo(){

}

#endif
