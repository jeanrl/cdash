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

#include "configdash.h"
#include "ui_configdash.h"

#include <QSettings>
#include <QTranslator>
#include <QDebug>

configDash::configDash(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::configDash)
{
    ui->setupUi(this);

    QSettings settings("config.ini", QSettings::IniFormat);

    QString idioma = settings.value("language").toString();

    ui->cbPaises->addItem(QIcon("://imagens/brasil_flag.png"), "Português");
    ui->cbPaises->addItem(QIcon("://imagens/eua_flag.png"), "English");
    ui->cbPaises->addItem(QIcon("://imagens/esp_flag.png"), "Español");

    if(idioma == "br")
      ui->cbPaises->setCurrentIndex(0);
    else if (idioma == "eua")
      ui->cbPaises->setCurrentIndex(1);
    else if (idioma == "esp")
      ui->cbPaises->setCurrentIndex(2);

    atualItem = ui->cbPaises->currentText();

    connect( ui->pbOk, SIGNAL(clicked()), this, SLOT(aplica())) ;
    connect( ui->pbCancel, SIGNAL(clicked()), this, SLOT(cancela()));
    connect( ui->pbOkSobre, SIGNAL(clicked()), this, SLOT(close()));

}

configDash::~configDash()
{
    delete ui;
}

void configDash::aplica()
{
     QSettings settings("config.ini", QSettings::IniFormat);

     if(ui->cbPaises->currentText() == "Português")
        settings.setValue("language", "br");
     else if(ui->cbPaises->currentText() == "English")
         settings.setValue("language", "eua");
     else if(ui->cbPaises->currentText() == "Español")
         settings.setValue("language", "esp");

     if(ui->cbPaises->currentText() != atualItem)
       accept();
     else
       reject();
}

void configDash::cancela()
{
     reject();
}
