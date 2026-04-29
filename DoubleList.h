#ifndef DOUBLELIST_H
#define DOUBLELIST_H
#include "Node.h"
#include <iostream>
#include <memory>
#include <stdexcept>

template <typename T>
class DoubleList {
private:
    std::shared_ptr<Node<T>> head;
    std::shared_ptr<Node<T>> tail;
    int size;
public:
    DoubleList() : head(nullptr), tail(nullptr), size(0) {}
    void push_front(T value) {
        auto newNode = std::make_shared<Node<T>>(value);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }
    void push_back(T value) {
        auto newNode = std::make_shared<Node<T>>(value);
        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }
    void pop_front() {
        if (!head)
            throw std::out_of_range("List is empty");
        head = head->next;
        if (head)
            head->prev.reset();
        else
            tail = nullptr;
        size--;
    }
    void pop_back() {
        if (!tail)
            throw std::out_of_range("List is empty");
        tail = tail->prev.lock();
        if (tail)
            tail->next = nullptr;
        else
            head = nullptr;
        size--;
    }
    T& at(int index) {
        if (index < 0 || index >= size)
            throw std::out_of_range("Index out of range");
        auto temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->data;
    }
    void insert(int index, T value) {
        if (index < 0 || index > size)
            throw std::out_of_range("Index out of range");
        if (index == 0) {
            push_front(value);
            return;
        }
        if (index == size) {
            push_back(value);
            return;
        }
        auto newNode = std::make_shared<Node<T>>(value);
        auto temp = head;
        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;
        size++;
    }
    void remove(int index) {
        if (index < 0 || index >= size)
            throw std::out_of_range("Index out of range");

        if (index == 0) {
            pop_front();
            return;
        }
        if (index == size - 1) {
            pop_back();
            return;
        }
        auto temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        auto prevNode = temp->prev.lock();
        prevNode->next = temp->next;
        temp->next->prev = prevNode;

        size--;
    }
    int getSize() {
        return size;
    }
    bool isEmpty() {
        return size == 0;
    }
    int find(T value) {
        auto temp = head;
        int index = 0;

        while (temp) {
            if (temp->data == value)
                return index;
            temp = temp->next;
            index++;
        }
        return -1;
    }
    friend ostream& operator<<(ostream& os, const DoubleList<T>& list) {
        auto cur = list.head;
        os << "[";
        bool first = true;
        while (cur) {
            if (!first) os << ", ";
            os << cur->data;
            first = false;
            cur = cur->next;
        }
        os << "]";
        return os;
    }
};
#endif
