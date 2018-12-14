#include "datamanager.h"
#include "ui_datamanager.h"
#include "adduserdlg.h"
#include <QObject>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QLibrary>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>

datamanager::datamanager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::datamanager)
{
    ui->setupUi(this);

    initUi();//创建四张表tab

    initAddDlg();//添加user里面的两个connect

    m_createDB = new createdb;

    m_createDB->initDB();  //打开数据库

    //onBtnRefresh(); //程序启动时，查询数据

    QList<QStringList> tableData1;

    tableData1 = m_createDB->selectDataFromBase1();
    if(!tableData1.isEmpty())
    {
        m_UserManager->clearTableData();
        QListIterator<QStringList> itr(tableData1);
        while(itr.hasNext())
        {
            m_UserManager->appendRowData(itr.next());
        }
    }

    QList<QStringList> tableData2;
    tableData2 = m_createDB->selectDataFromBase2();
    if(!tableData2.isEmpty())
    {
        m_ImageManager->clearTableData();
        QListIterator<QStringList> itr(tableData2);
        while(itr.hasNext())
        {
            m_ImageManager->appendRowData(itr.next());
        }
    }

//    QList<QStringList> tableData3;
//    tableData3 = m_createDB->selectDataFromBase3();
//    if(!tableData3.isEmpty())
//    {
//        m_ProcessManager->clearTableData();
//        QListIterator<QStringList> itr(tableData3);
//        while(itr.hasNext())
//        {
//            m_ProcessManager->appendRowData(itr.next());
//        }
//    }

    QList<QStringList> tableData4;
    tableData4 = m_createDB->selectDataFromBase4();
    if(!tableData4.isEmpty())
    {
        m_ArcManager->clearTableData();
        QListIterator<QStringList> itr(tableData4);
        while(itr.hasNext())
        {
            m_ArcManager->appendRowData(itr.next());
        }
    }

    a_recorddlg=new recorddlg();
    m_laserwelddlg=new laserwelddlg();
    m_arcdlg=new arcdlg();
    setTabCornerBtn();
}

datamanager::~datamanager()
{
    delete ui;
}

void datamanager::onBtnAdd()
{
    qDebug()<<"onBtnAdd";
    int tab_num=ui->tabWidget->currentIndex();
    quanju::m_operateType = 0;
    if(tab_num==2)
    {
        m_pAddStuDlg->activateWindow();
        m_pAddStuDlg->setWindowTitle(tr("添加: 用户信息"));
        m_pAddStuDlg->exec();
    }
    if(tab_num==1)
    {

        a_recorddlg->activateWindow();
        a_recorddlg->setWindowTitle(tr("添加: 缺陷检测记录"));
        a_recorddlg->exec();

    }
    if(tab_num==3)
    {

        m_laserwelddlg->activateWindow();
        m_laserwelddlg->setWindowTitle(tr("添加: 激光焊接工艺记录"));
        m_laserwelddlg->exec();
    }
    if(tab_num==0)
    {

        m_arcdlg->activateWindow();
        m_arcdlg->setWindowTitle(tr("添加: 激光电弧复合焊接工艺记录"));
        m_arcdlg->exec();
    }

}

void datamanager::onBtnEdit()
{
    qDebug()<<"onBtnEdit";
    int tab_num=ui->tabWidget->currentIndex();

    quanju::m_operateType = 1;
    if(tab_num==2)
    {
        QStringList rowData ;
        rowData = m_UserManager->getCurrentRowData();
        if(rowData.isEmpty())
        {
            QMessageBox::information(this, tr("提示") , tr("请选中需要编辑的数据!"));
            return ;
        }
        else
        {
            m_pAddStuDlg->setEditData(rowData);
        }
        m_pAddStuDlg->activateWindow();
        m_pAddStuDlg->setWindowTitle(tr("修改: 用户信息"));
        m_pAddStuDlg->exec();
    }
    if(tab_num==1)
    {
        QStringList rowData ;
        rowData = m_ImageManager->getCurrentRowData();
        if(rowData.isEmpty())
        {
            QMessageBox::information(this, tr("提示") , tr("请选中需要编辑的数据!"));
            return ;
        }
        else
        {
            a_recorddlg->setEditData(rowData);
        }
        a_recorddlg->activateWindow();
        a_recorddlg->setWindowTitle(tr("修改: 缺陷检测记录"));
        a_recorddlg->exec();
    }
    if(tab_num==3)
    {
        QStringList rowData ;
        rowData = m_ProcessManager->getCurrentRowData();
        if(rowData.isEmpty())
        {
            QMessageBox::information(this, tr("提示") , tr("请选中需要编辑的数据!"));
            return ;
        }
        else
        {
            m_laserwelddlg->setEditData(rowData);
        }
        m_laserwelddlg->activateWindow();
        m_laserwelddlg->setWindowTitle(tr("修改: 激光焊接工艺记录"));
        m_laserwelddlg->exec();
    }
    if(tab_num==0)
    {
        QStringList rowData ;
        rowData = m_ArcManager->getCurrentRowData();
        if(rowData.isEmpty())
        {
            QMessageBox::information(this, tr("提示") , tr("请选中需要编辑的数据!"));
            return ;
        }
        else
        {
            m_arcdlg->setEditData(rowData);
        }
        m_arcdlg->activateWindow();
        m_arcdlg->setWindowTitle(tr("修改: 激光电弧复合焊接工艺记录"));
        m_arcdlg->exec();
    }

}

