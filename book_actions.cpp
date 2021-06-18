#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class book_actions{
    private:
        string route = "./books/";

    public:
        void createBook(string name, string content){ //it's not necesary to add .txt
            string nameAux = route + name + ".txt";
            ofstream o(nameAux);
            o << content << endl;
            o.close();
            cout << "Book '" + name + "' was succesfully created...";
        }
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