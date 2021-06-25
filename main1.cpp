#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <dirent.h>
#include <SFML/Network.hpp>
#include "TECFS-Disk.cpp"
#include "huffman.cpp"

using namespace std;
using namespace sf;

int main() {
    Packet packetS, packetR;
    TcpListener listener;
    IpAddress ip = IpAddress::getLocalAddress(); //ip_
    TcpSocket socket;
    listener.listen(8080); //port_
    listener.accept(socket);
    string mapa;
    string pathReceived;
    TECFS_Disk checker;
    bool done = true;

    while (done) {
        socket.receive(packetR);

        if (packetR.getData() != nullptr){
            packetR >> mapa >> pathReceived;
            pathReceived = decomprimir(mapa, pathReceived);

            vector<string> nodes = checker.getDiskNodes();
            int tmp = checker.FileSize(pathReceived);
            cout << "pathReceived: " << pathReceived << " tmp: " << tmp << endl;
            tmp = tmp / 3;
            int size = checker.DiskNodeSize(nodes);
            cout << "size: " << size << " tmp2: " << tmp << endl;
            if (1024 - size < tmp) {
                packetS << false;
                cout << "false" << endl;
            } else {
                packetS << true;
                cout << "true" << endl;
            }

            socket.send(packetS);
            packetR.clear();
            packetS.clear();
        }
    }
}