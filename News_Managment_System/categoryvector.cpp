
#include "categoryvector.h"
//#include "Globals.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include <assert.h>

template <class T>
CategoryVector<T>::CategoryVector()
{   size=20;
    arr=new T[size];
    count=0;

}

template <class T>
int CategoryVector<T>::Length()
{
    return count;
}

template <class T>
void CategoryVector<T>::Append(T val)
{
    if(count==size)
        Expand();
    arr[count]=val;
    count++;
}

template <class T>
void CategoryVector<T>::Expand()
{
    size*=2; //define new capacity
    T* tmp=new T[size];
    for(int i=0; i<count;i++)
        tmp[i]=arr[i];
     //release old space
    arr=tmp;
}

template <class T>
T CategoryVector<T>::At(int pos)
{
    assert(pos<count);
    return arr[pos];
}

template <class T>
void CategoryVector<T>::insertAt(int pos, T val)
{
    assert(pos<count);
    if(count==size)
        Expand();
    //shift elements to the right
    for(int i=count;i>pos; i--)
        arr[i]=arr[i-1];
    //insert value at required position
    arr[pos]=val;
    count++;
}

template <class T>
void CategoryVector<T>::deleteAt(int pos)
{
    assert(pos<count);
    //shift elements to the left
    for(int i=pos;i<count-1;i++)
        arr[i]=arr[i+1];
    count--;
}


template <class T>
void CategoryVector<T>::writetofile()
{
    QFile file("C:\\Users\\PC\\OneDrive\\Desktop\\categories.txt");
    file.open(QIODevice::Truncate | QIODevice::WriteOnly);
    QTextStream stream(&file);
    for(int i=0;i<Length();i++)
    {
        stream << QString::fromStdString(arr[i]) << "\n";
    }
    file.close();
}

template <class T>
void CategoryVector<T>::writefromfile()
{
    QFile file("C:\\Users\\PC\\OneDrive\\Desktop\\categories.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    while (!stream.atEnd())
    {
        QString name = stream.readLine().trimmed();
        Append(name.toStdString());
    }
    file.close();
}




