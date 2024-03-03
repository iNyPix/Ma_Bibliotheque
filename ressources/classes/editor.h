/*!
 * \file editor.h
 * \brief An edithor's class.
 * \author {Thomas.N}
 * \version 1.0
 */
#ifndef EDITOR_H
#define EDITOR_H
#include <string>
using namespace std;

class Editor
{
private:
    string name; /*!< Editor's name.*/
public:
    Editor();

    const string &getName() const;

    void setName(const string &name);
};

#endif // EDITOR_H
