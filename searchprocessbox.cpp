#include <iostream>
#include "searchprocessbox.h"
#include "ui_searchprocessbox.h"

SearchProcessBox::SearchProcessBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchProcessBox)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);
}

SearchProcessBox::~SearchProcessBox()
{
    delete ui;
}

void SearchProcessBox::setPersentage(double Persentage)
{

    ui->progressBar->setValue(Persentage * 100);
}
