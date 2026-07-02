#include "page_calendar.h"
#include "ui_page_calendar.h"
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QSpacerItem>
#include <QSizePolicy>
#include <QStringList>

page_calendar::page_calendar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::page_calendar)
{
    ui->setupUi(this);
    ui->schGrpMon->layout()->addWidget(createEventCard("MAT 101", "10:00-12:00"));
}

page_calendar::~page_calendar()
{
    delete ui;
}

QFrame* page_calendar::createEventCard(const QString& course, const QString& time) {
    // 1. Main Card Container
    QFrame* card = new QFrame();
    // The 'card' prefix ensures .QFrame[objectName^="card"] styling applies
    card->setObjectName("cardDynamic_" + course);

    // Layout for the card
    QVBoxLayout* cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(9, 9, 9, 9); // Qt's default margins

    // 2. Header Box (Dot + Title + Spacer)
    QHBoxLayout* headerLayout = new QHBoxLayout();

    // Colored Dot Badge
    QWidget* dot = new QWidget();
    dot->setFixedSize(8, 8);

    // Match your existing CSS categories. Default to Math (blue) if not found.
    QStringList validCategories = {"Math", "Physics", "History", "Literature"};
    if (validCategories.contains(course)) {
        dot->setObjectName("dot" + course);
    } else {
        dot->setObjectName("dotMath");
    }

    // Course Title
    QLabel* titleLabel = new QLabel(course);
    titleLabel->setObjectName("cardTitle_" + course);

    // Push spacer to keep elements left-aligned
    QSpacerItem* spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    headerLayout->addWidget(dot);
    headerLayout->addWidget(titleLabel);
    headerLayout->addItem(spacer);

    // 3. Time Label
    QLabel* timeLabel = new QLabel(time);
    timeLabel->setObjectName("cardTime_" + course);

    // 4. Assemble the Card
    cardLayout->addLayout(headerLayout);
    cardLayout->addWidget(timeLabel);

    return card;
}