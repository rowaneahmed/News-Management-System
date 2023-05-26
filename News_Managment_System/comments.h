#ifndef COMMENTS_H
#define COMMENTS_H

#include <QDialog>
namespace Ui {
class Comments;
}

class Comments : public QDialog
{
    Q_OBJECT

public:
    explicit Comments(QWidget *parent = nullptr);
    ~Comments();



private slots:
    void on_addbtn_clicked();

    void on_readbtn_clicked();

private:
    Ui::Comments *ui;
};


#endif // COMMENTS_H
