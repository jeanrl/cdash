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

#include <QTimer>
#include <QTime>
#include <QDebug>
#include <QPropertyAnimation>
#include <QBitmap>
#include <QProcess>

#include "widget.h"
#include "ui_widget.h"

wcronometro::wcronometro(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    timer_cro = new QTimer(this);

    _cronometro = new Cronometro(this);

    createAct();

    reseta();
}

wcronometro::~wcronometro()
{
    delete ui;
}

void wcronometro::reseta()
{
    seg = 0;
    min = 0;
    hor = 0;

    txt_hora = "00";
    txt_min  = "00";
    txt_seg  = "00";

    ui->lcdNumber->setDigitCount(8);
    ui->lcdNumber->display("00:00:00");

    playAct->setEnabled(false);
    pauseAct->setEnabled(false);

    _cronometro->ini();
}

void wcronometro::mostraBalao()
{
    if(m_balao)
      return;

    balaoMsg = new QWidget;

    balaoMsg->installEventFilter(this);

    balaoMsg->setMinimumSize(510,300);
    balaoMsg->setMaximumSize(510,300);

    balaoMsg->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    balaoMsg->setAttribute(Qt::WA_TranslucentBackground);

    QPixmap bkgnd("://cronometro/imagens/balao_pontas_verde.png");

    QLabel *image = new QLabel(balaoMsg);
    image->setPixmap(bkgnd);
    image->setScaledContents(true);

    QLabel *msg = new QLabel(balaoMsg);

    QString tarefa = _cronometro->get_tarefa();

    msg->setText(tarefa.mid(0,22)+"\n"+
                 tarefa.mid(23,23));

    msg->move(110,115);
    msg->setStyleSheet("QLabel { color : white;font: bold italic 18pt }");

    QPropertyAnimation *animation = new QPropertyAnimation(balaoMsg, "geometry");
    animation->setDuration(2000);
    animation->setStartValue(QRect(0, 0, 50, 26));
    animation->setEndValue(QRect(230, height()/2, 348, 178));
    animation->setEasingCurve(QEasingCurve::OutElastic);

    animation->start();

    balaoMsg->raise();
    balaoMsg->show();

    m_balao = true;
}

void wcronometro::contextMenuEvent()
{
    QMenu *menu = new QMenu(this);

    menu->addAction(confAct);
    menu->addAction(playAct);
    menu->addAction(pauseAct);
    menu->addAction(resetAct);

    QRect ponto_ini = this->frameGeometry();

    QPropertyAnimation *animation = new QPropertyAnimation(menu, "geometry");
    animation->setDuration(500);
    animation->setStartValue(QRect(ponto_ini.right()-10, ponto_ini.top()+10,10,100));
    animation->setEndValue(QRect(ponto_ini.right()-10, ponto_ini.top()+10,145,100));
    animation->setEasingCurve(QEasingCurve::OutElastic);
    animation->start();

    menu->exec();
}


void wcronometro::mousePressEvent(QMouseEvent *e)
{

    if(e->type() == QEvent::QEvent::MouseButtonPress)
    {
       contextMenuEvent();
    }
}

bool wcronometro::eventFilter(QObject *obj, QEvent *e)
{
    if(e->type() == QEvent::QEvent::MouseButtonPress)
    {
          this->removeEventFilter(this);
          m_balao = false;
          balaoMsg->close();
          return true;
    }
    else
    {
       return QWidget::eventFilter(obj,e);
    }
}

