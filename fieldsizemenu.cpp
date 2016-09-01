#include "fieldsizemenu.h"
#include <QMessageBox>

FieldSizeMenu::FieldSizeMenu(QWidget* parent)
    :QDialog(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);

    button4 = new QPushButton;
    button5 = new QPushButton;
    button6 = new QPushButton;

    button4->setToolTip("A field with 4x4 size - 16 tiles.");
    button5->setToolTip("A field with 5x5 size - 25 tiles.");
    button6->setToolTip("A field with 6x6 size - 36 tiles.");

    QPixmap px4(":resources/4.png");
    QIcon icon4(px4);

    button4->setIcon(icon4);
    button4->setIconSize(QSize(200, 200));
    button4->setFixedSize(QSize(200, 200));

    QPixmap px5(":resources/5.png");
    QIcon icon5(px5);

    button5->setIcon(icon5);
    button5->setIconSize(QSize(200, 200));
    button5->setFixedSize(QSize(200, 200));

    QPixmap px6(":resources/6.png");
    QIcon icon6(px6);

    button6->setIcon(icon6);
    button6->setIconSize(QSize(200, 200));
    button6->setFixedSize(QSize(200, 200));

    layout->addWidget(button4);
    layout->addWidget(button5);
    layout->addWidget(button6);

    QSignalMapper *mapper = new QSignalMapper(this);

    connect(button4, SIGNAL(clicked(bool)), mapper, SLOT(map()));
    connect(button5, SIGNAL(clicked(bool)), mapper, SLOT(map()));
    connect(button6, SIGNAL(clicked(bool)), mapper, SLOT(map()));

    mapper->setMapping(button4, 4);
    mapper->setMapping(button5, 5);
    mapper->setMapping(button6, 6);

    connect(mapper, SIGNAL(mapped(int)), SLOT(buttonClicked(qint32)));
}

FieldSizeMenu::~FieldSizeMenu()
{}

void FieldSizeMenu::buttonClicked(qint32 value)
{
    int questionResult = QMessageBox::question(this, "Caution", "Choosing new canvas size will cause losing "
                                                                " current game state, are you sure?",
                                               (QMessageBox::Ok | QMessageBox::Cancel), QMessageBox::Cancel);

    if (questionResult == QMessageBox::Cancel)
    {
        close();
    }
    else
        emit newSideSize(value);

    close();
}
