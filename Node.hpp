#pragma once
template<typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;

    Node() {};
    Node(const T& d) : data(d) {}
    Node(const T& d, Node* p, Node* n) : data(d), prev(p), next(n) {}
};
