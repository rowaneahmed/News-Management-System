
#ifndef NEWS_H
#define NEWS_H


#include<iostream>

#include <Qdate>
#include<Qstring>
#include "comments.h"

using namespace std;

typedef struct {
    QString title;
    QString text;
    QString username;
    QString date;
} comment;


class News
{
public:
    string title, description, category;
    QString rate = "0";
    int spamCounter = 0;
    QString rateCounter = "0";
    QDate date;
    QVector <comment>* mycomment;
    News();
    News(string t, string, QDate, string, QString,int);
    News(string t, string, QDate, string, QString, int s,QString);
    News(string t, string d, QDate dt, string c, QString r, comment);
    string toString();
    QString ReadComments();
    void AddComments();
};

#endif // NEWS_H
