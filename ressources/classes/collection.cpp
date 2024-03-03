#include "collection.h"

Collection::Collection()
{

}

const string &Collection::getName() const {
    return name;
}

void Collection::setName(const string &name) {
    Collection::name = name;
}

int Collection::getNumberOf() const {
    return numberOf;
}

void Collection::setNumberOf(int numberOf) {
    Collection::numberOf = numberOf;
}
