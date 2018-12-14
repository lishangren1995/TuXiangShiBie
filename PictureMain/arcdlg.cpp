#include "arcdlg.h"
#include "ui_arcdlg.h"
#include <QSqlQuery>
#include <QMessageBox>

arcdlg::arcdlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::arcdlg)
{
    ui->setupUi(this);
}

arcdlg::~arcdlg()
{
    delete ui;
}

void arcdlg::setEditData(QStringList rowData)
{
    ui->PIDEdit->setText(rowData.at(0));
    ui->baseMetalEdit->setText(rowData.at(1));
    ui->JointEdit->setText(rowData.at(2));
    ui->gasEdit->setText(rowData.at(3));
    ui->HansiEdit->setText(rowData.at(4));
    ui->IEdit->setText(rowData.at(5));
    ui->V_Edit->setText(rowData.at(6));
    ui->songsiEdit->setText(rowData.at(7));
    ui->pianjiaoEdit->setText(rowData.at(8));
    ui->positionEdit->setText(rowData.at(9));
    ui->PEdit->setText(rowData.at(10));
    ui->SpeedEdit->setText(rowData.at(11));
//    ui->FEdit->setText(rowData.at(12));
//    ui->RemarkEdit->setText(rowData.at(13));
    ui->PIDEdit->setEnabled(false);
}

void arcdlg::clearData()
{
    ui->PIDEdit->clear();
    ui->baseMetalEdit->clear();
    ui->JointEdit->clear();
    ui->gasEdit->clear();
    ui->HansiEdit->clear();
    ui->IEdit->clear();
    ui->V_Edit->clear();
    ui->songsiEdit->clear();
    ui->pianjiaoEdit->clear();
    ui->positionEdit->clear();
    ui->PEdit->clear();
    ui->SpeedEdit->clear();
//    ui->FEdit->clear();
//    ui->RemarkEdit->clear();
}


void arcdlg::on_buttonBox_2_accepted()
{
    QVariantMap stuInfo;

    QString pid = ui->PIDEdit->text();
    QString baseMetal = ui->baseMetalEdit->text();
    QString Joint = ui->JointEdit->text();
    QString gas = ui->gasEdit->text();
    QString hansi = ui->HansiEdit->text();
    QString dianliu = ui->IEdit->text();
    QString dianya = ui->V_Edit->text();
    QString songsi = ui->songsiEdit->text();
    QString pianjiao = ui->pianjiaoEdit->text();
    QString position = ui->positionEdit->text();
    QString power = ui->PEdit->text();
    QString speed = ui->SpeedEdit->text();
//    QString defocuse = ui->FEdit->text();
//    QString remark = ui->RemarkEdit->text();


    stuInfo.insert("pid" ,pid );
    stuInfo.insert("baseMetal" ,baseMetal );
    stuInfo.insert("Joint" ,Joint );
    stuInfo.insert("gas" ,gas );
    stuInfo.insert("hansi" ,hansi );
    stuInfo.insert("dianliu" ,dianliu );
    stuInfo.insert("dianya" ,dianya );
    stuInfo.insert("songsi" ,songsi );
    stuInfo.insert("pianjiao" ,pianjiao );
    stuInfo.insert("position" ,position );
    stuInfo.insert("power" ,power );
    stuInfo.insert("speed" ,speed );
//    stuInfo.insert("defocuse" ,defocuse );
//    stuInfo.insert("remark" ,remark );



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
        QString hansi =stuInfo.value("hansi").toString();
        QString dianliu = stuInfo.value("dianliu").toString();
        QString dianya = stuInfo.value("dianya").toString();
        QString songsi = stuInfo.value("songsi").toString();
        QString pianjiao = stuInfo.value("pianjiao").toString();
        QString position = stuInfo.value("position").toString();
        QString power = stuInfo.value("power").toString();
        QString speed = stuInfo.value("speed").toString();
//        QString defocuse = stuInfo.value("defocuse").toString();
//        QString remark = stuInfo.value("remark").toString();

        QString sql;
        sql = QString("insert into ArcManager1 (wps,date,mucai,hjfangfa,jietou,weizhi,zhijing,dianliu,dianya,dlzhonglei,songsisd,speed)"
                      " VALUES ('%1', '%2' , '%3' , '%4' , '%5' , '%6' , '%7' , '%8' ,'%9', '%10', '%11' , '%12' )")
                .arg(pid).arg(baseMetal).arg(Joint).arg(gas).arg(hansi).arg(dianliu).arg(dianya).arg(songsi).arg(pianjiao).arg(position).arg(power).arg(speed);

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
        QString hansi =stuInfo.value("hansi").toString();
        QString dianliu = stuInfo.value("dianliu").toString();
        QString dianya = stuInfo.value("dianya").toString();
        QString songsi = stuInfo.value("songsi").toString();
        QString pianjiao = stuInfo.value("pianjiao").toString();
        QString position = stuInfo.value("position").toString();
        QString power = stuInfo.value("power").toString();
        QString speed = stuInfo.value("speed").toString();
//        QString defocuse = stuInfo.value("defocuse").toString();
//        QString remark = stuInfo.value("remark").toString();

        QString sql;
        sql = QString("UPDATE ArcManager1 "
                      "set wps = '%0' ,date = '%2' ,mucai = '%3',"
                      "hjfangfa = '%4',jietou = '%5',weizhi = '%6', zhijing = '%7',dianliu = '%8',dianya = '%9',dlzhonglei = '%10',songsisd = '%11',speed = '%12'"
                      " where wps = '%0' ")
                .arg(pid).arg(baseMetal).arg(Joint).arg(gas).arg(hansi).arg(dianliu).arg(dianya).arg(songsi).arg(pianjiao).arg(position).arg(power).arg(speed);

        QSqlQuery query;
        bool ok = query.exec(sql);
        if(ok)
        {
            emit signalStuInfo();//通过信号signalStuInfo直接调用槽函数ExecAddSql

            QMessageBox::information(this ,tr("提示") , tr("修改成功!"));

        }
        else
        {
            QMessageBox::information(this ,tr("提示") , tr("修改失败!"));
        }
    }

//    db.close();
    ui->PIDEdit->setEnabled(true);
    clearData(); //清除编辑的数据
    close();
}

void arcdlg::on_buttonBox_2_rejected()
{
      ui->PIDEdit->setEnabled(true);
      clearData(); //清除编辑的数据
      this->close();
}
