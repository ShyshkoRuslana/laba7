#ifndef NODE_H
#define NODE_H
#include <memory>
using namespace std;

template <typename T>
class Node {
public:
    T data;
    std::shared_ptr<Node<T>> next;
    std::weak_ptr<Node<T>> prev;
    Node(const T& d):data(d),next(nullptr),prev(){}
};
#endif
