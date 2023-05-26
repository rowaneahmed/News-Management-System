#ifndef ADDCATEGORY_H
#define ADDCATEGORY_H

#include <QDialog>
#include <iostream>
using namespace std;

namespace Ui {
class AddCategory;
}

class AddCategory : public QDialog
{
    Q_OBJECT

public:
    explicit AddCategory(QWidget *parent = nullptr);
    ~AddCategory();

signals:
    void categorySaved();

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();



private:
    Ui::AddCategory *ui;
};

#endif // ADDCATEGORY_H
