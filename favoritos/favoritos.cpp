#include "favoritos.h"
#include "ui_favoritos.h"
#include <QUrl>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QProxyStyle>
#include <QTextCodec>
#include <QDebug>

favoritos::favoritos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::favoritos)
{
    ui->setupUi(this);

    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    ui->gridLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    totalBotoes  = 0;
    lineLayoute  = 0;
    colummLayout = 0;

    setAcceptDrops(true);
    setMouseTracking(true);

    QSettings settings("config.ini", QSettings::IniFormat);

    settings.beginGroup("Favoritos");

    int contBtn = settings.value("total").toInt();

    if(contBtn > 0)
    {
       desapearBackground();
       loadButtons(contBtn);
    }

    settings.endGroup();

}

favoritos::~favoritos()
{
    delete ui;
}

void favoritos::dragEnterEvent(QDragEnterEvent *ev)
{
    ev->accept();
}

void favoritos::dragLeaveEvent(QDragLeaveEvent *ev)
{
     ev->accept();
}

void favoritos::dragMoveEvent(QDragMoveEvent *ev)
{
     ev->accept();
}

void favoritos::dropEvent(QDropEvent *ev)
{
     if(numBotao == 0)
     {
        QGraphicsOpacityEffect *opacity = new QGraphicsOpacityEffect;
        QPropertyAnimation *anim = new QPropertyAnimation( opacity, "opacity" );
        ui->label->setGraphicsEffect(opacity);
        anim->setDuration( 500 );
        anim->setStartValue( 1.0 );
        anim->setEndValue( 0.0 );
        anim->setEasingCurve( QEasingCurve::InCubic );
        anim->start(QAbstractAnimation::DeleteWhenStopped);
        connect(anim, SIGNAL(finished()), this, SLOT(desapearBackground()));

     }

     if(numBotao == 16)
        return;

     detailsButton detalhes;
     QSettings settings("config.ini", QSettings::IniFormat);
     settings.setIniCodec(QTextCodec::codecForName("LATIN-1"));

     settings.beginGroup("Favoritos");

     int contBtn = settings.value("total").toInt();

     numBotao = contBtn;

     QList<QUrl> lista = ev->mimeData()->urls();
     for(int i = 0; i < lista.size(); ++i)
     {
         btn[numBotao] = new jbotao(this);
         btn[numBotao]->setMinimumSize(51,51);
         btn[numBotao]->setMaximumSize(51,51);
         btn[numBotao]->setTipo(jbotao::retangulo);
         btn[numBotao]->setAutocommand(true);

         const QString nome = lista.at(i).toLocalFile();

         QFileInfo info(nome);
         const QString ext = info.suffix().toLower();

         //se for atalho padrão significa que é um programa
         if(ext == "desktop")
         {
            detalhes = readFile(nome);
            btn[numBotao]->setIcon(detalhes.icon);
            btn[numBotao]->setTypeCommand(jbotao::programCmd);
            btn[numBotao]->setCommandRun(detalhes.command);
         }
         //se for vazio é porque é uma pasta ou
         //o caminho direto do aplicativo incluindo ele
         else if(ext == "")
         {
            QIcon icon;
            if(info.isDir())
            {
               icon = QIcon::fromTheme("folder");
               btn[numBotao]->setTypeCommand(jbotao::customCmd);
               btn[numBotao]->setCommandRun(nome);
               detalhes.meta = "folder";
            }
            else
            {
               icon = QIcon::fromTheme("application-x-executable");
               btn[numBotao]->setTypeCommand(jbotao::programCmd);
               btn[numBotao]->setCommandRun(nome);
               detalhes.meta = "application-x-executable";
            }
            btn[numBotao]->setIcon(icon.pixmap(QSize(32,32)));
            detalhes.name = nome;
            detalhes.command = "custom";
         }
         //se não for nenhum dos acimas é porque é um arquivo
         //pode ser um pdf, doc, mp3, etc, etc.
         else
         {
            detalhes = returnIcon(ext);
            detalhes.name = nome;
            detalhes.command = "custom";
            btn[numBotao]->setIcon(detalhes.icon);
            btn[numBotao]->setTypeCommand(jbotao::customCmd);
            btn[numBotao]->setCommandRun(detalhes.name);
         }

         ui->gridLayout->addWidget(btn[numBotao], lineLayoute, colummLayout);
     }

     int totalFav = numBotao + 1;

     settings.setValue("total",QString::number(totalFav));

     QString valor = detalhes.name;
     settings.setValue("btn"+QString::number(numBotao),valor);
     settings.setValue("cmd"+QString::number(numBotao),detalhes.command);
     settings.setValue("icn"+QString::number(numBotao),detalhes.meta); //coloca o meta ou nome do icone incluindo path

     settings.endGroup();

     numBotao++;

     if(numBotao == 4 || numBotao == 8 || numBotao == 12)
     {
        lineLayoute++;
        colummLayout = 0;
     }
     else
        colummLayout++;

     ev->accept();
}

void favoritos::desapearBackground()
{
     ui->label->setVisible(false);
}

