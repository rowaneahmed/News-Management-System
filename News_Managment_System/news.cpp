#include<iostream>
#include<vector>
#include<QStringListModel>
#include<QStringList>
#include<iostream>
#include <QFile>
#include "news_page.h"
#include <Qdate>
#include<Qstring>
#include "news.h"

using namespace std;

News::News()
{
    title = " ";
    description = " ";
    category = " ";
    rate = " ";
    mycomment = new QVector<comment>;
    spamCounter = 0;
    rateCounter = "0";
}
News::News(string t, string d, QDate dt, string c, QString r,int s) {
    title = t;
    description = d;
    date = dt;
    category = c;
    rate = r;
    spamCounter = s;
}
News::News(string t, string d, QDate dt, string c, QString r,int s, QString ratecount) {
    title = t;
    description = d;
    date = dt;
    category = c;
    rate = r;
    spamCounter = s;
    rateCounter = ratecount;
}

News:: News(string t, string d, QDate dt, string c, QString r, comment com)
{
    title = t;
    description = d;
    date = dt;
    category = c;
    rate = r;
    mycomment = new QVector<comment>;
    mycomment->push_back(com);
    spamCounter = 0;
}


string News::toString() {
    string newsString;
    newsString += "Title: " + title + "\n";
    newsString += "Description: " + description + "\n";
    newsString += "Date: " + date.toString("yyyy-MM-dd").toStdString() + "\n";
    newsString += "Category: " + category + "\n";
    newsString += "Rate: " + rate.toStdString() + "\n";
    newsString += "Spam Counter: " + to_string(spamCounter) + "\n";
    return newsString;
}

QString News::ReadComments()
{
    QString cmts_str = "";
    qDebug()<< (*posts_comments)[titleName].size();
    for(int i = 0; i < (*posts_comments)[titleName].size(); i++) {
        comment cmt = (*posts_comments)[titleName][i];
        QString cmt_str = "";
        cmt_str += "Title : " + cmt.title + "\n";
        cmt_str += "Username : " + cmt.username+ "\n";
        cmt_str += "Comment : " +cmt.text+ "\n";
        cmt_str += "Date : " +cmt.date + "\n********\n";
        cmts_str += cmt_str;
    }
    return cmts_str;
}

void News::AddComments(){}

