#ifndef PAGE_CALENDAR_H
#define PAGE_CALENDAR_H

#include <QWidget>
#include <QFrame>
#include <QString>

namespace Ui {
class page_calendar;
}

class page_calendar : public QWidget
{
    Q_OBJECT

public:
    explicit page_calendar(QWidget *parent = nullptr);
    ~page_calendar();

private slots:
    QFrame* createEventCard(const QString& course, const QString& time);

private:
    Ui::page_calendar *ui;
};

#endif // PAGE_CALENDAR_H
