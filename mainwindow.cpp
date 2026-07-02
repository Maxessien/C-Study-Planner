#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./page_tasks.h"
#include "./page_calendar.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // 1. Create instances of your dynamic views
    page_tasks *tasks = new page_tasks(this);
    page_calendar *cal = new page_calendar(this);

    // 2. Add them to the empty stacked widget container
    ui->stackedWidget->addWidget(tasks); // Index 0
    ui->stackedWidget->addWidget(cal);   // Index 1

    // 3. Connect sidebar buttons to swap layout visibility indexes
    connect(ui->btnTasks, &QPushButton::clicked,     [this]() { ui->stackedWidget->setCurrentIndex(0); });
    connect(ui->btnCal, &QPushButton::clicked,  [this]() { ui->stackedWidget->setCurrentIndex(1); });
}

MainWindow::~MainWindow() {
    delete ui;
}
