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
    ejem.insert(20);
    ejem.insert(24);
    ejem.insert(48);
    ejem.imprimir();
    //cout<< ejem.getT();
    return 0;
}
