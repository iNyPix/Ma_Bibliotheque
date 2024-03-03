/*!
 * \file author.h
 * \brief An author's class.
 * \author {Thomas.N}
 * \version 1.0
 */
#ifndef AUTHOR_H
#define AUTHOR_H
#include <string>
using namespace std;
/*! \class Author.
 *  \brief Represents an author.
 */
class Author
{
private:
    string name; /*!< Author's name.*/
    string surname; /*!< Author's surname.*/
public:
    Author();
};

#endif // AUTHOR_H
