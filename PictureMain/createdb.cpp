#include "createdb.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

createdb::createdb()
{

}

void createdb::initDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("HostName.db");
    db.setDatabaseName("DataManager");
    bool ok = db.open();
    if(ok)
    {
        qDebug()<<"Create DB";

        QSqlQuery query1;
        QSqlQuery query2;
        QSqlQuery query3;
        QSqlQuery query4;
        query1.exec("create table UserManager (create_date datetime, "
                    "id varchar(20)  primary key, name varchar(20) ,"
                    " sex varchar(20) ,age INTEGER ,"
                    "business varchar(20) , password varchar(12) , remark varchar(50))");

        query2.exec("create table ImageManager1 (WildID varchar(20) primary key, "
                    "PID varchar(20) , check_date varchar(20) ,"
                    " check_person varchar(20) ,defect_type varchar(50) ,"
                    "defect_num varchar(50) ,defect_type2 varchar(50),defect_num2 varchar(50),result varchar(20) , remark varchar(50))");

//                query2.exec("create table ImageManager (WildID varchar(20) primary key, "
//                            "PID varchar(20) , check_date varchar(20) ,"
//                            " check_person varchar(20) ,defect_type varchar(50) ,"
//                            "defect_num varchar(50),result varchar(20) , remark varchar(50))");

        query3.exec("create table LaserManager (pid varchar(20) primary key, "
                    "baseMetal varchar(50), joint varchar(20) ,"
                    " gas varchar(50) ,pianjiao varchar(20) ,"
                    " position varchar(10) , power varchar(20) , "
                    " speed varchar(20),defocuse varchar(20),remark varchar(50))");


        query4.exec("create table ArcManager1 (wps varchar(20) primary key, "
                    "date varchar(50), mucai varchar(20) ,"
                    " hjfangfa varchar(50) ,jietou varchar(50),"
                    "weizhi varchar(20),zhijing varchar(20),"
                    "dianliu varchar(50),dianya varchar(20) ,"
                    " dlzhonglei varchar(10) , songsisd varchar(20) , "
                    " speed varchar(20))");
    }
    else
    {
        qDebug()<<db.databaseName();
    }
}

QList<QStringList> createdb::selectDataFromBase1()
{
    QSqlQuery query1("SELECT * FROM UserManager");

    QList<QStringList> UserInfo;

    while (query1.next())
    {
        QStringList rowData ;

        rowData <<query1.value(2).toString();
        rowData <<query1.value(1).toString();
        rowData <<query1.value(3).toString();
        rowData <<query1.value(4).toString();
        rowData <<query1.value(5).toString();
        rowData <<query1.value(6).toString();
        rowData <<query1.value(7).toString();

        UserInfo.append(rowData);
    }
    return UserInfo;
}

QList<QStringList> createdb::selectDataFromBase2()
{
    QSqlQuery query2("SELECT * FROM ImageManager1");

    QList<QStringList> ImageInfo;

    while (query2.next())
    {
        QStringList rowData ;
        rowData <<query2.value(0).toString();
        rowData <<query2.value(1).toString();
        rowData <<query2.value(2).toString();
        rowData <<query2.value(3).toString();
        rowData <<query2.value(4).toString();
        rowData <<query2.value(5).toString();
        rowData <<query2.value(6).toString();
        rowData <<query2.value(7).toString();
        rowData <<query2.value(8).toString();
        rowData <<query2.value(9).toString();
        ImageInfo.append(rowData);
    }
    return ImageInfo;
}

QList<QStringList> createdb::selectDataFromBase3()
{
    QSqlQuery query2("SELECT * FROM LaserManager");

    QList<QStringList> ImageInfo;

    while (query2.next())
    {
        QStringList rowData ;
        rowData <<query2.value(0).toString();
        rowData <<query2.value(1).toString();
        rowData <<query2.value(2).toString();
        rowData <<query2.value(3).toString();
        rowData <<query2.value(4).toString();
        rowData <<query2.value(5).toString();
        rowData <<query2.value(6).toString();
        rowData <<query2.value(7).toString();
        rowData <<query2.value(8).toString();
        rowData <<query2.value(9).toString();
        ImageInfo.append(rowData);
    }
    return ImageInfo;
}

QList<QStringList> createdb::selectDataFromBase4()
{
    QSqlQuery query2("SELECT * FROM ArcManager1");

    QList<QStringList> ImageInfo;

    while (query2.next())
    {
        QStringList rowData ;
        rowData <<query2.value(0).toString();
        rowData <<query2.value(1).toString();
        rowData <<query2.value(2).toString();
        rowData <<query2.value(3).toString();
        rowData <<query2.value(4).toString();
        rowData <<query2.value(5).toString();
        rowData <<query2.value(6).toString();
        rowData <<query2.value(7).toString();
        rowData <<query2.value(8).toString();
        rowData <<query2.value(9).toString();
        rowData <<query2.value(10).toString();
        rowData <<query2.value(11).toString();
        //        rowData <<query2.value(12).toString();
        //        rowData <<query2.value(13).toString();
        ImageInfo.append(rowData);
    }
    return ImageInfo;
}
