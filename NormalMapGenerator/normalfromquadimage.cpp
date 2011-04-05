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

#include "normalfromquadimage.h"
#include "ui_normalfromquadimage.h"

NormalFromQuadImage::NormalFromQuadImage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NormalFromQuadImage)
{
    ui->setupUi(this);

    imageSelect = new ImageSelect();
    imageSelect->setWindowTitle("");
    imageSelect->setWindowFlags(Qt::Tool);

}

NormalFromQuadImage::~NormalFromQuadImage()
{
    delete ui;
    delete imageSelect;
}

void NormalFromQuadImage::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void NormalFromQuadImage::on_OpenImages_clicked()
{
    imageSelect->show();
}
