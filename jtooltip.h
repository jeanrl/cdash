#ifndef JTOOLTIP_H
#define JTOOLTIP_H

#include <QWidget>

class jtooltip : public QWidget
{
    Q_OBJECT
public:
    explicit jtooltip(QWidget *parent = 0);
    virtual ~jtooltip();
    QPixmap bgttp;

protected:
    void paintEvent (QPaintEvent *);


signals:

public slots:

};

#endif // JTOOLTIP_H
