#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint)
    , bPressFlag(false)
{



    //creat background music when start the game.
    QMediaPlayer * bgm = new QMediaPlayer(this);
    bgm->setMedia(QUrl("qrc:/sounds/background_music.mp3"));
    bgm->play();


    setAutoFillBackground(true);
    QPalette  backGround = palette();
    setPalette(backGround);
    // Lable 2048
    titleLabel = new QLabel(tr("2048"), this);
    titleLabel->setFont(QFont("arial", 50, QFont::Black));

    // the game widget
    gameWidget = new GameWidget(this);
    gameWidget->setFocus();
    connect(gameWidget, SIGNAL(ScoreInc(int)), this, SLOT(onScoreInc(int)));
    connect(gameWidget, SIGNAL(GameOver()), this, SLOT(onGameOver()));
    connect(gameWidget, SIGNAL(win()), this, SLOT(onWin()));

    // the format of word
    QFont font;
    font.setFamily("Arial");
    font.setBold(true);
    font.setPixelSize(15);

    // the button for the new game
    restartBtn = new QPushButton("New Game", this);
    restartBtn->setFont(font);
    restartBtn->setStyleSheet("QPushButton{color: white;background:#907963;border-style:flat;}");
    restartBtn->setFocusPolicy(Qt::NoFocus);
    connect(restartBtn, SIGNAL(clicked()), gameWidget, SLOT(restart()));
    connect(restartBtn, SIGNAL(clicked()), this, SLOT(buttonMusic()));

    // score label
    scoreLbl = new QLabel("SCORE\n0", this);
    scoreLbl->setFont(font);
    scoreLbl->setAlignment(Qt::AlignCenter);


    // close the window
    closeBtn = new QPushButton("X", this);
    closeBtn->setFocusPolicy(Qt::NoFocus);
    closeBtn->setFont(QFont("Arial", 11, QFont::Normal));
    closeBtn->setCursor(Qt::PointingHandCursor);
    closeBtn->setGeometry(400 - 18, 3, 15, 15);
    connect(closeBtn, SIGNAL(clicked()), this, SLOT(close()));
    resize(400, 510);
}

// destructor
Widget::~Widget()
{
    delete restartBtn;
    delete scoreLbl;
    delete gameWidget;
}

// updata the score
void Widget::onScoreInc(int score)
{
    scoreLbl->setText(QString("Score:\n %1").arg(score));
}

// win and lost a new window come out
void Widget::onGameOver()
{
    QMessageBox::information(this, "GameOver", "You lost !");
}

void Widget::onWin()
{
    QMessageBox::information(this, "Congratulation", "You win !");
}

// arrange different components
void Widget::resizeEvent(QResizeEvent *)
{
    // the ratio of height and width
    ratioW = width() / 400.0f;
    ratioH = height() / 510.0f;
    // the positions
    titleLabel->setGeometry(40 * ratioW, 40 * ratioH , 130 * ratioW, 50 * ratioH);
    gameWidget->setGeometry(18 * ratioW, 140 * ratioH, 365 * ratioW, 365 * ratioH);
    restartBtn->setGeometry(260 * ratioW, 90 * ratioH, 100 * ratioW, 30 * ratioH);
    scoreLbl->setGeometry(260 * ratioW, 40 * ratioH, 80 * ratioW, 40 * ratioH);
}

// press the key will play the button music and do the up, down, left, right.
void Widget::keyPressEvent(QKeyEvent *event)
{
    QMediaPlayer * buttonM  = new QMediaPlayer(this);
    buttonM ->setMedia(QUrl("qrc:/sounds/keyboard_music.wav"));
    buttonM->play();

    gameWidget->setFocus();
    QWidget::keyPressEvent(event);
}

// mouse event (DOWN)
void Widget::mousePressEvent ( QMouseEvent * event)
{
    bPressFlag = true;
    dragPosition = event->pos();
    QWidget::mousePressEvent(event);
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (bPressFlag) {
        QPoint relaPos(QCursor::pos() - dragPosition);
        move(relaPos);
    }
    QWidget::mouseMoveEvent(event);
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}

// click the button will play button music
void Widget::buttonMusic(){
       QMediaPlayer * buttonM  = new QMediaPlayer(this);
        buttonM ->setMedia(QUrl("qrc:/sounds/keyboard_music.wav"));
       buttonM->play();
}



