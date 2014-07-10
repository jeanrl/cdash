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
#include "filipeta.h"

#include <QPainter>

filipeta::filipeta(QWidget *parent) :
    QWidget(parent)
{

    setWindowFlags(Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_X11NetWmWindowTypeDock, true);
    setAttribute(Qt::WA_TranslucentBackground);
/*
    setMinimumSize(100,320);
    setMaximumSize(100,320);
*/

    setMinimumSize(100,300);
    setMaximumSize(100,300);

    bgflp.load("://imagens/filipeta_fundo.png");

}

filipeta::~filipeta()
{

}

void filipeta::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
    painter.drawPixmap(QPoint(0,0),bgflp);

}
