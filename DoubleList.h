#ifndef DOUBLELIST_H
#define DOUBLELIST_H
#include "Node.h"
#include <iostream>
#include <memory>
#include <stdexcept>
template<typename T>
class DoubleList {
private:
    shared_ptr<Node<T>> head;
    shared_ptr<Node<T>> tail;
    size_t sz;
public:
    DoubleList() : head(nullptr), tail(nullptr), sz(0) {}
    ~DoubleList() = default;
    void push_front(const T& val) {
        shared_ptr<Node<T>>  node = make_shared<Node<T>>(val);
        node->next = head;
        if (head) head->prev = node;
        head = node;
        if (!tail) tail = head;
        sz++;
    }
    void push_back(const T& val) {
        shared_ptr<Node<T>>node = make_shared<Node<T>>(val);
        if (!tail) {
            head = tail = node;
        }
        else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        sz++;
    }
    void pop_front() {
        if (!head) throw runtime_error("List is empty");
        head = head->next;
        if (head) head->prev.reset();
        else tail = nullptr;
        sz--;
    }
    void pop_back() {
        if (!tail) throw runtime_error("List is empty");
        auto p = tail->prev.lock();
        if (p) {
            p->next = nullptr;
            tail = p;
        } else {
            head = tail = nullptr;
        }
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
        shared_ptr<Node<T>>  cur = head;
        for (size_t i = 0; i < index; ++i) cur = cur->next;
        return cur->data;
    }
    const T& operator[](size_t index) const {
        if (index >= sz) throw out_of_range("Index out of range");
        auto cur = head;
        for (size_t i = 0; i < index; ++i) cur = cur->next;
        return cur->data;
    }
    void insert_at(size_t index, const T& val) {
        if (index > sz) throw out_of_range("Index out of range");
        if (index == 0) {
            push_front(val);
            return;
        }
        if (index == sz) {
            push_back(val);
            return;
        }
        auto cur = head;
        for (size_t i = 0; i < index - 1; ++i) cur = cur->next;
        auto node = make_shared<Node<T>>(val);
        node->next = cur->next;
        node->prev = cur;
        cur->next->prev = node;
        cur->next = node;
        sz++;
    }
    void remove_at(size_t index) {
        if (index >= sz) throw out_of_range("Index out of range");
        if (index == 0) {
            pop_front();
            return;
        }
        if (index == sz - 1) {
            pop_back();
            return;
        }
        auto cur = head;
        for (size_t i = 0; i < index; ++i) cur = cur->next;
        auto p = cur->prev.lock();
        p->next = cur->next;
        cur->next->prev = p;
        sz--;
    }
    int find(const T& val) const {
        auto cur = head;
        size_t i = 0;
        while (cur) {
            if (cur->data == val) return (int)i;
            cur = cur->next;
            ++i;
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