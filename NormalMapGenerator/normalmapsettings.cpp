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

#include "normalmapsettings.h"
#include "ui_normalmapsettings.h"

NormalMapSettings::NormalMapSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NormalMapSettings)
{
    ui->setupUi(this);

    fromImage = new NormalFromImage(ui->WidgetFrame);
    fromNormal = new NormalFromNormal(ui->WidgetFrame);
    fromGenerator = new NormalFromGenerator(ui->WidgetFrame);
    fromQuadImage = new NormalFromQuadImage(ui->WidgetFrame);
    ui->horizontalLayout_3->addWidget((QWidget*)fromImage);
    ui->horizontalLayout_3->addWidget((QWidget*)fromNormal);
    ui->horizontalLayout_3->addWidget((QWidget*)fromGenerator);
    ui->horizontalLayout_3->addWidget((QWidget*)fromQuadImage);

    //fromImage->setVisible(false);
    fromNormal->setVisible(false);
    fromGenerator->setVisible(false);
    fromQuadImage->setVisible(false);
}

NormalMapSettings::~NormalMapSettings()
{
    delete ui;
    delete fromImage;
    delete fromNormal;
    delete fromGenerator;
}

void NormalMapSettings::changeEvent(QEvent *e)
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

void NormalMapSettings::on_Cancel_clicked()
{
    this->hide();
}
