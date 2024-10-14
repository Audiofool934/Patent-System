#ifndef VECTOR_TEMPLATE_HPP
#define VECTOR_TEMPLATE_HPP

#include <iostream>
#include <stdexcept>
#include <algorithm>

template<typename T>
class myVector {
private:
    T* data;
    size_t size_;
    size_t capacity_;

    // 动态调整内存大小
    void resizeIfNeeded() {
        if (size_ >= capacity_) {
            capacity_ = capacity_ == 0 ? 1 : capacity_ *2;
            T* newData = new T[capacity_];
            std::copy(data, data + size_, newData); // 复制现有数据到新分配的内存
            delete[] data; // 释放旧内存
            data = newData;
        }
    }

public:
    myVector() : data(nullptr), size_(0), capacity_(0) {}
    // 支持通过数组初始化
    myVector(const T arr[], size_t arr_size) : size_(arr_size), capacity_(arr_size) {
        data = new T[capacity_];
        std::copy(arr, arr + arr_size, data);
    }

    // 支持通过列表初始化
    myVector(std::initializer_list<T> init_list) : size_(init_list.size()), capacity_(init_list.size()) {
        data = new T[capacity_];
        std::copy(init_list.begin(), init_list.end(), data);
    }

    size_t size() const {
        return size_;
    }

    size_t capacity() const {
        return capacity_;
    }

    // 通过索引访问元素
    T& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // 添加元素到末尾
    void push_back(const T& value) {
        resizeIfNeeded();
        data[size_++] = value;
    }

    // 移除最后一个元素（栈）
    void pop_back() {
        if (size_ > 0) {
            --size_;
        }
    }

    // 按索引移除元素
    void remove_at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        std::move(data + index + 1, data + size_, data + index);
        --size_;
    }

    // 按值移除元素
    bool remove_element(const T& value) {
        for (size_t i = 0; i < size_; ++i) {
            if (data[i] == value) {
                remove_at(i);
                return true;
            }
        }
        return false;
    }

    void print() const {
        std::cout << "[";
        for (size_t i = 0; i < size_; ++i) {
            std::cout << data[i];
            if (i < size_ - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }

    // 迭代器
    T* begin() {
        return data;
    }

    T* end() {
        return data + size_;
    }

    const T* begin() const {
        return data;
    }

    const T* end() const {
        return data + size_;
    }
    
    void clear() {
        size_ = 0;
    }

    ~myVector() {
        delete[] data;
    }
};

#endif