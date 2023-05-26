
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "login.h"
#include "ui_mainwindow.h"
#include "QList"
#include "sign_up.h"
#include "QPixmap"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_Signup_clicked();

    void on_Login_clicked();

private:
    Ui::MainWindow *ui;
    Sign_Up *signup;
    login *log;
    UsersDatabase users_database;

};

#endif // MAINWINDOW_H
