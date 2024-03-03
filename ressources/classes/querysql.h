/*!
 * \file querysql.h
 * \brief Interface class with the db.
 * \author {Thomas.N}
 * \version 1.0
 */
#ifndef QUERYSQL_H
#define QUERYSQL_H
#include <QObject>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlRecord>
#include <string>
#include <QSqlQueryModel>
using namespace std;
#include "book.h"
#include "author.h"
#include "editor.h"
#include "gender.h"
#include "collection.h"

/*! \class QuerySQL.
 *  \brief Interaction class with the db.
 */
class QuerySQL: public QObject
{
    Q_OBJECT

private:
    QSqlDatabase db; /*!< Database.*/
    QSqlQueryModel* model;

public:
    /*!
         *  \brief Constructor.
         *
         *  Default constructor.
         */
    QuerySQL();
    /*!
         *  \brief Destructeur.
         *
         *  Destructeur of the class.
         */
    ~QuerySQL();
    /*!
         *  \brief Database name.
         *
         *  \return The QSqlDatabse name
         */
    string getQSqlDatabaseName();
    /*!
         *  \brief Database.
         *
         *  \return The QSqlDatabse object.
         */
    QSqlDatabase getQSqlDatabase();
    /*!
         *  \brief DB Connexion.
         *
         *  For connect to the DB.
         */
    void connexionDBWithPath(string);
    /*!
         *  \brief Disconnect BDD.
         *
         *  For disconnect with the db.
         */
    void deconnexionBDD();
    /*!
         *  \brief Conversion QString.
         *
         *  For convert from string to QString.
         */
    QString stringToQS(string)const;
    QSqlQueryModel* getSQLBookModel();

public slots:

    /* CRUD Book fonctions */
    /*!
         *  \brief Add book.
         *
         *  Slot to add a book into the DB.
         */
    void addBook(Book);
    /*!
         *  \brief Edit Book.
         *
         *  Slot to modify the book from the DB.
         */
    void editBook(Book);
    /*!
         *  \brief Delete Book.
         *
         *  Slot to delete a book from the DB.
         */
    void suppBook(Book);

    /* CRUD Author fonctions */
    /*!
         *  \brief Add Author.
         *
         *  Slot to add an Author into the DB.
         */
    void addAuthor(Author);
    /*!
         *  \brief Edit Author.
         *
         *  Slot to modify an author from the DB.
         */
    void editAuthor(Author);
    /*!
         *  \brief Delete Author.
         *
         *  Slot to delete an author from the DB.
         */
    void suppAuthor(Author);

    /* CRUD Editor fonctions */
    /*!
         *  \brief Add Editor.
         *
         *  Slot to add an editor into the DB.
         */
    void addEditor(Editor);
    /*!
         *  \brief Edit Editor.
         *
         *  Slot to modify an editor from the DB.
         */
    void editEditor(Editor);
    /*!
         *  \brief Delete Editor.
         *
         *  Slot to delete an editor from the DB.
         */
    void suppEditor(Editor);

    /* CRUD Gender fonctions */
    /*!
         *  \brief Add Gender.
         *
         *  Slot to add a gender into the DB.
         */
    void addGender(Gender);
    /*!
         *  \brief Edit Gender.
         *
         *  Slot to modify a gender from the DB.
         */
    void editGender(Gender);
    /*!
         *  \brief Delete Gender.
         *
         *  Slot to delete a gender from the DB.
         */
    void suppGender(Gender);

    /* CRUD Collections fonctions */
    /*!
         *  \brief Add Collection.
         *
         *  Slot to add a collection into the DB.
         */
    void addCollection(Collection);
    /*!
         *  \brief Edit Collection.
         *
         *  Slot to modify a collection from the DB.
         */
    void editCollection(Collection);
    /*!
         *  \brief Delete Collection.
         *
         *  Slot to delete a collection from the DB.
         */
    void suppCollection(Collection);

    /* Fonctions autres */
       /*!
            *  \brief Return books.
            *
            *  Slot for asking all books of the DB.
            */
       void getAllBooks();
       /*!
            *  \brief Return Authors.
            *
            *  Slot for asking all authors of the DB.
            */
       void getAllAuthors();
       /*!
            *  \brief Return Editors.
            *
            *  Slot for asking all editors of the DB.
            */
       void getAllEditors();
       /*!
            *  \brief Return Genders.
            *
            *  Slot for asking all genders of the DB.
            */
       void getAllGenders();
       /*!
            *  \brief Return Collections.
            *
            *  Slot for asking all collections of the DB.
            */
       void getAllCollections();

signals:
       /*!
            *  \brief Send Book's list.
            *
            *  Signal to send a book's list.
            */
    void envListBooks(list<Book>);
    /*!
            *  \brief Send Author's list.
            *
            *  Signal to send a author's list.
            */
    void envListAuthors(list<Author>);
    /*!
            *  \brief Send Editor's list.
            *
            *  Signal to send a editor's list.
            */
    void envListEditors(list<Editor>);
    /*!
            *  \brief Send Gender's list.
            *
            *  Signal to send a gender's list.
            */
    void envListGenders(list<Gender>);
    /*!
            *  \brief Send Collection's list.
            *
            *  Signal to send a collection's list.
            */
    void envListCollections(list<Collection>);
};

#endif // QUERYSQL_H
