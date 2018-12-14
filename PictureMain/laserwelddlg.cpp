#include "laserwelddlg.h"
#include "ui_laserwelddlg.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDialog>
#include <QPrintDialog>
#include"quanju.h"
laserwelddlg::laserwelddlg(QWidget *parent) :
//    QWidget(parent),
QDialog(parent),
    ui(new Ui::laserwelddlg)
{
    ui->setupUi(this);
}

laserwelddlg::~laserwelddlg()
{
    delete ui;
}


void laserwelddlg::setEditData(QStringList rowData)
{
    ui->PIDEdit->setText(rowData.at(0));
    ui->baseMetalEdit->setText(rowData.at(1));
    ui->JointEdit->setText(rowData.at(2));
    ui->gasEdit->setText(rowData.at(3));
    ui->pianjiaoEdit->setText(rowData.at(4));
    ui->positionEdit->setText(rowData.at(5));
    ui->PEdit->setText(rowData.at(6));
    ui->VEdit->setText(rowData.at(7));
    ui->FEdit->setText(rowData.at(8));
    ui->RemarkEdit->setText(rowData.at(9));
    ui->PIDEdit->setEnabled(false);
}



void laserwelddlg::clearData()
{
    ui->PIDEdit->clear();
    ui->baseMetalEdit->clear();
    ui->JointEdit->clear();
    ui->gasEdit->clear();
    ui->pianjiaoEdit->clear();
    ui->positionEdit->clear();
    ui->PEdit->clear();
    ui->VEdit->clear();
    ui->FEdit->clear();
    ui->RemarkEdit->clear();
}

void laserwelddlg::on_buttonBox_accepted()
{
    QVariantMap stuInfo;

    QString pid = ui->PIDEdit->text();
    QString baseMetal = ui->baseMetalEdit->text();
    QString Joint = ui->JointEdit->text();
    QString gas = ui->gasEdit->text();
    QString pianjiao = ui->pianjiaoEdit->text();
    QString position = ui->positionEdit->text();
    QString power = ui->PEdit->text();
    QString speed = ui->VEdit->text();
    QString defocuse = ui->FEdit->text();
    QString remark = ui->RemarkEdit->text();

    stuInfo.insert("pid" ,pid );
    stuInfo.insert("baseMetal" ,baseMetal );
    stuInfo.insert("Joint" ,Joint );
    stuInfo.insert("gas" ,gas );
    stuInfo.insert("pianjiao" ,pianjiao );
    stuInfo.insert("position" ,position );
    stuInfo.insert("power" ,power );
    stuInfo.insert("speed" ,speed );
    stuInfo.insert("defocuse" ,defocuse );
    stuInfo.insert("remark" ,remark );

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("HostName.db");
    db.setDatabaseName("DataManager");
    db.open();

    if(quanju::m_operateType == 0)
    {
        QString pid = stuInfo.value("pid").toString();
        QString baseMetal = stuInfo.value("baseMetal").toString();
        QString Joint = stuInfo.value("Joint").toString();
        QString gas = stuInfo.value("gas").toString();
        QString pianjiao = stuInfo.value("pianjiao").toString();
        QString position = stuInfo.value("position").toString();
        QString power =stuInfo.value("power").toString();
        QString speed =stuInfo.value("speed").toString();
        QString defocuse = stuInfo.value("defocuse").toString();
        QString remark = stuInfo.value("remark").toString();

        QString sql;
        sql = QString("insert into LaserManager (pid,baseMetal ,joint ,gas ,pianjiao ,position , power ,speed ,defocuse ,remark)"
                      " VALUES ('%1', '%2' , '%3' , '%4' , '%5' , '%6' , '%7' , '%8' ,'%9', '%10')")
                .arg(pid).arg(baseMetal).arg(Joint).arg(gas).arg(pianjiao).arg(position).arg(power).arg(speed).arg(defocuse).arg(remark);

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
        QString baseMetal = stuInfo.value("baseMetal").toString();
        QString Joint = stuInfo.value("Joint").toString();
        QString gas = stuInfo.value("gas").toString();
        QString pianjiao = stuInfo.value("pianjiao").toString();
        QString position = stuInfo.value("position").toString();
        QString power =stuInfo.value("power").toString();
        QString speed =stuInfo.value("speed").toString();
        QString defocuse = stuInfo.value("defocuse").toString();
        QString remark = stuInfo.value("remark").toString();

        QString sql;
        sql = QString("UPDATE LaserManager "
                      "set pid = '%0' ,baseMetal = '%2' ,joint = '%3',"
                      "gas = '%4',pianjiao = '%5',position = '%6', power = '%7',speed = '%8',defocuse = '%9',remark = '%10'"
                      " where pid = '%0' ")
                .arg(pid).arg(baseMetal).arg(Joint).arg(gas).arg(pianjiao).arg(position).arg(power).arg(speed).arg(defocuse).arg(remark);

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

    clearData(); //清除编辑的数据
    close();
}

void laserwelddlg::on_buttonBox_rejected()
{
        this->close();
}
