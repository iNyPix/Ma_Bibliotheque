#include "gender.h"

Gender::Gender()
{

}

const string &Gender::getType() const {
    return type;
}

void Gender::setType(const string &type) {
    Gender::type = type;
}
