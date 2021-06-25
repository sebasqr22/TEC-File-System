/**
 * @file controller_node.cpp
 * @title Controller Node
 * @brief Class that handles the memory and lecture of books of a RAID
**/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <dirent.h>
#include "LinkedList.cpp"

using namespace std;

typedef unsigned char byte;
int memBlock = 0;

/**
 * @brief Method to create book partitions and save them in different disks
 **/
void createBookPartitions(LinkedList<vector<byte>> book, string name) {
    string content;
    string nameAux;
    string route;

    for (int i=0; i < 4; i++) {
        vector<byte> bookPartition = book.getElement(i)->getData();
        for (auto & j : bookPartition) {
            content += j;
        }
        route = "/home/sebas/Escritorio/ceROBOT/ceROBOT/RAID/disk" + to_string(i) + "/bloque" + to_string(memBlock) + "/";
        nameAux = route + name + to_string(i) + ".txt";

        ofstream o(route);
        o.close();

        cout << nameAux << endl;

        o.open(nameAux, fstream::app);
        o << content << "\n";
        o.close();
        content = "";
    }
    memBlock++;
}

/**
 * @brief Method to calculate parity vector of the book parts
 * @return parity vector
 **/
vector<byte> calculateParity(vector<byte> A, vector<byte> B, vector<byte> C) {
    vector<byte> vectorParity;
    for (int i=0; i < C.size(); i++){
        vectorParity.push_back(A[i] ^ B[i] ^ C[i]);
    }
    return vectorParity;
}

/**
 * @brief Method to recover lost data of a book
 * @return recovered book vector
 **/
string recoverData(string partAStr, string partBStr, string parityString) {
    vector<byte> recoveredVector;

    vector<byte> partA(partAStr.begin(), partAStr.end());
    vector<byte> partB(partBStr.begin(), partBStr.end());
    vector<byte> parity(parityString.begin(), parityString.end());

    for (int i=0; i < parity.size(); i++)
        recoveredVector.push_back(partA[i] ^ partB[i] ^ parity[i]);

    if (partA.size() != partB.size()) {
        for (int j=0; j < (parity.size() - partA.size()); j++)
            recoveredVector.erase(recoveredVector.begin() + (recoveredVector.size() - 1));
    }

    string recovered(recoveredVector.begin(), recoveredVector.end());
    return recovered;
}

/**
 * @brief Method to locate what disk was erased
 **/
void locatePartitionErased(LinkedList<vector<byte>> book, vector<byte> vectorRecovered) {
    for (int i=0; i < 4; i++) {
        if (book.getElement(i)->getData() == vectorRecovered)
            book.insertElement(vectorRecovered, i);
    }
}

/**
 * @brief Method to split file into different vectors and adds them into a linked list
 * @return linked list of the book
 **/
LinkedList<vector<byte>> splitFile(string file) {
    ifstream toSplit;
    int counter = 0, partSize = 0;
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
        //cout << characters[start] << characters[end] << endl;
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

string joinBookParts(string part1, string part2, string part3) {
    vector<byte> vector1(part1.begin(), part1.end());
    vector<byte> vector2(part2.begin(), part2.end());
    vector<byte> vector3(part3.begin(), part3.end());

    vector1.insert(vector1.end(), vector2.begin(), vector2.end());
    vector1.insert(vector1.end(), vector3.begin(), vector3.end());

    string book = string(vector1.begin(), vector1.end());
    return book;
}

/**
 * @brief Method to open books located on the disks
 **/
vector<string> openBooks(string name) {
    vector<string> books;
    vector<string> bookParts;
    vector<string> bookPartsName;
    DIR * dir; struct dirent *diread;
    for (int j=0; j < 20; j++) {
        for (int i=0; i < 4; i++) {
            string route = "/home/sebas/Escritorio/ceROBOT/ceROBOT/RAID/disk" + to_string(i) + "/bloque" + to_string(j) + "/";
            if ((dir = opendir(route.c_str())) != nullptr) {
                while ((diread = readdir(dir)) != nullptr) {
                    string fname = diread->d_name;
                    string line, content;
                    if (fname.find(name) != string::npos) {
                        ifstream is(route + fname);
                        if (is.is_open()) {
                            while (getline(is, line)) {
                                content += line;
                            }
                        }
                        is.close();
                        bookParts.push_back(content);
                        bookPartsName.push_back(fname);
                        cout << "found book: " << fname << " in " << route << endl;
                        //cout << "contents: " << content << endl;
                    }
                }
            }
        }
        if (bookParts.size() != 4 && !bookParts.empty()) {
            string bookContent, lostContent;
            int lostPart;
            string name_ = bookPartsName[0].substr(0, bookPartsName[0].size() - 4);
            for (int i=0; i < 3; i++) {
                bookPartsName[i] = bookPartsName[i].substr(0, bookPartsName[i].size() - 4);
                if (((bookPartsName[i].back()) - '0') != i) {
                    lostContent = recoverData(bookParts[0], bookParts[1], bookParts[2]);
                    cout << "recovering data..." << endl;
                    bookParts.insert(bookParts.begin() + (i), lostContent);
                    break;
                }
            }
            cout << "joining the books..." << endl;
            bookParts.pop_back();
            for (auto & i : bookParts) {
                bookContent += i;
            }
            
            string nameAux = "./openedBooks/" + name + ".txt";
            ofstream o("./openedBooks/");
            o.close();
            o.open(nameAux, fstream::app);
            o << bookContent;
            o.close();

            books.push_back(nameAux);
            bookParts.clear();
        }
        else if (bookParts.size() == 4) {
            cout << "joining the books..." << endl;
            string bookContent;
            bookParts.pop_back();
            string name_ = bookPartsName[0].substr(0, bookPartsName[0].size() - 4);
            for (auto & i : bookParts) {
                bookContent += i;
            }
            string nameAux = "./openedBooks/" + name + ".txt";
            ofstream o("./openedBooks/");
            o.close();
            o.open(nameAux, fstream::app);
            o << bookContent;
            o.close();
            
            books.push_back(nameAux);
            bookParts.clear();
        }
    }
    return books;
}

/*int main(){
    LinkedList<vector<byte>> book; 
    for (int i=0; i < 10; i++) {
        book = splitFile(i);
        createBookPartitions(book, i);
    }
    LinkedList<vector<byte>> book2 = splitFile("test2.txt");
    //LinkedList<vector<byte>> book2 = splitFile("test.txt");
    createBookPartitions(book, "test");
    createBookPartitions(book, "test2");
    //cout << "Enter a disk you want to erase: ";
    //cin >> diskToErase;
    //book.deleteElement(diskToErase);
    //book.insertElement(recoverData(book.getElement(0)->getData(), book.getElement(1)->getData(), book.getElement(2)->getData()), diskToErase);
    //createBookPartitions(book, "test");

    return 0;
}*/
