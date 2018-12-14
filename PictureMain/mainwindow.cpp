#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QPrintDialog>
#include <QPrinter>
#include <QPainter>
#include <QColorDialog>
#include <QColor>
#include <QTextList>
#include <QStatusBar>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QSettings>
#include "mainwindow.h"
#include "utils.h"
#include "dialognoreduce.h"
#include <QTime>

#include <QDialog>
#include <QPrintDialog>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <iostream>

#include<opencv2\imgproc\imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include"yuchuli.h"
#include"fenge.h"
#include"histogram.h"
#include "SDK.h"
//#include"xiangji.h"

#include <QProcess>
using namespace cv;
using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setWindowState(Qt::WindowMaximized);
    setWindowTitle(tr("基于机器视觉的焊缝外观缺陷检测系统"));			//设置窗体标题
    lable->setText(tr("||欢迎使用焊缝缺陷检测系统!|| 当前用户：李尚仁"));
    //m_recent = new RecentOpened(recentMenu);

    chushi = imread("zhgt.jpg");
    int a=ui->graphicsView->width();
    int b= ui->graphicsView->height();
    cv::resize(chushi, chushi, Size(a, b), 0, 0, INTER_LINEAR);
    //cv::resize(chushi, chushi, Size(chushi.cols*1.5, chushi.rows*1.5), 0, 0, INTER_LINEAR);
    QPixmap pixmap= Mat2Pixmap(chushi);//Mat对象转化为Qpixmap对象
    pixItem = new PixItem(pixmap);
    scene->addItem(pixItem);
    pixItem->setPos(0,0);
    ui->graphicsView->setScene(scene);

    m_showImg = imread("zhgt.jpg");
    m_result = m_showImg;

    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(60);
    ui->tableWidget->setRowCount(200);
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    ui->tableWidget->setStyleSheet("selection-background-color:lightblue;");

    ui->tableWidget_2->horizontalHeader()->setDefaultSectionSize(60);
    ui->tableWidget_2->setRowCount(200);
    ui->tableWidget_2->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    ui->tableWidget_2->setStyleSheet("selection-background-color:lightblue;");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_dakai_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("打开图像"),"",tr("Image Files(*.png *.jpg *.bmp)"));
    {
        if(fileName.isEmpty()) return;
        //m_recent->UpdateList(fileName);//更新最近打开图片列表
        //m_showImg = imread(ws2s(fileName.toStdWString()));
        filedakai=fileName;
        loadImage(fileName,m_showImg);//导入图并重定义大小
        chushiImg=m_showImg;
        //loadImage(fileName,chushiImg);
        on_pushButton_7_clicked();
        loadImage1(m_showImg);


    }
}

void MainWindow::loadImage(const QString &fileName,cv::Mat &showImg)
{
    showImg = cv::imread(ws2s(fileName.toStdWString()));
    double alpha = 1.0;
    int width = showImg.cols;
    int height =showImg.rows;
    int a=ui->graphicsView->width();
    int b= ui->graphicsView->height();
    if(width>a || height>b)
    {
        alpha = Max((double)width/a,(double)height/b);
        width /= alpha;
        height /= alpha;
    }
    if(alpha!=1)
        cv::resize(showImg,showImg,cv::Size(width,height), 0, 0, INTER_LINEAR);
    //cv::resize(showImg,showImg,cv::Size(showImg.cols / 3, showImg.rows / 3), 0, 0, INTER_LINEAR);
}

void MainWindow::loadImage1(Mat showImg1)//将视图对象与场景相连
{
    pixshow = Mat2Pixmap(showImg1);
    pixItem = new PixItem(pixshow);
    scene->clear();
    scene->addItem(pixItem);
    pixItem->setPos(0,0);
    ui->graphicsView->setScene(scene);
}


void MainWindow::on_Tyuchuli_triggered()
{
    yuchuli y;
    y.yclimage(m_showImg);
    //y.yclimage(chushiImg);
    loadImage1(m_showImg);
}

