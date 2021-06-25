/**
 * @file ceROBOT.cpp
 * @title ceROBOT
 * @brief Class that contains the ceROBOT for searching books
**/
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "LinkedList.cpp"
#include "text_box.cpp"
#include "button.cpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include "controller_node.cpp"
#include "disk_node.cpp"
#include "huffman.cpp"
#include "rapidjson/document.h"

using namespace rapidjson;

/**
 * @brief Method to add books to the RAID
 * */
void AddToRaid(const char* directory){
    LinkedList<vector<byte>> linked;
    disk_node diskNode;
    vector<string> books;
    string aux;
    Packet packetS, packetR;
    IpAddress ip = IpAddress::getLocalAddress();
    TcpSocket socket;

    socket.connect(ip, 8080);

    DIR *dir;
    struct dirent *ent;
    if((dir = opendir(directory)) != NULL){
        while((ent = readdir(dir)) != NULL){
            aux = string(ent->d_name);
            if(aux != "." && aux != ".." && aux.find("txt")){
                books.push_back(aux);
            }
        }
        closedir(dir);
    }
    else{
        cout << "Can't open dc" << endl;
    }

    int size = books.size();

    diskNode.create();
    for (auto & i : books) {
        string path = "./books/" + i;
        string mapa = start_huffman(path);
        string comprimido = comprimirMensaje(path);

        packetS << mapa << comprimido;
        socket.send(packetS);
        bool createPartitions;

        socket.receive(packetR);

        if (packetR.getData() != nullptr) {
            packetR >> createPartitions;
        }

        if (createPartitions) {
            linked = splitFile(string(directory) + "/" + i);
            string name = i.substr(0, i.size() - 4);
            createBookPartitions(linked, name); 
        }
        else 
            cout << "Book Partition could not be added: disk size is exceeded" << endl;
        
        packetS.clear();
        packetR.clear();
    }
    cout << "finished" << endl;
}
/**
 * @brief Method that creates the GUI
 * */
int ceROBOT() {
    Font font;
    font.loadFromFile("BigShouldersStencilDisplay-Regular.ttf");
    RenderWindow window(VideoMode(750,750), "TEC-File System");
    Texture backgroundTexture;
    RectangleShape background;
    Text searchText;

    searchText.setString("Please enter the path you want to put into the RAID: ");
    searchText.setPosition(10,80);
    searchText.setFont(font);
    searchText.setFillColor(Color::Green);

    backgroundTexture.loadFromFile("background.png");
    background.setPosition(0,0);
    background.setTexture(&backgroundTexture);
    background.setSize(Vector2f(750,750));

    text_box searchPath(50, Vector2f(250, 60), Color::White, Color::Black, false, Vector2f(50,150), font);
    button search(Vector2f(125, 250), Vector2f(100,50), font, "SEARCH", Color::Red, Color::Green);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;

                case Event::TextEntered:
                    searchPath.setString(event);

                case Event::MouseButtonPressed:
                    searchPath.update(Vector2f(event.mouseButton.x, event.mouseButton.y));
            }
            search.update(Vector2f(event.mouseButton.x, event.mouseButton.y));
            if (search.isPressed() && searchPath.getString() != "") {
                string lookFor = searchPath.getString();
                cout << lookFor << endl;
                AddToRaid(lookFor.c_str());
            }
        }
        window.clear();
        window.draw(background);
        window.draw(searchText);
        searchPath.draw(window);
        search.draw(window);
        window.display();
    }
}