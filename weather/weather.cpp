#include "weather.h"
#include "ui_weather.h"

#include <QSettings>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <qjson/parser.h>
#include <QMovie>
#include <QMessageBox>
#include <QDebug>

weather::weather(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::weather)
{
    ui->setupUi(this);

    setMaximumWidth(220);
    setMaximumHeight(400);

    ui->lcidade->setText("");
    ui->ltemperatura->setText("");
    ui->linfo->setText("");

    QSettings settings("config.ini", QSettings::IniFormat);

    settings.beginGroup("Weather");
    chaveCidade = settings.value("chave").toString();
    nomeCidade = settings.value("cidade").toString();
    unidade = settings.value("unidade").toString();
    settings.endGroup();

    if(chaveCidade != "")
    {
       consultaWeather(chaveCidade);
    }

}

weather::~weather()
{
    delete ui;
}

void weather::mousePressEvent(QMouseEvent *ev)
{
    if(ev->type() == QEvent::QEvent::MouseButtonPress)
    {
       showConfig();
    }

    QWidget::mousePressEvent(ev);
}

void weather::showConfig()
{
    configweat * wndConfig = new configweat;

    wndConfig->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    wndConfig->setAttribute(Qt::WA_X11NetWmWindowTypeToolBar);

    wndConfig->setStyleSheet("background-image: url(://imagens/fundo_branco.png)");

    wndConfig->setMinimumSize(1,1);
    wndConfig->setMaximumSize(451,372);

    QRect ponto_ini = this->frameGeometry();

    QPropertyAnimation *animation = new QPropertyAnimation(wndConfig, "geometry");
    animation->setDuration(500);
    animation->setStartValue(QRect(ponto_ini.right()-50, ponto_ini.top(),10,100));
    animation->setEndValue(QRect(ponto_ini.right()+12, ponto_ini.top(),451,372));
    animation->setEasingCurve(QEasingCurve::OutElastic);
    animation->start();

    if(wndConfig->exec() == QDialog::Accepted)
    {
       chaveCidade = wndConfig->chaveCid;
       nomeCidade = wndConfig->nomeCidade;
       unidade = wndConfig ->unidade;
       atualiza = wndConfig->atualiza;
       delete wndConfig;
       consultaWeather(chaveCidade);
       QSettings settings("config.ini", QSettings::IniFormat);
       settings.beginGroup("Weather");
       settings.setValue("chave", chaveCidade);
       settings.setValue("cidade", nomeCidade);
       settings.setValue("unidade", unidade);
       settings.setValue("update", atualiza);
    }

}

void weather::consultaWeather(QString chaveCidade)
{
    /*
    QMovie *movie = new QMovie("://weather/imagens/loading.gif");
    QLabel *processLabel = new QLabel(this);
    processLabel->setAlignment(Qt::AlignHCenter);
    processLabel->setMovie(movie);
    movie->start();
*/
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(parseJson(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl("http://apidev.accuweather.com/currentconditions/v1/"+chaveCidade+".json?language=en&apikey=hAilspiKe")));

    QGraphicsOpacityEffect *opacity = new QGraphicsOpacityEffect;
    QPropertyAnimation *anim = new QPropertyAnimation( opacity, "opacity" );
    ui->limagem->setGraphicsEffect(opacity);
    anim->setDuration( 1000 );
    anim->setStartValue( 1.0 );
    anim->setEndValue( 0.0 );
    anim->setEasingCurve( QEasingCurve::InCubic );
    anim->start(QAbstractAnimation::DeleteWhenStopped);
    connect(anim, SIGNAL(finished()), this, SLOT(desapearBackground()));
}