void datamanager::onBtnDel()
{
    qDebug()<<"onBtnDel";
    int tab_num=ui->tabWidget->currentIndex();
    if(tab_num==2)
    {
        QString ID = m_UserManager->getCurrentID();
        if(ID.isEmpty())
        {
            QMessageBox::information(this , tr("提示") , tr("请选中一条记录！"));
            return ;
        }
        QMessageBox::StandardButton button = QMessageBox::question(this , tr("提示") ,tr("确定删除这一条记录？"));
        if(button == QMessageBox::Yes)
        {
            //删除操作
            ExecDelSql(ID);
        }
    }
    if(tab_num==1)
    {
        QString ID = m_ImageManager->getCurrentID();
        if(ID.isEmpty())
        {
            QMessageBox::information(this , tr("提示") , tr("请选中一条记录！"));
            return ;
        }
        QMessageBox::StandardButton button = QMessageBox::question(this , tr("提示") ,tr("确定删除这一条记录？"));
        if(button == QMessageBox::Yes)
        {
            //删除操作
            QString sql;
            sql = QString("DELETE FROM ImageManager "
                          " where WildID = '%1' ").arg(ID);

            QSqlQuery query;
            bool ok = query.exec(sql);
            if(ok)
            {
                onBtnRefresh(); //重新加载数据
                QMessageBox::information(this ,tr("提示") , tr("删除成功!"));
            }
            else
            {
                QMessageBox::information(this ,tr("提示") , tr("删除失败!"));
            }
        }
    }

    if(tab_num==3)
    {
        QString ID = m_ProcessManager->getCurrentID();
        if(ID.isEmpty())
        {
            QMessageBox::information(this , tr("提示") , tr("请选中一条记录！"));
            return ;
        }
        QMessageBox::StandardButton button = QMessageBox::question(this , tr("提示") ,tr("确定删除这一条记录？"));
        if(button == QMessageBox::Yes)
        {
            //删除操作
            QString sql;
            sql = QString("DELETE FROM LaserManager "
                          " where pid = '%1' ").arg(ID);

            QSqlQuery query;
            bool ok = query.exec(sql);
            if(ok)
            {
                onBtnRefresh(); //重新加载数据
                QMessageBox::information(this ,tr("提示") , tr("删除成功!"));
            }
            else
            {
                QMessageBox::information(this ,tr("提示") , tr("删除失败!"));
            }
        }
    }
    if(tab_num==0)
    {
        QString ID = m_ArcManager->getCurrentID();
        if(ID.isEmpty())
        {
            QMessageBox::information(this , tr("提示") , tr("请选中一条记录！"));
            return ;
        }
        QMessageBox::StandardButton button = QMessageBox::question(this , tr("提示") ,tr("确定删除这一条记录？"));
        if(button == QMessageBox::Yes)
        {
            //删除操作
            QString sql;
            sql = QString("DELETE FROM ArcManager1 "
                          " where wps = '%1' ").arg(ID);

            QSqlQuery query;
            bool ok = query.exec(sql);
            if(ok)
            {
                onBtnRefresh(); //重新加载数据
                QMessageBox::information(this ,tr("提示") , tr("删除成功!"));
            }
            else
            {
                QMessageBox::information(this ,tr("提示") , tr("删除失败!"));
            }
        }
    }
}

void datamanager::onBtnRefresh()
{
    qDebug()<<"onBtnRefresh";
    QList<QStringList> tableData1;

    tableData1 = m_createDB->selectDataFromBase1();
    if(!tableData1.isEmpty())
    {
        m_UserManager->clearTableData();
        QListIterator<QStringList> itr(tableData1);
        while(itr.hasNext())
        {
            m_UserManager->appendRowData(itr.next());
        }
    }

    QList<QStringList> tableData2;
    tableData2 = m_createDB->selectDataFromBase2();
    if(!tableData2.isEmpty())
    {
        m_ImageManager->clearTableData();
        QListIterator<QStringList> itr(tableData2);
        while(itr.hasNext())
        {
            m_ImageManager->appendRowData(itr.next());
        }
    }

//    QList<QStringList> tableData3;
//    tableData3 = m_createDB->selectDataFromBase3();
//    if(!tableData3.isEmpty())
//    {
//        m_ProcessManager->clearTableData();
//        QListIterator<QStringList> itr(tableData3);
//        while(itr.hasNext())
//        {
//            m_ProcessManager->appendRowData(itr.next());
//        }
//    }

    QList<QStringList> tableData4;
    tableData4 = m_createDB->selectDataFromBase4();
    if(!tableData4.isEmpty())
    {
        m_ArcManager->clearTableData();
        QListIterator<QStringList> itr(tableData4);
        while(itr.hasNext())
        {
            m_ArcManager->appendRowData(itr.next());
        }
    }

}

