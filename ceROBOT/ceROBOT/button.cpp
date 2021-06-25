/**
 * @file button.cpp
 * @title Button
 * @brief Classs for create a button
 * */

#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

enum button_states{BTN_IDLE = 0, BTN_ACTIVE = 1};

class button {
    private:
        RectangleShape buttonShape;
        Text text;
        Color idleColor;
        Color activeColor;
        short unsigned buttonState;
        int counter;

    public:
        /**
         * @brief Main constructor
         * */
        button(Vector2f position, Vector2f size, Font &font, string content, Color idle, Color active) {
            buttonState = BTN_IDLE;
            buttonShape.setPosition(position);
            buttonShape.setFillColor(idle);
            buttonShape.setSize(size);
            text.setCharacterSize(15);
            text.setFont(font);
            text.setFillColor(Color::Black);
            text.setPosition(buttonShape.getPosition().x + (buttonShape.getGlobalBounds().width / 2.f - text.getGlobalBounds().width / 2.f),
                            buttonShape.getPosition().y + (buttonShape.getGlobalBounds().height / 2.f - text.getGlobalBounds().height / 2.f));
            text.setString(content);
            idleColor = idle;
            activeColor = active;
        }
        /**
         * @brief Method to check if the button was pressed
         * @return Bool value
         * */
        bool isPressed() {
            if (buttonShape.getFillColor() == activeColor) {
                return true;
            }
            return false;
        }
        /**
         * @brief Method to update the button
         * */
        void update(Vector2f mousepos) {
            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (buttonShape.getGlobalBounds().contains(mousepos) && counter == 0) {
                    counter++;
                    buttonShape.setFillColor(activeColor);
                }       
            }
            else {
                buttonShape.setFillColor(idleColor);
                counter = 0;
            }
            /*else {
                counter = 0;
                buttonShape.setFillColor(idleColor);
            }*/

            //cout << "buttonState: " << buttonState << endl;

            /*switch(buttonState) {
                case BTN_IDLE:
                    buttonShape.setFillColor(idleColor);
                    cout << "entered btn_idle" << endl;
                case BTN_ACTIVE:
                    buttonShape.setFillColor(activeColor);
                    cout << "entered btn_active" << endl;
            }*/
        }
        /**
         * @brief Method to draw the button
         * */
        void draw(RenderWindow &window) {
            window.draw(buttonShape);
            window.draw(text);
        }

};