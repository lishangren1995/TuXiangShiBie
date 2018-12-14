#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QComboBox>
#include <QSpinBox>
#include <QToolBar>
#include <QFontComboBox>
#include <QToolButton>
#include <QTextCharFormat>
#include <QStatusBar>
#include <QGraphicsScene>
#include "showwidget.h"
#include "recentopened.h"
#include "pixitem.h"
#include "dialognoreduce.h"
#include <opencv2/core/core.hpp>
#include"yuchuli.h"
#include"fenge.h"
#include"histogram.h"
#include"adduserdlg.h"
#include"arcdlg.h"
#include"datamanager.h"
#include"laserwelddlg.h"
#include"recorddlg.h"
#include <QDialog>
#include <QPrintDialog>


#include <QDockWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QUndoGroup>
#include <QUndoStack>
#include "laserwelddlg.h"
#include "fenge.h"
#include "arcdlg.h"
#include "showwidget.h"
#include "recentopened.h"
#include "pixitem.h"
#include "dialognoreduce.h"
#include "datamanager.h"
#include <opencv2/core/core.hpp>
#include "recorddlg.h"
#include "datamanager.h"
#include "ca.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    int p=1;
    QImage qimg;
    QGraphicsScene sce;
    QGraphicsScene *scene = new QGraphicsScene;
    DialogNoReduce * m_Dialog;
    PixItem *pixItem;
    cv::Mat m_showImg;
    cv::Mat chushiImg;
    cv::Mat m_result;
    cv::Mat chushi;
    cv::Mat huanyuan;
    cv::Mat caiji;
    QPixmap pixshow;

    void loadFile(QString filename);
    void loadImage(const QString &fileName,cv::Mat &showImg);
    void loadImage1(cv::Mat showImg1);
    void qsleep(unsigned int ms);



    laserwelddlg *m_LaserWeld;
    RecentOpened *m_recent;
    recorddlg *m_recordDlg;
    arcdlg *m_ArcDlg;

   QString filedakai;
//    comeradlg *m_camera;
//    defectDock *m_defect;
    datamanager *m_dataManager;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void getmsg(QString msg1,QString msg2,QString msg3,QString msg4,QString msg5,QString msg6);

public slots:

    void PrintLogMsg(QString msg);

private slots:
    void on_dakai_triggered();

    void on_Tyuchuli_triggered();

    void on_Tfenge_triggered();

    void on_Tshibie_triggered();

    void on_baocun_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();



    void on_djgluru_triggered();

    void on_shujuku_triggered();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_fangda_triggered();

    void on_jcbaocun_triggered();

    void on_fhluru_triggered();

    void on_suoxiao_triggered();

    void on_xuanzhuan90_triggered();

    void on_xuanzhuan180_triggered();

    void on_guanbitu_triggered();

    void on_pushButton_xuanze_clicked();

    void on_pushButton_6_clicked();

    void on_jiance_triggered();

    void on_xiata_triggered();

    void on_newbaocun_triggered();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;
    QPixmap img;
    QString *fileName;
    ca xj;
    QLabel *lable = new QLabel(this);
    //RecentOpened *m_recent;


};

#endif // MAINWINDOW_H
