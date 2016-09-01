/*
    Current class is the main game window. Used for interaction with user and also contains all other elements, like
    Canvas, dialog window for choosing new game field size, and records manager. Canvas and dialog window are widgets, whose
    parent is main window, but records manager just c++ class and for the code flexibility, it is injected in main window's
    constructor at the moment of creation, and for it's deletion QScopedPointer is used. Thus, it is possible to implement
    another way of storing/retrieving records and pass it to the constructor.
    Main window receives signals from its nested widgets and acts accordingly to the situation.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSize>
#include <QPaintEvent>

#include "filerecordmanager.h"
#include "canvas.h"
#include "fieldsizemenu.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:

    explicit MainWindow(IRecordManager *mgr, QWidget *parent = 0);
    ~MainWindow();

    void closeEvent(QCloseEvent *event);

public slots:

    void notifyWin(qint32 score);
    void notifyLose(qint32 score);
    void scoreChanged(qint32 score);

private:

    qint32 previousRecord;
    qint32 currentScore;

    Canvas* canvas;
    FieldSizeMenu* sizeMenu;
    QScopedPointer<IRecordManager> recordManager;

    QLCDNumber* gameLcdLabel;
    QLCDNumber* currentScoreLcdLabel;
    QLCDNumber* previousRecordLcdLabel;

    qint32 getPreviousRecord();
    void writeNewRecord(qint32 score);
};

#endif // MAINWINDOW_H
