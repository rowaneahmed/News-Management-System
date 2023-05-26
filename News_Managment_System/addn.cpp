#include "addn.h"
#include "ui_addn.h"
#include <QDateTime>
addN::addN(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addN)
{
    ui->setupUi(this);
    QFile File("C:\\Users\\PC\\OneDrive\\Desktop\\categories.txt");
    if (File.open(QIODevice::ReadOnly)) {
        QTextStream stream(&File);
        QStringList cat;
        while (stream.atEnd() == false) {
            cat.append(stream.readLine());
        }
        ui->categoryComboBox->addItems(cat);
    }
}


void addN::on_cancelbtn_clicked()
{
    ui->titleInput->clear();
    ui->descriptionInput->clear();
    hide();
}

void addN::on_savebtn_clicked()
{
    //Getting user input
    QString title = ui->titleInput->text();
    QString description = ui->descriptionInput->toPlainText();
    QDate c_date = QDate::currentDate();
    //QString date = c_date.toString("yyyy-MM-dd");
    QString category = ui->categoryComboBox->currentText();
    // Saving it to a linkedlist
    News n(title.toStdString(), description.toStdString(), c_date, category.toStdString(),"0", 0);
    newsLL.Append(n);
    // Saving it to file
    QFile File("C:\\Users\\PC\\OneDrive\\Desktop\\news.txt");
    if (File.open(QIODevice::Append | QIODevice::WriteOnly)) {
        QTextStream stream(&File);
        stream << "Title: " << title << "\n";
        stream << "Description: " << description << "\n";
        stream << "Date: " << c_date.toString("yyyy-MM-dd") << "\n";
        stream << "Category: " << category << "\n";
        stream << "Rate: 0\n";
        stream << "spamCounter: 0\n";
        stream << "rateCounter: 0\n";
        stream << "****\n";
    }
    File.close();
    emit newsSaved();
    on_cancelbtn_clicked();
}

addN::~addN()
{
    delete ui;
}
