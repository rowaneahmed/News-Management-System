#ifndef ADMINMAINWINDOW_H
#define ADMINMAINWINDOW_H

#include "categorymainwindow.h"
#include "newsadminwindow.h"
#include <QDialog>
class MainWindow;

namespace Ui {
class AdminMainWindow;
}

class AdminMainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AdminMainWindow(QWidget *parent = nullptr);
    ~AdminMainWindow();

private slots:
    void on_CategoryButton_clicked();
    void on_NewsButton_clicked();
    void on_logout_clicked();

private:
    Ui::AdminMainWindow *ui;
    CategoryMainWindow *category;
    NewsAdminWindow *news;
    MainWindow* mainwindow;

};

#endif // ADMINMAINWINDOW_H
