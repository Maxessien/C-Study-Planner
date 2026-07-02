#include "page_tasks.h"

#include "ui_page_tasks.h"

#include <QDebug>

#include <QDir>

#include <QFile>

#include <QStandardPaths>

#include <QJsonObject>

#include <QJsonArray>

#include <QJsonDocument>

#include "util.h"


QJsonArray Tasks::saved_tasks;



page_tasks::page_tasks(QWidget *parent)

    : QWidget(parent)

    , ui(new Ui::page_tasks)

{

    ui->setupUi(this);

    load_from_disk();

    for (int i = 0; i < saved_tasks.size(); i++)

    {

        QJsonValue value = saved_tasks[i];

        QJsonObject obj = value.toObject();



        // Extract the 'status' tag value from disk arrays (fallback to "In Progress" if missing)

        QString statusVal = obj.contains("status") ? obj["status"].toString() : "In Progress";



        insert_item(

            obj["course"].toString(),

            obj["title"].toString(),

            QDateTime::fromString(obj["date"].toString(), Qt::ISODate),

            obj["priority"].toString(),

            statusVal,

            i

            );

    }

}



page_tasks::~page_tasks()

{

    delete ui;

}



// Updated signature to take the 'status' parameter

void page_tasks::save_task_to_disk(QString course, QString title, QDateTime dueDate, QString priority, QString status){

    QJsonObject task;

    task["course"] = course;

    task["title"] = title;

    task["date"] = dueDate.toString(Qt::ISODate);

    task["priority"] = priority;

    task["status"] = status; // Save status to the JSON object



    int row = is_editing && edit_row > 0 ? edit_row - 1 : ui->tableWidgetTasks->rowCount();



    if (!is_editing) saved_tasks.append(task);

    else saved_tasks[row] = task;



    // Pass status to populate the table item UI properly

    insert_item(course, title, dueDate, priority, status, row);



    QString filePath = get_app_path() + "/tasks.json";



    QJsonDocument doc(saved_tasks);



    qDebug() << filePath << " : " << doc.toJson();



    QFile file(filePath);



    if (file.open(QIODevice::WriteOnly))

    {

        file.write(doc.toJson());

        file.close();

    }

}



// Updated layout table mapping logic to handle Column 4 (Status)

void page_tasks::insert_item(QString course, QString title, QDateTime date, QString priority, QString status, int row){



    if (!is_editing) ui->tableWidgetTasks->insertRow(row);



    ui->tableWidgetTasks->setItem(row, 0, new QTableWidgetItem(course));

    ui->tableWidgetTasks->setItem(row, 1, new QTableWidgetItem(title));

    ui->tableWidgetTasks->setItem(row, 2, new QTableWidgetItem(date.toString(Qt::ISODate)));

    ui->tableWidgetTasks->setItem(row, 3, new QTableWidgetItem(priority));

    ui->tableWidgetTasks->setItem(row, 4, new QTableWidgetItem(status)); // Set text item on column Index 4

}



void page_tasks::on_tableWidgetTasks_cellClicked(int row, int column)

{

    QTableWidgetItem *itemCourse   = ui->tableWidgetTasks->item(row, 0);

    QTableWidgetItem *itemTitle    = ui->tableWidgetTasks->item(row, 1);

    QTableWidgetItem *itemDate     = ui->tableWidgetTasks->item(row, 2);

    QTableWidgetItem *itemPriority = ui->tableWidgetTasks->item(row, 3);

    QTableWidgetItem *itemStatus   = ui->tableWidgetTasks->item(row, 4); // Added status extraction



    QString course   = itemCourse ? itemCourse->text() : "";

    QString title    = itemTitle ? itemTitle->text() : "";

    QDateTime date       = itemDate ? QDateTime::fromString(itemDate->text(), Qt::ISODate) : QDateTime::currentDateTime();

    QString priority = itemPriority ? itemPriority->text() : "";

    QString status   = itemStatus ? itemStatus->text() : "In Progress"; // Default fallback



    ui->inputCourse->setText(course);

    ui->inputTaskTitle->setText(title);

    ui->inputDueDate->setDateTime(date);

    ui->inputPriority->setCurrentText(priority);

    ui->inputStatus->setCurrentText(status); // Populates the overlay combobox with selected data row text



    // Update class state

    is_editing = true;

    edit_row = row + 1;



    // Reveal the overlay panel

    ui->taskOverlayWidget->show();

}



void page_tasks::on_buttonCancelTask_clicked()

{

    is_editing = false;

    edit_row = 0;

    ui->taskOverlayWidget->hide();

}



void page_tasks::on_buttonAddTask_clicked()

{

    is_editing = false;

    edit_row = 0;



    // Clear overlay forms for fresh entry profile setups

    ui->inputCourse->setText("");

    ui->inputTaskTitle->setText("");

    ui->inputDueDate->setDate(QDate::currentDate());

    ui->inputPriority->setCurrentText("Low");

    ui->inputStatus->setCurrentText("In Progress");



    ui->taskOverlayWidget->show();

}



void page_tasks::on_buttonSaveTask_clicked()

{

    QString course = ui->inputCourse->text();

    QString title = ui->inputTaskTitle->text();

    QDateTime date = ui->inputDueDate->dateTime();

    QString priority = ui->inputPriority->currentText();

    QString status   = ui->inputStatus->currentText(); // Extract value from status combo wrapper object



    save_task_to_disk(course, title, date, priority, status);



    // Form inputs cleanup sequence reset rules

    ui->inputCourse->setText("");

    ui->inputTaskTitle->setText("");

    ui->inputDueDate->setDateTime(QDateTime::currentDateTime());

    ui->inputPriority->setCurrentText("Low");

    ui->inputStatus->setCurrentText("In Progress");



    is_editing = false;

    edit_row = 0;



    ui->taskOverlayWidget->hide();

}

