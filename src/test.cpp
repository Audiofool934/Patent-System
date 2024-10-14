#include "../include/template/stack_template.hpp"
#include "../include/template/queue_template.hpp"
#include <iostream>

void testStack() {
    LinkedListStack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);

    std::cout << "Stack size: " << stack.size() << std::endl;
    std::cout << "Top element: " << stack.top() << std::endl;

    stack.pop();
    stack.pop();

    std::cout << "Stack size: " << stack.size() << std::endl;
    std::cout << "Top element: " << stack.top() << std::endl;

    std::vector<int> arr = stack.toVector();
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }

    stack.display();
}

void testQueue() {
    LinkedListQueue<int> queue;
    ArrayQueue<int> queue2(5);
    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.push(4);
    queue.push(5);

    queue2.push(1);
    queue2.push(2);
    queue2.push(3);
    queue2.push(4);
    queue2.push(5);

    queue.display();
    queue2.display();
}

int main() {
    testStack();
    testQueue();
    return 0;
}