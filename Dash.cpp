#include <QApplication>

#include "Dash.h"

m_Dash::m_Dash(QObject *parent) : QObject(parent)
{
}

m_Dash::~m_Dash()
{
}

void m_Dash::setWidth(int j)
{
    width = j;
}

void m_Dash::setHeight(int j)
{
    height = j;
}
