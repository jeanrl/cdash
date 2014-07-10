#ifndef FILIPETA_H
#define FILIPETA_H

#include <QWidget>

class filipeta : public QWidget
{
    Q_OBJECT
public:
    explicit filipeta(QWidget *parent = 0);
    virtual ~filipeta();
    QPixmap bgflp;

protected:
    void paintEvent (QPaintEvent *);


signals:

public slots:

};

#endif // FILIPETA_H
