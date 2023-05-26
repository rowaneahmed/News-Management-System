#include "newsadminwindow.h"
#include "ui_newsadminwindow.h"
#include<QStringListModel>
#include<QStringList>
#include<iostream>
using namespace std;

NewsAdminWindow::NewsAdminWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewsAdminWindow)
{
    ui->setupUi(this);
    qDebug()<<"showing news ";
    showNews();
    qDebug()<<"initializing pointers";
    ptrAddNews = new addN();
    ptrUpdateNews = new updateN();
    connect(ptrAddNews, &addN::newsSaved, this, &NewsAdminWindow::showNews);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &NewsAdminWindow::on_pushButton_2_clicked);
    connect(ptrUpdateNews, &updateN::newsUpdated ,this, &NewsAdminWindow::showNews);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &NewsAdminWindow::showNews);
}

void NewsAdminWindow::showNews() {
    qDebug()<<"opening news file ";
    QFile File("C:\\Users\\PC\\OneDrive\\Desktop\\news.txt");
    if (File.open(QIODevice::ReadOnly)) {
        QTextStream stream(&File);
        QString oneNews;
        QStringList newsList;
        QStringListModel* model;
        string lines[9];
        int counter = 0;
        qDebug()<<"entering the while loop ";

        while (stream.atEnd() == false) {
            QString s = stream.readLine();
            qDebug()<<"after s the while loop ";

            oneNews += s + "\n";
            if (s == "****") {
                News n(lines[0], lines[1], QDate::fromString(QString::fromStdString(lines[2]), "yyyy-MM-dd"), lines[3], QString::fromStdString(lines[4]), std::stoi(lines[5]));
                newsLL.Append(n);
                counter = 0;
                for (int i = 0; i < 8; i++)
                    lines[i] = "";
            }
            else {
                lines[counter] = s.toStdString();
                int pos = lines[counter].find(":");
                lines[counter] = lines[counter].substr(pos + 2, lines[counter].length() - pos);
                counter++;
            }
            newsList = oneNews.split("****");

        }
        qDebug()<<"after the while loop ";

        model = new QStringListModel(this);
        model->setStringList(newsList);
        ui->listView->setModel(model);
    }
    File.close();
}


NewsAdminWindow::~NewsAdminWindow()
{
    delete ptrAddNews;
    delete ptrUpdateNews;
    delete ui;
}

void NewsAdminWindow::on_pushButton_clicked()
{
    ptrAddNews->show();
}

// The user pressed edit btn
void NewsAdminWindow::on_pushButton_2_clicked()
{
    QModelIndex currentIndex = ui->listView->currentIndex();
    if (currentIndex.isValid()) {
        // the user selected a news item
        int rowNumber = currentIndex.row();      // index of selected item (0-based)
        // An index of zero means first item in linkedlist
        // I need to update it first in linkedlist
        // Then delete the content of the file and reload from linkedlist to file
        ptrUpdateNews->pos = rowNumber;
        ptrUpdateNews->show();
    }
}

// The user pressed delete btn
void NewsAdminWindow::on_pushButton_3_clicked()
{
    QModelIndex currentIndex = ui->listView->currentIndex();
    if (currentIndex.isValid()) {
        // the user selected a news item
        int rowNumber = currentIndex.row();      // index of selected item (0-based)
        // An index of zero means first item in linkedlist
        // Clearing linkedlist
        newsLL.Clear();
        // Re-writing to linkedlist
        newsLL.writeFromFile();
        // Deleting specified elememt from linkedlist
        newsLL.Delete(rowNumber);
        // Saving the changes to file
        newsLL.writetoFile();
    }
}

