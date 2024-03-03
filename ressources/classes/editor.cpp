#include "editor.h"

Editor::Editor()
{

}

const string &Editor::getName() const {
    return name;
}

void Editor::setName(const string &name) {
    Editor::name = name;
}
