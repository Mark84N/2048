/*
    Dialog widget, offers to user 3 game field dimensions: 4x4, 5x5, 6x6.
    User is able to change them at any time.
*/

#ifndef FIELDSIZEMENU_H
#define FIELDSIZEMENU_H

#include <QtWidgets>
#include <QSignalMapper>

class FieldSizeMenu: public QDialog
{
    Q_OBJECT

public:

    FieldSizeMenu(QWidget *parent=nullptr);
    ~FieldSizeMenu();

signals:

    void newSideSize(qint32 size);

private slots:

    void buttonClicked(qint32 value);

private:

    QPushButton* button4;
    QPushButton* button5;
    QPushButton* button6;
};

#endif // FIELDSIZEMENU_H
