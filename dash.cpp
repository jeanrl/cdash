#include "dash.h"

dash::dash(QWidget *parent) :
    QWidget(parent)
{
}

dash::~dash()
{

}

QRect dash::getPosicao() const
{
    return posicao;
}

void dash::setPosicao(const QRect &value)
{
    posicao = value;
}


