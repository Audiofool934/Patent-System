#ifndef STACK_TEMPLATE_HPP
#define STACK_TEMPLATE_HPP

#include <iostream>

template <typename T>
class stack {
public:
    virtual int size() const = 0;
    virtual bool isEmpty() = 0;
    virtual void push() = 0;
    virtual void pop() = 0;
    virtual T top() = 0;
    std::vector<T> toVector() = 0;
};

// 基于链表实现栈（头插）
template <typename T>
class LinkedListStack : public stack<T> {
private:
    struct ListNode {
        T data;
        ListNode* next;
        ListNode(T d): data(d), next(nullptr) {}
    };
    ListNode* stackTop;
    T stackSize;

public:
    LinkedListStack() {
        stackTop = nullptr;
        stackSize = 0;
    }

    ~LinkedListStack() {
        ListNode* curr = stackTop;
        while(curr != nullptr) {
            ListNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    T size() const override {
        return stackSize;
    }

    bool isEmpty() override {
        return size() == 0;
    }

    void push(T num) override {
        ListNode* node = new ListNode(num);
        node->next = stackTop;
        stackTop = node;
        stackSize++;
    }

    void pop() override {
        ListNode* node = stackTop;
        stackTop = stackTop->next;
        delete node;
        stackSize--;
    }

    T top() override {
        if (isEmpty())
            throw std:: out_of_range("stack is empty!");
        return stackTop->data;
    }

    std::vector<T> toVector() override {
        ListNode* node = stackTop;
        std::vector<T> res(size());
        for (T i = res.size() - 1; i >= 0; i--) {
            res[i] = node->data;
            node = node->next;
        }
    }
};

template <typename T>
class ArrayStack : public stack<T> {
    private:
        std::vector<int> stack;
    public:
        int size() const override {
            return stack.size();
        }

        bool isEmpty() override{
            return stack.size() == 0;
        }

        void push(int num) override {
            stack.push_back(num);
        }

        int pop() override {
            int num = top();
            stack.pop_back();
            return num;
        }

        int top() override{
            if (isEmpty())
                throw std::out_of_range("stack is empty!");
            return stack.back();
        }

        vector<int> toVector() override {
            return stack;
        }
};

#endif