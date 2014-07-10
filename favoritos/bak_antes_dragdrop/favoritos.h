#ifndef FAVORITOS_H
#define FAVORITOS_H

#include <QWidget>
#include "jbotao.h"
#include <QDir>

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
    int totalBotoes;
    jbotao *botao;
    QList<QString> *listFavApps;
    QString plataforma;


private:
    Ui::favoritos *ui;
    jbotao *jbtn10;
    void createList();
    void findInPath();
    void readFile(QString fileRead);
    void createButton(QString nome, QString comando, QPixmap icone);
    void hideButtons();
    void geraLista();



    void leApps();
    bool achaFile(const QDir &dir, QList<QString> *list);
    void leFile(QString path);
    bool buscaIcone(QString nome);
    QImage loadIcon(const QString& themeName, const QString& iconName, int size);
    void geraBotoes(QString nome, QString comando, QPixmap icone);

protected slots:
    void dragEnterEvent(QDragEnterEvent * ev);
    void dragLeaveEvent(QDragLeaveEvent * ev);
    void dragMoveEvent(QDragMoveEvent * ev);
    void dropEvent(QDropEvent * ev);

};

#endif // FAVORITOS_H
