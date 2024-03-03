#include "querysql.h"
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QtSql/QSqlError>
#include <iostream>

QuerySQL::QuerySQL() {
}

QuerySQL::~QuerySQL() {}

string QuerySQL::getQSqlDatabaseName() {
    string s = db.databaseName().toStdString();
    size_t i = s.rfind('/', s.length());
    if (i != std::string::npos) {
        return s.substr(i + 1, s.rfind('.') - i - 1);
    }
    return "";
}

QSqlDatabase QuerySQL::getQSqlDatabase() {
    return db;
}

void QuerySQL::connexionDBWithPath(string chemin) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    if (db.isOpen()) {
        db.commit();
        db.removeDatabase(db.databaseName());
        deconnexionBDD();
    }
    db.setDatabaseName(QString::fromStdString(chemin));
    if (!db.open()) {
        qDebug() << "SQL --> Impossible connection to the db !";
    } else
        qDebug() << "SQL --> Success connection to the db !";
}

void QuerySQL::deconnexionBDD() {
    if (db.isOpen())
        db.close();
}

QString QuerySQL::stringToQS(string str) const {
    return QString::fromStdString(str);
}

void QuerySQL::addBook(Book b) {
    cout << "SQL <-- Try adding the book " << b.getId() << " to the db..." << endl;
    QSqlQuery query;
    query.prepare(
            "INSERT INTO Books(id, title, authors, editors, parutionyear, gender, nbexemplary, collection, tome, nbtomes, isbn, summary,img) VALUES (:id, :ti, :au, :ed, :py, :ge, :ne, :co, :to, :nt, :isbn, :su, :img)");
    query.bindValue(":id", b.getId());
    query.bindValue(":ti", stringToQS(b.getTitle()));
    query.bindValue(":au", stringToQS(b.getAuthors()));
    query.bindValue(":ed", stringToQS(b.getEditors()));
    query.bindValue(":py", b.getYear());
    query.bindValue(":ge", stringToQS(b.getGender()));
    query.bindValue(":ne", b.getNumbers());
    query.bindValue(":co", stringToQS(b.getCollection()));
    query.bindValue(":to", b.getTome());
    query.bindValue(":nt", b.getTomeEnd());
    query.bindValue(":isbn", b.getIsbn());
    query.bindValue(":su", stringToQS(b.getSummary()));
    query.bindValue(":img", stringToQS(b.getImg()));
    if (!query.exec()) {
        qDebug() << "SQL --> Error for adding the book into the database";
        qDebug() << "SQL --> ERROR: " << query.lastError().text();
    } else
        qDebug() << "SQL --> Adding book success !";
}

void QuerySQL::suppBook(Book b) {
    cout << "SQL <-- Try deleting the book " << b.getId() << " from the db..." << endl;
    QSqlQuery query;
    query.prepare("DELETE FROM Books WHERE id =:i ");
    query.bindValue(":i", b.getId());

    if (!query.exec()) {
        qDebug() << "SQL --> Error for deleting the book";
        qDebug() << "SQL --> ERROR: " << query.lastError().text();
    } else
        qDebug() << "SQL --> Deleting book success !";
}

void QuerySQL::editBook(Book b) {
    cout << "SQL <-- Try updating the book " << b.getId() << " from the db..." << endl;
    QSqlQuery query;
    query.prepare(
            "UPDATE Contact SET id=:newid, title=:newti, authors=:newau, editors=:newed, parutionyear=:newpy, gender=:newge, nbexemplary=:newne, collection=:newco, tome=:newto, nbtomes=:newnt, isbn=:newisbn, summary=:newsu,img=:newimg WHERE id=:i");

    query.bindValue(":i", b.getId());
    query.bindValue(":newti", stringToQS(b.getTitle()));
    query.bindValue(":newau", stringToQS(b.getAuthors()));
    query.bindValue(":newed", stringToQS(b.getEditors()));
    query.bindValue(":newpy", stringToQS(to_string(b.getYear())));
    query.bindValue(":newge", stringToQS(b.getGender()));
    query.bindValue(":newne", b.getNumbers());
    query.bindValue(":newco", stringToQS(b.getCollection()));
    query.bindValue(":newto", stringToQS(to_string(b.getTome())));
    query.bindValue(":newnt", stringToQS(to_string(b.getTomeEnd())));
    query.bindValue(":newisbn", stringToQS(to_string(b.getIsbn())));
    query.bindValue(":newsu", stringToQS(b.getSummary()));
    query.bindValue(":newimg", stringToQS(b.getImg()));
    if (!query.exec()) {
        qDebug() << "SQL --> Error for updating the book";
        qDebug() << "SQL --> ERROR: " << query.lastError().text();
    } else
        qDebug() << "SQL --> Updating the book success !";
}