void MainWindow::on_Tfenge_triggered()
{
    fenge f;
    m_showImg= f.gra(m_showImg);
    cv::Mat foreground(chushiImg.size(), CV_8UC3, cv::Scalar(255, 255, 255));
    //背景值为 GC_BGD=0，作为掩码
    Mat Frame=chushiImg;
    Frame.copyTo(foreground, m_showImg);
    //cvtColor( m_showImg, m_showImg,CV_BGR2GRAY);//三通道转单通道
    loadImage1(foreground);
}

void MainWindow::on_Tshibie_triggered()
{
    vector<Feather> featherList;                    // 存放连通域特征
    Mat dst;
    int nliantongyu;
    fenge f;
    nliantongyu=f.bwLabel(m_showImg,dst,featherList);

    string nliantongyu_string = to_string(nliantongyu);
    QString nliantongyu_qstring;
    nliantongyu_qstring = QString::fromStdString(nliantongyu_string);
    ui->lineEdit->setText(nliantongyu_qstring);
    // 为了方便观察，可以将label“放大”
    //    for (int i = 0; i < dst.rows; i++)
    //    {
    //        uchar *p = dst.ptr<uchar>(i);
    //        for (int j = 0; j < dst.cols; j++)
    //        {
    //            p[j] = 30 * p[j];
    //        }
    //    }

    Point p;
    int i=0;
    if(chushiImg.channels()==1)
    {
        Mat frame;
        frame = cvCreateImage(chushiImg.size(), IPL_DEPTH_8U, 3);
        cvtColor(chushiImg, frame, CV_GRAY2BGR);
        chushiImg=frame;
    }
    int area=0;
    for (vector<Feather>::iterator it = featherList.begin(); it < featherList.end(); it++)
    {
        area+=it->area;
        cv::rectangle(chushiImg, it->boundingbox, cv::Scalar(0,0,255));
        cv::Rect r0 = it->boundingbox;
        p.x = r0.x;
        p.y = r0.y;

        string number_buf_string = to_string(it->area);
        QString qstr;
        qstr = QString::fromStdString(number_buf_string);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(qstr));
        //ui->tableWidget->item(i, 0)->setTextAlignment(Qt::AlignCenter);//设置单元格内容居中

        string number_buf_string1 = to_string(it->length);
        QString qstr1;
        qstr1 = QString::fromStdString(number_buf_string1);
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(qstr1));
        //ui->tableWidget->item(i,1)->setTextAlignment(Qt::AlignCenter);

        string number_buf_string2 = to_string(it->r);
        QString qstr2;
        qstr2 = QString::fromStdString(number_buf_string2);
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(qstr2));
        //ui->tableWidget->item(i,2)->setTextAlignment(Qt::AlignCenter);

        i++;
        string num=to_string(i);
        //putText(dst, num, p, cv::FONT_HERSHEY_COMPLEX, 0.7, cv::Scalar(180, 180, 180), 0.7, 8, 0);
        putText(chushiImg, num, p, cv::FONT_HERSHEY_COMPLEX, 0.7, cv::Scalar(0,0,255), 0.7, 8, 0);
    }

    //double da=area/(ui->graphicsView->width()*ui->graphicsView->height());
    double da=area/7124.51;
    string area_string = to_string(da);
    QString area_qstring;
    area_qstring = QString::fromStdString(area_string);
    ui->lineEdit_3->setText(area_qstring);

    if(m_showImg.channels()==1)
    {
        Mat mframe;
        mframe = cvCreateImage(m_showImg.size(), IPL_DEPTH_8U, 3);
        cvtColor(m_showImg, mframe, CV_GRAY2BGR);
        m_showImg=mframe;
        m_showImg=chushiImg;
    }
    loadImage1(chushiImg);

    //chushiImg用来承载框框
    //huanyuan用来一键还原
}

