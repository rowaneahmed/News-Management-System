#include "login.h"
#include "ui_login.h"
#include<QMessageBox>
#include<QRegularExpressionMatch>
#include"user.h"
#include<qDebug>
#include "sign_up.h"

QString currentUser;
//QStringList userNames;
//unordered_map<QString, User> login_info;
login::login(QWidget *parent, UsersDatabase usersdatabasearg) :
    QDialog(parent),
    ui(new Ui::login)
   ,users_database(usersdatabasearg)
{
    ui->setupUi(this);
    QPixmap pix("C:\\Users\\PC\\OneDrive\\Desktop\\login.jpg");
    ui->label_3->setPixmap(pix.scaled(261,241,Qt::KeepAspectRatio));

    //loaddata_userfile( login_info);
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_login_clicked()
{
    QString userNname = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    userName=userNname;

    if (userNname.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "failed", "Please fill all data");
        return;
    }

    //get users from the hash table of usersdatabase
    unordered_map<QString,User> usersdatabase = users_database.getusersdatabase();

    unordered_map<QString, User>::iterator it= usersdatabase.find(userNname);

    QRegularExpression adm("admin.*",QRegularExpression::CaseInsensitiveOption);
    if (it != usersdatabase.end())
    {
        if (password == it->second.getPassword())
        {
            QRegularExpressionMatch match = adm.match(userNname);
            if (match.hasMatch()) {

                QMessageBox::information(this, "succ", "welcome admin");
                //open admin window
                this->hide();
                admin=new AdminMainWindow(this);
                admin->show();
            }
            else
            {
                currentUser=it->first;

                //open disblay window
                hide();
                n=new News_page(this);
                n->show();
            }

        }
        else
        {
            QMessageBox::critical(this, "warning", "Wrong Password Try Again");

        }

    }
    else {
        QMessageBox::warning(this, "warning", "This Account doesn't exist Register now");
    }
}

//void login::loaddata_userfile(unordered_map<QString,User>& login_info){


//    QFile myfile("C:/Users/marie/OneDrive/Documents/college/Subjects Materials/data structure/Users info.txt");
//    QTextStream in(&myfile);

//    if (!myfile.open(QIODevice::ReadOnly))
//    {
//        QMessageBox::warning(this, "warning", "file not open");
//    }

//    while (!in.atEnd()) {
//        QString line = in.readLine();
//        if(!line.isEmpty()){
//            QVector<QString> line_splitted = line.split(",");
//            User newUser(line_splitted[0],line_splitted[1]);
//            login_info[line_splitted[0]]=newUser;
//            userNames.append(line_splitted[0]);

//        }
//    }
//    myfile.close();

//}


void login::on_pushButton_signup_clicked()
{
    hide();
    signup=new Sign_Up(this,users_database);
    signup->show();
}

