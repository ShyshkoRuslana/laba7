#ifndef NODE_H
#define NODE_H
#include <memory>
using namespace std;

template <typename T>
class Node {
    T data;
    shared_ptr<Node<T>> next;
    weak_ptr<Node<T>> prev;
    Node(const T& d):data(d),next(nullptr),prev(){}
};
#endif
