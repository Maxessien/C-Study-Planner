#ifndef PAGE_CALENDAR_H
#define PAGE_CALENDAR_H

#include <QWidget>

namespace Ui {
class page_calendar;
}

class page_calendar : public QWidget
{
    Q_OBJECT

public:
    explicit page_calendar(QWidget *parent = nullptr);
    ~page_calendar();

private:
    Ui::page_calendar *ui;
};

#endif // PAGE_CALENDAR_H
