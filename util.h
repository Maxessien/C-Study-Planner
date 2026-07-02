#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QJsonArray>
#include <QStandardPaths>
#include <QDir>
#include <QFile>

class Tasks
{
public:
    static QJsonArray saved_tasks;
    Tasks() {}

protected:
    QString get_app_path();
    void load_from_disk();

};

inline QString Tasks::get_app_path(){

    QString path = QStandardPaths::writableLocation(

        QStandardPaths::AppDataLocation

        );

    QDir dir(path);



    if (!dir.exists())

    {

        dir.mkpath(".");

    }



    return path;

}


inline void Tasks::load_from_disk(){



    QString filePath = get_app_path() + "/tasks.json";



    if(!QFile::exists(filePath)){

        QJsonDocument doc = QJsonDocument::fromJson("[]");



        saved_tasks = doc.array();



        QFile file(filePath);



        if (file.open(QIODevice::WriteOnly))

        {

            file.write("[]");

            file.close();

        }



        return;

    };



    QFile file(filePath);



    if (file.open(QIODevice::ReadOnly))

    {

        QByteArray data = file.readAll();

        file.close();



        QJsonDocument doc = QJsonDocument::fromJson(data);

        QJsonArray arr = doc.array();

        saved_tasks = arr;

    }

}

#endif // UTIL_H
