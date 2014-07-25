#ifndef CONFIGWEAT_H
#define CONFIGWEAT_H

#include <QDialog>
#include <QNetworkReply>
#include <qjson/parser.h>

namespace Ui {
class configweat;
}

class configweat : public QDialog
{
    Q_OBJECT

public:
    explicit configweat(QWidget *parent = 0);
    ~configweat();
    QString chaveCid, nomeCidade, pais, regiao, estado, latitude, longitude, unidade, atualiza;

private:
    Ui::configweat *ui;

private slots:
    void buscaCidade();
    void parseCidade(QNetworkReply *Reply);
    void selectCity(int);
    void cancela();
    void aplicar();


};

#endif // CONFIGWEAT_H
