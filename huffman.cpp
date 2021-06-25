/**
 * @file huffman.cpp
 * @title Huffman
 * @brief Class that compresses a string using Huffman's algortihm
 * */
#pragma once
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
/**
 * @brief Method to create a string that represents the character's map
 * @return String of the map
 * */
string diccionarioStr(){
    string mapa;
    
    for (auto v=caracteres.begin(); v!=caracteres.end(); v++){
        //cout << v->first <<' ' << v->second << endl;
        mapa += "-";
        mapa += v->first;
        mapa += "|";
        mapa += v->second;
        mapa += "|";
    };
    mapa += "-";
    return mapa;
}
/**
 * @brief Method to decode the code
 * @return Decoded string
 * */
string decodeHuffman(vector<string> simbolo, vector<string> parte, string code){
    string delimitador = "-";
    size_t pos1 = 0;
    string key;
    int j = 0;
    string decodificado = "";

    while ((pos1 = code.find(delimitador)) != std::string::npos) {
        key = code.substr(0, pos1);

        // loop through the array elements
        for (size_t i = 0; i < parte.size(); i++) {
            if (key == parte[i]){
                decodificado += simbolo[i];
                break;
            }
        }
        code.erase(0, pos1 + delimitador.length());
    }
    return decodificado;
}
/**
 * @brief Method for compress a message
 * @return Coded string
 * */
string comprimirMensaje(string mensaje){
    string comprimido;
    for (auto i: mensaje){
        comprimido += caracteres[i];
        comprimido += "-";
    }
    return comprimido;
}
/**
 * @brief Sets the initial values for the compression
 * @return String of the message's map
 * */
string start_huffman(string mensaje){
    setFrecuencia(mensaje, mensaje.length());
    generarHuffman(mensaje.length());
    string mapa = diccionarioStr();
    return mapa;
}
/**
 * @brief Method for decode a message
 * @return Decoded Message
 * */
string decomprimir(string mapa, string comprimido){
    std::string delimitador = "-";
    std::vector<std::string> simbolo;
    std::vector<std::string> parte;
    size_t pos1 = 0;
    size_t pos2 = 0;
    std::string key;
    std::string value;
    bool first = true;
    int moment = 0;

    while ((pos1 = mapa.find(delimitador)) != std::string::npos) {
        key = mapa.substr(0, pos1);
        if (first == true){
            first = false;
        }
        else{
            while ((pos2 = key.find("|")) != std::string::npos) {
                value = key.substr(0, pos2);
                if(moment == 0){
                    simbolo.push_back(value);
                    moment += 1;
                }else{
                    parte.push_back(value);
                }
                key.erase(0, pos2 + 1);
            }
            moment = 0;
        }
        mapa.erase(0, pos1 + delimitador.length());
    }

    string decomprimido = decodeHuffman(simbolo, parte, comprimido);
    return decomprimido;
}
/**
 * @brief Method that returns de main tree
 * @return Main tree
 **/
priority_queue<nodo *, std::vector<nodo *>, comparacion> getMinimo() {
    return minimo;
}