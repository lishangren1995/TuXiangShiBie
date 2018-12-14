#ifndef DIALOGNOREDUCE_H
#define DIALOGNOREDUCE_H

#include <QDialog>
#include "Utils.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QPixmap>
using namespace cv;

namespace Ui {
class DialogNoReduce;
}

class DialogNoReduce : public QDialog//对话框基类
{
    Q_OBJECT

public:
    explicit DialogNoReduce(cv::Mat dst,QWidget *parent = 0);
    ~DialogNoReduce();
    cv::Mat m_NoreduceResult;
signals:
    void sendResult(cv::Mat);


private slots:
    void on_pushButton_Average_clicked();

    void on_pushButton_Gaussian_clicked();

    void on_pushButton_Median_clicked();

    void on_pushButton_Bilateral_clicked();

    void on_pushButton_reset_clicked();

    void on_pushButton_OK_clicked();

    void on_pushButton_Cancel_clicked();


private:
    Ui::DialogNoReduce *ui;
    cv::Mat m_Noreduce;
    cv::Mat m_mask;


};

#endif // DIALOGNOREDUCE_H