void QuerySQL::addAuthor(Author) {
//    cout << "SQL <-- Tentative d'ajout d'une interaction " << i.getId() << " à la bdd..." << endl;
//    QSqlQuery query;
//    query.prepare("INSERT INTO Interaction(idInteraction,idContact, date, contenu, modification) VALUES (:ii,:ic, :d, :c, :m)");
//    query.bindValue(":ii",i.getId());
//    query.bindValue(":ic",i.getIdContact());
//    query.bindValue(":d",stringToQS(i.getDate().affiche()));
//    query.bindValue(":c",stringToQS(i.getContenu()));
//    query.bindValue(":m",stringToQS(i.getDateModif().affiche()));
//    if (!query.exec())
//    {
//        qDebug() << "SQL --> Erreur à l'ajout d'une interaction";
//            qDebug() << "SQL --> Erreur SQL : " << query.lastError().text();
//    }
//    else
//        qDebug() << "SQL --> Ajout interaction réussite !";
}

void QuerySQL::editAuthor(Author) {
//    cout << "SQL <-- Tentative d'edition d'une interaction " << oldI.getId() << " de la bdd..." << endl;
//    QSqlQuery query;
//    query.prepare("UPDATE Interaction SET date=:newd, contenu=:newc, modification=:newm WHERE idInteraction=:ii AND idContact=:ic");
//    query.bindValue(":ii",oldI.getId());
//    query.bindValue(":ic",oldI.getIdContact());

//    query.bindValue(":newd",stringToQS(oldI.getDate().affiche()));
//    query.bindValue(":newc",stringToQS(oldI.getContenu()));
//    query.bindValue(":newm",stringToQS(oldI.getDateModif().affiche()));

//    if (!query.exec())
//    {
//        qDebug() << "SQL --> Erreur à la modificationn d'une interaction";
//            qDebug() << "SQL --> Erreur SQL : " << query.lastError().text();
//    }
//    else
//        qDebug() << "SQL --> Modification d'interaction réussite !";
}

void QuerySQL::suppAuthor(Author) {
//    cout << "SQL <-- Tentative de suppression d'une interaction " << i.getId() << "  de la bdd..." << endl;
//    QSqlQuery query;
//    query.prepare("DELETE FROM Interaction WHERE idInteraction=:ii ");
//    query.bindValue(":ii",i.getId());
//    if (!query.exec())
//    {
//        qDebug() << "SQL --> Erreur à la suppression";
//        qDebug() << "SQL --> Erreur SQL : " << query.lastError().text();
//    }
//    else
//        qDebug() << "SQL --> Suppression interaction réussite !";
}

void QuerySQL::addEditor(Editor) {
//    cout << "SQL <-- Tentative d'ajout d'un todo " << td.getId() << " à la bdd..." << endl;
//    QSqlQuery query;
//    query.prepare("INSERT INTO Todo(idTodo,contenu,date) VALUES (:itd,:c,:d)");
//    query.bindValue(":itd",td.getId());
//    query.bindValue(":c",stringToQS(td.getContenu()));
//    query.bindValue(":d",stringToQS(td.getDate().affiche()));
//    if (!query.exec())
//    {
//        qDebug() << "SQL --> Erreur à l'ajout d'une interaction";
//            qDebug() << "SQL --> Erreur SQL : " << query.lastError().text();
//    }
//    else
//        qDebug() << "SQL --> Ajout interaction réussite !";
}

void QuerySQL::editEditor(Editor) {
//    cout << "SQL <-- Tentative d'edition d'un todo " << oldTd.getId() << " de la bdd..." << endl;
//    QSqlQuery query;
//    query.prepare("UPDATE Todo SET contenu=:newc, date=:newd WHERE idTodo=:itd");
//    query.bindValue(":itd",oldTd.getId());
//    query.bindValue(":newc",stringToQS(oldTd.getContenu()));
//    query.bindValue(":newd",stringToQS(oldTd.getDate().affiche()));


//    if (!query.exec())
//    {
//        qDebug() << "SQL --> Erreur à la modificationn d'un Todo";
//            qDebug() << "SQL --> Erreur SQL : " << query.lastError().text();
//    }
//    else
//        qDebug() << "SQL --> Modification Todo réussite !";
}

