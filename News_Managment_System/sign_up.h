#ifndef SIGN_UP_H
#define SIGN_UP_H

#include "login.h"
#include "news_page.h"
#include "usersdatabase.h"
#include <QDialog>

extern QString userName;
namespace Ui {
class Sign_Up;
}

class Sign_Up : public QDialog
{
    Q_OBJECT

public:
    explicit Sign_Up(QWidget *parent = nullptr, UsersDatabase userdatabase = {});
    ~Sign_Up();

private slots:
    void on_pushButton_signup_clicked();

    void on_pushButton_login_clicked();

private:
    Ui::Sign_Up *ui;
    News_page* newspage;
    UsersDatabase users_database;
    login* log_in;


};

#endif // SIGN_UP_H
