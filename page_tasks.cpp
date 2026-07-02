#include "page_tasks.h"
#include "ui_page_tasks.h"
#include <QDebug>

page_tasks::page_tasks(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::page_tasks)
{
    ui->setupUi(this);
}

page_tasks::~page_tasks()
{
    delete ui;
}



void page_tasks::on_tableWidgetTasks_cellClicked(int row, int column)
{
    QTableWidgetItem *itemCourse   = ui->tableWidgetTasks->item(row, 0);
    QTableWidgetItem *itemTitle    = ui->tableWidgetTasks->item(row, 1);
    QTableWidgetItem *itemDate     = ui->tableWidgetTasks->item(row, 2);
    QTableWidgetItem *itemPriority = ui->tableWidgetTasks->item(row, 3);

    QString course   = itemCourse   ? itemCourse->text()   : "";
    QString title    = itemTitle    ? itemTitle->text()    : "";
    QDate date     = itemDate     ? QDate::fromString(itemDate->text())     : QDate::currentDate();
    QString priority = itemPriority ? itemPriority->text() : "";

    ui->inputCourse->setText(course);
    ui->inputTaskTitle->setText(title);
    ui->inputDueDate->setDate(date);
    ui->inputPriority->setCurrentText(priority);

    // 4. Update class state
    is_editing = true;
    edit_row = row + 1;

    // 5. Reveal the overlay panel
    ui->taskOverlayWidget->show();
}



void page_tasks::on_buttonCancelTask_clicked()
{
    is_editing = false;
    edit_row = 0;
    ui->taskOverlayWidget->hide();
}


// void page_tasks::on_tableWidgetTasks_itemClicked(QTableWidgetItem *item)
// {
//     qDebug() << item->text();
// }


void page_tasks::on_buttonAddTask_clicked()
{
    is_editing = false;
    edit_row = 0;
    ui->taskOverlayWidget->show();
}


void page_tasks::on_buttonSaveTask_clicked()
{
    QString course   = ui->inputCourse->text();
    QString title    = ui->inputTaskTitle->text();
    QDate date     = ui->inputDueDate->date();
    QString priority = ui->inputPriority->currentText();

    int row = is_editing && edit_row > 0 ? edit_row - 1 : ui->tableWidgetTasks->rowCount();

    if (!is_editing) ui->tableWidgetTasks->insertRow(row);

    ui->tableWidgetTasks->setItem(row, 0, new QTableWidgetItem(course));
    ui->tableWidgetTasks->setItem(row, 1, new QTableWidgetItem(title));
    ui->tableWidgetTasks->setItem(row, 2, new QTableWidgetItem(date.toString(Qt::ISODate)));
    ui->tableWidgetTasks->setItem(row, 3, new QTableWidgetItem(priority));

    ui->inputCourse->setText("");
    ui->inputTaskTitle->setText("");
    ui->inputDueDate->setDate(QDate::currentDate());
    ui->inputPriority->setCurrentText("Low");


    is_editing = false;
    edit_row = 0;

    ui->taskOverlayWidget->hide();
}

