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

#include "cdash.h"

#include <QDebug>
#include <QApplication>
#include <QtGui>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPropertyAnimation>
#include <QTranslator>
#include <QGraphicsItem>

#include <QX11Info>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

CDash::CDash(QWidget *parent) :
    QWidget(parent)
{
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_X11NetWmWindowTypeDock, true);
    setAttribute(Qt::WA_TranslucentBackground);

    QCoreApplication::setApplicationName("CDash");
    QCoreApplication::setOrganizationName("Jean Softwares");

    setMouseTracking(true);

    bg.load("://imagens/fundo.png");

    createCDWindow();

    createFP();

    tmFilipeta = new QTimer(this);
    connect(tmFilipeta, SIGNAL(timeout()), this, SLOT(temporizador()));
}

CDash::~CDash()
{
    XDeleteProperty(QX11Info::display(), winId(),
                    XInternAtom(QX11Info::display(), "_KDE_NET_WM_BLUR_BEHIND_REGION", False));

    XDeleteProperty(QX11Info::display(), winId(),
                    XInternAtom(QX11Info::display(), "_NET_WM_STRUT_PARTIAL", False));

    XDeleteProperty(QX11Info::display(), winId(),
                    XInternAtom(QX11Info::display(), "_NET_WM_DESKTOP", False));
}

void CDash::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
    painter.drawPixmap(QPoint(0,0),bg);
}

void CDash::mouseMoveEvent(QMouseEvent *ev)
{

    if(ev->x() == 0)
    {
       tempConfig = 1;
       tmFilipeta->start(500);
    }
    else
    {
       if(vsvFilipeta)
       {
          tmFilipeta->stop();
          mataFilipeta();
       }
    }
}

void CDash::mousePressEvent(QMouseEvent *ev)
{
    if(ev->type() == QEvent::QEvent::MouseButtonPress)
    {
        if(ev->button() == Qt::LeftButton);
        if(ev->button() == Qt::RightButton);
        if(ev->button() == Qt::MidButton)
        {
            QMessageBox msgBox;
            msgBox.setWindowFlags(Qt::ToolTip);
            msgBox.setWindowTitle("Cláudia Dash");
            msgBox.setWindowIcon(QIcon(QPixmap("://imagens/claudia2.png")));
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setText(tr("Deseja Realmente Fechar o Cláudia Dash ?"));
            msgBox.setInformativeText(tr("Pense bem, estamos aqui para lhe ajudar :("));
            msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Cancel);
            int ret = msgBox.exec();
            if(ret == QMessageBox::Ok)
                QCoreApplication::exit();
        }
    }
}

void CDash::createCDWindow()
{
    QRect screen = QApplication::desktop()->availableGeometry(0);

    setMinimumSize(0, 0);
    setMaximumSize(250, screen.height());

    QRect rectDash = QRect(0, 0, 250, screen.height());
    setGeometry(rectDash);
    setFixedHeight(screen.height());

    this->move(0, 0);

    QPropertyAnimation *animation = new QPropertyAnimation(this, "size");
    animation->setDuration(400);
    animation->setStartValue(QSize(0, 0));
    animation->setEndValue(QSize(250, screen.height()));
    animation->start();

    wrelogio *relogio = new wrelogio(this);
    wcronometro *wcron = new wcronometro(this);

    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(relogio, 1, 0);

    layout->addWidget(wcron);

    layout->setAlignment(Qt::AlignTop);

    ulong struts[12] = {};
    struts[0] = 250;
    struts[4] = screen.left();
    struts[5] = screen.y() + screen.height();

    static Atom desktopAtom = XInternAtom(QX11Info::display(), "_NET_WM_DESKTOP", False);
    ulong data[1];
    data[0] = 0xFFFFFFFF;
    XChangeProperty(QX11Info::display(), winId(), desktopAtom, desktopAtom, 32, PropModeReplace, (unsigned char *) data, 1);

    static Atom strutAtom = XInternAtom(QX11Info::display(), "_NET_WM_STRUT_PARTIAL", False);
    XChangeProperty(QX11Info::display(), winId(), strutAtom, XA_CARDINAL, 32, PropModeReplace, (unsigned char *) struts, 12);

    ulong strutBlur[4] = {};
    strutBlur[0] = 0;
    strutBlur[1] = 0;
    strutBlur[2] = width();
    strutBlur[3] = height();

    XChangeProperty(QX11Info::display(), winId(), XInternAtom(QX11Info::display(), "_KDE_NET_WM_BLUR_BEHIND_REGION", False),
                    XA_CARDINAL, 32, PropModeReplace, reinterpret_cast<const unsigned char*>(&strutBlur), 4);

    show();

}

void CDash::createFP()
{
    flpConfig = new QWidget;

    flpConfig->setWindowFlags(Qt::WindowStaysOnTopHint);
    flpConfig->setAttribute(Qt::WA_X11NetWmWindowTypeDock, true);
    flpConfig->setAttribute(Qt::WA_TranslucentBackground);

    QGridLayout *gld = new QGridLayout(flpConfig);

    QPixmap bkgnd("://imagens/filipeta.png");

    QLabel *image = new QLabel(flpConfig);
    image->setPixmap(bkgnd);
    image->setMask(bkgnd.mask());

    gld->addWidget(image);

    flpConfig->setMinimumSize(10,10);
    flpConfig->setMaximumSize(200,200);
}

void CDash::temporizador()
{

    if(tempConfig > 0)
    {
       if(!vsvFilipeta)
          animFilipeta();
       tempConfig++;
       if(tempConfig == 3)
       {
          tempConfig = 0;
          tmFilipeta->stop();
          mataFilipeta();
          showConfig();
       }
    }

}

void CDash::animFilipeta()
{
    vsvFilipeta = true;

    QPropertyAnimation *animation = new QPropertyAnimation(flpConfig, "pos");
    animation->setEasingCurve(QEasingCurve::OutQuad);

    animation->setDuration(200);
    animation->setStartValue(QPoint(-200, height() / 2));
    animation->setEndValue(QPoint(-10,height() / 2));
    animation->start();

    flpConfig->raise();
    flpConfig->show();
}

void CDash::mataFilipeta()
{
    vsvFilipeta = false;

    QPropertyAnimation *animation = new QPropertyAnimation(flpConfig, "pos");
    animation->setEasingCurve(QEasingCurve::OutQuad);

    animation->setDuration(300);
    animation->setStartValue(QPoint(-10,height() / 2));
    animation->setEndValue(QPoint(-200, height() / 2));
    animation->start();

    flpConfig->show();
}

void CDash::showConfig()
{
    configDash * wndConfig = new configDash;

    wndConfig->setWindowFlags(Qt::WindowStaysOnTopHint);
    wndConfig->setAttribute(Qt::WA_X11NetWmWindowTypeDock, true);
    wndConfig->setAttribute(Qt::WA_TranslucentBackground);

    wndConfig->setStyleSheet("background-image: url(://imagens/fundo_branco.png)");

    wndConfig->setMinimumSize(1,1);
    wndConfig->setMaximumSize(350,213);

    QRect ponto_ini = this->frameGeometry();

    QPropertyAnimation *animation = new QPropertyAnimation(wndConfig, "geometry");
    animation->setDuration(500);
    animation->setStartValue(QRect(ponto_ini.right()-10, ponto_ini.top(),10,100));
    animation->setEndValue(QRect(ponto_ini.right(), ponto_ini.top(),350,213));
    animation->setEasingCurve(QEasingCurve::OutElastic);
    animation->start();

    wndConfig->exec();
}