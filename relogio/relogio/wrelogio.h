#ifndef WRELOGIO_H
#define WRELOGIO_H

#include <QWidget>
#include <QtGui>


class wrelogio : public QWidget
{
    Q_OBJECT

public:
    wrelogio(QWidget *parent = 0);
    ~wrelogio();
    int angulo_seg, angulo_hor, angulo_min, contador;

private:
    QPixmap bg;

protected:
    void paintEvent (QPaintEvent *);

};

#endif // WIDGET_H