void MainWindow::on_baocun_triggered()
{
    QString selectedFilter;
    QString filename = QFileDialog::getSaveFileName(this,tr("保存"),"未命名",tr("*.jpg;; *.png;; *.bmp"), &selectedFilter);
    QPixmap pixmap = Mat2Pixmap(m_showImg);
    pixmap.save(filename,"jpg");
    QMessageBox::information(this,"提醒","保存成功");


}

void MainWindow::on_pushButton_clicked()//飞溅检测
{
    //    on_Tyuchuli_triggered();
    //    on_Tfenge_triggered();
    loadImage(filedakai,m_showImg);
    loadImage(filedakai,chushiImg);
    yuchuli y;
    y.yclimage(m_showImg);
    fenge f;
    m_showImg= f.gra(m_showImg);
    on_Tshibie_triggered();
}

void MainWindow::on_pushButton_2_clicked()//下塌检测
{
    loadImage(filedakai,m_showImg);
    loadImage(filedakai,chushiImg);
    on_xiata_triggered();
}

void MainWindow::on_djgluru_triggered()
{
    m_LaserWeld = new laserwelddlg(this);
    m_LaserWeld->activateWindow();
    m_LaserWeld->setWindowTitle(tr("添加: 激光焊接工艺信息"));
    m_LaserWeld->exec();

}

void MainWindow::on_shujuku_triggered()//打开数据库
{

    m_dataManager = new datamanager();
    connect(m_dataManager, SIGNAL(GetUdpLogMsg(QString )), this, SLOT(PrintLogMsg(QString )));
    m_dataManager->setWindowTitle(tr("数据维护"));
    m_dataManager->show();
}

void MainWindow::on_jcbaocun_triggered()
{
    m_recordDlg = new recorddlg(this);
    m_recordDlg->activateWindow();
    m_recordDlg->setWindowTitle(tr("焊缝缺陷检测结果记录"));
    m_recordDlg->exec();
}

void MainWindow::on_fhluru_triggered()
{
    m_ArcDlg = new arcdlg(this);
    //m_ArcDlg->activateWindow();
    m_ArcDlg->setWindowTitle(tr("添加: 激光电弧复合焊接工艺信息"));
    m_ArcDlg->exec();
}

