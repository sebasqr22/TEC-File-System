#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <dirent.h>
#include "LinkedList.cpp"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "button.cpp"
#include "ceSEARCH.cpp"
#include "ceROBOT.cpp"

using namespace sf;
using namespace std;

int main(){
    Font font;
    font.loadFromFile("BigShouldersStencilDisplay-Regular.ttf");
    RenderWindow window(VideoMode(750,750), "TEC-File System");
    Texture backgroundTexture;
    RectangleShape background;
    Text searchText;
    searchText.setString("Please choose an app you want to use: ");
    searchText.setPosition(200,80);
    searchText.setFont(font);
    searchText.setFillColor(Color::Green);

    backgroundTexture.loadFromFile("background.png");
    background.setPosition(0,0);
    background.setTexture(&backgroundTexture);
    background.setSize(Vector2f(750,750));

    button ceROBOT_(Vector2f(125, 250), Vector2f(100,50), font, "ceROBOT", Color::Red, Color::Green);
    button ceSEARCH_(Vector2f(525, 250), Vector2f(100,50), font, "ceSEARCH", Color::Blue, Color::Green);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;
            }
            ceROBOT_.update(Vector2f(event.mouseButton.x, event.mouseButton.y));
            ceSEARCH_.update(Vector2f(event.mouseButton.x, event.mouseButton.y));
            if (ceROBOT_.isPressed()) {
                window.close();
                ceROBOT();
            }
            else if (ceSEARCH_.isPressed()) {
                window.close();
                ceSEARCH();
            }
        }
        window.clear();
        window.draw(background);
        window.draw(searchText);
        ceROBOT_.draw(window);
        ceSEARCH_.draw(window);

        window.display();
    }

    return 0;
}
