
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "usersdatabase.h"
#include "QFile"
#include "QTextStream"
#include "QMessageBox"
#include "QList"
#include "sign_up.h"
#include "QPixmap"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    users_database.loadUsersData();
    QPixmap pix("C:\\Users\\PC\\OneDrive\\Desktop\\3d-world-news-background.jpg");
    ui->label_pic->setPixmap(pix.scaled(431,211,Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_Signup_clicked()
{
//    UsersDatabase usersdatabase;
//    usersdatabase.loadUsersData();
    hide();
    signup=new Sign_Up(this,users_database);
    signup->show();
}


void MainWindow::on_Login_clicked()
{
    hide();
    log=new login(this,users_database);
    log->show();

}

