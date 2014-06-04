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

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMenu>
#include <QMouseEvent>

#include "configcron.h"
#include "jcronometro.h"

namespace Ui {
class Widget;
}

class wcronometro : public QWidget
{
    Q_OBJECT

public:
    explicit wcronometro(QWidget *parent = 0);
    ~wcronometro();
    void createAct();
    void finaliza();
    QAction *confAct;
    QAction *playAct;
    QAction *pauseAct;
    QAction *resetAct;
    QString txt_hora;
    QString txt_min;
    QString txt_seg;
    int seg, min, hor;
    QTimer *timer_cro;
    bool cro_ini;
    bool m_balao = false;

protected:
    void contextMenuEvent();

private:
    Ui::Widget *ui;
    Cronometro * _cronometro;
    QWidget *balaoMsg;
    void mostraBalao();

private slots:
     void showTime();
     void showConfig();
     void dispara();
     void rodacro();
     void pausa();
     void reseta();

protected slots:
     void mousePressEvent(QMouseEvent *e);
     bool eventFilter(QObject* obj, QEvent *e);

};

#endif // WIDGET_H
