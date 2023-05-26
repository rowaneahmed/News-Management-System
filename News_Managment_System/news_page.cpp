#include "news_page.h"
#include "login.h"
#include "mainwindow.h"
#include "ui_news_page.h"
#include "QFile"
#include"QStringListModel"
#include "QStringList"
#include "news.h"


QString titleName;
unordered_map<QString, vector<comment>>* posts_comments = new unordered_map<QString, vector<comment>>();

News_page::News_page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::News_page)
{
    ui->setupUi(this);

    //load news from file
    loadNewsFromFile();
    //initialize comments map
    initCommentsMap();


    for (News& n : newsVec) {
        ui->titlecombox->addItem(QString::fromStdString(n.title));
    }

    //load categories to combo box
    QFile file1("C:\\Users\\PC\\OneDrive\\Desktop\\categories.txt");
    qDebug()<<"File1 opened";
    if(!file1.open(QFile::ReadOnly | QFile::Text)){
        qWarning("title","File not open");
    }
    QTextStream stream(&file1);
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        ui->categorycombox->addItem(line);
    }
    file1.close();
    qDebug()<<"File1 closed";

    //show all news when user enters
    showAllNews();

    connect(ui->allNewsButton, &QPushButton::clicked, this, &News_page::showAllNews);
    connect(ui->categorycombox, &QComboBox::currentTextChanged, this, &News_page::showNewsByCategory);
    connect(ui->dateButton, &QPushButton::clicked, this, &News_page::showNewsByDate);
    connect(ui->ratebutton, &QPushButton::clicked, this, &News_page::showNewsByRate);
    connect(ui->ratinpushbutton, &QPushButton::clicked, this, &News_page::rating);
    connect(ui->pushButton_spam ,&QPushButton::clicked, this, &News_page::markAsSpam);
}

void News_page::loadNewsFromFile(){
    Load_Spammed();
    QFile file("C:\\Users\\PC\\OneDrive\\Desktop\\news.txt");
    qDebug()<<"spam loaded";
    bool spammed=false;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString title = in.readLine().section(':', 1).trimmed();
            QString description = in.readLine().section(':', 1).trimmed();
            QString datestr = in.readLine().section(':', 1).trimmed();
            QString category = in.readLine().section(':', 1).trimmed();
            QString rate = in.readLine().section(':', 1).trimmed();
            int spamcounter=in.readLine().section(":",1).trimmed().toInt();
            QString ratecounter = in.readLine().section(':', 1).trimmed();
            in.readLine(); // skip delimiter line

            QDate date = QDate::fromString(datestr, "yyyy-MM-dd");
            News n(title.toStdString(), description.toStdString(), date, category.toStdString(), rate,spamcounter,ratecounter);
            newsmap[title.toStdString()]=n;
            newsVec.append(n);
        }
    }
    file.close();
    qDebug()<<"news loaded";

    if(userHasSpam.contains(currentUser)==true){
        for (News& n : newsVec) {
            QVector<QString> comparelist=user_spammedT[currentUser][0].split("+");
            for(int i=0;i<comparelist.size();i++)
            {
                if(n.title==comparelist[i].remove("+").toStdString())
                {
                    qDebug()<<comparelist[i].remove("+").toStdString();
                    spammed=true;
                    break;
                }
                else {
                    continue;
                }
            }
            if(spammed==true)
            {
                spammed=false;
                continue;
            }
            newsVecAfterSpam.append(n);
        }
    }
    else {
        for (News& n : newsVec) {
            newsVecAfterSpam.append(n);
        }
    }
}
void News_page::initCommentsMap(){
    QFile file("C:\\Users\\PC\\OneDrive\\Desktop\\Comments.txt");
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        qWarning("title","File not open");
        return;
    }

    // Read the file line by line
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString reader = in.readLine();
        comment cmt;
        while (!reader.startsWith("**") && !reader.isEmpty()) {
            if (reader.startsWith("Title :"))
                cmt.title = reader.mid(8);
            else if (reader.startsWith("Username :"))
                cmt.username = reader.mid(10);
            else if (reader.startsWith("Comment :"))
                cmt.text = reader.mid(10);
            else if (reader.startsWith("Date :"))
                cmt.date = reader.mid(6);
            reader = in.readLine();
        }
        qDebug()<< "begining titles : \n"<<cmt.title<< "\n";
        (*posts_comments)[cmt.title].push_back(cmt);
    }
}

