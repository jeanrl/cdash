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

#include "jcronometro.h"

Cronometro::Cronometro(QObject *parent) :
    QObject(parent)
{
}

Cronometro::~Cronometro()
{

}

int Cronometro::get_hor() const
{
    return hora;
}

void Cronometro::set_hor(int h)
{
    hora = h;
}

int Cronometro::get_min() const
{
    return minuto;
}

void Cronometro::set_min(int m)
{
    minuto = m;
}

int Cronometro::get_seg() const
{
    return segundo;
}

void Cronometro::set_seg(int s)
{
    segundo = s;
}

bool Cronometro::get_tocaaudio() const
{
    return toca;
}

void Cronometro::set_tocaaudio(bool t)
{
    toca = t;
}

QString Cronometro::get_audio() const
{
    return audio;
}

void Cronometro::set_audio(QString a)
{
    audio = a;
}

bool Cronometro::get_sinalvisual() const
{
    return sinalVisual;
}

void Cronometro::set_sinalvisual(bool sv)
{
    sinalVisual = sv;
}

QString Cronometro::get_tarefa() const
{
    return tarefa;
}

void Cronometro::set_tarefa(QString tf)
{
    tarefa = tf;
}

void Cronometro::ini()
{
    hora = 0;
    minuto = 0;
    segundo = 0;
    toca = true;
    audio = "";
    sinalVisual = true;
    tarefa = "";
}
