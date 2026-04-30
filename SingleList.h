#ifndef SINGLELIST_H
#define SINGLELIST_H
#include "Node.h"
#include <iostream>
#include <memory>
#include <stdexcept>

template<typename T>
class SingleList {
private:
    shared_ptr<Node<T>> head;
    size_t sz;
public:
    SingleList() : head(nullptr), sz(0) {}
    ~SingleList() = default;
    // Вставка значення на початок списку
    void push_front(const T& val) {
        shared_ptr<Node<T>> node = make_shared<Node<T>>(val);
        node->next = head;
        head = node;
        sz++;
    }
    // Вставка значення в кінець списку
    void push_back(const T& val) {
        shared_ptr<Node<T>> node = make_shared<Node<T>>(val);
        if (!head) {
            head = node;
        } else {
            shared_ptr<Node<T>> cur = head;
            while (cur->next) cur = cur->next;
            cur->next = node;
        }
        sz++;
    }
    void pop_front() {
        if (!head) throw runtime_error("List is empty");
        head = head->next;
        sz--;
    }
    // Видалення останнього елементу
    void pop_back() {
        if (!head) throw runtime_error("List is empty");
        if (!head->next) {
            head = nullptr;
            sz = 0;
            return;
        }
        shared_ptr<Node<T>> cur = head;
        while (cur->next && cur->next->next) cur = cur->next;
        cur->next = nullptr;
        sz--;
    }
    size_t size() const {
        return sz;
    }
    bool empty() const {
        return sz == 0;
    }
    T& operator[](size_t index) {
        if (index >= sz) throw out_of_range("Index out of range");
        shared_ptr<Node<T>> cur = head;
        for (size_t i = 0; i < index; ++i) cur = cur->next;
        return cur->data;
    }
    void insert_at(size_t index, const T& val) {
        if (index > sz) throw out_of_range("Index out of range");
        if (index == 0) {
            push_front(val);
            return;
        }
        shared_ptr<Node<T>> cur = head;
        for (size_t i = 0; i < index - 1; ++i) cur = cur->next;
        shared_ptr<Node<T>> node = make_shared<Node<T>>(val);
        node->next = cur->next;
        cur->next = node;
        sz++;
    }
    void remove_at(size_t index) {
        if (index >= sz) throw out_of_range("Index out of range");
        if (index == 0) {
            pop_front();
            return;
        }
        shared_ptr<Node<T>> cur = head;
        for (size_t i = 0; i < index - 1; ++i) cur = cur->next;
        cur->next = cur->next->next;
        sz--;
    }
    int find(const T& val) const {
        shared_ptr<Node<T>> cur = head;
        size_t i = 0;
        while (cur) {
            if (cur->data == val) {
                return i;
            }
            cur = cur->next;
            ++i;
        }
        return -1;
    }
    friend ostream& operator<<(ostream& os, const SingleList<T>& list) {
        shared_ptr<Node<T>> cur = list.head;
        os << "[";
        bool first = true;
        while (cur) {
            if (!first) {
                os << ", ";
            }
            os << cur->data;
            first = false;
            cur = cur->next;
        }
        os << "]";
        return os;
    }
};
#endif