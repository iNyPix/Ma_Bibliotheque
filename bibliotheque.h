/*!
 * \file bibliotheque.h
 * \brief MainWindow of the application
 * \author {Thomas.Nicolle}
 * \version 1.0
 */
#ifndef BIBLIOTHEQUE_H
#define BIBLIOTHEQUE_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include "addbookdialog.h"
#include "ressources/classes/querysql.h"
#include "ressources/classes/book.h"
#include "aboutdialog.h"
#include "ressources/classes/addgooglebookdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Bibliotheque; }
QT_END_NAMESPACE
/*! \class Bibliotheque.
 *  \brief Class of the MainWindow.
 */
class Bibliotheque : public QMainWindow
{
    Q_OBJECT

public:
    Bibliotheque(QWidget *parent = nullptr);
    ~Bibliotheque();
    void errorDialog(string); /*!< Function for error dialog.*/
    void refreshBooksView();
    Book getBookById(int id);
    static bool isISBN10Valid(const string&);
    static bool isISBN13Valid(const string&);
    static bool isISBNValid(const string&);

private:
    Ui::Bibliotheque *ui;
    // Dialog
    AboutDialog aboutDialog; /*!< Instance of the about dialog.*/
    QFileDialog *openDbDialog; /*!< QFileDialog instance to open a db file.*/
    AddBookDialog addBookDialog;/*!< Instance dialog to add a book.*/
    addGoogleBookDialog addGoogleBookDialog; /*!< Instance dialog to add a book with google.*/
    // Other
    QuerySQL qsql; /*!< Instance of the db interface.*/
    QSqlQueryModel *model; /*!< QTableView/BooksView model.*/
    list<Book> listBooks;

private slots:
    void on_buttonAddBook_clicked();

    void on_actionOuvrir_une_biblioth_que_triggered();

    void on_actionNouvelle_biblioth_que_triggered();

    void on_actionSupprimer_une_biblioth_que_triggered();

    void on_actionRenommer_la_biblioth_que_triggered();

    void on_actionR_initialiser_la_biblioth_que_triggered();

    void on_titleLineEdit_editingFinished();

    void recData(list<Book>);
    void recNewBook(Book);
    void on_booksView_clicked(const QModelIndex &index);
    void on_buttonDeleteBook_clicked();
    void on_actionA_propos_triggered();
    void on_buttonImportBook_clicked();
    void on_buttonSaveBook_clicked();
};
#endif // BIBLIOTHEQUE_H
