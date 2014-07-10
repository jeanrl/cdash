#include "favoritos.h"
#include "ui_favoritos.h"
#include <QBoxLayout>
#include <QSettings>
#include <QDir>
#include <QSet>
#include <QToolTip>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDebug>

favoritos::favoritos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::favoritos)
{
    ui->setupUi(this);

    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    ui->pb1->setTipo(jbotao::retangulo);
    ui->pb2->setTipo(jbotao::retangulo);
    ui->pb3->setTipo(jbotao::retangulo);
    ui->pb4->setTipo(jbotao::retangulo);
    ui->pb5->setTipo(jbotao::retangulo);
    ui->pb6->setTipo(jbotao::retangulo);
    ui->pb7->setTipo(jbotao::retangulo);
    ui->pb8->setTipo(jbotao::retangulo);
    ui->pb9->setTipo(jbotao::retangulo);
    ui->pb10->setTipo(jbotao::retangulo);
    ui->pb11->setTipo(jbotao::retangulo);
    ui->pb12->setTipo(jbotao::retangulo);
    ui->pb13->setTipo(jbotao::retangulo);
    ui->pb14->setTipo(jbotao::retangulo);
    ui->pb15->setTipo(jbotao::retangulo);
    ui->pb16->setTipo(jbotao::retangulo);

//    layoutB->setAlignment(Qt::AlignTop);

    hideButtons();

    totalBotoes = 0;

    QSettings settings("config.ini", QSettings::IniFormat);

    QString plataforma = settings.value("plataforma").toString();

    QGridLayout *layout = new QGridLayout;
    layout->setAlignment(Qt::AlignLeft);

    setLayout(layout);

    setAcceptDrops(true);



/*
    createList();
    findInPath();
*/
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

    ev->accept();

}

void favoritos::createList()
{

}

void favoritos::findInPath()
{

     QString xdgDataDirs;
     char *xdgDataDirsEnv = getenv("XDG_DATA_DIRS");

     if(xdgDataDirsEnv != NULL)
     {
        xdgDataDirs = xdgDataDirsEnv;
     }
     else
     {
        xdgDataDirs = "/usr/local/share/:/usr/share/";
     }

     QStringList folderSplit = xdgDataDirs.split(':');
     QStringList folders;

     QDir dir;

     for(int countDirs = 0;  countDirs < folderSplit.size(); ++countDirs)
     {
         if(folderSplit[countDirs].right(1) != "/")
            folderSplit[countDirs] = folderSplit[countDirs] + "/applications";
         else
            folderSplit[countDirs] = folderSplit[countDirs] + "applications";

         dir.setPath(folderSplit[countDirs]);
         if(dir.exists())
            folders << folderSplit[countDirs];

     }

     folders.removeDuplicates();

     QList<QString> listFavApps;

//Escritório
     listFavApps.append("libreoffice-writer.desktop");
     listFavApps.append("libreoffice-calc.desktop");
     listFavApps.append("libreoffice-impress.desktop");
     listFavApps.append("libreoffice-draw.desktop");
/*
     if(plataforma == "xfce")
     {
      xfce4-settings-manager
     }
*/

//Gráficas
     listFavApps.append("gimp.desktop");
     listFavApps.append("inkscape.desktop");
     listFavApps.append("xsane.desktop");
//Internet
     listFavApps.append("google-chrome.desktop");
     listFavApps.append("firefox.desktop");
     listFavApps.append("brasero.desktop");
     listFavApps.append("chromium-browser.desktop");
//Multimídia
     listFavApps.append("vlc.desktop");
     listFavApps.append("vlc.desktop");

//xdg-open detectDE
/*
     if(plataforma == "xfce")
     {
      xfce4-settings-manager
     }

*/
     listFavApps.append("configurações");
     listFavApps.append("calculadora");
     listFavApps.append("gerenciador de arquivos");
     listFavApps.append("terminal");
     listFavApps.append("tocador de audio/vídeo");
     listFavApps.append("k3b");



     for(int countItens = 0;  countItens <= 12; ++countItens)
     {

         foreach(const QString& path, folders)
         {
             QDir dir(path);

             QFileInfoList fileInfos = dir.entryInfoList(QStringList("*.desktop"), QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files);

             foreach(const QFileInfo& fileInfo, fileInfos)
             {
                  if(listFavApps.at(countItens) == fileInfo.fileName())
                     readFile(fileInfo.filePath());
             }
         }
     }
}

