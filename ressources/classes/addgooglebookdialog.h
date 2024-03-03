#ifndef ADDGOOGLEBOOKDIALOG_H
#define ADDGOOGLEBOOKDIALOG_H

#include <QDialog>
#include <QtNetwork/QNetworkAccessManager>
#include <QUrlQuery>
#include <QJsonArray>
#include "book.h"

namespace Ui {
class addGoogleBookDialog;
}

class addGoogleBookDialog : public QDialog
{
    Q_OBJECT
private:
    QNetworkAccessManager manager;
    QUrlQuery query; /*!< Query adding to after API's url.*/
    QJsonArray jsonArray;/*!< Json array with book's informations.*/
public:
    explicit addGoogleBookDialog(QWidget *parent = nullptr);
    ~addGoogleBookDialog();
    void searchBook();
    void resetDialog();

private slots:
    void on_horizontalSlider_sliderMoved(int position);

    void on_searchPushButton_clicked();

    void on_titleSearchLineEdit_returnPressed();

    void on_authorSearchLineEdit_returnPressed();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::addGoogleBookDialog *ui;

signals:
    void sendBook(Book);
};

#endif // ADDGOOGLEBOOKDIALOG_H
