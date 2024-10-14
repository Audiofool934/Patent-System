#ifndef LINKED_LIST_TEMPLATE_HPP
#define LINKED_LIST_TEMPLATE_HPP

#include <iostream>
#include <stdexcept>

template <typename T>
class LinkedList {
public:
    virtual void insert(const T& data) = 0;
    virtual void remove(const T& data) = 0;
    virtual bool find(const T& data) const = 0;
    virtual T find_and_return(const T& data) const = 0;
    virtual void display() const = 0;
    virtual ~LinkedList() {}
};

template <typename T>
class SinglyLinkedList: public LinkedList<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d): data(d), next(nullptr) {}
    };
    Node* head;

public:
    SinglyLinkedList() : head(nullptr) {}

    Node* getHead() const { return head; }

    void insert(const T& data) override {
        Node* newNode = new Node(data);
        newNode->next = head;
        head = newNode;
    }

    void remove(const T& data) override {
        if (!head) return;

        Node* temp = head;
        if (head->data == data) {
            head = head->next;
            delete temp;
            return;
        } // 这里就不额外创造哨兵节点了

        Node* prev = nullptr;
        while (temp && temp->data != data) {
            prev = temp;
            temp = temp->next;
        }

        if (!temp) {
            throw std::invalid_argument("Element not found in the list");
        }

        prev->next = temp->next;
        delete temp;
    }

    bool find(const T& data) const override {
        Node* temp = head;
        while (temp) {
            if (temp->data == data) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    T find_and_return(const T& data) const override {
        Node* temp = head;
        while (temp) {
            if (temp->data == data) {
                return temp->data;
            }
            temp = temp->next;
        }
        return T();
    }

    void display() const override {
        if (!head) {
            throw std::out_of_range("The list is empty!");
        }

        Node* temp = head;
        while (temp) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "null" << std::endl;
    }

    ~SinglyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

template <typename T>
class DoublyLinkedList : public LinkedList<T> {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& d) : data(d), prev(nullptr), next(nullptr) {}
    };
    Node* head;

public:
    DoublyLinkedList() : head(nullptr) {}

    void insert(const T& data) override {
        Node* newNode = new Node(data);
        if (head) {
            head->prev = newNode;
            newNode->next = head;
        }
        head = newNode;
    }

    void remove(const T& data) override {
        if (!head) return;

        Node* temp = head;
        while (temp && temp->data != data) {
            temp = temp->next;
        }

        if (temp) {
            if (temp->prev) {
                temp->prev->next = temp->next;
            } else {
                head = temp->next;
            }
            if (temp->next) {
                temp->next->prev = temp->prev;
            }
            delete temp;
        }
    }

    bool find(const T& data) const override {
        Node* temp = head;
        while (temp) {
            if (temp->data == data) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void display() const override {
        if (!head) {
            throw std::out_of_range("The list is empty!");
        }

        Node* temp = head;
        while (temp) {
            std::cout << temp->data << " <->";
            temp = temp->next;
        }
        std::cout << "null" << std::endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

template <typename T>
class CircularLinkedList : public LinkedList<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {}
    };
    Node* tail;

public:
    CircularLinkedList() : tail(nullptr) {}

    void insert(const T& data) override {
        Node* newNode = new Node(data);
        if (!tail) {
            tail = newNode;
            tail->next = tail;
        } else {
            newNode->next = tail->next;
        }
    }

    void remove(const T& data) override {
        if (!tail) return;

        Node* curr = tail->next;
        Node* prev = tail;

        do {
            if (curr->data == data) {
                if (curr == tail) {
                    if (tail == tail->next) {
                        delete tail;
                        tail = nullptr;
                    } else {
                        prev->next = curr->next;
                        delete tail;
                        tail = prev;
                    }
                } else {
                    prev->next = curr->next;
                    delete curr;
                }
                return;
                prev = curr;
                curr = curr->next;
            }
        } while (curr != tail->next);
    }

    bool find(const T& data) const override {
        if (!tail) return false;

        Node* curr = tail->next;
        do {
            if (curr->data == data) return true;
            curr = curr->next;
        } while (curr != tail->next);

        return false;
    }
    
    void display() const override {
        if (!tail) return;

        Node* curr = tail->next;
        do {
            std::cout << curr->data << " -> ";
            curr = curr->next;
        } while (curr != tail->next);

        std::cout << "(back to head)" << std::endl;
    }
    
    ~CircularLinkedList() {
        if (!tail) return;

        Node* curr = tail->next;
        tail->next = nullptr; // 打破循环链
        while (curr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }

        tail = nullptr;
    }
};

#endif