bool News_page::saveCommentMap(){
    QFile file("C:\\Users\\PC\\OneDrive\\Desktop\\Comments.txt");
    if(!file.open(QFile::WriteOnly | QFile::Truncate)){
        qWarning("title","File not open");
    }
    QTextStream Out(&file);
    QString cmts_str = "";
    for(auto& post_comment: *posts_comments) {
        for(int i = 0; i < post_comment.second.size(); i++) {
            comment cmt = post_comment.second[i];
            QString cmt_str = "";
            cmt_str += "Title : " + cmt.title + "\n";
            cmt_str += "Username : " + cmt.username + "\n";
            cmt_str += "Comment : " + cmt.text + "\n";
            cmt_str += "Date : " + cmt.date + "\n*******\n";
            cmts_str += cmt_str;

        }
    }
    Out << cmts_str;

    file.flush();
    file.close();
    return 0;
}

void News_page::showAllNews() {
    if(!newsVec.isEmpty()){
        newsVec.clear();
        newsVecAfterSpam.clear();
        newsList.clear();
    }
    loadNewsFromFile();
    for (News n : newsVecAfterSpam) {
        newsList.append(QString::fromStdString(n.toString()));
    }
    QStringListModel* model = new QStringListModel();
    model->setStringList(newsList);
    ui->listView->setModel(model);
}

void News_page::showNewsByCategory(QString category){

    QStringList catnewslist;
    for (News n : newsVecAfterSpam) {
        if (n.category == category.toStdString()) {
            catnewslist.append(QString::fromStdString(n.toString()));
        }
    }
    QStringListModel* model = new QStringListModel();
    model->setStringList(catnewslist);
    ui->listView->setModel(model);
}

void News_page::showNewsByDate(){

    QStringList datenewslist;

    // Sort the news by date
    std::sort(newsVecAfterSpam.begin(), newsVecAfterSpam.end(),
              [](const News& n1, const News& n2) { return n1.date > n2.date; });


    for (News n : newsVecAfterSpam) {
        datenewslist.append(QString::fromStdString(n.toString()));
    }

    QStringListModel* model = new QStringListModel();
    model->setStringList(datenewslist);
    ui->listView->setModel(model);
}

void News_page::showNewsByRate(){

    QStringList ratenewslist;

    sort(newsVecAfterSpam.begin(), newsVecAfterSpam.end(), [](const News& n1, const News& n2) {
        return n1.rate > n2.rate;
    });

    for (News n : newsVecAfterSpam) {
        int r = n.rate.toInt();
        if(r <= 2)
            continue;
        ratenewslist.append(QString::fromStdString(n.toString()));
    }

    QStringListModel* model = new QStringListModel();
    model->setStringList(ratenewslist);
    ui->listView->setModel(model);
}

void News_page::rating(){
    QFile file("C:\\Users\\PC\\OneDrive\\Desktop\\news.txt");
    QTextStream in(&file);

    QString title = ui->titlecombox->currentText();
    float rating = ui->ratingcombox->currentIndex() + 1;


    //calculate average rate
    float newRate;
    int newRateCount;
    for (News& n : newsVec) {
        if(n.title==title.toStdString()){
            if(n.rateCounter.toInt()>0){
                newRateCount=n.rateCounter.toInt()+1;
                n.rateCounter=QString::number(newRateCount);
                newRate = (n.rate.toFloat()+rating)/n.rateCounter.toInt();
                n.rate = QString::number(newRate);
            }
            else{
                newRateCount=n.rateCounter.toInt()+1;
                n.rateCounter=QString::number(newRateCount);
                n.rate=QString::number(rating);
            }
            break;
        }
    }

    //write to file updated rating
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qWarning("Failed to open file.");
        return;
    }

    for(News& n : newsVec){
        QString d = n.date.toString("yyyy-MM-dd");
        in <<"Title: "<< QString::fromStdString(n.title) <<"\n";
        in <<"Description: "<< QString::fromStdString(n.description) <<"\n";
        in <<"Date: "<< d <<"\n";
        in <<"Category:  "<< QString::fromStdString(n.category) <<"\n";
        in <<"Rate: "<< n.rate <<"\n";
        in <<"SpamCounter: "<< n.spamCounter <<"\n";
        in <<"RateCounter: "<< n.rateCounter <<"\n";
        in <<"****\n";
    }

    file.close();

}



