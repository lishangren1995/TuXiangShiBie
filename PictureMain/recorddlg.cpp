#include "recorddlg.h"
#include "ui_recorddlg.h"
#include <QSqlQuery>
#include <QMessageBox>
#include "quanju.h"

recorddlg::recorddlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::recorddlg)
{
    ui->setupUi(this);
}

recorddlg::~recorddlg()
{
    delete ui;
}
void recorddlg::on_buttonBox_accepted()
{
    QVariantMap stuInfo;


    QString pid = ui->PIDEdit->text();
    QString WID = ui->WIDEdit->text();
    QString check_date = ui->dateEdit->text();
    QString check_person = ui->personEdit->text();
    QString defect_Type = ui->defectEdit->text();
    QString defect_num = ui->amoutEdit->text();
    QString defect_Type2 = ui->defectEdit_2->text();
    QString defect_num2 = ui->amoutEdit_2->text();
    QString result = ui->resultEdit->text();
    QString remark = ui->RemarkEdit->toPlainText();

    stuInfo.insert("pid" ,pid );
    stuInfo.insert("wid" ,WID );
    stuInfo.insert("date" ,check_date );
    stuInfo.insert("person" ,check_person );
    stuInfo.insert("defect" ,defect_Type );
    stuInfo.insert("amout" ,defect_num );
    stuInfo.insert("defect2" ,defect_Type2 );
    stuInfo.insert("amout2" ,defect_num2 );
    stuInfo.insert("result" ,result );
    stuInfo.insert("remark" ,remark );


    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("HostName.db");
    db.setDatabaseName("DataManager");
    db.open();



    if(quanju::m_operateType == 0)
    {
        QString pid = stuInfo.value("pid").toString();
        QString WID = stuInfo.value("wid").toString();
        QString check_date = stuInfo.value("date").toString();
        QString check_person = stuInfo.value("person").toString();
        QString defect_Type = stuInfo.value("defect").toString();
        QString defect_num = stuInfo.value("amout").toString();
        QString defect_Type2 = stuInfo.value("defect2").toString();
        QString defect_num2 = stuInfo.value("amout2").toString();
        QString result = stuInfo.value("result").toString();
        QString remark = stuInfo.value("remark").toString();

        QString sql;
        sql = QString("insert into ImageManager1 (WildID,PID ,check_date ,check_person ,defect_type,defect_num,defect_type2,defect_num2,result ,remark)"
                      " VALUES ('%1', '%2' , '%3' , '%4' , '%5' , '%6' , '%7' , '%8', '%9' , '%10')")
                .arg(WID).arg(pid).arg(check_date).arg(check_person).arg(defect_Type).arg(defect_num).arg(defect_Type2).arg(defect_num2).arg(result).arg(remark);
//        sql = QString("insert into ImageManager (WildID,PID ,check_date ,check_person ,defect_type,defect_num,result ,remark)"
//                      " VALUES ('%1', '%2' , '%3' , '%4' , '%5' , '%6' , '%7' , '%8')")
//                .arg(WID).arg(pid).arg(check_date).arg(check_person).arg(defect_Type).arg(defect_num).arg(result).arg(remark);
        QSqlQuery query;
        bool ok = query.exec(sql);
        if(ok)
        {
            QMessageBox::information(this ,tr("提示") , tr("添加成功!"));
        }
        else
        {
            QMessageBox::information(this ,tr("提示") , tr("添加失败!"));
        }
    }

    if(quanju::m_operateType == 1)
    {
        QString pid = stuInfo.value("pid").toString();
        QString WID = stuInfo.value("wid").toString();
        QString check_date = stuInfo.value("date").toString();
        QString check_person = stuInfo.value("person").toString();
        QString defect_Type = stuInfo.value("defect").toString();
        QString defect_num = stuInfo.value("amout").toString();
        QString defect_Type2 = stuInfo.value("defect2").toString();
        QString defect_num2 = stuInfo.value("amout2").toString();
        QString result = stuInfo.value("result").toString();
        QString remark = stuInfo.value("remark").toString();

        QString sql;
        sql = QString("UPDATE ImageManager1 "
                      "set WildID = '%0' ,PID = '%2' ,check_date = '%3',"
                      "check_person = '%4',defect_type = '%5',defect_num = '%6',defect_type2 = '%7',defect_num2 = '%8', result = '%9',remark = '%10'"
                      " where WildID = '%0' ")
                .arg(WID).arg(pid).arg(check_date).arg(check_person).arg(defect_Type).arg(defect_num).arg(defect_Type2).arg(defect_num2).arg(result).arg(remark);
        QSqlQuery query;
        bool ok = query.exec(sql);
        if(ok)
        {
            QMessageBox::information(this ,tr("提示") , tr("修改成功!"));
        }
        else
        {
            QMessageBox::information(this ,tr("提示") , tr("修改失败!"));
        }
    }

    //db.close();

    //clearData(); //清除编辑的数据
    close();
}

void recorddlg::setEditData(QStringList rowData)
{
    ui->WIDEdit->setText(rowData.at(0));
    ui->PIDEdit->setText(rowData.at(1));
    QString str=rowData.at(2);
    QDate date=QDate::fromString(str,"yyyy/M/d");
    ui->dateEdit->setDate(date);
    ui->personEdit->setText(rowData.at(3));
    ui->defectEdit->setText(rowData.at(4));
    ui->amoutEdit->setText(rowData.at(5));
    ui->defectEdit_2->setText(rowData.at(6));
    ui->amoutEdit_2->setText(rowData.at(7));
    ui->resultEdit->setText(rowData.at(8));
    ui->RemarkEdit->setText(rowData.at(9));
    ui->WIDEdit->setEnabled(false);
}

void recorddlg::on_buttonBox_rejected()
{
    close();
}

void recorddlg::printdata(QString msg1,QString msg2,QString msg3,QString msg4,QString msg5,QString msg6)
{
     ui->PIDEdit->setText(msg1);
     ui->defectEdit->setText(msg2);
     ui->amoutEdit->setText(msg3);
     ui->defectEdit_2->setText(msg4);
     ui->amoutEdit_2->setText(msg5);
     ui->resultEdit->setText(msg6);
}
