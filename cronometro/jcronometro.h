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

#ifndef CRONOMETRO_H
#define CRONOMETRO_H

#include <QObject>
#include <QString>

class Cronometro : public QObject
{
    Q_OBJECT
public:
    explicit Cronometro(QObject *parent = 0);
    virtual ~Cronometro();

    int get_hor() const;
    void set_hor(int h);
    int get_min() const;
    void set_min( int m);
    int get_seg() const;
    void set_seg(int s);

    bool get_tocaaudio() const;
    void set_tocaaudio(bool t);

    QString get_audio() const;
    void set_audio( QString a);

    bool get_sinalvisual() const;
    void set_sinalvisual(bool sv);

    QString get_tarefa() const;
    void set_tarefa( QString tf);

    void ini();

private:
    int hora, minuto, segundo;
    bool toca = true;
    QString audio;
    bool sinalVisual = true;
    QString tarefa;

signals:

public slots:

};

#endif // CRONOMETRO_H


