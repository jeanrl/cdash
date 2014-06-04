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

#include "configcron.h"
#include "ui_configcron.h"
#include <QFileDialog>
#include <QDebug>
#include <QProcess>

configcron::configcron(Cronometro *c, QDialog *parent) :
    QDialog(parent), ui(new Ui::configcron), _cronometro(c)
{
    ui->setupUi(this);

    connect ( ui->cbHora, SIGNAL(currentIndexChanged(int)), this, SLOT(defHor(int)));
    connect ( ui->cbMin, SIGNAL(currentIndexChanged(int)), this, SLOT(defMin(int)));
    connect ( ui->cbSeg, SIGNAL(currentIndexChanged(int)), this, SLOT(defSeg(int)));

    connect ( ui->ckbAudio, SIGNAL(clicked()), this, SLOT(defTocaAudio()));
    connect ( ui->pbDefAudio, SIGNAL(clicked()), this, SLOT(escolheaudio()));

    connect ( ui->ckbVisual, SIGNAL(clicked()), this, SLOT(defSinalVisual()));

    connect ( ui->pbOk, SIGNAL(clicked()), this, SLOT(aplicar())) ;
    connect ( ui->pbCancel, SIGNAL(clicked()), this, SLOT(cancelar())) ;

}

configcron::~configcron()
{
    delete ui;
}

void configcron::closeEvent(QCloseEvent *)
{
    this->deleteLater();
}

void configcron::aplicar()
{
    tituloVisual();
    accept();
    close();
}

void configcron::cancelar()
{
     reject();
}

void configcron::defHor(int ind)
{
    _cronometro->set_hor(ind);
}

void configcron::defMin(int ind)
{
    _cronometro->set_min(ind);
}

void configcron::defSeg(int ind)
{
    _cronometro->set_seg(ind);
}

void configcron::defTocaAudio()
{
    _cronometro->set_tocaaudio(ui->ckbAudio->isChecked());
}

void configcron::escolheaudio()
{
    _cronometro->set_audio(QFileDialog::getOpenFileName(this,
                                                    tr("Abrir Arquivo de Áudio"), QDir::homePath(), tr("Audio Files (*.mp3 *.wav *.ogg)")));
    ui->leAudio->setText(_cronometro->get_audio());
}

void configcron::defSinalVisual()
{
    _cronometro->set_sinalvisual(ui->ckbVisual->isChecked());
    qDebug() << _cronometro->get_sinalvisual();
}

void configcron::tituloVisual()
{
     _cronometro->set_tarefa(ui->leTarefa->text());
}
