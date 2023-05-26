
#ifndef USER_H
#define USER_H
#include <iostream>
#include "QString"
#include "list"
using namespace std;



class User
{
protected:
    int userID=0;
    QString Username;
    QString Password;
    list<QString> comments;
public:
    User();
    User(QString name , QString password);

    // Access Functions
    int getUserID();
    QString getUserName();
    QString getPassword();
    list<QString> getComments();

};

#endif // USER_H
