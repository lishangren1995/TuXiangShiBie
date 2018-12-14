#include "imagemanager.h"
#include "ui_imagemanager.h"

ImageManager::ImageManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageManager)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(10);
    ui->tableWidget->setColumnWidth(1,300);
    //ui->tableWidget->setColumnWidth(1,120);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() <<"焊缝编号" << "工艺编号"<< "检测时间"
                                                <<"检测人员"<<"飞溅数量" <<"飞溅面积" <<"下塌数量" <<"下塌面积" <<"检测结果"<<"备注");

    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

}

ImageManager::~ImageManager()
{
    delete ui;
}

void ImageManager::appendRowData(QStringList rowData)
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

void ImageManager::clearTableData()
{
    //清除表格
    int rowCount = ui->tableWidget->rowCount();
    for(int r = rowCount-1 ; r >=0 ; r--)
    {
        ui->tableWidget->removeRow(r);
    }
}

QStringList ImageManager::getCurrentRowData()
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

QString ImageManager::getCurrentID()
{
    QString ID ;
    int row = ui->tableWidget->currentRow();
    if(row != -1)
    {
        ID =  ui->tableWidget->item(row , 0)->text();
    }
    return ID;
}
