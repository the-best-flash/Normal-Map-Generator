/***************************************************************************
    Normal Map Generator Copyright © 2010 Colton Manville
    (Contact: the_best_flash@hotmail.com)

    This file is part of Normal Map Generator.

    Normal Map Generator is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Normal Map Generator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Normal Map Generator.

    If not, see <http://www.gnu.org/licenses/gpl.txt>.
***************************************************************************/

#include "normalmaplist.h"
#include "ui_normalmaplist.h"

NormalMapList::NormalMapList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NormalMapList)
{
    ui->setupUi(this);

    nSettings = new NormalMapSettings();
    nSettings->setWindowFlags((nSettings->windowFlags() & ~Qt::WindowContextHelpButtonHint & ~Qt::WindowCloseButtonHint & ~Qt::WindowSystemMenuHint) | Qt::CustomizeWindowHint);

    addLayer = new AddLayer(this);
    addLayer->setWindowFlags((addLayer->windowFlags() & ~Qt::WindowContextHelpButtonHint & ~Qt::WindowCloseButtonHint & ~Qt::WindowSystemMenuHint) | Qt::CustomizeWindowHint);


    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

NormalMapList::~NormalMapList()
{
    delete ui;
    delete nSettings;
}

void NormalMapList::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void NormalMapList::on_EditButton_clicked()
{
    nSettings->show();
}

void NormalMapList::on_Add_clicked()
{
    addLayer->show();
    this->hide();
}
