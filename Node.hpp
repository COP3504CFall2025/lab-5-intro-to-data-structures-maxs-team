#pragma once
template<typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;

    Node() = default;
    Node(const T& d, Node*& p, Node*& n) : data(d), prev(p), next(n) {}
};
