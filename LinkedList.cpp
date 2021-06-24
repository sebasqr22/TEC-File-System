#pragma once
#include <iostream>
#include "Node.cpp"

template <class T>
class LinkedList {
private:
    Node<T> *first;
    int size;

public:
    LinkedList(){
        first = nullptr;
        size = 0;
    }

    int getSize() {
        return size;
    }

    void insertAtFirst(T data) {
        Node<T> *newNode = new Node<T>(data);
        if(first == nullptr){
            first = newNode;
        } else {
            newNode->setNext(first);
            first = newNode;
        }
        size++;
    }

    void insertAtEnd(T data) {
        Node<T> *newNode = new Node<T>(data);
        if (first == nullptr) {
            first = newNode;
        } else {
            Node<T> *current = first;
            while (current->getNext() != nullptr) {
                current = current->getNext();
            }
            current->setNext(newNode);
        }
        size++;
    }

    void insertElement(T data, int position) {
        Node<T> *newNode = new Node<T>(data);
        Node<T> *current = first;

        if(first != nullptr) {
            if (1 <= position && position < size) {
                for (int i = 0; i < (position - 1); ++i) {
                    current = current->getNext();
                }
                newNode->setNext(current->getNext());
                current->setNext(newNode);
            }
            if (position == 0) {
                newNode->setNext(first);
                first = newNode;
            }
            if (size <= position) {
                for (int i = 0; i < (size - 1); ++i) {
                    current = current->getNext();
                }
                current->setNext(newNode);
            }
        } else{
            first = newNode;
        }
        size++;
    }

    Node<T>* getElement(int position) {
        Node<T> *current = first;

        if(position < size && position >= 0) {
            for (int i = 0; i < position; i++) {
                current = current->getNext();
            }
        } else{
            return nullptr;
        }
        return current;
    }

    Node<T>* getElement2(T data) {
        Node<T> *current = first;

        for (int i = 0; i < size; ++i) {
            if (current->getData() == data){
                return current; 
            } else
                current = current->getNext();
        }
        Node<T>* notFoundNode = new Node<T>(nullptr);
        return notFoundNode;
    }

    void setElement(T element, int position) {
        Node<T> *current = first;

        if (first != nullptr && position < size) {
            if (1 <= position && position < size) {
                for (int i = 0; i < (position - 1); i++) {
                    current = current->getNext();
                }
                current->getNext()->setData(element);
            }
            if (position == 0) {
                first->setData(element);
            }
            if (size <= position) {
                for (int i = 0; i < (size - 1); i++) {
                    current = current->getNext();
                }
                current->getNext()->setData(element);
            }
        }
    }

    void deleteElement(int position) {
        if (position == 0 && size > 0) {
            first = first->getNext();
            size--;
        } else {
            if (position <= (size - 1)) {
                Node<T>* current = first;
                for (int i = 0; i < (position - 1); i++) {
                    current = current->getNext();
                }
                current->setNext(current->getNext()->getNext());
                size--;
            }
        }
    }

    void deleteElement2(T data) {
        Node<T> *current = first;

        if (size > 0){
            if (*current->getData() == *data) {
                first = first->getNext();
                this->size--;
            } else {
                while (current != nullptr && current->getNext() != nullptr) {
                    if (*current->getNext()->getData() == *data) {
                        current->setNext(current->getNext()->getNext());
                        this->size--;
                    }
                    current = current->getNext();
                }
            }
        }
    }

    bool containsElement(T data) {
        Node<T> *current = first;

        for (int i = 0; i < size; ++i) {
            if (current->getData() == data){
                return true;
            } else
                current = current->getNext();
        }
        return false;
    }

    void printList() {
        Node<T> *current = first;
        while(current != nullptr){
            std::cout << (current->getData()) << ", ";
            current = current->getNext();
        }
        std::cout << std::endl;
    }
};