void wcronometro::createAct()
{
    confAct = new QAction(QIcon("://cronometro/imagens/config.png"),tr("  Configuração"), this);
    connect(confAct, SIGNAL(triggered()), this, SLOT(showConfig()));

    playAct = new QAction(QIcon("://cronometro/imagens/play.png"),tr("  Dispara"), this);
    connect(playAct, SIGNAL(triggered()), this, SLOT(dispara()));
    playAct->setEnabled(false);

    pauseAct = new QAction(QIcon("://cronometro/imagens/pause.png"),tr("  Pausa"), this);
    connect(pauseAct, SIGNAL(triggered()), this, SLOT(pausa()));
    pauseAct->setEnabled(false);

    resetAct = new QAction(QIcon("://cronometro/imagens/stop.png"),tr("  Reset"), this);
    connect(resetAct, SIGNAL(triggered()), this, SLOT(reseta()));
}

void wcronometro::showTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm:ss");

    txt_seg = time.toString("ss");

    QString junta = txt_hora+":"+txt_min+":"+txt_seg;

    ui->lcdNumber->display(junta);
}

void wcronometro::showConfig()
{
    configcron * janela = new configcron(_cronometro);

    janela->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    janela->setAttribute(Qt::WA_TranslucentBackground);
    janela->setAttribute(Qt::WA_X11NetWmWindowTypeToolBar);

    janela->setStyleSheet("background-image: url(://imagens/fundo_branco.png)");

    janela->setGeometry(frameGeometry());

    janela->setMinimumSize(1,1);
    janela->setMaximumSize(400,300);

    QRect ponto_ini = this->frameGeometry();

    QPropertyAnimation *animation = new QPropertyAnimation(janela, "pos");
    animation->setEasingCurve(QEasingCurve::OutQuad);

    animation->setDuration(500);
    animation->setStartValue(QPoint(100, ponto_ini.top()));
    animation->setEndValue(QPoint(237, ponto_ini.top()));
    animation->start();

    if(janela->exec() == QDialog::Rejected)
    {
        reseta();
    }
    else
    {
        if( (_cronometro->get_hor() > 0) || (_cronometro->get_min() > 0) || (_cronometro->get_seg() > 0) )
        {
            hor = _cronometro->get_hor();
            min = _cronometro->get_min();
            seg = _cronometro->get_seg();
            txt_hora = QString::number(_cronometro->get_hor()).rightJustified(2, '0');
            txt_min = QString::number(_cronometro->get_min()).rightJustified(2, '0');
            txt_seg = QString::number(_cronometro->get_seg()).rightJustified(2, '0');

            QString junta = txt_hora+":"+txt_min+":"+txt_seg;
            ui->lcdNumber->display(junta);
            playAct->setEnabled(true);
        }
        else
        {
            reseta();
        }
    }
}

void wcronometro::dispara()
{
    pauseAct->setEnabled(true);

    if(!cro_ini)
    {
       connect(timer_cro, SIGNAL(timeout()), this, SLOT(rodacro()));
       timer_cro->start(1000);
       cro_ini = true;
    }
    else
    {
       timer_cro->start(1000);
    }
}

void wcronometro::rodacro()
{

    if( seg == 0 )
    {
        if( min == 0)
        {
            if( hor == 0)
            {
                finaliza();
            }
            else
            {
                hor--;
                min = 59;
                seg = 59;
            }
        }
        else
        {
           min--;
           seg = 59;
        }
    }
    else
    {
        seg--;
    }

    txt_seg  = QString::number(seg).rightJustified(2, '0');
    txt_min  = QString::number(min).rightJustified(2, '0');
    txt_hora = QString::number(hor).rightJustified(2, '0');

    QString junta = txt_hora+":"+txt_min+":"+txt_seg;

    ui->lcdNumber->display(junta);
}

void wcronometro::pausa()
{
    timer_cro->stop();
}

void wcronometro::finaliza()
{
    pausa();

    QString toca;

    if(_cronometro->get_tocaaudio())
    {
       if(_cronometro->get_audio().isEmpty())
          toca = "play ./audios/balao.ogg";
       else
          toca = "play "+_cronometro->get_audio();

       QProcess *myProcess = new QProcess;
       myProcess->start(toca);
    }

    if(_cronometro->get_sinalvisual())
       mostraBalao();
}

