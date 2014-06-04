#ifndef DASH_H
#define DASH_H

#include <QObject>
#include <QString>

class m_Dash : public QObject
{
    Q_OBJECT
        public:
        explicit m_Dash(QObject *parent = 0);
        virtual ~m_Dash();

        void setWidth (int j);
        void setHeight (int j);

        QString width;
        QString height;

    private:

};
#endif  //DASH_H

