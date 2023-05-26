#include "adminmainwindow.h"
#include "mainwindow.h"
#include "ui_adminmainwindow.h"

AdminMainWindow::AdminMainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminMainWindow)
{
    ui->setupUi(this);
}

AdminMainWindow::~AdminMainWindow()
{
    delete ui;
}

void AdminMainWindow::on_CategoryButton_clicked()
{
    category=new CategoryMainWindow(this);
    category->show();
}

void AdminMainWindow::on_NewsButton_clicked()
{
    qDebug()<<"initializing newsadmin";
    news = new NewsAdminWindow(this);
    qDebug()<<"Showing newsadmin";
    news->show();
}

void AdminMainWindow::on_logout_clicked()
{
    this->close();
    mainwindow= new MainWindow(this);
    mainwindow->show();
}

