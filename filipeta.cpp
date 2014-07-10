#include "filipeta.h"

#include <QPainter>

filipeta::filipeta(QWidget *parent) :
    QWidget(parent)
{

    setWindowFlags(Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_X11NetWmWindowTypeDock, true);
    setAttribute(Qt::WA_TranslucentBackground);
/*
    setMinimumSize(100,320);
    setMaximumSize(100,320);
*/

    setMinimumSize(100,300);
    setMaximumSize(100,300);

    bgflp.load("://imagens/filipeta_fundo.png");

}

filipeta::~filipeta()
{

}

void filipeta::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
    painter.drawPixmap(QPoint(0,0),bgflp);

}
