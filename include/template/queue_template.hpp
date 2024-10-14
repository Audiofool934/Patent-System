#ifndef QUEUE_TEMPLATE_HPP
#define QUEUE_TEMPLATE_HPP

#include <iostream>

template <typename T>
class Queue {
public:
    virtual int size() const = 0;
    virtual bool isEmpty() const = 0;
    virtual void push(T num) = 0;
    virtual T pop() = 0;
    virtual T peek() const = 0;
    virtual std::vector<T> toVector() const = 0;
};

template <typename T>
class LinkedListQueue: public Queue<T> {
private:
    struct ListNode {
        T data;
        ListNode* next;
        ListNode(T d): data(d), next(nullptr) {}
    };
    ListNode *front, *rear;
    int queSize;

public:
    LinkedListQueue() {
        front = nullptr;
        rear = nullptr;
        queSize = 0;
    }

    ~LinkedListQueue() {
        ListNode* curr = front;
        while(curr != nullptr) {
            ListNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    int size() const override{
        return queSize;
    }

    bool isEmpty() const override {
        return queSize == 0;
    }

    void push(T num) override {
        ListNode* node = new ListNode(num);
        // 注意边际情况
        if (front == nullptr) {
            front = node;
            rear = node;
        } else {
            rear->next = node;
            rear = node;
        }
        queSize++;
    }

    T pop() override {
        T num = peek();
        
        ListNode* tmp = front;
        front = front->next;

        delete tmp;
        queSize--;
        return num;
    }

    T peek() const override {
        if (size() == 0) {
            throw std::out_of_range("queue is empty");
        }
        return front->data;
    }

    std::vector<T> toVector() const override {
        ListNode* node = front;
        std::vector<T> res(size());
        for (int i = 0; i < res.size(); i++) {
            res[i] = node->data;
            node = node->next;
        }
        return res;
    }

    void display() {
        ListNode* node = front;
        std::cout << "Queue (front): ";
        while (node != nullptr) {
            std::cout << node->data << " ";
            node = node->next;
        }
        std::cout << "Queue (rear): " << std::endl;
    }

};

template <typename T>
class ArrayQueue: public Queue<T> {
private:
    T* nums;
    T front;
    int queSize;
    int queCapacity;

public:
    ArrayQueue(int capacity) {
        nums = new T[capacity];
        queCapacity = capacity;
        front = queSize = 0;
    }

    ~ArrayQueue() {
        delete[] nums;
    }

    // int capacity() {
    //     return queCapacity;
    // }

    T size() const override {
        return queSize;
    }

    bool isEmpty() const override {
        return size() == 0;
    }

    void push(T num) override{
        if (queSize == queCapacity) {
            throw std::out_of_range("queue is full");
            return;
        }
        T rear = (front + queSize) % queCapacity;
        nums[rear] = num;
        queSize++;
    }

    T pop() override {
        T num = peek();
        front = (front + 1) % queCapacity;
        queSize--;
        return num;
    }

    T peek() const override {
            throw std::out_of_range("queue is empty");
        return nums[front];
    }

    std::vector<T> toVector() const override {
        std::vector<T> arr(queSize);
        for (int i = 0, j = front; i < queSize; i++, j++) {
            arr[i] = nums[j % queCapacity];
        }
        return arr;
    }

    void display() {
        std::cout << "Queue (front): ";
        for (int i = 0, j = front; i < queSize; i++, j++) {
            std::cout << nums[j % queCapacity] << " ";
        }
        std::cout << "Queue (rear): " << std::endl;
    }

};

#endif