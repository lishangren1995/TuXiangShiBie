#include "processmanager.h"
#include "ui_processmanager.h"

ProcessManager::ProcessManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProcessManager)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(10);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() <<"工艺编号" << "母材规格"<< "接头类型"
                                                <<"保护气体"<<"激光偏角" <<"光斑位置" <<"激光功率"<<"焊接速度"<<"离焦量"<<"备注");

    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ProcessManager::~ProcessManager()
{
    delete ui;
}
void ProcessManager::appendRowData(QStringList rowData)
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

void ProcessManager::clearTableData()
{
    //清除表格
    int rowCount = ui->tableWidget->rowCount();
    for(int r = rowCount-1 ; r >=0 ; r--)
    {
        ui->tableWidget->removeRow(r);
    }
}

QStringList ProcessManager::getCurrentRowData()
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
    }
    return rowData;
}

QString ProcessManager::getCurrentID()
{
    QString ID ;
    int row = ui->tableWidget->currentRow();
    if(row != -1)
    {
        ID =  ui->tableWidget->item(row , 0)->text();
    }
    return ID;
}
