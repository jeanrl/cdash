#ifndef DASH_H
#define DASH_H

#include <QWidget>

class dash : public QWidget
{
    Q_OBJECT

public:
    explicit dash(QWidget *parent = 0);
    ~dash();

    QRect getPosicao() const;
    void setPosicao(const QRect &value);

private:
    QRect posicao;

signals:

public slots:

};

#endif // DASH_H
