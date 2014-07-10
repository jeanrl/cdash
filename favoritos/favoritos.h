#ifndef FAVORITOS_H
#define FAVORITOS_H

#include <QWidget>
#include "jbotao.h"
#include <QDir>
#include <QBoxLayout>
#include <QSettings>

struct detailsButton
{
     QString name;
     QString command;
     QString typeCommand;
     QString meta;
     QPixmap icon;
};

namespace Ui {
class favoritos;
}

class favoritos : public QWidget
{
    Q_OBJECT

public:
    explicit favoritos(QWidget *parent = 0);
    ~favoritos();
    int numBotao = 0;
    int totalBotoes, lineLayoute, colummLayout;
    jbotao *botao;
    QList<QString> *listFavApps;
    QGridLayout *layout;

private:
    Ui::favoritos *ui;
    jbotao *btn[16];
    detailsButton readFile(QString fileRead);
    void hideButtons();
    detailsButton returnIcon(const QString &ext);
    void loadButtons(int qtdaBtn);

protected slots:
    void dragEnterEvent(QDragEnterEvent * ev);
    void dragLeaveEvent(QDragLeaveEvent * ev);
    void dragMoveEvent(QDragMoveEvent * ev);
    void dropEvent(QDropEvent * ev);
    void desapearBackground();

};

#endif // FAVORITOS_H
