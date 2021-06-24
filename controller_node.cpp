#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

using namespace std;

void toBinary(){
    int counter = 0;
    ifstream toConvert;
    ofstream destinationFile;
    string content;
    string binaryString = "";
    toConvert.open("test.txt", ios::binary);
    destinationFile.open("test2.txt", ios::binary);
    for (int i=0; toConvert.eof()!= true; i++)
        content += toConvert.get();

    for (char& _char : content) {
        binaryString += bitset<8>(_char).to_string() + " ";
        counter++;
    }
    cout << binaryString << endl;
    destinationFile.write(binaryString.c_str(), binaryString.length());

    toConvert.close();
    destinationFile.close();

    cout << "Cantidad de bits de 8: " << counter << endl;
    
    
}
void toText(){

}
int main(){
    toBinary();
    return 0;
}