void QuerySQL::suppEditor(Editor) {
//    cout << "SQL <-- Tentative de suppression d'un todo " << td.getId() << " de la bdd..." << endl;
//    QSqlQuery query;
//    query.prepare("DELETE FROM Todo WHERE idTodo=:itd AND contenu=:c AND date=:d ");
//    query.bindValue(":itd",td.getId());
//    query.bindValue(":c",stringToQS(td.getContenu()));
//    query.bindValue(":d",stringToQS(td.getDate().affiche()));
//    if (!query.exec())
//    {
//        qDebug() << "SQL --> Erreur à la suppression";
//        qDebug() << "SQL --> Erreur SQL : " << query.lastError().text();
//    }
//    else
//        qDebug() << "SQL --> Suppression Todo réussite !";
}

void QuerySQL::addGender(Gender) {
//    cout << "SQL <-- Tentative d'ajout d'une association " << idAiT << " à la bdd..." << endl;
//    QSqlQuery query;
//    query.prepare("INSERT INTO AssociationInteractionTodo(idAIT,todo, interaction, idContact) VALUES (:iait,:td,:i,:ic)");
//    query.bindValue(":iait",idAiT);
//    query.bindValue(":td", idTd);
//    query.bindValue(":i",idi);
//    query.bindValue(":ic",idC);
//    if (!query.exec())
//    {
//        qDebug() << "SQL --> Erreur à l'ajout d'une AssociationInteractionTodo";
//        qDebug() << "SQL --> Erreur SQL : " << query.lastError().text();
//    }
//    else
//        qDebug() << "SQL --> Ajout AssociationInteractionTodo réussite !";
}

void QuerySQL::editGender(Gender) {
//    cout << "SQL <-- Tentative d'edition d'une association " << oldAIT.getId() << " de la bdd..." << endl;
//    QSqlQuery query;
//    query.prepare("UPDATE AssociationInteractionTodo SET todo=:newtd, interaction=:newi WHERE idAIT=:iait");
//    query.bindValue(":iait", oldAIT.getId());

//    query.bindValue("newtd", oldAIT.getTodo().getId());
//    query.bindValue("newi", oldAIT.getInteraction().getId());

//    if (!query.exec())
//    {
//        qDebug() << "SQL --> Erreur à la modificationn d'une AssociationInteractionTodo";
//            qDebug() << "SQL --> Erreur SQL : " << query.lastError().text();
//    }
//    else
//        qDebug() << "SQL --> Modification AssociationInteractionTodo réussite !";
}

void QuerySQL::suppGender(Gender) {
//    cout << "SQL <-- Tentative de suppresion d'une association " << ait.getId() << " de la bdd..." << endl;
//    QSqlQuery query;
//    query.prepare("DELETE FROM AssociationInteractionTodo WHERE idAIT=:iait AND todo=:td AND interaction=:i AND idContact=: ic");
//    query.bindValue(":iait",ait.getId());
//    query.bindValue(":td",ait.getTodo().getId());
//    query.bindValue(":i",ait.getInteraction().getId());
//    query.bindValue(":ic",ait.getInteraction().getIdContact());
//    if (!query.exec())
//    {
//        qDebug() << "SQL --> Erreur à la suppression";
//        qDebug() << "SQL --> Erreur SQL : " << query.lastError().text();
//    }
//    else
//        qDebug() << "SQL --> Suppression AssociationInteractionTodo réussite !";
}

void QuerySQL::addCollection(Collection) {

}

void QuerySQL::editCollection(Collection) {

}

void QuerySQL::suppCollection(Collection) {

}

void QuerySQL::getAllBooks() {
    cout << "SQL <-- Trying to get all books from the db..." << endl;
    QSqlQuery query;
    query.prepare("SELECT id, title, authors, editors, parutionyear, gender, nbexemplary, collection, tome, nbtomes, isbn, summary,img FROM Books");
    if (!query.exec())
    {
        qDebug() << "SQL --> Erreur pour récupérer les contacts de la BDD";
        qDebug() << "SQL --> Erreur SQL : " << query.lastError().text();
    }
    else
    {
        qDebug() << "SQL --> Récupération réussie !";
        Book b;
        list<Book> list;
        while (query.next()) {
            QString r = query.value(0).toString(); // récupère id
            b.setId(r.toInt());
            r = query.value(1).toString(); // récupère nom
            b.setTitle(r.toStdString());
            r = query.value(2).toString(); // récupère prenom
            b.setAuthors(r.toStdString());
            r = query.value(3).toString(); // récupère age
            b.setEditors(r.toStdString());
            r = query.value(4).toString(); // récupère entreprise
            b.setYear(r.toInt());
            r = query.value(5).toString(); // récupère mail
            b.setGender(r.toStdString());
            r = query.value(6).toString(); // récupère telephone
            b.setNumbers(r.toInt());
            r = query.value(7).toString(); // récupère url
            b.setCollection(r.toStdString());
            r = query.value(8).toString(); // récupère date
            b.setTome(r.toInt());
            r = query.value(9).toString(); // récupère date
            b.setTomeEnd(r.toInt());
            r = query.value(10).toString(); // récupère date
            b.setIsbn(r.toInt());
            r = query.value(11).toString(); // récupère date
            b.setSummary(r.toStdString());
            r = query.value(12).toString(); // récupère date
            b.setImg(r.toStdString());
            list.push_back(b);
        }
        emit envListBooks(list);
    }
}

