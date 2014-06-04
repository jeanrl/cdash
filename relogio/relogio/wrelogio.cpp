#include "wrelogio.h"

wrelogio::wrelogio(QWidget *parent)
    : QWidget(parent)
{

    setMaximumWidth(231);
    setMaximumHeight(237);

    bg.load("://imagens/clock.png");

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);

}

wrelogio::~wrelogio()
{

}

void wrelogio::paintEvent(QPaintEvent *)
{

    QTime hora = QTime::currentTime();

    if((hora.toString("hh a").left(2).toInt()  >= 1) && (hora.toString("hh a").left(2).toInt() <= 3))
    {
       angulo_hor = ( 90 - (hora.toString("hh a").left(2).toInt() * 30) );
    }
    else
    {
       angulo_hor = ((hora.toString("hh a").left(2).toInt() - 3) * 30) * -1;
    }

    if((hora.toString("mm a").left(2).toInt()  >= 1) && (hora.toString("mm a").left(2).toInt() <= 15))
    {
       angulo_min = ( 90 - (hora.toString("mm a").left(2).toInt() * 6) );
    }
    else
    {
       angulo_min = ((hora.toString("mm a").left(2).toInt() - 15) * 6) * -1;
    }

    if((hora.toString("ss a").left(2).toInt()  >= 1) && (hora.toString("ss a").left(2).toInt() <= 15))
    {
       angulo_seg = ( 90 - (hora.toString("ss a").left(2).toInt() * 6) );
    }
    else
    {
       angulo_seg = ((hora.toString("ss a").left(2).toInt() - 15) * 6) * -1;
    }


    QPainter painter(this);


    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
    painter.drawPixmap(QPoint(0,0),bg);

    //Hora

    QPen line_hora;

    line_hora.setWidth(12);
    line_hora.setColor(Qt::white);
    line_hora.setCapStyle(Qt::RoundCap);

    painter.setPen(line_hora);

    QLineF angleline_hora;
    angleline_hora.setP1(QPointF(115,115));
    angleline_hora.setAngle(angulo_hor);
    angleline_hora.setLength(50);
    painter.drawLine(angleline_hora);

    line_hora.setWidth(3);
    line_hora.setColor(Qt::darkGreen);
    line_hora.setCapStyle(Qt::RoundCap);

    painter.setPen(line_hora);

    QLineF interhora;
    interhora.setP1(QPointF(115,115));
    interhora.setAngle(angulo_hor);
    interhora.setLength(44);

    painter.drawLine(interhora);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    painter.drawEllipse(QPointF(115,115), 5, 5);

    //Minuto

    QPen line_min;

    line_min.setWidth(8);
    line_min.setColor(Qt::white);
    line_min.setCapStyle(Qt::RoundCap);

    painter.setPen(line_min);

    QLineF angleline_min;

    angleline_min.setP1(QPointF(115,115));
    angleline_min.setAngle(angulo_min);
    angleline_min.setLength(75);
    painter.drawLine(angleline_min);

    line_min.setWidth(1);
    line_min.setColor(Qt::darkGreen);
    line_min.setCapStyle(Qt::RoundCap);

    painter.setPen(line_min);

    QLineF interminut;
    interminut.setP1(QPointF(115,115));
    interminut.setAngle(angulo_min);
    interminut.setLength(70);

    painter.drawLine(interminut);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    painter.drawEllipse(QPointF(115,115), 1, 1);

    //segundos

    painter.setPen(QPen(Qt::red,1));

    QLineF angleline_seg;
    angleline_seg.setP1(QPointF(115,115));
    angleline_seg.setAngle(angulo_seg);
    angleline_seg.setLength(90);

    painter.drawLine(angleline_seg);

    painter.end();

}
