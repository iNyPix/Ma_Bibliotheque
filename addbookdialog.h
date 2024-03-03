/*!
 * \file addbookdialog.h
 * \brief Dialog to add a book.
 * \author {Thomas.Nicolle}
 * \version 1.0
 */
#ifndef ADDBOOKDIALOG_H
#define ADDBOOKDIALOG_H

#include <QDialog>
#include <QTranslator>
#include "ressources/classes/book.h"

namespace Ui {
class AddBookDialog;
}
/*! \class AddBookDialog.
 *  \brief Class to add a book.
 */
class AddBookDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::AddBookDialog *ui;

public:
    explicit AddBookDialog(QWidget *parent = nullptr);
    ~AddBookDialog();
    QTranslator translator; /*!< Translator.*/

private slots:
    void clearForm();
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

    void on_addImgButton_clicked();

signals:
    void sendNewBook(Book);


};

#endif // ADDBOOKDIALOG_H
