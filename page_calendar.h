#ifndef PAGE_CALENDAR_H
#define PAGE_CALENDAR_H

#include <QWidget>
#include <QFrame>
#include <QString>
#include <QDateTime>
#include <QList>
#include "util.h"

namespace Ui {
class page_calendar;
}

class page_calendar : public QWidget, public Tasks
{
    Q_OBJECT

public:
    explicit page_calendar(QWidget *parent = nullptr);
    ~page_calendar();

private slots:
    QFrame* create_event_card(const QString& course, const QString& time, const QString& status);
    QList<QDateTime> get_week_dates(int week_back = 0);
    void load_week(QList<QDateTime> week);
    void showEvent(QShowEvent *ev);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::page_calendar *ui;
    int active_week;
};

#endif // PAGE_CALENDAR_H
