
#ifndef CATEGORYVECTOR_H
#define CATEGORYVECTOR_H

#include <string>
#include<iostream>
using namespace std;

template <class T>
class CategoryVector
{
    T* arr;
    int size, count;
public:
    CategoryVector();
    int Length();
    void Append(T);
    void Expand();
    T At(int);
    void insertAt(int, T);
    void deleteAt(int);
    void writetofile();
    void writefromfile();};

#endif // CATEGORYVECTOR_H
