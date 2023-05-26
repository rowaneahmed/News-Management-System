#include "addcategory.h"
#include "ui_addcategory.h"
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QCoreApplication>
#include "Globals.h"
using namespace std;

AddCategory::AddCategory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCategory)
{
    ui->setupUi(this);
}

AddCategory::~AddCategory()
{
    delete ui;
}


void AddCategory::on_pushButton_3_clicked()
{
    QString name = ui->lineEdit->text();

    QFile file("C:\\Users\\PC\\OneDrive\\Desktop\\categories.txt");
    bool found = false;
    int index = 0;

    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        QString line;
        QStringList lines;
        while (!stream.atEnd())
        {
            line = stream.readLine();
            if (line.contains(name, Qt::CaseInsensitive))
            {
                found = true;
            }
            else index++;
        }
    }

    if (found)
    {
        QMessageBox::warning(this, "Found", "Category Found");
        ui->lineEdit->clear();
        return;
    }

    if (!found)
    {
        file.open(QIODevice::Append | QIODevice::WriteOnly);
        QTextStream stream(&file);
        stream << name << "\n";
        myCategory.Append(name.toStdString());
        file.close();
    }

    ui->lineEdit->clear();
    file.close();
    emit categorySaved();
    on_pushButton_2_clicked();

}


void AddCategory::on_pushButton_2_clicked()
{
    ui->lineEdit->clear();
    hide();
}




