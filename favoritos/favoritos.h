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
#ifndef FAVORITOS_H
#define FAVORITOS_H

#include <QWidget>
#include "jbotao.h"
#include <QDir>
#include <QBoxLayout>
#include <QSettings>

struct detailsButton
{
     QString name;
     QString command;
     QString typeCommand;
     QString meta;
     QPixmap icon;
};

namespace Ui {
class favoritos;
}

class favoritos : public QWidget
{
    Q_OBJECT

public:
    explicit favoritos(QWidget *parent = 0);
    ~favoritos();
    int numBotao = 0;
    int totalBotoes, lineLayoute, colummLayout;
    jbotao *botao;
    QList<QString> *listFavApps;
    QGridLayout *layout;

private:
    Ui::favoritos *ui;
    jbotao *btn[16];
    detailsButton readFile(QString fileRead);
    void hideButtons();
    detailsButton returnIcon(const QString &ext);
    void loadButtons(int qtdaBtn);

protected slots:
    void dragEnterEvent(QDragEnterEvent * ev);
    void dragLeaveEvent(QDragLeaveEvent * ev);
    void dragMoveEvent(QDragMoveEvent * ev);
    void dropEvent(QDropEvent * ev);
    void desapearBackground();

};

#endif // FAVORITOS_H
