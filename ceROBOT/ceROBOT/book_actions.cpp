/**
 * @file book_actions.cpp
 * @title Book Actions
 * @brief Class that creates and reads all the books
**/

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class book_actions{
    private:
        string route = "/home/sebas/Escritorio/ceROBOT/ceROBOT/books/";

    public:
        /**
         * @brief Method that creates a new book
        **/
        void createBook(string name, string content){ //it's not necesary to add .txt
            string nameAux = route + name + ".txt";
            ofstream o(route);
            o.close();

            o.open(nameAux, fstream::app);
            o << content << "\n";
            o.close();
            cout << "Book '" + nameAux + "' was succesfully created...";
        }
        /**
         * @brief Method that extracts the information from a book and reads it.
        **/
        void readBook(string name){
            string line;
            string content;
            ifstream book(route + name + ".txt");
            if(book.is_open()){
                while(getline(book, line)){
                    content + line + "\n";
                }
                book.close();
            }
            else{
                cout << "It was unable to open " << name << endl;
            }
        }
};