void MainWindow::on_pushButton_3_clicked()//开始采集
{
    // discover camera
    //发现设备
    xj.ret = GENICAM_getSystemInstance(&xj.pSystem);//设备发现函数，<0创建失败,=0创建成功
    //        if (-1 == xj.ret)
    //        {
    //         QMessageBox::information(this ,tr("提示") , tr("未发现设备!"));
    //        }

    xj.ret = xj.pSystem->discovery(xj.pSystem, &xj.pCameraList, &xj.cameraCnt, typeGige);
    //        if (-1 == xj.ret)
    //        {
    //         QMessageBox::information(this ,tr("提示") , tr("发现失败!"));
    //        }

    if (xj.cameraCnt < 1)
    {
        QMessageBox::information(this ,tr("提示") , tr("无相机"));
        return;
    }
    xj.pCamera = &xj.pCameraList[0];

    // connect to camera
    //连接设备
    xj.ret = xj.GENICAM_connect(xj.pCamera);
    if (xj.ret == 0)
    {
        QMessageBox::information(this ,tr("提示") , tr("已连接相机"));
    }
    else return;

    xj.modifyCamralExposureTime(xj.pCamera);
    //创建流对象
    xj.ret = xj.GENICAM_CreateStreamSource(xj.pCamera, &pStreamSource);
    if ((xj.ret != 0) || (NULL == pStreamSource))
    {
        return;
    }
    // create frame grabbing thread
    //xj.threadHandle = (HANDLE)_beginthreadex(NULL,0, frameGrabbingProc,NULL,CREATE_SUSPENDED,&xj.threadID);

    //        if ( xj.threadHandle == 0)
    //        {

    //            //注意：需要释放pStreamSource内部对象内存
    //            pStreamSource->release(pStreamSource);
    //        }
    // start grabbing from camera创建框架抓取线程
    //拉流
    xj.ret = xj.GENICAM_startGrabbing(pStreamSource);
    if (xj.ret != 0)
    {

        //注意：需要释放pStreamSource内部对象内存
        pStreamSource->release(pStreamSource);
        return;
    }

    // start grabbing thread开始抓住线程
    //ResumeThread(xj.threadHandle);

    int32_t ret = -1;


    GENICAM_Frame* pFrame;
    MainWindow::p=1;
    //    for (i = 0; i < 30; i++)
    //    {
    while(MainWindow::p){
        ret = pStreamSource->getFrame(pStreamSource, &pFrame, INFINITE);
        if (ret < 0)
        {
            continue;
        }

        ret = pFrame->valid(pFrame);
        if (ret < 0)
        {
            //注意：使用该帧后需要显示释放
            pFrame->release(pFrame);
            continue;
        }

        const void* pdata = pFrame->getImage(pFrame);
        //cv::Mat imagemat(800,600,CV_8UC3,const_cast<void*>(pdata));

        cv::Mat imagemat(2048, 3072, CV_8U, const_cast<void*>(pdata));
        m_showImg=imagemat;

        int a=ui->graphicsView->width();
        int b= ui->graphicsView->height();
        cv::resize(m_showImg, m_showImg, Size(a, b), 0, 0, INTER_LINEAR);

        chushiImg=m_showImg;
        huanyuan=m_showImg;

        pixshow = Mat2Pixmap(m_showImg);
        pixItem = new PixItem(pixshow);
        scene->clear();
        scene->addItem(pixItem);
        pixItem->setPos(0,0);
        ui->graphicsView->setScene(scene);			//将视图对象与场景相连

        qsleep(1);

        //        QPixmap pixmap = Mat2Pixmap(m_showImg);
        //        String bianhaoi=std::to_string(i);
        //        String sfile="E:\\"+bianhaoi+".jpg";
        //        QString file=QString::fromStdString(sfile);
        //        pixmap.save(file,"jpg");

        //注意：使用该帧后需要显示释放
        pFrame->release(pFrame);
    }
    //    }
    //WaitForSingleObject(xj.threadHandle, INFINITE);//等待单个对象
    //CloseHandle(xj.threadHandle);//关

    // stop grabbing from camera
    //int32_t ge;
    //ge=xj.GENICAM_stopGrabbing(pStreamSource);
    int32_t isStopGrabbingSuccess;

    isStopGrabbingSuccess = pStreamSource->stopGrabbing(pStreamSource);
    //注意：需要释放pStreamSource内部对象内存
    pStreamSource->release(pStreamSource);
    //getchar();
}

void MainWindow::on_pushButton_4_clicked()
{
    MainWindow::p=0;
}





void MainWindow::on_fangda_triggered()
{
    if(pixshow.isNull())
        return;
    QMatrix martix;
    martix.scale(2,2);
    pixshow = pixshow.transformed(martix);

    //QImage img = pixmap.toImage();
    //m_showImg=QImage2cvMat(img);

    pixItem = new PixItem(pixshow);
    scene->clear();
    scene->addItem(pixItem);
    pixItem->setPos(0,0);
    ui->graphicsView->setScene(scene);

    // lable->setText(tr(" 当前操作：图像放大"));
}

void MainWindow::on_suoxiao_triggered()
{
    if(pixshow.isNull())
        return;
    QMatrix martix;
    martix.scale(0.5,0.5);
    pixshow = pixshow.transformed(martix);
    pixItem = new PixItem(pixshow);
    scene->clear();
    scene->addItem(pixItem);
    pixItem->setPos(0,0);
    ui->graphicsView->setScene(scene);
}

void MainWindow::on_xuanzhuan90_triggered()
{

    if(pixshow.isNull())
        return;
    QMatrix martix;
    martix.rotate(90);
    pixshow = pixshow.transformed(martix);
    pixItem = new PixItem(pixshow);
    scene->clear();
    scene->addItem(pixItem);
    pixItem->setPos(0,0);
    ui->graphicsView->setScene(scene);
}