void QuerySQL::getAllAuthors() {
//    cout << "SQL <-- Tentative de récupération des intéractions de la bdd..." << endl;
//    QSqlQuery query;
//    query.prepare("SELECT idInteraction,idContact, date, contenu, modification FROM Interaction");
//    if (!query.exec())
//    {
//        qDebug() << "SQL --> Erreur pour récupérer les interactions de la BDD";
//            qDebug() << "SQL --> Erreur SQL : " << query.lastError().text();
//    }
//    else
//    {
//        qDebug() << "SQL --> Récupération réussie !";
//        Interaction i;
//        list<Interaction> listI;
//        while (query.next()) {
//            QString r = query.value(0).toString(); // récupère id
//            i.setId(r.toInt());

//            r = query.value(1).toString(); // récupère idContact
//            i.setIdContact(r.toInt());

//            r = query.value(2).toString(); // récupère Date
//            Date d(r.toStdString());
//            i.setDate(d);

//            r = query.value(3).toString(); // récupère Contenu
//            i.setContenu(r.toStdString());

//            r = query.value(4).toString(); // récupère Date
//            Date modif(r.toStdString());
//            i.setDateModifD(modif);
//            listI.push_back(i);
//        }
//        emit envListI(listI);
//    }
}

void QuerySQL::getAllEditors() {
//    cout << "SQL <-- Tentative de récupération des todos de la bdd..." << endl;
//    QSqlQuery query;
//    query.prepare("SELECT idTodo, contenu, date FROM Todo");
//    if (!query.exec())
//    {
//        qDebug() << "SQL --> Erreur pour récupérer les todos de la BDD";
//            qDebug() << "SQL --> Erreur SQL : " << query.lastError().text();
//    }
//    else
//    {
//        qDebug() << "SQL --> Récupération réussie !";
//        Todo td;
//        list<Todo> listTd;
//        while (query.next()) {
//            QString r = query.value(0).toString(); // récupère id
//            td.setId(r.toInt());

//            r = query.value(1).toString(); // récupère Contenu
//            td.setContenu(r.toStdString());

//            r = query.value(2).toString(); // récupère Date
//            Date d(r.toStdString());
//            td.setDate(d);

//            listTd.push_back(td);
//        }
//        emit envListTd(listTd);
//    }
}

void QuerySQL::getAllGenders() {
//    cout << "SQL <-- Tentative de récupération des associations de la bdd..." << endl;
//    QSqlQuery query;
//    query.prepare("SELECT idAIT,todo, interaction, idContact FROM AssociationInteractionTodo");
//    if (!query.exec())
//    {
//        qDebug() << "SQL --> Erreur pour récupérer les associations de la BDD";
//            qDebug() << "SQL --> Erreur SQL : " << query.lastError().text();
//    }
//    else
//    {
//        qDebug() << "SQL --> Récupération réussie !";
//        list<list<int>> listAIT;

//        while (query.next()) {
//            list<int> ait;
//            QString r = query.value(0).toString(); // récupère id
//            ait.push_back(r.toInt());

//            r = query.value(1).toString(); // récupère idTodo
//            ait.push_back(r.toInt());

//            r = query.value(2).toString(); // récupère idInteraction
//            ait.push_back(r.toInt());

//            r = query.value(3).toString(); // récupère idInteraction
//            ait.push_back(r.toInt());

//            listAIT.push_back(ait);
//        }
//        emit envListAIT(listAIT);
//    }
}

void QuerySQL::getAllCollections() {

}

QSqlQueryModel* QuerySQL::getSQLBookModel()
{
    model->setQuery("SELECT id, title, authors, editors, parutionyear, gender, nbexemplary, collection FROM Books");
    return model;
}

