#include "arcmanager.h"
#include "ui_arcmanager.h"

ArcManager::ArcManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArcManager)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(12);
    ui->tableWidget->setColumnWidth(0,120);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() <<"  WPS号  " << "日期"<< "母材型号"
                                                <<"焊接方法"<<"街头类型"<<"焊接位置"<<"送丝直径"<<"焊接电流"<<"焊接电压" <<"电流种类" <<"送丝速度"<<"焊接速度");

    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

ArcManager::~ArcManager()
{
    delete ui;
}

void ArcManager::appendRowData(QStringList rowData)
{
    int row = ui->tableWidget->rowCount();

    ui->tableWidget->insertRow(row);

    for(int i  = 0 ; i < rowData.size() ; i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(rowData.at(i));
        ui->tableWidget->setItem(row , i , item);
    }
}

void ArcManager::clearTableData()
{
    //清除表格
    int rowCount = ui->tableWidget->rowCount();
    for(int r = rowCount-1 ; r >=0 ; r--)
    {
        ui->tableWidget->removeRow(r);
    }
}

QStringList ArcManager::getCurrentRowData()
{
    QStringList rowData;
    int row = ui->tableWidget->currentRow();
    if(row != -1)
    {
        rowData << ui->tableWidget->item(row , 0)->text();
        rowData << ui->tableWidget->item(row , 1)->text();
        rowData << ui->tableWidget->item(row , 2)->text();
        rowData << ui->tableWidget->item(row , 3)->text();
        rowData << ui->tableWidget->item(row , 4)->text();
        rowData << ui->tableWidget->item(row , 5)->text();
        rowData << ui->tableWidget->item(row , 6)->text();
        rowData << ui->tableWidget->item(row , 7)->text();
        rowData << ui->tableWidget->item(row , 8)->text();
        rowData << ui->tableWidget->item(row , 9)->text();
        rowData << ui->tableWidget->item(row , 10)->text();
        rowData << ui->tableWidget->item(row , 11)->text();
    }
    return rowData;
}

QString ArcManager::getCurrentID()
{
    QString ID ;
    int row = ui->tableWidget->currentRow();
    if(row != -1)
    {
        ID =  ui->tableWidget->item(row , 0)->text();
    }
    return ID;
}
