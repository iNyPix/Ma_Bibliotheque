/*!
 * \file collection.h
 * \brief A collection's class.
 * \author {Thomas.N}
 * \version 1.0
 */
#ifndef COLLECTION_H
#define COLLECTION_H
#include <string>
using namespace std;
/*! \class Collection.
 *  \brief Represents a book's collection.
 */
class Collection
{
private:
    string name; /*!< Collection's name.*/
    int numberOf; /*!< Number of books inside the collection.*/
public:
    Collection();

    const string &getName() const;

    void setName(const string &name);

    int getNumberOf() const;

    void setNumberOf(int numberOf);
};

#endif // COLLECTION_H
