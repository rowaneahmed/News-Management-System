#ifndef ADDN_H
#define ADDN_H

#include <QDialog>
#include"fileheader.h"
#include "globals.h"
namespace Ui {
class addN;
}

class addN : public QDialog
{
    Q_OBJECT

public:
    explicit addN(QWidget *parent = nullptr);
    ~addN();
signals:
    void newsSaved();
public slots:
    void on_savebtn_clicked();
    void on_cancelbtn_clicked();

private:
    Ui::addN *ui;
};

#endif // ADDN_H
