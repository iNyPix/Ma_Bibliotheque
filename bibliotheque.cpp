#include <QGraphicsPixmapItem>
#include "bibliotheque.h"
#include "ui_bibliotheque.h"
#include "aboutdialog.h"


Bibliotheque::Bibliotheque(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Bibliotheque)
{
    ui->setupUi(this);
    ui->centralwidget->setLayout(ui->mainLayout);
    model = new QSqlQueryModel();

    qsql.connexionDBWithPath("ressources/db/biblioDB.sqlite");
    ui->dbNameLabel->setText(QString::fromStdString(qsql.getQSqlDatabaseName()));

    /* Connection */
    connect(&qsql,SIGNAL(envListBooks(list<Book>)),this, SLOT(recData(list<Book>)));
    connect(&addBookDialog,SIGNAL(sendNewBook(Book)),this,SLOT(recNewBook(Book)));
    connect(&addGoogleBookDialog,SIGNAL(sendBook(Book)),this,SLOT(recNewBook(Book)));

    qsql.getAllBooks();
    refreshBooksView();
}

Bibliotheque::~Bibliotheque()
{
    delete ui;
}

bool Bibliotheque::isISBN10Valid(const string &isbn)
{
    string cleanedISBN;

    // Delete not-numeric character except 'X'
    for (char c : isbn) {
        if (isdigit(c) || (c == 'X' && cleanedISBN.size() == 9)) {
            cleanedISBN += c;
        }
    }

    if (cleanedISBN.size() != 10) {
        return false;
    }

    if (toupper(cleanedISBN[9]) == 'X') {
        cleanedISBN[9] = '0';
    }

    int suma = 0;

    for (int i = 0; i < 10; i++) {
        suma += (10 - i) * (cleanedISBN[i] - '0');
    }

    return (suma % 11) == 0;
}

bool Bibliotheque::isISBN13Valid(const string &isbn)
{
    string cleanedISBN;

    // Delete not-numeric character
    for (char c : isbn) {
        if (isdigit(c)) {
            cleanedISBN += c;
        }
    }

    if (cleanedISBN.size() != 13) {
        return false;
    }

    int suma = 0;

    for (int i = 0; i < 13; i++) {
        int digit = cleanedISBN[i] - '0';
        suma += (i % 2 == 0) ? digit : digit * 3;
    }

    return (suma % 10) == 0;
}

bool Bibliotheque::isISBNValid(const string &isbn) {
    return isISBN10Valid(isbn) || isISBN13Valid(isbn);
}


Book Bibliotheque::getBookById(int id)
{
    for(Book b : listBooks)
        if(b.getId() == id)
            return b;
}

void Bibliotheque::errorDialog(string msg)
{
    QMessageBox::critical(this, "Erreur", QString::fromStdString(msg));
}
void Bibliotheque::recData(list<Book> list){
    listBooks = list;
}

void Bibliotheque::refreshBooksView()
{
    model->setQuery("SELECT id, title, authors, editors, parutionyear, gender, nbexemplary, collection FROM Books", qsql.getQSqlDatabase());
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Titre"));
    model->setHeaderData(2, Qt::Horizontal, tr("Auteurs"));
    model->setHeaderData(3, Qt::Horizontal, tr("Editeurs"));
    model->setHeaderData(4, Qt::Horizontal, tr("Date de parution"));
    model->setHeaderData(5, Qt::Horizontal, tr("Genre"));
    model->setHeaderData(6, Qt::Horizontal, tr("Nbr exemplaires"));
    model->setHeaderData(7, Qt::Horizontal, tr("Collection"));

    ui->booksView->setModel(model);
    ui->lcdNumber->display((int)listBooks.size());
}

void Bibliotheque::recNewBook(Book b)
{
    Book newBook = b;
    newBook.setId(listBooks.size()+1);
    listBooks.push_back(newBook);
    qsql.addBook(newBook);
    refreshBooksView();
}

void Bibliotheque::on_buttonAddBook_clicked()
{
    addBookDialog.show(); // Show the dialog for adding a book
}


void Bibliotheque::on_actionOuvrir_une_biblioth_que_triggered()
{
    QString filename = openDbDialog->getOpenFileName(nullptr, tr("Ouvrir une Bibliothèque"), QDir::homePath(), tr("SQLite Database Files (*.db *.sqlite *.sqlite3);;All Files (*)"));
    if(!filename.isEmpty())
    {
        qsql.connexionDBWithPath(filename.toStdString());
        ui->dbNameLabel->setText(QString::fromStdString(qsql.getQSqlDatabaseName()));
    }
}


