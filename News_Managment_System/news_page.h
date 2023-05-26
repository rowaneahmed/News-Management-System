#ifndef NEWS_PAGE_H
#define NEWS_PAGE_H

#include "comments.h"
#include "news.h"
#include <QDialog>
#include<iostream>
#include <QListView>
#include <Qdate>
#include<Qstring>
#include <QStringList>
#include<QStringListModel>

using namespace std;
extern unordered_map<string,News> newsmap;
extern unordered_map<QString,QVector<QString>> user_spammedT;
extern QStringList userHasSpam;
extern QString titleName;
extern unordered_map<QString, std::vector<comment>>* posts_comments;
class MainWindow;

namespace Ui {
class News_page;
}

class News_page : public QDialog
{
    Q_OBJECT

public:
    explicit News_page(QWidget *parent = nullptr);
    ~News_page();

public :
    void loadNewsFromFile();
    void initCommentsMap();
    void showAllNews();
    void showNewsByCategory(QString category);
    void showNewsByDate();
    void showNewsByRate();
    void rating();
    void markAsSpam();
    void UpdateFile(unordered_map<string,News> updatednews);
    void Update_UsreSpamFile( QString spammed_title);
    void Load_Spammed();
    bool saveCommentMap();

private slots:    
    void on_commentsbtn_clicked();

    void on_logoutButton_clicked();

private:
    Ui::News_page *ui;
    QStringListModel* model;
    Comments* commentspage;
    MainWindow* mainwindow;
    QVector<News> newsVec;
    QVector<News> newsVecAfterSpam;
    QStringList newsList;
    unordered_map<string,News> newsmap;
    unordered_map<QString,QVector<QString>> user_spammedT;
    QStringList userHasSpam;
};

#endif // NEWS_PAGE_H
