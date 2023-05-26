#include "categorymainwindow.h"
#include "ui_categorymainwindow.h"
#include <QFile>
#include "Globals.h"
#include <QTextStream>
#include <QtCore>
#include <QListView>
#include <QStringList>
#include <QStringListModel>
#include <Qt>
#include "addcategory.h"
#include "deletecategory.h"
#include <iostream>
using namespace std;

CategoryMainWindow::CategoryMainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CategoryMainWindow)
{
    ui->setupUi(this);
    showCategory();
    ptrAddCategory = new AddCategory();
    ptrDeleteCategory = new DeleteCategory();
    ptrFindCategory = new FindCategory();
    connect(ptrAddCategory, &AddCategory::categorySaved, this, &CategoryMainWindow::showCategory);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &CategoryMainWindow::on_pushButton_2_clicked);
    connect(ptrDeleteCategory, &DeleteCategory::categoryDeleted, this, &CategoryMainWindow::showCategory);
    connect(ui->pushButton, &QPushButton::clicked, this, &CategoryMainWindow::showCategory);
}

CategoryMainWindow::~CategoryMainWindow()
{

    delete ptrAddCategory;
    delete ptrDeleteCategory;
    delete ptrFindCategory;
    delete ui;
}

void CategoryMainWindow::on_pushButton_2_clicked()
{
    ptrAddCategory->show();
}

void CategoryMainWindow::on_pushButton_clicked()
{
    ptrDeleteCategory->show();
}

void CategoryMainWindow::on_pushButton_3_clicked()
{
    ptrFindCategory->show();
}

void CategoryMainWindow::showCategory()
{
    QFile file("C:\\Users\\PC\\OneDrive\\Desktop\\categories.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    QStringList lines;
    while(!stream.atEnd())
    {
        QString name = stream.readLine();
        myCategory.Append(name.toStdString());
        lines.append(name);
    }
    QStringListModel *model = new QStringListModel(lines);
    ui->listView->setModel(model);
    file.close();
}

void CategoryMainWindow::on_verticalScrollBar_actionTriggered(int action)
{
    scrollBar = new QScrollBar(Qt::Vertical,this);
    scrollBar->setRange(0,100);
    scrollBar->setPageStep(10);
    scrollBar->setValue(50);
    connect(scrollBar, &QScrollBar::valueChanged, this, [](int value){qDebug() <<"Value changed : " <<value;});
}


