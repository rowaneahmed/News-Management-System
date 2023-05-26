#include "sign_up.h"
#include "ui_sign_up.h"
#include "user.h"
#include "QPixmap"
#include "QFile"
#include "QTextStream"
#include "QMessageBox"
#include "QList"
#include "usersdatabase.h"
#include <iostream>
using namespace std;

QString userName;
Sign_Up::Sign_Up(QWidget *parent, UsersDatabase usersdatabasearg) :
    QDialog(parent)
    ,ui(new Ui::Sign_Up)
    ,users_database(usersdatabasearg)
{
    ui->setupUi(this);
    QPixmap pix("C:\\Users\\PC\\OneDrive\\Desktop\\signup.jpg");
    ui->label_pic->setPixmap(pix.scaled(201,271,Qt::KeepAspectRatio));
}

Sign_Up::~Sign_Up()
{
    delete ui;
}


void Sign_Up::on_pushButton_signup_clicked()
{
    QFile file("C:\\Users\\PC\\OneDrive\\Desktop\\Users info.txt");

    QString username =ui->lineEdit_usernme->text();
    userName=username;
    QString password =ui->lineEdit_password->text();
    if(username.isEmpty() || password.isEmpty()){
        QMessageBox::warning(this,"failed","Please fill all data");
        return;
    }

    //get users from the hash table of usersdatabase
    unordered_map<QString,User> usersdatabase = users_database.getusersdatabase();

    //check if the user entered a valid username
    static QRegularExpression adm("admin.*",QRegularExpression::CaseInsensitiveOption);
    if(adm.match(username).hasMatch()){
        QMessageBox::warning(this,"failed","User cannot use admin as a username");
        return;
    }
    //check if username already exists or not
    if(usersdatabase.find(username) != usersdatabase.end()){
        QMessageBox::warning(this,"failed","User Already exists Log in or try another username");
        return;
    }

    //insert new user
    file.open(QIODevice::Append | QIODevice::WriteOnly);
    QTextStream out(&file);
    out<<"\n"<<username<<","<<password;
    User newUser(username,password);
    usersdatabase[username]=newUser;
    QMessageBox::information(this,"congrats","signed up successfully");
    file.close();

    hide();
    newspage=new News_page(this);
    newspage->show();

}



void Sign_Up::on_pushButton_login_clicked()
{
    hide();
    log_in=new login(this,users_database);
    log_in->show();
}

