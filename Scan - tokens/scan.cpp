#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>

using std::cout; using std::cin;
using std::endl; using std::string;
using std::vector; using std::istringstream;
using std::stringstream;

bool isNumber(const string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

void scan (string text){

    char space_char = ' ';
    vector<string> words{};

    stringstream sstream(text);
    string word;
    while (std::getline(sstream, word, space_char)){
        word.erase(std::remove_if(word.begin()  , word.end(), ispunct), word.end());
        words.push_back(word);
    }
/*
    for (const auto &str : words) {
        cout << str << endl;
    }*/
    
    cout<<"word: "<<words[0]<< "a"<<endl;
    if(words[0]=="add"){
        if(isNumber(words[1])){
            cout<<"funcion para agregar numero"<<endl;
            if(words[2]==";"){
                cout<<"fin";
                
            }
        }
        else{
             cout<<" funcion para agregar string";
             if(words[2]==";"){
                cout<<"fin";
                
            }
        }
    }
    if(words[0]=="remove"){
        if(isNumber(words[1])){
            cout<<"funcion para remover numero";
            if(words[2]==";"){
                cout<<"fin";
                
            }
        }
        else{
             cout<<"funcion para remover string";
             if(words[2]==";"){
                cout<<"fin";
                
            }
        }
    }
    if(words[0]=="update"){
        if(isNumber(words[1])){
            cout<<"funcion para actualizar numero";
            if(words[2]==";"){
                cout<<"fin";
                
            }
        }
        else{
             cout<<"funcion para actualizar string";
             if(words[2]==";"){
                cout<<"fin";
                
            }
        }
    }

    
}
int main(){
    string frase;
    cout<<"Ingrese comando: "<<endl; getline(cin,frase);;
    
    scan(frase);
    return   0;
}
