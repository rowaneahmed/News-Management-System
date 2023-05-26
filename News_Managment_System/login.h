#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "adminmainwindow.h"
#include "user.h"
#include<unordered_map>
#include<QFile>
#include"news_page.h"
#include "usersdatabase.h"
class Sign_Up;

extern QString currentUser;
namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr, UsersDatabase userdatabase = {});
    //void loaddata_userfile(unordered_map<QString,User>&);
    ~login();

private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_signup_clicked();

private:
    Ui::login *ui;
    News_page *n;
    AdminMainWindow *admin;
    Sign_Up *signup;
    UsersDatabase users_database;


};

#endif // LOGIN_H
