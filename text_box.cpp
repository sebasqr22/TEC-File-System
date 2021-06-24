#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class text_box {
    private: 
        Text text;
        string textStr;
        RectangleShape textbox;
        bool isSelected = false;

    public:
        text_box(int charSize, Vector2f textboxSize, Color charColor, Color textboxColor, bool selected, Vector2f position, Font &font) {
            text.setCharacterSize(charSize);
            text.setFillColor(charColor);
            text.setFont(font);
            textbox.setSize(textboxSize);
            textbox.setFillColor(textboxColor);
            textbox.setPosition(position);
            text.setPosition(Vector2f(textbox.getPosition().x, textbox.getPosition().y));
            isSelected = selected;
        }

        void setSelected(bool selected) {
            isSelected = selected;
        }

        void draw(RenderWindow &window) {
            window.draw(textbox);
            window.draw(text);
        }

        void update(Vector2f mousepos) {
            if (textbox.getGlobalBounds().contains(mousepos) && Mouse::isButtonPressed(Mouse::Left)) {
                isSelected = true;
            }
        }

        bool getSelected() {
            return isSelected;
        }

        void setString(Event input) {
            if (isSelected) {
                int chartyped = input.text.unicode;
                if (chartyped != 8 && chartyped != 13 && chartyped != 27)
                    textStr += static_cast<char>(chartyped);
                else if (chartyped == 8)
                    textStr.pop_back();
                else if (chartyped == 13)
                    isSelected = false;
                
                text.setString(textStr + "_");
            }
            text.setString(textStr);
        }

        string getString() {
            return textStr;
        }
};