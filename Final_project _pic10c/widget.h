#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QFile>
#include <QtGui>
#include <QMediaPlayer>
#include <QDebug>
#include "gamewidget.h"


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    // reset buttion and close button
    QPushButton *restartBtn;
    QPushButton *closeBtn;

    // the three lables.
    QLabel *titleLabel;
    QLabel *tipsLabel;
    QLabel *scoreLbl;

    // widget fo the game
    GameWidget *gameWidget;
    qreal ratioW, ratioH;
    QPoint dragPosition;
    bool bPressFlag;

    // events for the mouse and keyborad.
protected:
    void resizeEvent(QResizeEvent *);
    void keyPressEvent(QKeyEvent * event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public slots:
    void onScoreInc(int);
    void onGameOver();
    void onWin();
    void buttonMusic();
};

#endif // WIDGET_H
