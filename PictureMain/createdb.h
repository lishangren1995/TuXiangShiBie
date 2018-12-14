#ifndef CREATEDB_H
#define CREATEDB_H
#include <QList>
#include <QStringList>
//enum OperateType
//{
//    Add ,
//    Edit
//};
//    OperateType m_operateType;

class createdb
{
public:
    createdb();
    void initDB();

    QList<QStringList> selectDataFromBase1();

    QList<QStringList> selectDataFromBase2();

    QList<QStringList> selectDataFromBase3();

    QList<QStringList> selectDataFromBase4();
};

#endif // CREATEDB_H
