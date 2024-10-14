#ifndef QUEUE_TEMPLATE_HPP
#define QUEUE_TEMPLATE_HPP

#include <iostream>

template <typename T>
class LinkedListQueue {
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
        ListNode* curr = stackTop;
        while(curr != nullptr) {
            ListNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    int size() {
        return queSize;
    }

    bool isEmpty() {
        return queSize == 0;
    }

    void push(int num) {
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

    int pop() {
        int num = peek();
        
        ListNode* tmp = front;
        front = front next;

        delete tmp;
        queSize--;
        return num;
    }

    int peek() {
        if (size() == 0) {
            std::cout << "empty! " << std::endl;
        }
        return front->data;
    }

    std::vector<int> tostd::vector() {
        ListNode* node = front;
        std::vector<int> res(size());
        for (int i = 0; i < res.size(); i++) {
            res[i] = node->data;
            node = node->next;
        }
        return res;
    }
};

class ArrayQueue {
private:
    int* nums;
    int front;
    int queSize;
    int queCapacity;
public:
    ArrayQueue(int capacity) {
        nums = new int[capacity];
        queCapacity = capacity;
        front = queSize = 0;
    }

    ~ArrayQueue() {
        delete[] nums;
    }

    int capacity() {
        return queCapacity;
    }

    int size() {
        return queSize;
    }

    bool isEmpty() {
        return size() == 0;
    }

    void push(int num) {
        if (queSize == queCapacity) {
            std::cout << "Full" << std::endl;
            return;
        }
        int rear = (front + queSize) % queCapacity;
        nums[rear] = num;
        queSize++;
    }

    int pop() {
        int num = peek();
        front = (front + 1) % queCapacity;
        queSize--;
        return num;
    }

    int peek() {
            throw std::out_of_range("队列为空");
            throw std::out_of_range("队列为空");
        return nums[front];
    }

    std::vector<int> toVector() {
        std::vector<int> arr(queSize);
        for (int i = 0, j = front; i < queSize; i++, j++) {
            arr[i] = nums[j % queCapacity];
        }
        return arr;
    }

};

#endif