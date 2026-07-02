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
#include <QDateTime>
#include <QList>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>

page_calendar::page_calendar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::page_calendar)
{
    ui->setupUi(this);
    active_week = 0;
    load_from_disk();
}

void page_calendar::showEvent(QShowEvent *ev){
    QWidget::showEvent(ev);

    load_week(get_week_dates());
}

page_calendar::~page_calendar()
{
    delete ui;
}

void page_calendar::load_week(QList<QDateTime> week)
{
    ui->labelDateRange->setText(week[0].date().toString(Qt::ISODate) + " - " + week[6].date().toString(Qt::ISODate));

    ui->lblDayNumMon->setText(QString::number(week[0].date().day()));
    ui->lblDayNumTue->setText(QString::number(week[1].date().day()));
    ui->lblDayNumWed->setText(QString::number(week[2].date().day()));
    ui->lblDayNumThu->setText(QString::number(week[3].date().day()));
    ui->lblDayNumFri->setText(QString::number(week[4].date().day()));
    ui->lblDayNumSat->setText(QString::number(week[5].date().day()));
    ui->lblDayNumSun->setText(QString::number(week[6].date().day()));

    QWidget* groups[] = {
        ui->schGrpMon,
        ui->schGrpTues,
        ui->schGrpWed,
        ui->schGrpThur,
        ui->schGrpFri,
        ui->schGrpSat,
        ui->schGrpSun
    };

    // Ensure every group has a layout and clear old cards
    for (QWidget* group : groups)
    {
        if (!group->layout())
            group->setLayout(new QVBoxLayout);

        QLayout* layout = group->layout();

        while (QLayoutItem* item = layout->takeAt(0))
        {
            if (item->widget())
                delete item->widget();

            delete item;
        }
    }

    // Add cards
    for (const QJsonValue& value : saved_tasks)
    {
        QJsonObject obj = value.toObject();

        QDateTime date =
            QDateTime::fromString(obj["date"].toString(), Qt::ISODate);

        QDate eventDate = date.date();
        QString timeStr = date.time().toString("hh:mm AP");
        QString course = obj["course"].toString();
        QString status = obj["status"].toString();

        for (int day = 0; day < 7; ++day)
        {
            if (eventDate == week[day].date())
            {
                groups[day]->layout()->addWidget(
                    create_event_card(course, timeStr, status)
                    );
                break;
            }
        }
    }
}

QList<QDateTime> page_calendar::get_week_dates(int week_back) {
    QList<QDateTime> weekDates;
    QDateTime current = QDateTime::currentDateTime();

    // 1. Get the current day of the week (Monday = 1, Sunday = 7)
    int dayOfWeek = current.date().dayOfWeek();

    // 2. Find the Monday of chosen week
    QDateTime monday = current.addDays(-(dayOfWeek - 1)).addDays(7 * week_back);

    // 3. Generate the 7 days
    for (int i = 0; i < 7; ++i) {
        weekDates.append(monday.addDays(i));
    }

    return weekDates;
}

QFrame* page_calendar::create_event_card(const QString& course, const QString& time, const QString& status) {
    QFrame* card = new QFrame();
    card->setObjectName("cardDynamic_" + course);

    QVBoxLayout* cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(9, 9, 9, 9);

    // 2. Header Box (Dot + Title + Spacer)
    QHBoxLayout* headerLayout = new QHBoxLayout();

    // Colored Category Dot
    QWidget* dot = new QWidget();
    dot->setFixedSize(8, 8);
    QStringList validCategories = {"Math", "Physics", "History", "Literature"};
    dot->setObjectName(validCategories.contains(course) ? "dot" + course : "dotMath");

    QLabel* titleLabel = new QLabel(course);
    titleLabel->setObjectName("cardTitle_" + course);

    // Status Badge
    QLabel* statusBadge = new QLabel(status);
    statusBadge->setObjectName("statusBadge"); // Common class for styling
    // Create a specific ID for color mapping
    statusBadge->setProperty("statusValue", status);
    statusBadge->setStyleSheet("padding: 2px 6px; border-radius: 4px; font-size: 10px; font-weight: bold;");

    QSpacerItem* spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    headerLayout->addWidget(dot);
    headerLayout->addWidget(titleLabel);
    headerLayout->addItem(spacer);
    headerLayout->addWidget(statusBadge);

    // 3. Time Label
    QLabel* timeLabel = new QLabel(time);
    timeLabel->setObjectName("cardTime_" + course);

    cardLayout->addLayout(headerLayout);
    cardLayout->addWidget(timeLabel);

    return card;
}
void page_calendar::on_pushButton_clicked()
{
    active_week++;

    load_week(get_week_dates(active_week));
}


void page_calendar::on_pushButton_2_clicked()
{
    active_week--;

    load_week(get_week_dates(active_week));
}

