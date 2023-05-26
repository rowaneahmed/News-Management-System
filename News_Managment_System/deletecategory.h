#ifndef DELETECATEGORY_H
#define DELETECATEGORY_H

#include <QDialog>

namespace Ui {
class DeleteCategory;
}

class DeleteCategory : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteCategory(QWidget *parent = nullptr);
    ~DeleteCategory();

signals:
    void categoryDeleted();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::DeleteCategory *ui;
};

#endif // DELETECATEGORY_H
