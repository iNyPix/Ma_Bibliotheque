/*!
 * \file book.h
 * \brief A book's class.
 * \author {Thomas.N}
 * \version 1.0
 */
#ifndef BOOK_H
#define BOOK_H
#include <string>
using namespace std;
/*! \class Book.
 *  \brief A book's class.
 */
class Book
{
private:
    int id;
    string title; /*!< Book's title.*/
    string authors; /*!< Book's authors.*/
    string editors; /*!< Book's editors.*/
    string gender; /*!< Book's gender.*/
    string collection; /*!< Book's collection.*/
    int numbers; /*!< Numbers of this book.*/
    int year; /*!< Year of publication of this book.*/
    int tome; /*!< Book's tome.*/
    int tomeEnd; /*!< Book's tome end.*/
    int isbn; /*!< Book's isbn.*/
    string summary; /*!< Book's summary.*/
    string img; /*!< Image path of this book.*/
public:
    Book();
    /*!
         *  \brief Get Id.
         *
         *  \return The book's id.
         */
    const int &getId() const;

    void setId(int id);
    /*!
         *  \brief Get Title.
         *
         *  \return The book's title.
         */
    const string &getTitle() const;

    void setTitle(const string &title);
    /*!
         *  \brief Get Authors.
         *
         *  \return The book's authors.
         */
    const string &getAuthors() const;

    void setAuthors(const string &authors);
    /*!
         *  \brief Get Editors.
         *
         *  \return The book's editors.
         */
    const string &getEditors() const;

    void setEditors(const string &editors);
    /*!
         *  \brief Get Gender.
         *
         *  \return The book's gender.
         */
    const string &getGender() const;

    void setGender(const string &gender);
    /*!
         *  \brief Get Collection.
         *
         *  \return The book's collection.
         */
    const string &getCollection() const;

    void setCollection(const string &collection);
    /*!
         *  \brief Get Numbers.
         *
         *  \return The book's numbers.
         */
    int getNumbers() const;

    void setNumbers(int numbers);
    /*!
         *  \brief Get Years.
         *
         *  \return The book's years.
         */
    int getYear() const;

    void setYear(int year);
    /*!
         *  \brief Get Tome.
         *
         *  \return The book's tome.
         */
    int getTome() const;

    void setTome(int tome);
    /*!
         *  \brief Get Tome End.
         *
         *  \return The book's tome end.
         */
    int getTomeEnd() const;

    void setTomeEnd(int tomeEnd);
    /*!
         *  \brief Get ISBN.
         *
         *  \return The book's ISBN.
         */
    int getIsbn() const;

    void setIsbn(int isbn);
    /*!
         *  \brief Get Summary.
         *
         *  \return The book's summary.
         */
    const string &getSummary() const;

    void setSummary(const string &summary);
    /*!
     *  \brief Get Image path.
     *
     *  \return The book's image path.
     */
    const string &getImg() const;

    void setImg(const string &img);

};

#endif // BOOK_H
