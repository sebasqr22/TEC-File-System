/**
 * @file main_cn.cpp
 * @title Main Cn
 * @brief Class that contains the ceSEARCH for searching books
**/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "LinkedList.cpp"
#include "controller_node.cpp"
#include "text_box.cpp"
#include "button.cpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;
typedef unsigned char byte;

/**
 * @brief Main method of the class
 * */
int ceSEARCH() {
    LinkedList<LinkedList<vector<byte>>> bookList;
    Font font;
    font.loadFromFile("BigShouldersStencilDisplay-Regular.ttf");
    RenderWindow window(VideoMode(750,750), "TEC-File System");
    Texture backgroundTexture;
    RectangleShape background;
    Text searchText;
    searchText.setString("Please enter codewords for the book: ");
    searchText.setPosition(10,80);
    searchText.setFont(font);
    searchText.setFillColor(Color::Black);

    backgroundTexture.loadFromFile("background.png");
    background.setPosition(0,0);
    background.setTexture(&backgroundTexture);
    background.setSize(Vector2f(750,750));

    text_box searchBook(50, Vector2f(250, 60), Color::White, Color::Black, false, Vector2f(50,150), font);
    text_box filesBox(25, Vector2f(300,600), Color::White, Color::Black, false, Vector2f(405,80), font);
    button search(Vector2f(125, 250), Vector2f(100,50), font, "SEARCH", Color::Red, Color::Green);


    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;

                case Event::TextEntered:
                    searchBook.setString(event);

                case Event::MouseButtonPressed:
                    searchBook.update(Vector2f(event.mouseButton.x, event.mouseButton.y));
            }
            search.update(Vector2f(event.mouseButton.x, event.mouseButton.y));
            if (search.isPressed() && searchBook.getString() != "") {
                string lookFor = searchBook.getString();
                cout << "Searching for: " << lookFor << "..." << endl;
                vector<string> booksFound = openBooks(lookFor);
                searchBook.setSelected(false);
                searchBook.setString2("");
                string booksFoundStr;
                for (auto & i : booksFound) {
                    booksFoundStr += i + "\n";
                }
                filesBox.setString2(booksFoundStr);
            }
        }
        window.clear();
        window.draw(background);
        window.draw(searchText);
        searchBook.draw(window);
        search.draw(window);
        filesBox.draw(window);
        window.display();
    }
}