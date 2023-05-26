#ifndef NEWSADMINWINDOW_H
#define NEWSADMINWINDOW_H

#include <QDialog>
#include "addn.h"
#include "updaten.h"
namespace Ui {
class NewsAdminWindow;
}

class NewsAdminWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NewsAdminWindow(QWidget *parent = nullptr);
    void showNews();
    ~NewsAdminWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::NewsAdminWindow *ui;
    addN* ptrAddNews;
    updateN* ptrUpdateNews;

};

#endif // NEWSADMINWINDOW_H