void weather::parseJson(QNetworkReply *Reply)
{
     if(Reply->isOpen())
     {
        QJson::Parser parser;
        bool ok;
        QByteArray json = Reply->readAll();

        QList<QVariant> result = parser.parse (json, &ok).toList();

        if(!ok)
        {
           QMessageBox msgBox;
           msgBox.setWindowFlags(Qt::Tool | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
           msgBox.setWindowTitle("Cláudia Dash");
           msgBox.setWindowIcon(QIcon(QPixmap("://imagens/claudia2.png")));
           msgBox.setIcon(QMessageBox::Critical);
           msgBox.setText(tr("Ocorreu um erro inesperado"));
           msgBox.setInformativeText(tr("e por isso não conseguimos captar os dados, tente mais tarde."));
           msgBox.setStandardButtons(QMessageBox::Ok);
           exit (1);
        }

        QVariantMap dadosMap, temperaturaMap;

        dadosMap = result[0].toMap();
        imgTempo = dadosMap["WeatherIcon"].toInt();
        eDia = dadosMap["IsDayTime"].toBool();

        if(unidade == "C")
        {
           temperaturaMap = dadosMap["Temperature"].toMap();
           temperaturaMap = temperaturaMap["Metric"].toMap();
           temperatura =  temperaturaMap["Value"].toString();
        }
        else if(unidade == "F")
        {
           temperaturaMap = dadosMap["Temperature"].toMap();
           temperaturaMap = temperaturaMap["Imperial"].toMap();
           temperatura = temperaturaMap["Value"].toString();
        }

        mostraTemp();
     }

     Reply->close();
}

void weather::desapearBackground()
{
    ui->limagem->setVisible(false);
}

void weather::mostraTemp()
{

    escolheimg();

    QLabel *imgFlui =  new QLabel(this);
    imgFlui->setPixmap(bg);
    imgFlui->show();

    QPropertyAnimation *animation = new QPropertyAnimation(imgFlui, "pos");
    animation->setEasingCurve(QEasingCurve::OutQuad);

    animation->setDuration(1400);
    animation->setStartValue(QPoint(-200, (height())));
    animation->setEndValue(QPoint(25,(height() / 2)-200));

    animation->start();

//    ui->limagem->setPixmap(bg);

    ui->lcidade->setText(nomeCidade);
    QGraphicsDropShadowEffect* effect	= new QGraphicsDropShadowEffect();
    effect->setXOffset(-3);
    effect->setYOffset(3);
    effect->setBlurRadius(5);
    effect->setColor(Qt::black);
    QGraphicsDropShadowEffect* effect2	= new QGraphicsDropShadowEffect();
    effect2->setXOffset(-3);
    effect2->setYOffset(3);
    effect2->setBlurRadius(5);
    effect2->setColor(Qt::black);
    ui->lcidade->setGraphicsEffect(effect);
    if(unidade == "C")
       ui->ltemperatura->setText(temperatura+"ºC");
    else
        ui->ltemperatura->setText(temperatura+"ºF");

    ui->ltemperatura->setGraphicsEffect(effect2);
    ui->linfo->setText(situ);
}

void weather::escolheimg()
{
    if((imgTempo == 1) || (imgTempo == 33))
    {
        if(eDia)
        {
           bg.load("://weather/imagens/ensolarado.png");
           situ=tr("Ensolarado");
        }
        else
        {
           bg.load("://weather/imagens/enluarado.png");
           situ=tr("Céu Claro");
        }
    }
    else if(imgTempo == 2 || (imgTempo == 3) || (imgTempo == 4) || (imgTempo == 34) || (imgTempo == 35) || (imgTempo == 36))
    {
         if(eDia)
         {
            bg.load("://weather/imagens/parcial_ensolarado.png");
         }
         else
         {
            bg.load("://weather/imagens/parcial_enluarado.png");
         }
         situ=tr("Algumas Nuvens");
    }
    else if(imgTempo == 5 || (imgTempo == 37) || (imgTempo == 21))
    {
         if(eDia)
         {
            bg.load("://weather/imagens/nebuloso_dia.png");
         }
         else
         {
            bg.load("://weather/imagens/nebuloso_noite.png");
         }
         situ=tr("Nebuloso");
    }
    else if(imgTempo == 6 || (imgTempo == 38))
    {
         if(eDia)
         {
            bg.load("://weather/imagens/nublado_dia.png");
         }
         else
         {
            bg.load("://weather/imagens/nublado_noite.png");
         }
         situ=tr("Nublado");
    }
    else if(imgTempo == 7  || (imgTempo == 8))
    {
         bg.load("://weather/imagens/totalmente_nublado.png");
         situ=tr("Nuvens Pesadas");
    }
    else if(imgTempo == 12 || (imgTempo == 13) || (imgTempo == 14) || (imgTempo == 18) || (imgTempo == 18) || (imgTempo == 20) || (imgTempo == 21))
    {
         bg.load("://weather/imagens/chuvas.png");
         situ=tr("Chuvas");
    }
    else if((imgTempo == 13) || (imgTempo == 14) || (imgTempo == 39) || (imgTempo == 40))
    {
        if(eDia)
        {
           bg.load("://weather/imagens/parcial_nublado_chuvas_dia.png");
        }
        else
        {
           bg.load("://weather/imagens/parcial_nublado_chuvas_noite.png");
        }
        situ=tr("Parcialmente Nublado com Chuvas");
    }
    else if((imgTempo == 15) || (imgTempo == 16) || (imgTempo == 17) || (imgTempo == 19) || (imgTempo == 43) || (imgTempo == 42) || (imgTempo == 41))
    {
         bg.load("://weather/imagens/tempestade.png");
         situ=tr("Tempestade");
    }
    else if((imgTempo == 22) || (imgTempo == 23) || (imgTempo == 44))
    {
         bg.load("://weather/imagens/tempestade.png");
         situ=tr("Neve");
    }
    else if((imgTempo == 24) || (imgTempo == 26) || (imgTempo == 44))
    {
         bg.load("://weather/imagens/tempestade.png");
         situ=tr("Granizo");
    }
    else if((imgTempo == 25) || (imgTempo == 29) || (imgTempo == 44))
    {
         bg.load("://weather/imagens/tempestade.png");
         situ=tr("Chuva e Neve");
    }

}
