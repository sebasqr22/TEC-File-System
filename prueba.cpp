#include "book_actions.cpp"
#include <string>
#include "TECFS-Disk.cpp"

using namespace std; //12.3 KB

book_actions actions;
TECFS_Disk manejador;


void crear(){
    cout << "Ingrese el nombre del libro a crear: ";
    string name;
    cin >> name;
    cout << "\n" << "Ingrese el contenido: " << endl;
    string content;
    cin >> content;

    cout << content;

    actions.createBook(name, content);
}

void leer(){
    cout << "Ingrese el nombre del libro a leer: ";
    string name;
    cin >> name;
    cout << endl;
    actions.readBook(name);
}

int main(){
    manejador.DiskNodeSize();

    return 0;
}