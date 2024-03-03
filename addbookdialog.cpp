#include "addbookdialog.h"
#include "ui_addbookdialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include <iostream>

AddBookDialog::AddBookDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddBookDialog)
{
    ui->setupUi(this);
    setLayout(ui->mainLayout);
    ui->exemplaryLineEdit->setText("1");
}

AddBookDialog::~AddBookDialog()
{
    delete ui;
}

void AddBookDialog::clearForm()
{
    ui->titleLineEdit->clear();
    ui->authorLineEdit->clear();
    ui->editorLineEdit->clear();
    ui->genderLineEdit->clear();
    ui->collectionLineEdit->clear();
    ui->summaryPlainTextEdit->clear();
    ui->exemplaryLineEdit->setText("1");
    ui->yearLineEdit->clear();
    ui->tomeSpinBox->clear();
    ui->tomeOfSpinBox->clear();
}

void AddBookDialog::on_buttonBox_rejected()
{
    close();
    clearForm();
}




void AddBookDialog::on_buttonBox_accepted()
{
    Book b;
    if(!ui->titleLineEdit->text().isNull())
    {
        b.setTitle(ui->titleLineEdit->text().toStdString());

        if(!ui->authorLineEdit->text().isNull())
            b.setAuthors(ui->authorLineEdit->text().toStdString());
        if(!ui->editorLineEdit->text().isNull())
            b.setEditors(ui->editorLineEdit->text().toStdString());
        if(!ui->genderLineEdit->text().isNull())
            b.setGender(ui->genderLineEdit->text().toStdString());
        if(!ui->collectionLineEdit->text().isNull())
            b.setCollection(ui->collectionLineEdit->text().toStdString());
        if(!ui->summaryPlainTextEdit->toPlainText().toStdString().empty())
        {
            std::cout <<"SUMMARY= "<< ui->summaryPlainTextEdit->toPlainText().toStdString().empty() << endl;
            b.setSummary(ui->summaryPlainTextEdit->toPlainText().toStdString());
        }
        if(!ui->exemplaryLineEdit->text().isNull())
            b.setNumbers(ui->exemplaryLineEdit->text().toInt());
        if(!ui->yearLineEdit->text().isNull())
            b.setYear(ui->yearLineEdit->text().toInt());
        if(!ui->tomeSpinBox->text().isNull())
            b.setTome(ui->tomeSpinBox->value());
        if(!ui->tomeOfSpinBox->text().isNull())
            b.setTomeEnd(ui->tomeOfSpinBox->value());
        if(!ui->isbnLineEdit->text().isNull())
            b.setIsbn(ui->isbnLineEdit->text().toInt());
        if(!ui->imgPathEdit->text().isNull())
            b.setImg(ui->imgPathEdit->text().toStdString());
        emit sendNewBook(b);
    }
    else{
        QMessageBox::critical(this, "Erreur", "Titre vide");
    }


}


void AddBookDialog::on_addImgButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(nullptr, tr("Choisir une image"), QDir::homePath(), tr("Images (*.png *.jpg *.jpeg *.bmp)"));
    if(!filename.isEmpty())
    {
        ui->imgPathEdit->setText(filename);
    }
}

