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

#include <QApplication>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QTranslator>

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

    startFPT = false;
    ligaInterf();

    createCDWindow();

    m_filipeta = new filipeta(this);

    startKill = false;

    tmMataFilipeta = new QTimer(this);
    connect(tmMataFilipeta, SIGNAL(timeout()), this, SLOT(mataFilipeta()));

}

CDash::~CDash()
{
    XDeleteProperty(QX11Info::display(), winId(),
                    XInternAtom(QX11Info::display(), "_KDE_NET_WM_BLUR_BEHIND_REGION", False));

    XDeleteProperty(QX11Info::display(), winId(),
                    XInternAtom(QX11Info::display(), "_NET_WM_STRUT_PARTIAL", False));

    XDeleteProperty(QX11Info::display(), winId(),
                    XInternAtom(QX11Info::display(), "_NET_WM_DESKTOP", False));

    delete m_interf;
    delete m_interfProp;
    delete m_filipeta;
    delete tmMataFilipeta;
}

void CDash::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
    painter.drawPixmap(QPoint(0,0),bg);
}

void CDash::mouseMoveEvent(QMouseEvent *e)
{
    if(e->x() == 0)
    {
       if(!vsvFilipeta)
           createFP();
    }
    else
    {
       if(vsvFilipeta && !startKill)
       {
          startKill = true;
          tmMataFilipeta->start(1500);
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
               QCoreApplication::exit();        }
    }
}

void CDash::ligaInterf()
{
     m_interf = new QDBusInterface("org.freedesktop.UPower", "/org/freedesktop/UPower", "org.freedesktop.UPower",
                                   QDBusConnection::systemBus());

     if(!m_interf->isValid())
     {
        m_interf = 0;
     }

     m_interfProp = new QDBusInterface("org.freedesktop.UPower", "/org/freedesktop/UPower",
                                       "org.freedesktop.DBus.Properties", QDBusConnection::systemBus());
     if(!m_interfProp->isValid()) {
        m_interf = 0;
        m_interfProp = 0;
     }

     m_interf = new QDBusInterface("org.freedesktop.UPower", "/org/freedesktop/UPower", "org.freedesktop.UPower",
                                     QDBusConnection::systemBus());

     if(!m_interf->isValid())
     {
        m_interf = 0;
     }

     m_interfProp = new QDBusInterface("org.freedesktop.UPower", "/org/freedesktop/UPower",
                                         "org.freedesktop.DBus.Properties", QDBusConnection::systemBus());
     if(!m_interfProp->isValid()) {
        m_interf = 0;
        m_interfProp = 0;
     }

}

void CDash::createCDWindow()
{

    QRect screenAvaliable = QApplication::desktop()->availableGeometry(0);
    QRect screenTotal = QApplication::desktop()->screenGeometry();

    if(screenAvaliable.height() < screenTotal.height())
    {
/*       if(screenAvaliable.y() > screenTotal.y())
          qDebug() << "TOP";
       else
          qDebug() << "BOTTOM"; */
    }

    setMinimumSize(250, screenAvaliable.height());
    setMaximumSize(250, screenAvaliable.height());

    setGeometry(QRect(0, 0, 250, screenAvaliable.height()));
    setFixedHeight(screenAvaliable.height());

    this->move(0, screenAvaliable.y());

    QPropertyAnimation *animation = new QPropertyAnimation(this, "size");
    animation->setDuration(400);
    animation->setStartValue(QSize(0, 26));
    animation->setEndValue(QSize(250, screenAvaliable.height()));
    animation->start();

    wrelogio *relogio = new wrelogio(this);
    wcronometro *wcron = new wcronometro(this);

    favoritos *wfav = new favoritos(this);

    weather *weat = new weather(this);

    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->setAlignment(Qt::AlignTop);

    layout->addWidget(relogio, 1, 0);
    layout->addWidget(wcron);
    layout->addWidget(wfav);
    layout->addWidget(weat);


   ulong struts[12] = {};
   struts[0] = 250;
   struts[4] = 0;
   struts[5] = screenAvaliable.height()+screenAvaliable.y();

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
    if(!startFPT)
    {
       startFPT = true;

       QVBoxLayout *layoutFlp = new QVBoxLayout(m_filipeta);

       layoutFlp->setMargin(22);
       layoutFlp->setSpacing(5);

       jbotao *jbtn1 = new jbotao(m_filipeta);
       jbotao *jbtn2 = new jbotao(m_filipeta);
       jbotao *jbtn3 = new jbotao(m_filipeta);
       jbotao *jbtn4 = new jbotao(m_filipeta);

       jbtn1->setTipo(jbotao::circular);
       jbtn1->setModel(jbotao::config);
       connect( jbtn1, SIGNAL(clicked()), this, SLOT(showConfig()));

       jbtn2->setTipo(jbotao::circular);
       jbtn2->setModel(jbotao::powerdown);
       connect( jbtn2, SIGNAL(clicked()), this, SLOT(shutdownComp()));

       jbtn3->setTipo(jbotao::circular);
       jbtn3->setModel(jbotao::reboot);
       connect( jbtn3, SIGNAL(clicked()), this, SLOT(rebootComp()));

       jbtn4->setTipo(jbotao::circular);
       jbtn4->setModel(jbotao::exit);
       connect( jbtn4, SIGNAL(clicked()), this, SLOT(closeapp()));

       if(m_interf == 0)
       {
           jbtn1->setEnabled(false);
           jbtn2->setEnabled(false);
           jbtn3->setEnabled(false);
           jbtn4->setEnabled(false);
       }

       layoutFlp->addWidget(jbtn1, 1, 0);
       layoutFlp->addWidget(jbtn2);
       layoutFlp->addWidget(jbtn3);
       layoutFlp->addWidget(jbtn4);

       layoutFlp->setAlignment(Qt::AlignTop);
    }

    animFilipeta();
}

