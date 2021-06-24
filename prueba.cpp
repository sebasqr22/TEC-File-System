#include "book_actions.cpp"
#include <string>
#include "TECFS-Disk.cpp"
#include "disk_node.cpp"

using namespace std;

book_actions actions;
TECFS_Disk manejador;
disk_node nodo;


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
    //vector<string> diskNodes = manejador.getDiskNodes();
    //manejador.DiskNodeSize(diskNodes);
    //cout << "Normal: " << manejador.FileSize("./NUEVA/prueba.txt") << endl;
    nodo.create();

    return 0;
}