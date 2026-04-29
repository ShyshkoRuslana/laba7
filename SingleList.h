#ifndef SINGLELIST_H
#define SINGLELIST_H
#include "Node.h"
#include <iostream>
#include <memory>
#include <stdexcept>

template <typename T>
class SingleList {
private:
    std::shared_ptr<Node<T>> head;
    int size;
public:
    SingleList() : head(nullptr), size(0) {}
    //додавання на початок
    void push_front(T value) {
        auto newNode = std::make_shared<Node<T>>(value);
        newNode->next = head;
        head = newNode;
        size++;
    }
    //додавання в кінець
    void push_back(T value) {
        auto newNode = std::make_shared<Node<T>>(value);
        if (!head) {
            head = newNode;
        }
        else {
            auto temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        size++;
    }
    //вилучення першого елемента
    void pop_front() {
        if (!head)
            throw std::out_of_range("List is empty");
        head = head->next;
        size--;
    }
    //вилученн останнбго елемента
    void pop_back() {
        if (!head)
            throw std::out_of_range("List is empty");
        if (!head->next) {
            head = nullptr;
        }
        else {
            auto temp = head;
            while (temp->next->next) {
                temp = temp->next;
            }
            temp->next = nullptr;
        }
        size--;
    }
    //можливість доступу до елемента за індеком
    T& at(int index) {
        if (index < 0 || index >= size)
            throw std::out_of_range("Index out of range");
        auto temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->data;
    }
    //додавання елемента за індексом
    void insert(int index, T value) {
        if (index < 0 || index > size)
            throw std::out_of_range("Index out of range");
        if (index == 0) {
            push_front(value);
            return;
        }
        auto newNode = std::make_shared<Node<T>>(value);
        auto temp = head;
        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;

        size++;
    }
    //вилучення елемента за індексом
    void remove(int index) {
        if (index < 0 || index >= size)
            throw std::out_of_range("Index out of range");
        if (index == 0) {
            pop_front();
            return;
        }
        auto temp = head;
        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        temp->next = temp->next->next;
        size--;
    }
    //перевірка списку на розмір
    int getSize() {
        return size;
    }
    //перевірка чи список не порожній
    bool isEmpty() {
        return size == 0;
    }
    //пошук елемента у списку
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
    //можливість веведення списку
    friend ostream& operator<<(ostream& os, const SingleList<T>& list) {
        shared_ptr<Node<T>> cur = list.head;
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