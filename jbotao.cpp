#include "jbotao.h"
#include <QToolTip>
#include <QPropertyAnimation>
#include <QEvent>
#include <QMouseEvent>
#include <QProcess>
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>

jbotao::jbotao(QWidget *parent) :
    QPushButton(parent)
{

    setFixedSize(60,60);

    setMouseTracking(true);

    update();
}

jbotao::~jbotao()
{

}

void jbotao::setIcon(const QPixmap pxm)
{
     m_pixmap = pxm;
     update();
}

void jbotao::setTipo(tipo wtipo)
{
     forma = wtipo;

     if(forma == retangulo)
     {
        fundo.load("://imagens/botao_plastico_quad_solto.png");
     }
     else
     {
        fundo.load("://imagens/botao_plastico_solto2.png");
     }
}

jbotao::tipo jbotao::getTipo()
{
    return forma;
}

void jbotao::setModel(models wmodel)
{
    modelo = wmodel;

    if(modelo == powerdown)
    {
       fundo_padrao.load("://imagens/btn_default_power_down.png");
    }
    else if(modelo == reboot)
    {
       fundo_padrao.load("://imagens/btn_default_reboot.png");
    }
    else if(modelo == config)
    {
       fundo_padrao.load("://imagens/btn_default_setup.png");
    }
    else if(modelo == exit)
    {
       fundo_padrao.load("://imagens/btn_default_exit.png");
    }
    else
    {
       fundo_padrao.load("");
    }


}

jbotao::models jbotao::getModel()
{
    return modelo;
}

void jbotao::setAutocommand(bool ac)
{
    autoCommand = ac;
}

bool jbotao::getAutocommand()
{
    return autoCommand;
}

void jbotao::setCommandRun(QString cmd)
{
     commandRun = cmd;
}

QString jbotao::getCommandRun()
{
    return commandRun;
}

void jbotao::setTypeCommand(jbotao::tpCommand tpcmd)
{
    wtpcmd = tpcmd;
}

jbotao::tpCommand jbotao::getTypeCommand()
{
    return wtpcmd;
}

void jbotao::paintEvent(QPaintEvent *ev)
{

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);

    if(getModel() != custom && getModel() != NULL )
    {
       painter.drawPixmap(QPoint(5,5), fundo_padrao);
    }

    painter.drawPixmap(QPoint(0,0),fundo);

    if(getTipo() == retangulo)
      painter.drawPixmap(QPoint(9,8), m_pixmap);
    else
      painter.drawPixmap(QPoint(9,7), m_pixmap);

}

void jbotao::enterEvent(QEvent *ev)
{
    if(getTipo() == retangulo)
       fundo.load("://imagens/botao_plastico_quad_hover.png");
    else
       fundo.load("://imagens/botao_plastico_hover.png");

    QPushButton::enterEvent(ev);
}

void jbotao::leaveEvent(QEvent *ev)
{
    if(getTipo() == retangulo)
       fundo.load("://imagens/botao_plastico_quad_solto.png");
    else
       fundo.load("://imagens/botao_plastico_solto2.png");


    QPushButton::leaveEvent(ev);
}

void jbotao::mousePressEvent(QMouseEvent *ev)
{
    if(getTipo() == retangulo)
       fundo.load("://imagens/botao_plastico_quad_apertado.png");
    else
       fundo.load("://imagens/botao_plastico_apertado.png");

    if(getAutocommand())
    {
       if(wtpcmd == programCmd)
       {
          QString program = commandRun.left(commandRun.indexOf(" "));

//       QString argumentsConvert = commandRun.right(commandRun.length() - commandRun.indexOf(" "));

          QStringList argumentsCommand;
//       argumentsCommand.append(argumentsConvert);

          QProcess *roda = new QProcess(this);
//       roda->start(program, argumentsCommand);
          roda->start(program, argumentsCommand);
       }
       //vai abrir usando o programa definido como padrão
       //para a extensão do arquivo passado
       else if(wtpcmd == customCmd)
       {
           QDesktopServices::openUrl(QUrl::fromLocalFile(commandRun));
       }
    }

    QPushButton::mousePressEvent(ev);
}

void jbotao::mouseReleaseEvent(QMouseEvent *ev)
{
    if(getTipo() == retangulo)
       fundo.load("://imagens/botao_plastico_quad_hover.png");
    else
       fundo.load("://imagens/botao_plastico_hover.png");

    QPushButton::mouseReleaseEvent(ev);
}

void jbotao::mouseMoveEvent(QMouseEvent *ev)
{
     QPushButton::mouseMoveEvent(ev);
}
