#include "bibliotheque.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "ressources/classes/addgooglebookdialog.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "MaBibliotheque_" + QLocale(locale).name();
        if (translator.load(":/translations/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    Bibliotheque w;
    w.show();



    addGoogleBookDialog agbd;
    agbd.show();

    return a.exec();
}
