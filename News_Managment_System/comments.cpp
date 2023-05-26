#include "comments.h"
#include "news.h"
#include "news_page.h"
#include "qdatetime.h"
#include "ui_comments.h"
#include "sign_up.h"
#include <QFile>
Comments::Comments(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Comments)
{
    ui->setupUi(this);
   // News* news = new News();
    //QString text = news->ReadComments();
    //ui->readlinedit->setPlainText(text);
}


void Comments::on_addbtn_clicked()
{

    comment cmt;
    QString text=ui->addlinedit->toPlainText();
    QDate c_date = QDate::currentDate();
    QString date = c_date.toString("yyyy-MM-dd");
    cmt.title = titleName;
    cmt.username = userName;
    cmt.text = text;
    cmt.date = date;
    (*posts_comments)[titleName].push_back(cmt);

}


void Comments::on_readbtn_clicked()
{
    News* news = new News();
    QString text = news->ReadComments();
    ui->readlinedit->setPlainText(text);
}

Comments::~Comments()
{
    delete ui;
}
