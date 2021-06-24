template <class T>
class Node {
private:
    T data;
    Node<T> *next;

public:
    Node(T data) {
        Node::data = data;
        next = nullptr;
    }

    void setData(T data) {
        Node::data = data;
    }

    T getData() {
        return data;
    }

    void setNext(Node *next) {
        Node::next = next;
    }

    Node* getNext() {
        return next;
    }
};