void datamanager::ExecAddSql(QVariantMap stuInfo)
{
    if(quanju::m_operateType == 0)
    {
        QString create_date = stuInfo.value("datetime").toString();
        QString id = stuInfo.value("number").toString();
        QString name = stuInfo.value("name").toString();
        QString sex = stuInfo.value("sex").toString();
        QString age = stuInfo.value("age").toString();
        QString address = stuInfo.value("address").toString();
        QString phone = stuInfo.value("phone").toString();
        QString description = stuInfo.value("desc").toString();

        QString sql;
        sql = QString("insert into UserManager (create_date,id ,name ,sex ,age ,business ,password ,remark)"
                      " VALUES ('%1', '%2' , '%3' , '%4' , '%5' , '%6' , '%7' , '%8')")
                .arg(create_date).arg(id).arg(name).arg(sex).arg(age).arg(address).arg(phone).arg(description);

        QSqlQuery query;
        bool ok = query.exec(sql);
        if(ok)
        {
            QStringList rowData;
            rowData << name <<id <<sex <<age << address <<phone << description ;
            m_UserManager->appendRowData(rowData);

            QMessageBox::information(this ,tr("提示") , tr("添加成功!"));
        }
        else
        {
            QMessageBox::information(this ,tr("提示") , tr("添加失败!"));
        }
    }
}

void datamanager::ExecEditSql(QVariantMap stuInfo)
{
    if(quanju::m_operateType == 1)
    {
        QString create_date = stuInfo.value("datetime").toString();
        QString id = stuInfo.value("number").toString();
        QString name = stuInfo.value("name").toString();
        QString sex = stuInfo.value("sex").toString();
        QString age = stuInfo.value("age").toString();
        QString address = stuInfo.value("address").toString();
        QString phone = stuInfo.value("phone").toString();
        QString description = stuInfo.value("desc").toString();

        QString sql;
        sql = QString("UPDATE UserManager "
                      "set create_date = '%0' ,id = '%2' ,name = '%3',"
                      "sex = '%4',age = '%5',business = '%6', password = '%7',remark = '%8'"
                      " where id = '%9' ")
                .arg(create_date).arg(id).arg(name).arg(sex).arg(age).arg(address).arg(phone).arg(description).arg(id);

        QSqlQuery query;
        bool ok = query.exec(sql);
        if(ok)
        {
            onBtnRefresh(); //重新加载数据
            QMessageBox::information(this ,tr("提示") , tr("修改成功!"));
        }
        else
        {
            QMessageBox::information(this ,tr("提示") , tr("修改失败!"));
        }
    }

}

void datamanager::ExecDelSql(QString id)
{
    QString sql;
    sql = QString("DELETE FROM UserManager "
                  " where id = '%1' ").arg(id);

    QSqlQuery query;
    bool ok = query.exec(sql);
    if(ok)
    {
        onBtnRefresh(); //重新加载数据
        QMessageBox::information(this ,tr("提示") , tr("删除成功!"));
    }
    else
    {
        QMessageBox::information(this ,tr("提示") , tr("删除失败!"));
    }
}

void datamanager::initUi()
{
    //m_ProcessManager= new ProcessManager;
    //ui->tabWidget->addTab(m_ProcessManager,tr("激光焊接工艺"));

    m_ArcManager=new ArcManager;
    ui->tabWidget->addTab(m_ArcManager,tr("电弧焊焊接工艺"));

    m_ImageManager = new ImageManager;
    ui->tabWidget->addTab(m_ImageManager,tr("焊缝缺陷检测记录"));

    m_UserManager= new UserManager;
    ui->tabWidget->addTab(m_UserManager,tr("用户管理"));
}

void datamanager::setTabCornerBtn()
{
    connect(ui->pshuaixin , SIGNAL(clicked(bool)) , this ,SLOT(onBtnRefresh()));
    connect(ui->ptianjia , SIGNAL(clicked(bool)) , this ,SLOT(onBtnAdd()));
    connect(ui->pxiugai , SIGNAL(clicked(bool)), this ,SLOT(onBtnEdit()));
    connect(ui->pshanchu , SIGNAL(clicked(bool)) ,this , SLOT(onBtnDel()));
}

void datamanager::initAddDlg()
{
    m_pAddStuDlg = new adduserdlg;
    connect(m_pAddStuDlg , SIGNAL(signalStuInfo(QVariantMap)) , this ,SLOT(ExecAddSql(QVariantMap)));
    connect(m_pAddStuDlg , SIGNAL(signalStuInfo(QVariantMap)) , this ,SLOT(ExecEditSql(QVariantMap)));
    m_arcdlg=new arcdlg;
    connect(m_arcdlg , SIGNAL(signalStuInfo()) , this ,SLOT(onBtnRefresh()));
}

void datamanager::on_pshuaixin_clicked()
{
    onBtnRefresh();
}


void datamanager::on_pushButton_kaishi_clicked()
{
    QStringList rowData ;
    rowData = m_ArcManager->getCurrentRowData();
    wps=rowData.at(0);
    ui->lineEdit->setText(wps);
    emit GetUdpLogMsg(wps);
    this->close();
}
