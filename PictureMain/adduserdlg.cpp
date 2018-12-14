#include "adduserdlg.h"
#include "ui_adduserdlg.h"
#include <QDateTime>
#include <QStringList>
#include <QString>

adduserdlg::adduserdlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adduserdlg)
{
    ui->setupUi(this);
}

adduserdlg::~adduserdlg()
{
    delete ui;
}

void adduserdlg::setEditData(QStringList rowData)
{
    ui->NameEdit_2->setText(rowData.at(0));
    ui->IDEdit_3->setText(rowData.at(1));
    ui->AgeSpinBox_3->setValue(rowData.at(3).toInt());
    ui->SexComboBox_3->setCurrentText(rowData.at(2));
    ui->businessEdit->setText(rowData.at(4));
    ui->passEdit->setText(rowData.at(5));
    ui->RemarkText->setText(rowData.at(6));
    //ui->IDEdit_3->setEnabled(false);
}

void adduserdlg::on_buttonBox_4_accepted()
{
    QVariantMap stuInfo;

    QString name = ui->NameEdit_2->text();
    QString number = ui->IDEdit_3->text();
    QString age = ui->AgeSpinBox_3->text();
    QString sex = ui->SexComboBox_3->currentText();
    QString address = ui->businessEdit->text();
    QString phone = ui->passEdit->text();
    QString desc = ui->RemarkText->toPlainText();

    QString datetime = QDateTime::currentDateTime().toString();

    stuInfo.insert("datetime" ,datetime );
    stuInfo.insert("name" ,name );
    stuInfo.insert("number" ,number );
    stuInfo.insert("age" ,age );
    stuInfo.insert("sex" ,sex );
    stuInfo.insert("address" ,address );
    stuInfo.insert("phone" ,phone );
    stuInfo.insert("desc" ,desc );

    emit signalStuInfo(stuInfo);//通过信号signalStuInfo直接调用槽函数ExecAddSql

    clearData(); //清除编辑的数据
    close();
    //ui->IDEdit_3->setEnabled(true);
}

void adduserdlg::on_buttonBox_4_rejected()
{
    close();
    ui->IDEdit_3->setEnabled(true);
}

void adduserdlg::clearData()
{
    ui->NameEdit_2->clear();
    ui->IDEdit_3->clear();
    ui->AgeSpinBox_3->clear();
    ui->businessEdit->clear();
    ui->passEdit->clear();
    ui->RemarkText->clear();
}
