
#include "usersdatabase.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>


unordered_map<QString, User>& UsersDatabase::getusersdatabase() {
    return usersdatabase;
}

void UsersDatabase::loadUsersData(){
    QFile file("C:\\Users\\PC\\OneDrive\\Desktop\\Users info.txt");
    QTextStream stream(&file);

    file.open(QIODevice::ReadOnly);

    while (!stream.atEnd()) {
        QString line = stream.readLine();
        if (line.isEmpty()) {
            continue; // Skip empty lines
        }

        QList<QString> pos=line.split(",");

        User newUser(pos[0],pos[1]);
        usersdatabase[pos[0]]=newUser;
    }
    file.close();
}

