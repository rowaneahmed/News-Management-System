#ifndef FINDCATEGORY_H
#define FINDCATEGORY_H

#include <QDialog>

namespace Ui {
class FindCategory;
}

class FindCategory : public QDialog
{
    Q_OBJECT

public:
    explicit FindCategory(QWidget *parent = nullptr);
    ~FindCategory();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::FindCategory *ui;
};

#endif // FINDCATEGORY_H
