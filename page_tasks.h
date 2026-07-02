#ifndef PAGE_TASKS_H
#define PAGE_TASKS_H

#include <QWidget>

namespace Ui {
class page_tasks;
}

class page_tasks : public QWidget
{
    Q_OBJECT

public:
    explicit page_tasks(QWidget *parent = nullptr);
    ~page_tasks();

private slots:
    // ADD THIS LINE BELOW:
    void on_tableWidgetTasks_cellClicked(int row, int column);

    void on_buttonCancelTask_clicked();

    // void on_tableWidgetTasks_itemClicked(QTableWidgetItem *item);

    void on_buttonAddTask_clicked();

    void on_buttonSaveTask_clicked();

private:
    Ui::page_tasks *ui;
    bool is_editing;
    int edit_row;
};

#endif // PAGE_TASKS_H