void MainWindow::on_xuanzhuan180_triggered()
{
    if(pixshow.isNull())
        return;
    QMatrix martix;
    martix.rotate(180);
    pixshow = pixshow.transformed(martix);
    pixItem = new PixItem(pixshow);
    scene->clear();
    scene->addItem(pixItem);
    pixItem->setPos(0,0);
    ui->graphicsView->setScene(scene);
}

void MainWindow::on_guanbitu_triggered()
{
    scene->clear();
    ui->graphicsView->setScene(scene);
    m_showImg.release();
}

void MainWindow::on_pushButton_xuanze_clicked()
{
    m_dataManager = new datamanager();
    connect(m_dataManager, SIGNAL(GetUdpLogMsg(QString )), this, SLOT(PrintLogMsg(QString )));
    m_dataManager->setWindowTitle(tr("数据维护"));
    m_dataManager->show();
}

void MainWindow::PrintLogMsg(QString msg)
{
    ui->lineEdit_2->setText(msg);
}

void MainWindow::on_pushButton_6_clicked()
{
    m_recordDlg = new recorddlg(this);
    QString q1=ui->lineEdit_2->text();
    QString q2=ui->lineEdit->text();
    QString q3=ui->lineEdit_3->text();
    QString q4=ui->lineEdit_4->text();
    QString q5=ui->lineEdit_5->text();
    QString q6=ui->lineEdit_6->text();

    connect(this, SIGNAL(getmsg(QString,QString,QString,QString,QString,QString )), m_recordDlg, SLOT(printdata(QString,QString,QString,QString,QString,QString)));
    emit getmsg(q1,q2,q3,q4,q5,q6);
    m_recordDlg->activateWindow();
    m_recordDlg->setWindowTitle(tr("焊缝缺陷检测结果记录"));
    m_recordDlg->exec();
}

void MainWindow::on_jiance_triggered()
{
    QProcess::startDetached("D:\\ruanjian\\jiance\\v5.3.5.exe",QStringList());
}

void MainWindow::qsleep(unsigned int ms)
{
    QTime qtime=QTime::currentTime().addMSecs(ms);
    while(QTime::currentTime()<qtime) QCoreApplication::processEvents(QEventLoop::AllEvents,100);
}

