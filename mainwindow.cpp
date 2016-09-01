#include "mainwindow.h"

MainWindow::MainWindow(IRecordManager * mgr, QWidget *parent)
    : QWidget(parent),
      previousRecord(0),
      currentScore(0),
      recordManager(mgr)
{
    canvas = new Canvas(this, 4);
    sizeMenu = new FieldSizeMenu(this);

    //  <labels>
    QLabel *score = new QLabel(this);
    QLabel *bestScore = new QLabel(this);

    score->setText("SCORE");
    bestScore->setText("BEST");

    score->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    bestScore->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    //  </labels>

    //  <LCD displays>
    gameLcdLabel = new QLCDNumber(4);
    currentScoreLcdLabel = new QLCDNumber(8);
    previousRecordLcdLabel = new QLCDNumber(8);

    gameLcdLabel->setToolTip("2048, baby!");
    currentScoreLcdLabel->setToolTip("You current score.");
    previousRecordLcdLabel->setToolTip("Biggest score gained previously in application.");

    previousRecord = getPreviousRecord();
    previousRecordLcdLabel->display(previousRecord);

    gameLcdLabel->display(2048);
    //  </LCD displays>

    //  <buttons>
    QPushButton *undoBtn = new QPushButton(this);
    undoBtn->setText("undo");
    undoBtn->setShortcut(Qt::CTRL+Qt::Key_Z);
    undoBtn->setToolTip("Undo the previous action.");

    QPushButton *restartBtn = new QPushButton(this);
    restartBtn->setText("restart");
    restartBtn->setToolTip("Lost current progress and restart the game.");

    QPushButton *menuButton = new QPushButton(this);
    menuButton->setStyleSheet("QPushButton{"
                              "border:no;}"
                              "QPushButton:hover:!pressed { border: 1px solid black;}"
                              "");
    QPixmap px(":resources/menu.png");
    QIcon icon(px);

    menuButton->setIcon(icon);
    menuButton->setIconSize(QSize(32,32));
    menuButton->setFixedSize(QSize(32,32));
    //  </buttons>

    //  <layout placing>
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(score, 0, 2);
    layout->addWidget(bestScore, 0, 3);
    layout->addWidget(gameLcdLabel, 0, 0, 2, 2);
    layout->addWidget(currentScoreLcdLabel, 1, 2);
    layout->addWidget(previousRecordLcdLabel, 1, 3);
    layout->addWidget(canvas, 2, 0, 10, 4);
    layout->addWidget(menuButton, 13, 0);
    layout->addWidget(restartBtn, 13, 2);
    layout->addWidget(undoBtn, 13, 3);
    //  </layout placing>

    //  <connections>
    connect(canvas, SIGNAL(lose(qint32)),SLOT(notifyLose(qint32)));
    connect(canvas, SIGNAL(scoreChanged(qint32)), SLOT(scoreChanged(qint32)));
    connect(canvas, SIGNAL(win(qint32)), SLOT(notifyWin(qint32)));
    connect(restartBtn, SIGNAL(pressed()), canvas, SLOT(reset()));
    connect(restartBtn, SIGNAL(released()), canvas, SLOT(setFocus()));
    connect(undoBtn, SIGNAL(clicked(bool)), canvas, SLOT(undo()));
    connect(undoBtn, SIGNAL(released()), canvas, SLOT(setFocus()));
    connect(menuButton, SIGNAL(clicked(bool)), sizeMenu, SLOT(show()));
    connect(menuButton, SIGNAL(released()), canvas, SLOT(setFocus()));
    connect(sizeMenu, SIGNAL(newSideSize(qint32)), canvas, SLOT(setAnotherField(qint32)));
    //  </connections>

    this->setMinimumSize(QSize(400, 480));
}

MainWindow::~MainWindow()
{}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (currentScore > previousRecord)
        writeNewRecord(currentScore);

    QMessageBox::StandardButton resultButton;
    resultButton = QMessageBox::question(this, ":(", "Really want to quit? Your best score will be saved.",
                                         QMessageBox::Yes|QMessageBox::No);

    if (resultButton == QMessageBox::Yes)
        close();
    else
        event->ignore();
}

void MainWindow::notifyLose(qint32 score)
{
    QMessageBox::information(this, "Game over!", "Your Score: " + QString::number(score));

    if (score > previousRecord)
    {
        this->previousRecordLcdLabel->display(score);
        writeNewRecord(score);
    }
    canvas->reset();
}

void MainWindow::notifyWin(qint32 score)
{
    QMessageBox::information(this, "You won!", "Your Score: " + QString::number(score));

    if (score > previousRecord)
    {
        this->previousRecordLcdLabel->display(score);
        writeNewRecord(score);
    }

    QMessageBox::StandardButton resultButton;
    resultButton = QMessageBox::question(this, "Go on?",
                                         "Continue playing?", QMessageBox::Yes|QMessageBox::No);

    if (resultButton == QMessageBox::No)
        canvas->reset();
}

void MainWindow::scoreChanged(qint32 score)
{
    currentScore = score;
    currentScoreLcdLabel->display(currentScore);

    if (currentScore > previousRecord)
        this->previousRecordLcdLabel->display(currentScore);
}

qint32 MainWindow::getPreviousRecord()
{
    return recordManager->getPreviousRecord();
}

void MainWindow::writeNewRecord(qint32 score)
{
    recordManager->writeNewRecord(score);
}
