#ifndef PAGE_DASHBOARD_H
#define PAGE_DASHBOARD_H

#include <QWidget>

namespace Ui {
class page_dashboard;
}

class page_dashboard : public QWidget
{
    Q_OBJECT

public:
    explicit page_dashboard(QWidget *parent = nullptr);
    ~page_dashboard();

private:
    Ui::page_dashboard *ui;
};

#endif // PAGE_DASHBOARD_H
