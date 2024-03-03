#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    setLayout(ui->mainLayout);
    ui->infoLabel->setWordWrap(true);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
