
#include "newslinkedlist.h"
#include "fileheader.h"
#include "news.h"
#include <assert.h>
template <class T>
Node<T>::Node(T n) {
    val = n;
    next = NULL;
}
template <class T>
NewsLinkedList<T>::NewsLinkedList()
{
    head = tail = 0;
    count = 0;
}
template <class T>
int NewsLinkedList<T>::Length() {
    return count;
}
template <class T>
void NewsLinkedList<T>::Append(T t) {
    Node<T>* n = new Node<T>(t);
    if (count == 0)
        head = tail = n;
    else {
        tail->next = n;
        tail = n;
    }
    count++;
}
template <class T>
void NewsLinkedList<T>::Update(string t, string d, int index) {
    Node<News>* temp = head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    temp->val.title = t;
    temp->val.description = d;
}
template <class T>
void NewsLinkedList<T>::Delete(int pos) {
    Node<T>* temp = head;
    if (pos == 0) {
        head = head->next;
        delete temp;
    }
    else {
        Node <T>* d;
        for (int i = 0; i < pos - 1; i++) {
            temp = temp->next;
        }
        d = temp->next;
        temp->next = d->next;
        delete d;
        if (pos == count - 1)
            tail = temp;
    }
    count--;
}

template<class T>
void NewsLinkedList<T>::Clear() {
    Node<T>* current = head;
    while (current != nullptr) {
        Node<T>* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
    count = 0;
}

template <class T>
void NewsLinkedList<T>::writetoFile() {
    QFile File("C:\\Users\\PC\\OneDrive\\Desktop\\news.txt");
    if (File.open(QIODevice::Truncate | QIODevice::WriteOnly)) {
        Node<News>* temp = head;
        QTextStream stream(&File);
        for (int i = 0; i < Length(); i++) {
            stream << "Title: " << QString::fromStdString(temp->val.title) << "\n";
            stream << "Description: " << QString::fromStdString(temp->val.description) << "\n";
            stream << "Date: " << temp->val.date.toString("yyyy-MM-dd") << "\n";
            stream << "Category: " << QString::fromStdString(temp->val.category) << "\n";
            stream << "Rate: " << temp->val.rate <<"\n";
            stream << "spamCounter: "<< temp->val.spamCounter <<"\n";
            stream << "rateCounter: "<< temp->val.rateCounter <<"\n";
            stream << "****\n";
            temp = temp->next;
        }
    }
    File.close();
}
template <class T>
void NewsLinkedList<T>::writeFromFile() {
    //QFile File("C:\\Users\\rowan\\OneDrive\\Desktop\\news.txt");
    //if (File.open(QIODevice::ReadOnly)) {
    //    QTextStream stream(&File);
    //    string lines[7];
    //    int counter = 0;
    //    while (stream.atEnd() == false) {
    //        QString s = stream.readLine();
    //        if (s == "**********************") {
    //            News n(lines[0], lines[1], lines[2], lines[3], lines[4]);
    //            Append(n);
    //            counter = 0;
    //            for (int i = 0; i < 7; i++)
    //                lines[i] = "";
    //        }
    //        else {
    //            lines[counter] = s.toStdString();
    //            int pos = lines[counter].find(":");
    //            lines[counter] = lines[counter].substr(pos + 2, lines[counter].length() - pos);
    //        }
    //        counter++;
    //    }
    //}
    //File.close();
    QFile file("C:\\Users\\PC\\OneDrive\\Desktop\\news.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString title = in.readLine().section(':', 1).trimmed();
            QString description = in.readLine().section(':', 1).trimmed();
            QString datestr = in.readLine().section(':', 1).trimmed();
            QDate date = QDate::fromString(datestr, "yyyy-MM-dd");
            QString category = in.readLine().section(':', 1).trimmed();
            QString rate = in.readLine().section(':', 1).trimmed();
            int spamcounter=in.readLine().section(":",1).trimmed().toInt();
            QString ratecounter = in.readLine().section(':', 1).trimmed();
            in.readLine(); // skip delimiter line
            News n(title.toStdString(), description.toStdString(), date, category.toStdString(), rate,spamcounter,ratecounter);
            Append(n);
        }
    }
    file.close();
}


