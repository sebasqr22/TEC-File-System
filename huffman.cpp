/**
 * @file huffman.cpp
 * @title Huffman
 * @brief Class that compresses a string using Huffman's algortihm
 * */

#include <iostream>
#include <bits/stdc++.h>
#define MAX_TREE_HT 256

using namespace std;

map<char, string>caracteres;
map<char, int>frecuencia;

struct nodo{
    char data;
    int frecuencia;
    nodo *izquierda, *derecha;
    nodo(char data, int frecuencia){
        izquierda = derecha = NULL;
        this->data = data;
        this->frecuencia = frecuencia;
    }
};

struct comparacion{
	bool operator()(nodo* izq, nodo* der)
	{
		return (izq->frecuencia > der->frecuencia);
	}
};
/**
 * @brief Method to save data to reused later
 * **/
void guardar(struct nodo* inicio, string tmp){
    if(inicio == NULL){
        return;
    }
    if(inicio->data != '$')
        caracteres[inicio->data] = tmp;
    guardar(inicio->izquierda, tmp + "0");
    guardar(inicio->derecha, tmp + "1");
}

priority_queue<nodo*, vector<nodo*>, comparacion>minimo;
/**
 * @brief Method to generate part of the compression
 * */
void generarHuffman(int largo){
    struct nodo *izquierda, *derecha, *arriba;
    for(map<char, int>::iterator v=frecuencia.begin(); v!=frecuencia.end();v++)
        minimo.push(new nodo(v->first, v->second));
    while(minimo.size() != 1){
        izquierda = minimo.top();
        minimo.pop();
        derecha = minimo.top();
        minimo.pop();
        arriba = new nodo('$', izquierda->frecuencia + derecha->frecuencia);
        arriba->izquierda = izquierda;
        arriba->derecha = derecha;
        minimo.push(arriba);
    }
    guardar(minimo.top(), "");
}
/**
 * @brief Method to calculate frecuency
 * */
void setFrecuencia(string data, int num){
    for(int i=0; i<data.size(); i++){
        frecuencia[data[i]]++;
    }
}
/**
 * @brief Method to create the decode
 * @return String with original content
 * */
string decodificacion(struct nodo* inicio, string tmp){
    string aux = "";
    struct nodo* actual = inicio;
    for(int i=0; i<tmp.size(); i++){
        if(tmp[i] == '0'){
            actual = actual->izquierda;
        }
        else{
            actual = actual->derecha;
        }

        if(actual->izquierda == NULL && actual->derecha == NULL){
            aux += actual->data;
            actual = inicio;
        }
    }
    return aux+'\0';
}
/**
 * @brief Method for generate the compression
 * @return String compressed
 * */
string crear(string datos){
    string resultado;
    setFrecuencia(datos, datos.length());
    generarHuffman(datos.length());
    for(auto i: datos){
        resultado += caracteres[i];
    }
    return resultado;
}
/*
int main(){
    string listo = crear("EL Bicho SIUU");
    cout << listo << endl;
    cout << decodificacion(minimo.top(), listo);
    return 0;
}*/