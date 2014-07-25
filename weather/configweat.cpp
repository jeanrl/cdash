#include "configweat.h"
#include "ui_configweat.h"

#include <QMessageBox>
#include <QDebug>

configweat::configweat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::configweat)
{
    ui->setupUi(this);

    ui->leCidade->setFocus();

    connect( ui->pbBusca, SIGNAL(clicked()), this, SLOT(buscaCidade()));
    connect( ui->pbCancel, SIGNAL(clicked()), this, SLOT(cancela()));
    connect( ui->pbOk, SIGNAL(clicked()), this, SLOT(aplicar()));

    connect(ui->cbCidades, SIGNAL(currentIndexChanged(int)), this, SLOT(selectCity(int)));

    ui->leCidade->setFocus();

}

configweat::~configweat()
{
    delete ui;
}

void configweat::buscaCidade()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(parseCidade(QNetworkReply*)));
//    manager->get(QNetworkRequest(QUrl("http://www.previsaodotempo.org/api.php?city="+cidade)));
    manager->get(QNetworkRequest(QUrl("http://apidev.accuweather.com/locations/v1/search?q="+ui->leCidade->text()+"&apikey=hAilspiKe")));

}

void configweat::parseCidade(QNetworkReply *Reply)
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

       QVariantMap wKeyMap, nomeCidadeMap, regiaoMap, paisMap, estadoMap, geoPositionMap;

       for(int i = 0;i < result.size()-1;i++)
       {
           wKeyMap = result[i].toMap();
           chaveCid   =  wKeyMap["Key"].toString();

           nomeCidadeMap = result[i].toMap();
           nomeCidade = nomeCidadeMap["EnglishName"].toString();

           regiaoMap = nomeCidadeMap["Region"].toMap();
           regiao = regiaoMap["EnglishName"].toString();

           paisMap = nomeCidadeMap["Country"].toMap();
           pais = paisMap["EnglishName"].toString();

           estadoMap = nomeCidadeMap["AdministrativeArea"].toMap();
           estado = estadoMap["ID"].toString();

           geoPositionMap = nomeCidadeMap["GeoPosition"].toMap();
           latitude = geoPositionMap["Latitude"].toString();
           longitude = geoPositionMap["Longitude"].toString();

           ui->cbCidades->addItem(nomeCidade+", "+estado+", "+pais+", "+regiao+", "+latitude+", "+longitude+", "+chaveCid);
       }

//       ui->cbCidades->setCurrentIndex(0);
       ui->cbCidades->update();

    }

    Reply->close();
}

void configweat::selectCity(int indice)
{
    QRegExp strResult(",");
    QString pegaDados = ui->cbCidades->itemText(indice);
    QStringList separa = pegaDados.split(strResult);

    ui->lcidade->setText(separa[0]);
    ui->lpais->setText(separa[2]);
    ui->lestado->setText(separa[1]);
    ui->llatitude->setText(separa[4]);
    ui->llongitude->setText(separa[5]);
}


void configweat::cancela()
{
    reject();
}

void configweat::aplicar()
{

    QRegExp strResult(",");
    QString pegaDados = ui->cbCidades->itemText(ui->cbCidades->currentIndex());
    QStringList separa = pegaDados.split(strResult);
    nomeCidade = separa[0];
    pais = separa[2];
    estado = separa[1];
    latitude = separa[4];
    longitude = separa[5];
    chaveCid = separa[6];

    ui->lcidade->setText(nomeCidade);
    ui->lpais->setText(pais);
    ui->lestado->setText(estado);
    ui->llatitude->setText(latitude);
    ui->llongitude->setText(longitude);

    if(ui->rbCelsius->isChecked())
       unidade = "C";
    else
       unidade = "F";

    if(ui->rbatuNornal->isChecked())
       atualiza = "S";
    else
       atualiza = "N";

    accept();
}
