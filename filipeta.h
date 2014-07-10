/***************************************************************************
*    CDash (Cláudia Dash) Panel Dash to Desktop
*    Copyright (C) 2014 by Jean Richard Lima
*    Author: Jean Richard Lima <jean@jeanrl.com.br>

*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.

*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.

*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.
***************************************************************************/
#ifndef FILIPETA_H
#define FILIPETA_H

#include <QWidget>

class filipeta : public QWidget
{
    Q_OBJECT
public:
    explicit filipeta(QWidget *parent = 0);
    virtual ~filipeta();
    QPixmap bgflp;

protected:
    void paintEvent (QPaintEvent *);


signals:

public slots:

};

#endif // FILIPETA_H
