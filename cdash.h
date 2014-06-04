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

#ifndef CDASH_H
#define CDASH_H

#include <QWidget>
#include "dash.h"
#include "configdash.h"
#include "relogio/wrelogio.h"
#include "cronometro/widget.h"


namespace Ui {
class Widget;
}

class CDash : public QWidget
{
    Q_OBJECT

public:
    explicit CDash(QWidget *parent = 0);
    ~CDash();
    int tempConfig = 0;
    bool vsvFilipeta = false;
    void animFilipeta();
    void mataFilipeta();

private:
    QWidget *flpConfig;
    QTimer *tmFilipeta;
    QPixmap bg;
    void createCDWindow();
    void createFP();

protected:
    void paintEvent (QPaintEvent *);

protected slots:
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void temporizador();

private slots:
     void showConfig();

};

#endif // WIDGET_H
