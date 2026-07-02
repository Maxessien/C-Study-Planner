#include "page_dashboard.h"
#include "ui_page_dashboard.h"

page_dashboard::page_dashboard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::page_dashboard)
{
    ui->setupUi(this);
}

page_dashboard::~page_dashboard()
{
    delete ui;
}
