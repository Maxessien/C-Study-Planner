#include "page_calendar.h"
#include "ui_page_calendar.h"

page_calendar::page_calendar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::page_calendar)
{
    ui->setupUi(this);
}

page_calendar::~page_calendar()
{
    delete ui;
}
