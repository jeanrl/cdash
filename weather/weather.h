#ifndef WEATHER_H
#define WEATHER_H

#include <QWidget>
#include <QNetworkReply>
#include "configweat.h"

namespace Ui {
class weather;
}

class weather : public QWidget
{
    Q_OBJECT

public:
    explicit weather(QWidget *parent = 0);
    ~weather();
    QString chaveCidade, nomeCidade, pais, temperatura, unidade, situ, atualiza;
    int imgTempo;
    bool eDia;
    QPixmap bg;
    void consultaWeather(QString chaveCidade);
    void mostraTemp();
    void escolheimg();

private:
    Ui::weather *ui;

private slots:
     void showConfig();
     void parseJson(QNetworkReply *Reply);
     void desapearBackground();

protected slots:
    void mousePressEvent(QMouseEvent *ev);

};

#endif // WEATHER_H
