
#include "user.h"

User::User(){

}
User::User(QString name , QString password)
{
    Username  = name ;
    Password = password ;
    userID++;
}


int User::getUserID(){
    return userID;
}
QString User::getUserName(){
    return Username;
}

QString User::getPassword(){
    return Password;
}

list<QString> User::getComments(){
    return comments;
}
