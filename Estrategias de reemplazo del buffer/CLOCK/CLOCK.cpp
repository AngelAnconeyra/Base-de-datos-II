#include<iostream>
#include "Double_Linked_List.h"
#include<vector>
#include<fstream>
#include<string>
using namespace std;
int const fr = 4;
char frames[fr];
int j = 0,hit = 0;
char frames[fr];
Double_Linked_List<char> Fr;

void llenar(vector<char> &Req){
    ifstream file("Req.txt");
    string texto;
    getline(file,texto);
    for(int i=0;i<texto.size();i++){
        if(texto[i]!=' ' && texto[i]!=','){
            Req.push_back(texto[i]);
        }
    }
}

int verificar(char letra){
    int k = Fr.get_size();
    for(int i=0;i<k;i++){

    }
    return -1;
}

void CLOCK(vector<char> Req){
    while(j < Req.size()){

        j++;
    }
}

int main(){
    vector<char> Req;
    llenar(Req);
    CLOCK(Req);
    for(int i=0;i<fr;i++){
        cout << frames[i] <<" ";
    }
    cout<<"\nHit: "<<hit<<endl;

    return 0;
}
