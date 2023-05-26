#include "findcategory.h"
#include "ui_findcategory.h"
#include <QtWidgets>
#include <QListWidget>
#include <QFile>
#include <QTextStream>
#include <QtCore>
#include <QListView>
#include <QStringList>
#include <QStringListModel>
#include <Qt>

FindCategory::FindCategory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindCategory)
{
    ui->setupUi(this);
}

FindCategory::~FindCategory()
{
    delete ui;
}

void FindCategory::on_pushButton_clicked()
{
    QString name = ui->lineEdit->text();
    QVector<QString> myCategory; // declare vector
    QFile file("C:\\Users\\PC\\OneDrive\\Desktop\\CategoriesNames.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&file);
    QString line;
    while (!stream.atEnd())
    {
        line = stream.readLine();
        myCategory.append(line);
    }
    file.close();

    QStringList lines;
    bool found = false;
    for (const QString& category : myCategory)
    {
        if (category.contains(name, Qt::CaseInsensitive))
        {
            lines.append(category);
            found = true;
        }
    }
    if (!found)
    {
        lines.append("Not Found");
    }
    QStringListModel* model = new QStringListModel(lines);
    ui->listView->setModel(model);

    file.close();
}

void FindCategory::on_pushButton_2_clicked()
{
    QStringListModel* emptymodel = new QStringListModel();
    ui->listView->setModel(emptymodel);
    ui->lineEdit->clear();
    hide();
}

