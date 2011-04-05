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

#ifndef ADDLAYER_H
#define ADDLAYER_H

#include <QDialog>

namespace Ui {
    class AddLayer;
}

class AddLayer : public QDialog {
    Q_OBJECT
public:
    AddLayer(QWidget *parent = 0);
    ~AddLayer();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::AddLayer *ui;

private slots:
    void on_Cancel_clicked();
};

#endif // ADDLAYER_H
