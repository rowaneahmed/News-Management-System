#ifndef UPDATEN_H
#define UPDATEN_H

#include <QDialog>

namespace Ui {
class updateN;
}

class updateN : public QDialog
{
    Q_OBJECT

public:
    explicit updateN(QWidget *parent = nullptr);
    int pos;
    ~updateN();
signals:
    void newsUpdated();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
private:
    Ui::updateN *ui;
};

#endif // UPDATEN_H
