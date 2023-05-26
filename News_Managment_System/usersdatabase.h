
#ifndef USERSDATABASE_H
#define USERSDATABASE_H
#include <QString>
#include <QFile>
#include "user.h"



class UsersDatabase
{
public:
    unordered_map<QString,User> usersdatabase;

    unordered_map<QString,User>& getusersdatabase();
    void loadUsersData();


};

#endif // USERSDATABASE_H
