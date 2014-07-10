#ifndef JBOTAO_H
#define JBOTAO_H

#include <QPushButton>
#include <QPainter>
#include <QPixmap>
#include <QEvent>
#include "jtooltip.h"

class jbotao : public QPushButton
{
    Q_OBJECT
public:
    explicit jbotao(QWidget *parent = 0);
    ~jbotao();
    //formato do botão
    //os nomes falam por si
    enum tipo
    {
        circular = 1,
        retangulo = 2
    };
    //Para botẽos pré-definidos
    //os nomes falam por si
    enum models
    {
        powerdown = 1,
        reboot = 2,
        config = 3,
        exit = 4,
        custom = 5
    };
    //tipo de comando no auto comando:
    //programCmd = executar um executável (óbvio né?! hehe)
    //customCmd = executor arquivos, exemplo: abrir uma planilha, um pdf e tudo com o programa padrão do SO
    //Sem definir nada fica livre para usar os Signals/Slots
    enum tpCommand
    {
        programCmd = 1,
        customCmd = 2
    };

    void setIcon(const QPixmap pxm);
    void setTipo(tipo wtipo);
    tipo getTipo();
    void setModel(models wmodel);
    models getModel();
    void setAutocommand(bool ac);
    bool getAutocommand();
    void setCommandRun(QString cmd);
    QString getCommandRun();
    void setTypeCommand(tpCommand tpcmd);
    tpCommand getTypeCommand();

private:
    QPixmap fundo;
    QPixmap fundo_padrao;
    QPixmap m_pixmap;
    jbotao::tipo forma;

    jbotao::models modelo;
    //true: o programa seguindo o padrão tpCommand
    //false: uso padrão Signals/Slots
    bool autoCommand = false;
    //Comando que vai executar quando estiver autoCommando = true
    QString commandRun;
    //Sem uso ainda, mas será usado no futuro
    QStringList argumentsCommand;
    //explicado acima
    tpCommand wtpcmd;

protected:
    void paintEvent(QPaintEvent *ev);

private slots:

protected slots:
     void enterEvent(QEvent *ev);
     void leaveEvent(QEvent* ev);
     void mousePressEvent(QMouseEvent *ev);
     void mouseReleaseEvent(QMouseEvent *  ev);
     void mouseMoveEvent(QMouseEvent *ev);

signals:

public slots:

};

#endif // JBOTAO_H