void News_page::on_commentsbtn_clicked()
{
    commentspage = new Comments(this);
    commentspage->show();
    titleName = ui->titlecombox->currentText();
}


void News_page::markAsSpam(){
    //int pos=ui->listView->currentIndex().row();
    QStringList row=ui->listView->currentIndex().data().toStringList();
    QStringList sections=row[0].split("\n");
    string key=sections[0].toStdString().substr(7);
    qDebug()<<"the key iam holding"<<key<<"\n";

    newsmap[key].spamCounter++;
    UpdateFile(newsmap);
    Update_UsreSpamFile(QString::fromStdString(key));


    qDebug()<<"SUCCC BACK"<<"\n";
    //model->removeRow(pos);
}

void News_page::UpdateFile(unordered_map<string,News> updatednews){
    QFile file("C:\\Users\\PC\\OneDrive\\Desktop\\news.txt");
    if(file.open(QIODevice::Truncate|QIODevice::WriteOnly)){
        QTextStream out(&file);
        unordered_map<string,News>::iterator it;

        for(it=updatednews.begin();it!=updatednews.end();it++){
            QString dt=it->second.date.toString("yyyy-MM-dd");
            out << "Title: " << QString::fromStdString(it->second.title) << "\n";
            out << "Description: " << QString::fromStdString(it->second.description) << "\n";
            out << "Date: " << dt << "\n";
            out << "Category: " << QString::fromStdString(it->second.category) << "\n";
            out << "Rate: " << it->second.rate <<"\n";
            out << "Spam Counter: " <<QString::fromStdString(to_string(it->second.spamCounter)) <<"\n";
            out << "Rate Counter: " << it->second.rateCounter <<"\n";
            out << "****\n";
        }
    }
    else {
        qWarning("warning", "file not open");

    }

    file.close();
}

void News_page::Update_UsreSpamFile(QString spammed_title)
{
    QFile file ("C:\\Users\\PC\\OneDrive\\Desktop\\spammed_news.txt");

    Load_Spammed();

    spammed_title=spammed_title+"+";

    user_spammedT[currentUser].append(spammed_title);

    if(file.open(QIODevice::Truncate|QIODevice::WriteOnly)){
        QTextStream out(&file);
        unordered_map<QString,QStringList>::iterator it;
        for(it=user_spammedT.begin();it!=user_spammedT.end();it++){
            out<<it->first<<"*";
            for (int i = 0; i < it->second.size(); ++i) {
                out<<it->second[i];

            }
            out<<"\n";
        }
    }
    else {
        qWarning("warning", "file not open");
    }
    file.close();



}

void News_page::Load_Spammed(){
    QFile file ("C:\\Users\\PC\\OneDrive\\Desktop\\spammed_news.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){

        QTextStream in(&file);
        QStringList line;
        QString userN;
        QString line_notsplitted;

        while(!in.atEnd()){

            line_notsplitted=in.readLine();
            if(line_notsplitted.isEmpty()){
                qDebug()<<"empty line\n";
                continue;
            }
            else {
                line=line_notsplitted.split("*");
                userN=line[0];
                userHasSpam.append(userN);
                line=line[1].split("/");
                qDebug()<<"line"<<line;
                user_spammedT[userN]=line;
            }
        }
    }
    else{
       qWarning("warning", "file not open");
    }
    file.close();
}

News_page::~News_page()
{
    delete ui;
}

void News_page::on_logoutButton_clicked()
{
    saveCommentMap();
    (*posts_comments).clear();
    this->close();
    mainwindow= new MainWindow(this);
    mainwindow->show();
}

