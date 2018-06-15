#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QEventLoop>
#include <QTimer>
#include <QPainter>
#include <QList>
#include <QMediaPlayer>
#include <QDebug>


enum GestureDirect
{
    LEFT = 0,
    RIGHT = 1,
    UP = 2,
    DOWN = 3
};

// the two type of aimation: move and create block
enum AnimationType
{
    MOVE = 0,
    APPEARANCE = 1
};

// the parameters of the new bolck
struct Animation
{
    AnimationType type;
    GestureDirect direct;
    QPointF startPos;
    QPointF endPos;
    int digit;
    int digit2;
};

// the widget of the game
class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent * event);

private:
    int board[4][4];
    // the digit number on each block
    int digitCount;
    int score;
    QPoint startPos;
    QList<Animation> animationList;
    qreal w, h;
    QImage *cacheImg;
    bool isAnimating;

    bool checkGameOver();
    bool checkWin();

    int getBitCount(int);
    // the animation
    bool playAnimation(Animation&, QPainter&);


    // events
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

    // connect gesture, blocks score, and end of game.
signals:
    void GestureMove(GestureDirect);
    void ScoreInc(int);
    void GameOver();
    void win();

    // slots
public slots:
    void onGestureMove(GestureDirect);
    void restart();

};





#endif // GAMEWIDGET_H
