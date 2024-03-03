/*!
 * \file gender.h
 * \brief A gender's class.
 * \author {Thomas.N}
 * \version 1.0
 */
#ifndef GENDER_H
#define GENDER_H
#include <string>
using namespace std;
/*! \class Gender.
 *  \brief Represents a book's type.
 */
class Gender
{
private:
    string type; /*!< Book's gender.*/
public:
    Gender();

    const string &getType() const;

    void setType(const string &type);
};

#endif // GENDER_H
