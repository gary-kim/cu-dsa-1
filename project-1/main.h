#ifndef CU_DSA_1_MAIN_H
#define CU_DSA_1_MAIN_H

#include <string>
#include <unordered_map>

template <class T>
class List {
private:
    std::string name;
protected:
    class Node {
    public:
        Node *next = NULL;
        T value;
        Node(T value) : value(value) {}
        Node(T value, Node *next) : value(value), next(next) {}
    };
    void insertStart(T const&);
    void insertEnd(T const&);
    T remove();
    Node *start = NULL;
    Node *end = NULL;
public:
    List(std::string name) : name(name) {}
    virtual void push(T const&) {};
    virtual T pop() {};
    bool isEmpty();
};

template <class T> void List<T>::insertStart(T const& value) {
    if (this->start == NULL) {
        this->start = new Node(value);
        this->end = this->start;
        return;
    }
    Node *tmp = this->start;
    this->start = new Node(value, tmp);
    return;
}

template <class T> void List<T>::insertEnd(T const& value) {
    if (this->end == NULL) {
        this->start = new Node(value);
        this->end = this->start;
        return;
    }
    Node *tmp = this->end;
    this->end = new Node(value);
    tmp->next = this->end;
}

template <class T> T List<T>::remove() {
    Node *tr = this->start;
    if (tr == NULL) {
        return NULL;
    }
    this->start = this->start->next;
    if (this->start == NULL) {
        this->end = NULL;
    }
    T t = tr->value;
    delete tr;
    return t;
}

template <class T> bool List<T>::isEmpty() {
    return this->start == NULL;
}

template <class T>
class Queue: public List<T> {
public:
    void push(T const& value) {
        this->insertEnd(value);
    }
    T pop() {
        return this->remove();
    }
    using List<T>::List;
};

template <class T>
class Stack: public List<T> {
public:
    void push(T const& value) {
        this->insertStart(value);
    }
    T pop() {
        return this->remove();
    }
    using List<T>::List;
};

enum listType {
    stack = 0,
    queue = 1,
};

struct listEntry {
    void* list = NULL;
    listType type;
};

enum listContents {
    anInteger = 1,
    aDouble = 2,
    aString = 3,
};

void runFile();
void create(std::unordered_map<std::string, listEntry>&, std::string, std::string);
void push(std::unordered_map<std::string, listEntry>&, std::string, std::string);
void pop(std::unordered_map<std::string, listEntry>&, std::string);
listContents getListContents(std::string);

#endif //CU_DSA_1_MAIN_H
