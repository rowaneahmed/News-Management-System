#include "updaten.h"
#include "ui_updaten.h"
#include "globals.h"
updateN::updateN(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::updateN)
{
    ui->setupUi(this);
}

updateN::~updateN()
{
    delete ui;
}
void updateN::on_pushButton_clicked() {
    if(newsLL.Length() == 0)
        newsLL.writeFromFile();
    QString title = ui->lineEdit->text();
    QString description = ui->textEdit->toPlainText();
    newsLL.Update(title.toStdString(), description.toStdString(), pos);
    // Updating the file
    newsLL.writetoFile();
    emit newsUpdated();
    on_pushButton_2_clicked();
}
void updateN::on_pushButton_2_clicked() {
    ui->lineEdit->clear();
    ui->textEdit->clear();
    hide();
}
