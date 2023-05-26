
#ifndef NEWSLINKEDLIST_H
#define NEWSLINKEDLIST_H
#include <string>
#include<iostream>
using namespace std;
template <class T>
class Node {
public:
    Node<T>* next;
    T val;
    Node(T);
};
template <class T>
class NewsLinkedList
{
    int count;
    Node<T>* head, * tail;
public:
    NewsLinkedList();
    int Length();
    void Append(T); //insert
    void Update(string t, string d, int index);
    void Delete(int);
    void Clear();
    void writetoFile();
    void writeFromFile();
};

#endif // NEWSLINKEDLIST_H