detailsButton favoritos::readFile(QString fileRead)
{

     QString nome, comando, nomeIcone;
     QPixmap iconeapp;
     QIcon pegaIcon;

     detailsButton Result;

     QSettings setDesk(fileRead, QSettings::IniFormat);
     setDesk.beginGroup("Desktop Entry");

     nome = setDesk.value("name").toString();
     comando = setDesk.value("exec").toString();
     nomeIcone = setDesk.value("icon").toString();

     if (QIcon::hasThemeIcon(nomeIcone))
     {
         pegaIcon = QIcon::fromTheme(nomeIcone);
         iconeapp = pegaIcon.pixmap(QSize(32,32));
     }
     else
     {
         if(!nomeIcone.contains("/"))
            nomeIcone = "/usr/share/pixmaps/"+nomeIcone;

         if(nomeIcone.right(3) != "png" && nomeIcone.right(3) != "xpm")
         {
            if(!QFile(nomeIcone+".png").exists())
            {
               if(!QFile(nomeIcone+".xpm").exists())
                  nomeIcone = "";
               else
                  nomeIcone = nomeIcone+".xpm";
                  iconeapp.load(nomeIcone);
            }
            else
            {
               nomeIcone = nomeIcone+".png";
               iconeapp.load(nomeIcone);
            }
         }
     }

     if(nomeIcone != "")
     {
        iconeapp = iconeapp.scaled(32,32, Qt::KeepAspectRatio, Qt::FastTransformation);
        Result.meta = nomeIcone;
     }
     else
     {
         pegaIcon = QIcon::fromTheme("application-x-executable");
         iconeapp = pegaIcon.pixmap(QSize(32,32));
         Result.meta = "application-x-executable";
     }

     Result.name = nome;
     Result.command = comando;
     Result.icon = iconeapp;

     return Result;
}

void favoritos::hideButtons()
{
    QList<jbotao*> buttons = findChildren<jbotao*>();
    foreach (jbotao * button, buttons) {
       button->setVisible(false);
    }
}

detailsButton favoritos::returnIcon(const QString &ext)
{

//Pega ícone do tema padrão do SO
//para a extensão do arquivo passado

    detailsButton Result;
    QIcon icon;

    if (ext == "pdf")
    {
        icon=QIcon::fromTheme("application-pdf");
        Result.meta = "application-pdf";
    }
    else if (ext.startsWith("doc") || ext.startsWith("docx"))
    {
        icon=QIcon::fromTheme("x-office-document");
        Result.meta = "x-office-document";
    }
    else if (ext.startsWith("xls") || ext.startsWith("xlxx"))
    {
        icon=QIcon::fromTheme("x-office-spreadsheet");
        Result.meta = "x-office-spreadsheet";
    }
    else if (ext.startsWith("ppt") || ext.startsWith("pptx"))
    {
        icon=QIcon::fromTheme("x-office-presentation");
        Result.meta = "x-office-presentation";
    }
    else if (ext=="zip" || ext=="gz" || ext=="bz2" )
    {
        icon=QIcon::fromTheme("application-x-archive");
        Result.meta = "application-x-archive";
    }
    else if (ext=="png" || ext=="jpg" || ext=="gif" || ext=="svg" || ext=="bmp")
    {
        icon=QIcon::fromTheme("image-x-generic");
        Result.meta = "image-x-generic";
    }
    else if (ext=="wav" || ext=="mp3" || ext=="ogg" || ext=="wma" || ext=="aac" || ext=="ac3")
    {
        icon=QIcon::fromTheme("audio-x-generic");
        Result.meta = "audio-x-generic";
    }
    else if (ext=="avi" || ext=="mp4" || ext=="mrvb" || ext=="mkt" || ext=="mov" || ext=="rm")
    {
        icon=QIcon::fromTheme("video-x-generic");
        Result.meta = "video-x-generic";
    }
    else
    {
        QProxyStyle s;
        icon=s.standardIcon (QStyle::SP_FileIcon);
        Result.meta = "QStyle::SP_FileIcon";
    }

    //converte porque no jbotao uso QPixmap
    Result.icon = icon.pixmap(QSize(32,32));

    return Result;


/*
 * Outros Atalhos Padrões
 "application-pdf"
 "application-msword"
 "application-x-archive"
 "image-x-generic"
*/

}

void favoritos::loadButtons(int qtdaBtn)
{
     jbotao *btn[qtdaBtn];
     QPixmap iconeapp;
     QIcon icon;
     QString nome, nomeIcone, comando;

     QSettings settings("config.ini", QSettings::IniFormat);
     settings.setIniCodec(QTextCodec::codecForName("LATIN-1"));

     settings.beginGroup("Favoritos");

     for(int i=0;i<qtdaBtn;i++)
     {
         btn[i] = new jbotao(this);
         btn[i]->setMinimumSize(51,51);
         btn[i]->setMaximumSize(51,51);
         btn[i]->setTipo(jbotao::retangulo);
         btn[i]->setAutocommand(true);

         nome      = settings.value("btn"+QString::number(i)).toString();
         comando   = settings.value("cmd"+QString::number(i)).toString();
         nomeIcone = settings.value("icn"+QString::number(i)).toString();

         if(nomeIcone.contains("/"))
         {
             if(QFile(nomeIcone).exists())
             {
                iconeapp.load(nomeIcone);
             }
             iconeapp = iconeapp.scaled(32,32, Qt::KeepAspectRatio, Qt::FastTransformation);
         }
         else
         {
            icon=QIcon::fromTheme(nomeIcone);
            iconeapp = icon.pixmap(QSize(32,32));
         }

         btn[i]->setIcon(iconeapp);

         if(comando == "custom")
         {
            btn[i]->setTypeCommand(jbotao::customCmd);
            btn[i]->setCommandRun(nome);
         }
         else
         {
            btn[i]->setTypeCommand(jbotao::programCmd);
            btn[i]->setCommandRun(comando);
         }

         ui->gridLayout->addWidget(btn[i], lineLayoute, colummLayout);

         if(i == 3 || i == 7 || i == 11)
         {
            lineLayoute++;
            colummLayout = 0;
         }
         else
            colummLayout++;
     }


     settings.endGroup();

}
