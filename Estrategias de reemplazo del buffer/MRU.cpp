#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;
int j = 0,k = 0, hit=0;
int const fr = 8;
char frames[fr];
char pila[fr];

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

//verifica si esta en la fila y devuelve su posicion
int verificar(char letra){ 
    for(int i=0;i<k;i++){
        if(pila[i] == letra){
            return i;
        }
    }
    return -1;
}

//busca en los frames y devuelve su posicion
int buscar(char letra){ 
    for(int i=0;i<k;i++){
        if(frames[i] == letra){
            return i;
        }
    }
    return 0;
}

void MRU(vector<char> Req){
    while(j < Req.size()){
        int num = verificar(Req[j]); // si simbolo ya se encuentra del frame o no
        if(num != -1){ // si se encuentra en el frame
            for(int i =num ; i <k-1;i++){
                swap(pila[i],pila[i+1]); //le coloca al final de la fila
            }
            hit++;
        }
        //Si no se encuentra entre los frames
        else{
            //Si no se llenaron todos los frames
            if(k < fr){  //k < 4
                frames[k] = Req[j];
                pila[k] = Req[j];
                k++;
            }
            //Si estan llenos todos los frames
            else{
                int n = buscar(pila[fr-1]);
                pila[fr-1] = Req[j]; // j-1
                frames[n] = Req[j];
            }
        }
        j++;
    }
}
//A D B F E C A H I D L B C J K M E A C M H I G
//C L B F E M H G 
//FR = 8

int main(){
    vector<char> Req;
    llenar(Req);
    MRU(Req);
    for(int i=0;i<fr;i++){
        cout << frames[i] <<" ";
    }
    cout<<"\nHit: "<<hit<<endl;
    
    return 0;
}
