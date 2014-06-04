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

#ifndef WRELOGIO_H
#define WRELOGIO_H

#include <QWidget>
#include <QtGui>


class wrelogio : public QWidget
{
    Q_OBJECT

public:
    wrelogio(QWidget *parent = 0);
    ~wrelogio();
    int angulo_seg, angulo_hor, angulo_min, contador;

private:
    QPixmap bg;
    void gravaSettings();
    void leSettings();

protected:
    void paintEvent (QPaintEvent *);
    void mousePressEvent(QMouseEvent *ev);

};

#endif // WIDGET_H
