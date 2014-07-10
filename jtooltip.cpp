#include "jtooltip.h"

#include <QPainter>

jtooltip::jtooltip(QWidget *parent) :
    QWidget(parent)
{

    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowFlags(Qt::ToolTip);
    setAttribute(Qt::WA_TranslucentBackground);

    setMinimumSize(10,20);
    setMaximumSize(200,20);

    bgttp.load("://imagens/tooltip_fundo.png");

}

jtooltip::~jtooltip()
{

}

void jtooltip::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
    painter.drawPixmap(QPoint(0,0),bgttp);

}
