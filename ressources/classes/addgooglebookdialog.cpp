#include "addgooglebookdialog.h"
#include "ui_addgooglebookdialog.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

#include <QJsonDocument>
#include <QJsonObject>


addGoogleBookDialog::addGoogleBookDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addGoogleBookDialog)
{
    ui->setupUi(this);
}

addGoogleBookDialog::~addGoogleBookDialog()
{
    delete ui;
}

void addGoogleBookDialog::resetDialog()
{
    ui->authorLineEdit->clear();
    ui->authorSearchLineEdit->clear();
    ui->titleSearchLineEdit->clear();
    ui->titleLineEdit->clear();
    ui->collectionLineEdit->clear();
    ui->editorLineEdit->clear();
    ui->tomeLineEdit->clear();
    ui->tomeEndLineEdit->clear();
    ui->genderLineEdit->clear();
    ui->isbnLineEdit->clear();
    ui->yearLineEdit->clear();
    ui->summaryPlainTextEdit->clear();
    ui->horizontalSlider->setSliderPosition(0);
    ui->nbQuerylcdNumber->display(0);
    ui->nbrFindBookLabel->setText(tr("x livre(s) trouvé(s):"));
    ui->authorsCheckBox->setChecked(false);
    ui->editorCheckBox->setChecked(false);
    ui->collectionCheckBox->setChecked(false);
    ui->tomeCheckBox->setChecked(false);
    ui->genderCheckBox->setChecked(false);
    ui->imgCheckBox->setChecked(false);
    ui->isbnCheckBox->setChecked(false);
    ui->summaryCheckBox->setChecked(false);
    ui->titleCheckBox->setChecked(false);
    ui->yearCheckBox->setChecked(false);
}

void addGoogleBookDialog::searchBook()
{
    QUrl url("https://www.googleapis.com/books/v1/volumes");

    QString intitle= "";
    QString inauthor= "";
    if(!query.isEmpty())
        query.clear();
    if(!ui->titleSearchLineEdit->text().isEmpty() && !ui->authorSearchLineEdit->text().isEmpty())
    {
        intitle = ui->titleSearchLineEdit->text();
        inauthor = ui->authorSearchLineEdit->text();
        query.addQueryItem("q", "intitle:" + intitle + " inauthor:" + inauthor);
    }
    else if(!ui->titleSearchLineEdit->text().isEmpty() && ui->authorSearchLineEdit->text().isEmpty())
    {
        intitle = ui->titleSearchLineEdit->text();
        query.addQueryItem("q", "intitle:" + intitle);
    }
    url.setQuery(query);
    QNetworkRequest request(url);
    QNetworkReply *reply = manager.get(request);
    qDebug() <<"TEST= " << query.query();
    QObject::connect(reply, &QNetworkReply::finished, [=] {
        if (reply->error()) {
            qDebug() << reply->errorString();
            return;
        }

        QString response = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response.toUtf8());
        QJsonObject jsonObject = jsonResponse.object(); // Get Object
        jsonArray = jsonObject["items"].toArray(); // Get "items" Object
        std::string nbrFindBooks = std::to_string(jsonArray.size());
        QString text = tr(" livre(s) trouvé(s):");
        std::string s_nbrFindBooks = nbrFindBooks + text.toStdString();
        ui->nbrFindBookLabel->setText(QString::fromStdString(s_nbrFindBooks)); // label x books find
        ui->horizontalSlider->setMaximum(jsonArray.size()); // max slide = books finds
        reply->deleteLater();
    });
}

void addGoogleBookDialog::on_horizontalSlider_sliderMoved(int position)
{
    ui->nbQuerylcdNumber->display(position); // change lcdNumber
    QJsonObject bookObject = jsonArray[ui->horizontalSlider->value()].toObject();
    QJsonObject volumeInfo = bookObject["volumeInfo"].toObject();
    ui->titleLineEdit->setText(volumeInfo["title"].toString());
    QString result ="";
    for (int i = 0; i < volumeInfo["authors"].toArray().size(); ++i) {
        if (i != 0)
            result += ", ";
        result += volumeInfo["authors"].toArray()[i].toString();
    }
    ui->authorLineEdit->setText(result);
    ui->editorLineEdit->setText(volumeInfo["publisher"].toString());
    result = "";
    for (int i = 0; i < volumeInfo["categories"].toArray().size(); ++i) {
        if (i != 0)
            result += ", ";
        result += volumeInfo["categories"].toArray()[i].toString();
    }
    ui->genderLineEdit->setText(result);
    ui->collectionLineEdit->setText(volumeInfo["title"].toString());
    ui->summaryPlainTextEdit->setPlainText(volumeInfo["description"].toString());
    ui->yearLineEdit->setText(QString::fromStdString(volumeInfo["publishedDate"].toString().toStdString().substr(0,4)));

    QJsonArray industryIdentifiers = volumeInfo["industryIdentifiers"].toArray();
    QString isbn13 = "";
    for (int i = 0; i < industryIdentifiers.size(); ++i) {
        QJsonObject identifier = industryIdentifiers[i].toObject();
        if (identifier["type"].toString() == "ISBN_13") {
            isbn13 = identifier["identifier"].toString();
            break;
        }
    }
    ui->isbnLineEdit->setText(isbn13);
}


void addGoogleBookDialog::on_searchPushButton_clicked()
{
    searchBook();
}


void addGoogleBookDialog::on_titleSearchLineEdit_returnPressed()
{
    searchBook();
}


void addGoogleBookDialog::on_authorSearchLineEdit_returnPressed()
{
    searchBook();
}


void addGoogleBookDialog::on_buttonBox_accepted()
{
    Book b;
    if(ui->titleCheckBox->isChecked())
        b.setTitle(ui->titleLineEdit->text().toStdString());
    if(ui->authorsCheckBox->isChecked())
        b.setAuthors(ui->authorLineEdit->text().toStdString());
    if(ui->editorCheckBox->isChecked())
        b.setEditors(ui->editorLineEdit->text().toStdString());
    if(ui->collectionCheckBox->isChecked())
        b.setCollection(ui->collectionLineEdit->text().toStdString());
    if(ui->tomeCheckBox->isChecked())
    {
        b.setTome(ui->tomeLineEdit->text().toInt());
        b.setTomeEnd(ui->tomeEndLineEdit->text().toInt());
    }
    if(ui->genderCheckBox->isChecked())
        b.setGender(ui->genderLineEdit->text().toStdString());
    if(ui->imgCheckBox->isChecked())
       // SAUVEGARDE DE L'IMAGE DANS LE DISQUE PUIS RECUPERER CHEMIN ET SET
    if(ui->isbnCheckBox->isChecked())
        b.setIsbn(ui->isbnLineEdit->text().toInt());
    if(ui->summaryCheckBox->isChecked())
        b.setSummary(ui->summaryPlainTextEdit->toPlainText().toStdString());
    if(ui->yearCheckBox->isChecked())
        b.setYear(ui->yearLineEdit->text().toInt());

    emit sendBook(b);
}


void addGoogleBookDialog::on_buttonBox_rejected()
{
    resetDialog();
}

