/**
 * @file Node.cpp
 * @title Node
 * @brief Class for create a node for the linked list
 * */

template <class T>
class Node {
private:
    T data;
    Node<T> *next;

public:
    /**
     *@brief Method to set a node and a pointer to its next
     **/
    Node(T data) {
        Node::data = data;
        next = nullptr;
    }
    /**
     * @brief Method to set a node 
     * */
    void setData(T data) {
        Node::data = data;
    }
    /**
     * @brief Method tu get an specific data
     * @return Data
     **/
    T getData() {
        return data;
    }
position
    /**
     * @brief Method to set nect node
     **/
    void setNext(Node *next) {
        Node::next = next;
    }
    /**
     * @brief Method to get next node
     * @return Next node
     **/
    Node* getNext() {
        return next;
    }
};