void Bibliotheque::on_actionNouvelle_biblioth_que_triggered()
{
    QString modelPath = "ressources/db/model_biblioDB.sqlite";
    if(modelPath.isEmpty())
        errorDialog("Impossible de trouver le modèle d'une biblitohèque:" + modelPath.toStdString());
    else
    {
        QString destPath = openDbDialog->getSaveFileName(nullptr, tr("Nouvelle Bibliothèque"), QDir::homePath(), tr("SQLite Database Files (*.db *.sqlite *.sqlite3)"));
        if(destPath.isEmpty())
        {
            errorDialog("Impossible de créer la bibliothèque ici:" + modelPath.toStdString());
        }
        else
        {
            QFile modelFile(modelPath);
            if(!modelFile.open(QIODevice::ReadWrite))
            {
                errorDialog("Impossible d'ouvrir le modèle de bibliothèque");
            }
            else
            {
                destPath.append(".sqlite");
                QFile destFile(destPath);
                QFile::copy(modelPath,destPath);
                qsql.connexionDBWithPath(destPath.toStdString());
                ui->dbNameLabel->setText(QString::fromStdString(qsql.getQSqlDatabaseName()));
            }
        }
    }
}


void Bibliotheque::on_actionSupprimer_une_biblioth_que_triggered()
{
    QFile db(qsql.getQSqlDatabase().databaseName());
    if(db.exists()){
        db.remove();
        QMessageBox::warning(this, tr("Attention"), tr("La bibliothèque a été supprimée"));
    }
}


void Bibliotheque::on_actionRenommer_la_biblioth_que_triggered()
{

}


void Bibliotheque::on_actionR_initialiser_la_biblioth_que_triggered()
{
    QString modelPath = "ressources/db/model_biblioDB.sqlite";
    if(modelPath.isEmpty())
        errorDialog("Impossible de trouver le modèle d'une biblitohèque:" + modelPath.toStdString());
    else
    {
        QString destPath = qsql.getQSqlDatabase().databaseName();
        if(destPath.isEmpty())
        {
            errorDialog("Impossible de trouver la bibliothèque ici:" + modelPath.toStdString());
        }
        else
        {
            QFile modelFile(modelPath);
            if(!modelFile.open(QIODevice::ReadWrite))
            {
                errorDialog("Impossible d'ouvrir le modèle de bibliothèque");
            }
            else
            {
                QFile destFile(destPath);
                QFile::copy(modelPath,destPath);
                qsql.connexionDBWithPath(destPath.toStdString());
            }
        }
    }
}


void Bibliotheque::on_titleLineEdit_editingFinished()
{
    qDebug() << "FIN";
}


void Bibliotheque::on_booksView_clicked(const QModelIndex &index)
{
    ui->buttonSaveBook->setEnabled(true);
    QSqlRecord record = model->record(index.row());
    QString id = record.value("id").toString();
    ui->idLineEdit->setText(id);
    QString title = record.value("title").toString();
    ui->titleLineEdit->setText(title);
    QString authors = record.value("authors").toString();
    ui->authorLineEdit->setText(authors);
    QString year = record.value("parutionyear").toString();
    ui->yearLineEdit->setText(year);
    QString gender = record.value("gender").toString();
    ui->genderLineEdit->setText(gender);
    QString nbexemplary = record.value("nbexemplary").toString();
    ui->exemplaryLineEdit->setText(nbexemplary);
    QString collection = record.value("collection").toString();
    ui->collectionLineEdit->setText(collection);
    QString tome = record.value("tome").toString();
    ui->tomeSpinBox->setValue(tome.toInt());
    QString nbtomes = record.value("nbtomes").toString();
    ui->tomeEndSpinBox->setValue(nbtomes.toInt());
    QString isbn = record.value("isbn").toString();
    ui->isbnLineEdit->setText(isbn);
    QString summary = record.value("summary").toString();
    ui->summaryPlainTextEdit->setPlainText(summary);

    Book it = getBookById(id.toInt());
    QString imgPath = QString::fromStdString(it.getImg());

    if(!imgPath.isNull()){
        QGraphicsScene* scene = new QGraphicsScene(this);
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap(imgPath));
        scene->addItem(item);
        ui->bookPhoto->setScene(scene);
    }
}

void Bibliotheque::on_buttonDeleteBook_clicked()
{
    // Get the index of the selected row
    QModelIndex index = ui->booksView->selectionModel()->currentIndex();
    if(index.isValid())
    {
        // Get the index of the column "id"
        int indexColumn = model->record().indexOf("id");
        // Get the value of the column "id" for the selected row
        QVariant idValue = ui->booksView->model()->data(ui->booksView->model()->index(index.row(), indexColumn));
        Book supp;
        supp.setId(idValue.toInt());
        qsql.suppBook(supp);
        QMessageBox::information(this, tr("Information"), tr("Le livre a été supprimé"));
    }
}


void Bibliotheque::on_actionA_propos_triggered()
{
    aboutDialog.show();
}


void Bibliotheque::on_buttonImportBook_clicked()
{
    addGoogleBookDialog.show();
}


void Bibliotheque::on_buttonSaveBook_clicked()
{
    //
}