void favoritos::readFile(QString fileRead)
{

     QString nome, comando, nomeIcone;
     QPixmap iconeapp;
     QIcon pegaIcon;

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
                  iconeapp.load(nomeIcone+".xpm");
            }
            else
               iconeapp.load(nomeIcone+".png");
         }
     }

     if(nomeIcone != "")
     {
        iconeapp = iconeapp.scaled(32,32, Qt::KeepAspectRatio, Qt::FastTransformation);
     }
     else
     {
         pegaIcon = QIcon::fromTheme("application-x-executable");
         iconeapp = pegaIcon.pixmap(QSize(32,32));
     }

     createButton(nome, comando, iconeapp);

}

void favoritos::createButton(QString nome, QString comando, QPixmap icone)
{
    numBotao++;
    totalBotoes++;

    if(numBotao == 1)
    {
       ui->pb1->setIcon(icone);
       ui->pb1->setVisible(true);

//       QToolTip::showText( ui->pb1->mapToGlobal( QPoint( 0, 0 ) ), "Teste" );
    }
    else if(numBotao == 2)
    {
        ui->pb2->setIcon(icone);
//        ui->pb2->setToolTip(comando);
        ui->pb2->setVisible(true);
    }
    else if(numBotao == 3)
    {
        ui->pb3->setIcon(icone);
        ui->pb3->setVisible(true);
//        ui->pb3->setToolTip(comando);
    }
    else if(numBotao == 4)
    {
        ui->pb4->setIcon(icone);
        ui->pb4->setVisible(true);
//        ui->pb4->setToolTip(comando);
    }
    else if(numBotao == 5)
    {
        ui->pb5->setIcon(icone);
        ui->pb5->setVisible(true);
//        ui->pb5->setToolTip(comando);
    }
    else if(numBotao == 6)
    {
        ui->pb6->setIcon(icone);
        ui->pb6->setVisible(true);
//        ui->pb6->setToolTip(comando);
    }
    else if(numBotao == 7)
    {
        ui->pb7->setIcon(icone);
        ui->pb7->setVisible(true);
//        ui->pb7->setToolTip(comando);
    }
    else if(numBotao == 8)
    {
        ui->pb8->setIcon(icone);
        ui->pb8->setVisible(true);
//        ui->pb8->setToolTip(comando);
    }
    else if(numBotao == 9)
    {
        ui->pb9->setIcon(icone);
        ui->pb9->setVisible(true);
//        ui->pb9->setToolTip(comando);
    }
    else if(numBotao == 10)
    {
        ui->pb10->setIcon(icone);
        ui->pb10->setVisible(true);
//        ui->pb10->setToolTip(comando);
    }
    else if(numBotao == 11)
    {
        ui->pb11->setIcon(icone);
        ui->pb11->setVisible(true);
//        ui->pb11->setToolTip(comando);
    }
    else if(numBotao == 12)
    {
        ui->pb12->setIcon(icone);
        ui->pb12->setVisible(true);
//        ui->pb12->setToolTip(comando);
    }
    else if(numBotao == 13)
    {
        ui->pb13->setIcon(icone);
        ui->pb13->setVisible(true);
//        ui->pb13->setToolTip(comando);
    }
    else if(numBotao == 14)
    {
        ui->pb14->setIcon(icone);
        ui->pb14->setVisible(true);
//        ui->pb14->setToolTip(comando);
    }
    else if(numBotao == 15)
    {
        ui->pb15->setIcon(icone);
        ui->pb15->setVisible(true);
//        ui->pb15->setToolTip(comando);
    }
    else if(numBotao == 16)
    {
        ui->pb16->setIcon(icone);
        ui->pb16->setVisible(true);
//        ui->pb16->setToolTip(comando);
    }

}

void favoritos::hideButtons()
{
    QList<jbotao*> buttons = findChildren<jbotao*>();
    foreach (jbotao * button, buttons) {
       button->setVisible(false);
    }
}

void favoritos::geraLista()
{
    QList<QString> listFavApps;

//Escritório
    listFavApps.append("libreoffice-writer.desktop");
    listFavApps.append("libreoffice-calc.desktop");
    listFavApps.append("libreoffice-impress.desktop");
    listFavApps.append("libreoffice-draw.desktop");
//Gráficas
    listFavApps.append("gimp.desktop");
    listFavApps.append("inkscape.desktop");
    listFavApps.append("xsane.desktop");
//Internet
    listFavApps.append("google-chrome.desktop");
    listFavApps.append("firefox.desktop");
    listFavApps.append("brasero.desktop");
    listFavApps.append("chromium-browser.desktop");
//Multimídia
    listFavApps.append("vlc.desktop");
    listFavApps.append("vlc.desktop");

//xdg-open detectDE
/*
    while(true)
    {




    }

    if(plataforma == "xfce")
    {
     xfce4-settings-manager
    }
*/
}

