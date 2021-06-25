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
int main() {
    LinkedList<LinkedList<vector<byte>>> bookList;
    Font font;
    font.loadFromFile("BigShouldersStencilDisplay-Regular.ttf");
    RenderWindow window(VideoMode(750,750), "TEC-File System");
    Texture backgroundTexture;
    RectangleShape background;

    backgroundTexture.loadFromFile("background.png");
    background.setPosition(0,0);
    background.setTexture(&backgroundTexture);
    background.setSize(Vector2f(750,750));

    text_box searchBook(50, Vector2f(250, 60), Color::White, Color::Black, false, Vector2f(50,150), font);
    button search(Vector2f(125, 250), Vector2f(100,50), font, "SEARCH", Color::Red, Color::Green);


    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case Event::Closed:
                    //socket.disconnect();
                    window.close();
                    break;

                case Event::TextEntered:
                    searchBook.setString(event);

                case Event::MouseButtonPressed:
                    searchBook.update(Vector2f(event.mouseButton.x, event.mouseButton.y));
            }
            search.update(Vector2f(event.mouseButton.x, event.mouseButton.y));
            if (search.isPressed()) {
                cout << "Searching... " << endl;
            }
        }
        window.clear();
        window.draw(background);
        searchBook.draw(window);
        search.draw(window);
        window.display();
    }
}