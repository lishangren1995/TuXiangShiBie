#include "showwidget.h"
#include <QHBoxLayout>
#include <QTreeWidgetItem>
#include<QHeaderView>
ShowWidget::ShowWidget(QWidget *parent) : QWidget(parent)
{
   graph = new QGraphicsView;
   //graph->setv
   table_widget=new QTableWidget;
   table_widget->setColumnCount(2); //设置列数
   table_widget->horizontalHeader()->setDefaultSectionSize(140);
   //table_widget->horizontalHeader()->setClickable(false); //设置表头不可点击（默认点击后进行排序）
   QStringList header;
   header<<tr("编号")<<tr("大小");
   table_widget->setHorizontalHeaderLabels(header);
   table_widget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
   table_widget->setStyleSheet("selection-background-color:lightblue;");
   table_widget->setColumnCount(2);
   table_widget->setRowCount(50);
   QTableWidgetItem *a;
   QString b="111111";
   a=new QTableWidgetItem(b);
  // table_widget->setItem(1, 0, new QTableWidgetItem("abc"));

  // menuTree = new QTreeWidget;
   //menuTree->setHeaderLabel(tr("系统主菜单"));
   QHBoxLayout *mainLayout = new QHBoxLayout(this);
   mainLayout->addWidget(menuTree);
   mainLayout->addWidget(graph);
   mainLayout->addWidget(table_widget);
   mainLayout->setStretchFactor(menuTree,1);
   mainLayout->setStretchFactor(graph,7);
   mainLayout->setStretchFactor(table_widget,2);
   //initTreeWidget();
}

//void ShowWidget::initTreeWidget()
//{
//   menuTree->clear();
//   {
//       QTreeWidgetItem *fileTree = new QTreeWidgetItem(menuTree);    //文件菜单
//       fileTree->setText(0,tr("文件"));
//       QTreeWidgetItem *open = new QTreeWidgetItem(fileTree);
//       open->setText(0,tr("打开"));
//       open->setIcon(0,QIcon("open.png"));
//       QTreeWidgetItem *camera = new QTreeWidgetItem(fileTree);
//       camera->setText(0,tr("打开相机"));
//       camera->setIcon(0,QIcon("camera.png"));
//       QTreeWidgetItem *newFile = new QTreeWidgetItem(fileTree);
//       newFile->setText(0,tr("新建"));
//       newFile->setIcon(0,QIcon("new.png"));
//       QTreeWidgetItem *addressIP = new QTreeWidgetItem(fileTree);
//       addressIP->setText(0,tr("连续采集保存地址"));
//       addressIP->setIcon(0,QIcon("address.png"));
//       QTreeWidgetItem *save = new QTreeWidgetItem(fileTree);
//       save->setText(0,tr("保存"));
//       save->setIcon(0,QIcon("save.png"));
//       QTreeWidgetItem *printText = new QTreeWidgetItem(fileTree);
//       printText->setText(0,tr("打印文本"));
//       printText->setIcon(0,QIcon("printText.png"));
//       QTreeWidgetItem *printImage = new QTreeWidgetItem(fileTree);
//       printImage->setText(0,tr("打印图像"));
//       printImage->setIcon(0,QIcon("printImage.png"));
//       QTreeWidgetItem *exit = new QTreeWidgetItem(fileTree);
//       exit->setText(0,tr("退出"));
//       exit->setIcon(0,QIcon("exit.png"));
//   }
//   {
//       QTreeWidgetItem *editTree = new QTreeWidgetItem(menuTree);    //编辑菜单
//       editTree->setText(0,tr("编辑"));
//       QTreeWidgetItem *zoomIn = new QTreeWidgetItem(editTree);
//       zoomIn->setText(0,tr("放大"));
//       zoomIn->setIcon(0,QIcon("zoomIn.png"));
//       QTreeWidgetItem *zoomOut = new QTreeWidgetItem(editTree);
//       zoomOut->setText(0,tr("缩小"));
//       zoomOut->setIcon(0,QIcon("zoomOut.png"));
//       QTreeWidgetItem *undo = new QTreeWidgetItem(editTree);
//       undo->setText(0,tr("撤销"));
//       undo->setIcon(0,QIcon("undo.png"));
//       QTreeWidgetItem *redo = new QTreeWidgetItem(editTree);
//       redo->setText(0,tr("恢复"));
//       redo->setIcon(0,QIcon("redo.png"));
//   }
//   {
//       QTreeWidgetItem *pretreatTree = new QTreeWidgetItem(menuTree);    //图像预处理
//       pretreatTree->setText(0,tr("焊缝图像预处理"));
//       QTreeWidgetItem *detail = new QTreeWidgetItem(pretreatTree);
//       detail->setText(0,tr("图像详细信息"));
//       QTreeWidgetItem *transformation = new QTreeWidgetItem(pretreatTree);
//       transformation->setText(0,tr("图像灰度变换"));
//       QTreeWidgetItem *Noreduce = new QTreeWidgetItem(pretreatTree);
//       Noreduce->setText(0,tr("图像降噪"));
//       QTreeWidgetItem *Enhance = new QTreeWidgetItem(pretreatTree);
//       Enhance->setText(0,tr("图像增强"));
//   }
//   {
//       QTreeWidgetItem *SegmentTree = new QTreeWidgetItem(menuTree);    //图像分割提取
//       SegmentTree->setText(0,tr("焊缝图像分割提取"));
//       QTreeWidgetItem *ImgSegment = new QTreeWidgetItem(SegmentTree);
//       ImgSegment->setText(0,tr("图像分割"));
//       QTreeWidgetItem *Contour = new QTreeWidgetItem(SegmentTree);
//       Contour->setText(0,tr("轮廓提取"));
//       QTreeWidgetItem *Califibrate = new QTreeWidgetItem(SegmentTree);
//       Califibrate->setText(0,tr("区域标定"));
//   }
//   {
//       QTreeWidgetItem *weldDITree = new QTreeWidgetItem(menuTree);    //焊缝缺陷识别
//       weldDITree->setText(0,tr("焊缝缺陷识别"));
//       QTreeWidgetItem *Parameter = new QTreeWidgetItem(weldDITree);
//       Parameter->setText(0,tr("特征参数计算"));
//       QTreeWidgetItem *Identify = new QTreeWidgetItem(weldDITree);
//       Identify->setText(0,tr("缺陷识别"));
//   }
//   {
//       QTreeWidgetItem *SystemTree = new QTreeWidgetItem(menuTree);    //图像分割提取
//       SystemTree->setText(0,tr("系统管理"));
//       QTreeWidgetItem *dataInfo = new QTreeWidgetItem(SystemTree);
//       dataInfo->setText(0,tr("数据维护"));
//       QTreeWidgetItem *userInfo = new QTreeWidgetItem(SystemTree);
//       userInfo->setText(0,tr("用户管理"));
//       QTreeWidgetItem *Help = new QTreeWidgetItem(SystemTree);
//       Help->setText(0,tr("系统帮助"));
//   }
//}