void CDash::animFilipeta()
{
    vsvFilipeta = true;

    QPropertyAnimation *animation = new QPropertyAnimation(m_filipeta, "pos");
    animation->setEasingCurve(QEasingCurve::OutQuad);

    animation->setDuration(200);
    animation->setStartValue(QPoint(-200, (height() / 2)-100));
    animation->setEndValue(QPoint(1,(height() / 2)-100));
    animation->start();

    m_filipeta->raise();
    m_filipeta->show();
}

void CDash::mataFilipeta()
{
    QPropertyAnimation *animation = new QPropertyAnimation(m_filipeta, "pos");
    animation->setEasingCurve(QEasingCurve::OutQuad);
    animation->setDuration(300);
    animation->setStartValue(QPoint(-10,(height() / 2)-100));
    animation->setEndValue(QPoint(-200, (height() / 2)-100));
    animation->start();

    m_filipeta->raise();
    m_filipeta->show();

    tmMataFilipeta->stop();
    startKill = false;
    vsvFilipeta = false;
}

void CDash::shutdownComp()
{
    QMessageBox msgBox;
    msgBox.setWindowFlags(Qt::Tool | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    msgBox.setWindowTitle("Cláudia Dash");
    msgBox.setWindowIcon(QIcon(QPixmap("://imagens/claudia2.png")));
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setText(tr("Deseja Realmente Desligar o Computador?"));
    msgBox.setInformativeText(tr("Esse procedimento irá Desligar a máquina"));
    msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Cancel);

    QPropertyAnimation *animation = new QPropertyAnimation(&msgBox, "pos");
    animation->setEasingCurve(QEasingCurve::OutQuad);

    animation->setDuration(400);
    animation->setStartValue(QPoint(50, (height() / 2)-100));
    animation->setEndValue(QPoint(250,(height() / 2)-100));
    animation->start();

    int ret = msgBox.exec();
    if(ret != QMessageBox::Ok)
        return;

    QDBusInterface interface( "org.freedesktop.ConsoleKit", "/org/freedesktop/ConsoleKit/Manager", "org.freedesktop.ConsoleKit.Manager", QDBusConnection::systemBus() );
    interface.call( "Stop" );
}

void CDash::rebootComp()
{
    QMessageBox msgBox;
    msgBox.setWindowFlags(Qt::Tool | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    msgBox.setWindowTitle("Cláudia Dash");
    msgBox.setWindowIcon(QIcon(QPixmap("://imagens/claudia2.png")));
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setText(tr("Deseja Realmente Reiniciar o Computador?"));
    msgBox.setInformativeText(tr("Esse procedimento reinicia a máquina"));
    msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Cancel);

    QPropertyAnimation *animation = new QPropertyAnimation(&msgBox, "pos");
    animation->setEasingCurve(QEasingCurve::OutQuad);

    animation->setDuration(400);
    animation->setStartValue(QPoint(50, (height() / 2)-100));
    animation->setEndValue(QPoint(250,(height() / 2)-100));
    animation->start();

    int ret = msgBox.exec();
    if(ret != QMessageBox::Ok)
        return;

    QDBusMessage response;

    QDBusInterface kdeSessionManager("org.kde.ksmserver", "/KSMServer",
                                     "org.kde.KSMServerInterface", QDBusConnection::sessionBus());

    response = kdeSessionManager.call("logout", 0, 2, 1);

    if(response.type() == QDBusMessage::ErrorMessage)
    {
       QDBusInterface interface( "org.freedesktop.ConsoleKit", "/org/freedesktop/ConsoleKit/Manager", "org.freedesktop.ConsoleKit.Manager", QDBusConnection::systemBus() );
       interface.call( "Restart" );
    }

    if(response.type() == QDBusMessage::ErrorMessage)
    {
      qWarning() << "W: " << response.errorName() << ":" << response.errorMessage();
    }
}

void CDash::closeapp()
{
    /*
    QMessageBox msgBox;
    msgBox.setWindowFlags(Qt::Tool | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    msgBox.setWindowTitle("Cláudia Dash");
    msgBox.setWindowIcon(QIcon(QPixmap("://imagens/claudia2.png")));
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setText(tr("Deseja Realmente Sair do Cláudia Dash?"));
    msgBox.setInformativeText(tr("Estamos aqui para lhe ajudar"));
    msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Cancel);

    QPropertyAnimation *animation = new QPropertyAnimation(&msgBox, "pos");
    animation->setEasingCurve(QEasingCurve::OutQuad);

    animation->setDuration(400);
    animation->setStartValue(QPoint(50, (height() / 2)-100));
    animation->setEndValue(QPoint(250,(height() / 2)-100));
    animation->start();

    int ret = msgBox.exec();
    if(ret != QMessageBox::Ok)
        return;
    */
    close();
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
    animation->setEndValue(QRect(ponto_ini.right()-15, ponto_ini.top(),350,213));
    animation->setEasingCurve(QEasingCurve::OutElastic);
    animation->start();

    wndConfig->exec();
}
