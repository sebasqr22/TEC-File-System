/**
 * @file main1.cpp
 * @title Main 1
 * @brief Class for TECFS-Disk app
 * */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <dirent.h>
#include <SFML/Network.hpp>
#include "TECFS-Disk.cpp"
#include "huffman.cpp"
#include "tinyxml2.cpp"

using namespace std;
using namespace sf;
using namespace tinyxml2;
/**
 * @brief Method to set initial data
 * */
void setData(TECFS_Disk *checker, IpAddress *ip, int *port) {
    XMLDocument doc;
    doc.LoadFile("config.xml");
    ip = doc.FirstChildElement("config")->FirstChildElement("ip")->GetText();
    port = doc.FirstChildElement("config")->FirstChildElement("ip")->NextSiblingElement("port")->GetText();
    checker->setRoute(doc.FirstChildElement("config")->LastChildElement("route")->GetText());
}
/**
 * @brief Main method of the class
 * */
int main() {
    Packet packetS, packetR;
    TcpListener listener;
    IpAddress ip;
    int port;
    TECFS_Disk checker;
    TcpSocket socket;
    setData(&checker, &ip, &port);
    listener.listen(port);
    listener.accept(socket);
    string mapa;
    string pathReceived;
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