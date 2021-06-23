#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void toBinary(){
    ifstream toConvert;
    ofstream destinationFile;
    string line;
    toConvert.open("test.txt", ios::binary);
    destinationFile.open("test2.txt", ios::binary);
    while(!toConvert.eof()){
        getline(toConvert, line);
        cout << line << endl;
        destinationFile.write(line.c_str(), line.length());
    }
    toConvert.close();
    destinationFile.close();
}
int main(){
    toBinary();
    return 0;
}