void MainWindow::on_xiata_triggered()
{
    yuchuli y;

    y.yclimage(m_showImg);

    fenge f;
    m_showImg= f.graxiata(m_showImg);
    cv::Mat foreground(chushiImg.size(), CV_8UC3, cv::Scalar(255, 255, 255));

    if(chushiImg.channels()==1)
    {
        Mat mframe;
        mframe = cvCreateImage(chushiImg.size(), IPL_DEPTH_8U, 3);
        cvtColor(chushiImg, mframe, CV_GRAY2BGR);
        chushiImg=mframe;
    }
    //背景值为 GC_BGD=0，作为掩码
    Mat Frame=chushiImg;
    Frame.copyTo(foreground, m_showImg);

    cvtColor(foreground,foreground,CV_BGR2GRAY);//三通道转单通道


    Mat foreground1;
    threshold(foreground, foreground1, 150, 255, THRESH_BINARY);   // 二值化图像

    Mat foreground2;

    threshold(foreground1, foreground2, 10, 255, THRESH_BINARY_INV);   // 二值化图像
    erode(foreground2, foreground2, cv::Mat());

    vector<Feather> featherList;                    // 存放连通域特征
    Mat dst;
    int nliantongyu;

    nliantongyu=f.bwLabelt(foreground2,dst,featherList);
    string nliantongyu_string = to_string(nliantongyu);
    QString nliantongyu_qstring;
    nliantongyu_qstring = QString::fromStdString(nliantongyu_string);
    ui->lineEdit_4->setText(nliantongyu_qstring);

    Point p;
    int i=0;
    int area=0;
    for (vector<Feather>::iterator it = featherList.begin(); it < featherList.end(); it++)
    {
        area+=it->area;
        cv::rectangle(chushiImg, it->boundingbox, cv::Scalar(0,0,255));
        cv::Rect r0 = it->boundingbox;
        p.x = r0.x;
        p.y = r0.y;

        string number_buf_string = to_string(it->area);
        QString qstr;
        qstr = QString::fromStdString(number_buf_string);
        ui->tableWidget_2->setItem(i,0,new QTableWidgetItem(qstr));
        //ui->tableWidget->item(i, 0)->setTextAlignment(Qt::AlignCenter);//设置单元格内容居中

        string number_buf_string1 = to_string(it->length);
        QString qstr1;
        qstr1 = QString::fromStdString(number_buf_string1);
        ui->tableWidget_2->setItem(i,1,new QTableWidgetItem(qstr1));
        //ui->tableWidget->item(i,1)->setTextAlignment(Qt::AlignCenter);

        string number_buf_string2 = to_string(it->r);
        QString qstr2;
        qstr2 = QString::fromStdString(number_buf_string2);
        ui->tableWidget_2->setItem(i,2,new QTableWidgetItem(qstr2));
        //ui->tableWidget->item(i,2)->setTextAlignment(Qt::AlignCenter);

        i++;
        string num=to_string(i);
        //putText(dst, num, p, cv::FONT_HERSHEY_COMPLEX, 0.7, cv::Scalar(180, 180, 180), 0.7, 8, 0);
        putText(chushiImg, num, p, cv::FONT_HERSHEY_COMPLEX, 0.7, cv::Scalar(0,0,255), 0.7, 8, 0);
    }

    double da=area/7124.51;
    string area_string = to_string(da);
    QString area_qstring;
    area_qstring = QString::fromStdString(area_string);
    ui->lineEdit_5->setText(area_qstring);


    cv::Mat rfore(chushiImg.size(), CV_8UC3, cv::Scalar(0, 0, 255));
    //设置掩码大小以及颜色，掩盖黑色区域
    Mat Frame1=chushiImg;
    Mat foreground3;
    threshold(foreground2, foreground3, 10, 255, THRESH_BINARY_INV);
    Frame1.copyTo(rfore, foreground3);

    loadImage1(rfore);
}

void MainWindow::on_newbaocun_triggered()//保存sence中的图片
{
    QString selectfile;
    QString filename = QFileDialog::getSaveFileName(this,tr("保存"),"未命名",tr("*.jpg;; *.png;; *.bmp"), &selectfile);
    QImage image(ui->graphicsView->width(),ui->graphicsView->height(),QImage::Format_ARGB32);

    QPainter painter(&image);
    scene->render(&painter);
    bool saveSuccess =  image.save(filename);
    if(saveSuccess==true) QMessageBox::information(this,"提醒","保存成功");
}

void MainWindow::on_pushButton_5_clicked()
{

   QString  fnqs=ui->lineEdit->text();
   QString  faqs=ui->lineEdit_3->text();
   QString  xnqs=ui->lineEdit_4->text();
   QString  xaqs=ui->lineEdit_5->text();
   if(ui->lineEdit->text().isEmpty()||ui->lineEdit_3->text().isEmpty()||ui->lineEdit_4->text().isEmpty()||ui->lineEdit_5->text().isEmpty())
   {
       QMessageBox::information(this,"提醒","请先检测");
   }
   double fn=fnqs.toDouble();
   double fa=faqs.toDouble();
   double xn=xnqs.toDouble();
   double xa=xaqs.toDouble();

   if((fn>5&&fa>0.5)||xa>1)
   {
       ui->lineEdit_6->setText("不合格");
   }
   else
   {
       ui->lineEdit_6->setText("合格");
   }

}

void MainWindow::on_pushButton_7_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->tableWidget->clear();
    ui->tableWidget_2->clear();
    //测试一下回滚功能
    //ceshiyuixiahebingfenzhi
}
