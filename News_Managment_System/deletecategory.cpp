#include "deletecategory.h"
#include "ui_deletecategory.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include "Globals.h"

DeleteCategory::DeleteCategory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteCategory)
{
    ui->setupUi(this);
}

DeleteCategory::~DeleteCategory()
{
    delete ui;
}


void DeleteCategory::on_pushButton_clicked()
{
    QString name = ui->lineEdit->text();
    QFile file("C:\\Users\\PC\\OneDrive\\Desktop\\categories.txt");
    int index = 0;
    bool found = false;
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        QString line;
        QStringList lines;
        while (!stream.atEnd())
        {
            line = stream.readLine();
            if (line.contains(name,Qt::CaseInsensitive))
            {
                found = true;
                break;
            }
            else index++;
        }
    }
    ui->lineEdit->clear();
    file.close();

    if(!found){
        QMessageBox::warning(this, "Not Found", "Category Not Found");
        ui->lineEdit->clear();
        return;
    }
    if (myCategory.Length() == 0)
        myCategory.writefromfile();

    myCategory.deleteAt(index);
    myCategory.writetofile();
    emit categoryDeleted();
    on_pushButton_2_clicked();
}

void DeleteCategory::on_pushButton_2_clicked()
{
    ui->lineEdit->clear();
    hide();
}
