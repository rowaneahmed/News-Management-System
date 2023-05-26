#ifndef CATEGORYMAINWINDOW_H
#define CATEGORYMAINWINDOW_H

#include <QDialog>
#include <QDialog>
#include <QMainWindow>
#include <QDialog>
#include <QScrollBar>
#include "addcategory.h"
#include "deletecategory.h"
#include "findcategory.h"

namespace Ui {
class CategoryMainWindow;
}

class CategoryMainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CategoryMainWindow(QWidget *parent = nullptr);
    void showCategory();
    ~CategoryMainWindow();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_verticalScrollBar_actionTriggered(int action);

private:
    Ui::CategoryMainWindow *ui;
    AddCategory *ptrAddCategory;
    DeleteCategory *ptrDeleteCategory;
    FindCategory *ptrFindCategory;
    QScrollBar *scrollBar;


};

#endif // CATEGORYMAINWINDOW_H
