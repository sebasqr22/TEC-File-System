#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "LinkedList.cpp"

using namespace std;

typedef unsigned char byte;
int memBlock;

void createBookPartitions(LinkedList<vector<byte>> book, string name) {
    string content;
    string nameAux;
    string route;

    for (int i=0; i < 4; i++) {
        vector<byte> bookPartition = book.getElement(i)->getData();
        for (auto & j : bookPartition) {
            content += j;
        }
        route = "./RAID/disk" + to_string(i) + "/bloque" + to_string(memBlock) + "/";
        nameAux = route + name + to_string(i) + ".txt";

        ofstream o(route);
        o.close();

        o.open(nameAux, fstream::app);
        o << content << "\n";
        o.close();
        content = "";
    }
    memBlock++;
}

vector<byte> calculateParity(vector<byte> A, vector<byte> B, vector<byte> C) {
    vector<byte> vectorParity;
    for (int i=0; i < C.size(); i++){
        vectorParity.push_back(A[i] ^ B[i] ^ C[i]);
    }
    return vectorParity;
}

vector<byte> recoverData(vector<byte> A, vector<byte> B, vector<byte> vectorParity) {
    vector<byte> vectorRecovered;
    for (int i=0; i < vectorParity.size(); i++){
        vectorRecovered.push_back(A[i] ^ B[i] ^ vectorParity[i]);
    }
    return vectorRecovered;
}

LinkedList<vector<byte>> splitFile(string file) {
    ifstream toSplit;
    int counter, partSize;
    string content;
    LinkedList<vector<byte>> book;
    toSplit.open(file);

    //Se saca la informacion del archivo y la cantidad de caracteres que contiene el mismo
    for (int i=0; toSplit.eof() != true; i++) {
        content += toSplit.get();
        counter++;
    }
    content.pop_back();
    partSize = counter / 3;
    int start = 0, end = partSize;
    cout << content << endl;

    //Se crea un vector de caracteres
    vector<byte> characters = vector<byte>(content.begin(), content.end());
    
    //Se divide el archivo en partes iguales
    for (int i=0; i < 3; i++) {
        if (i == 2)
            end = characters.size();
        vector<byte> sub(&characters[start], &characters[end]);
        book.insertAtEnd(sub);

        start = end;
        end += partSize;
        cout << "Partitioned file into disk: " << i << endl;
    }

    //Se calcula la paridad del bloque de memoria
    vector<byte> parityVector = calculateParity(book.getElement(0)->getData(), book.getElement(1)->getData(), book.getElement(2)->getData());
    book.insertAtEnd(parityVector);

    return book;
}

int main(){
    LinkedList<vector<byte>> book = splitFile("test.txt");
    createBookPartitions(book, "test");
    int diskToErase;
    cout << "Enter a disk you want to erase: ";
    cin >> diskToErase;
    book.deleteElement(diskToErase);
    book.insertElement(recoverData(book.getElement(0)->getData(), book.getElement(1)->getData(), book.getElement(2)->getData()), diskToErase);
    createBookPartitions(book, "test");

    return 0;
}