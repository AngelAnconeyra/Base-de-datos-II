#include "BTree.h"
#include<iostream>
using namespace std;

int main(){
    BTree ejem(4);
    ejem.insert(10);
    ejem.insert(27);
    ejem.insert(29);
    ejem.insert(17);
    ejem.insert(25);

    ejem.insert(21);
    ejem.insert(15);
    ejem.insert(31);

    ejem.insert(13);

    ejem.insert(51);

    //ejem.insert(20);
    //ejem.insert(24);

    //ejem.insert(48);
    //ejem.insert(19);
    //ejem.insert(60);

    //ejem.insert(35);
    //ejem.insert(66);

    //ejem.insert(70);

    //ejem.insert(9);
    //ejem.insert(11);
    //ejem.insert(14);

    //ejem.erase(25);
    ejem.imprimir();
    //ejem.imprimirHojas();
    //ejem.buscarRango(13,17);
    return 0;
}
