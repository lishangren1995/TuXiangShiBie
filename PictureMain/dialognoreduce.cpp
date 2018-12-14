#include "dialognoreduce.h"
#include "ui_dialognoreduce.h"

DialogNoReduce::DialogNoReduce(cv::Mat dst,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNoReduce)
{
    ui->setupUi(this);
    m_Noreduce = dst;
    m_mask = dst;
    connect(ui->pushButton_Average,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_Average_clicked()));
    connect(ui->pushButton_Gaussian,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_Gaussian_clicked()));
    connect(ui->pushButton_Median,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_Median_clicked()));
    connect(ui->pushButton_Bilateral,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_Bilateral_clicked()));
    connect(ui->pushButton_OK,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_OK_clicked()));
    connect(ui->pushButton_Cancel,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_Cancel_clicked()));
}

DialogNoReduce::~DialogNoReduce()
{
    delete ui;
}

void DialogNoReduce::on_pushButton_Average_clicked()
{
    Mat imageAver;
    cv::blur(m_Noreduce,imageAver,Size(5,5));
    m_NoreduceResult = imageAver;
    emit sendResult(m_NoreduceResult);
    m_Noreduce =m_NoreduceResult;
}

void DialogNoReduce::on_pushButton_Gaussian_clicked()
{
    Mat imageGauss;
    GaussianBlur(m_Noreduce, imageGauss, Size(3, 3), 1);
    m_NoreduceResult = imageGauss;
    emit sendResult(m_NoreduceResult);
    m_Noreduce =m_NoreduceResult;
}

void DialogNoReduce::on_pushButton_Median_clicked()
{
    Mat imageMedian;
    medianBlur(m_Noreduce,imageMedian,5);
    m_NoreduceResult = imageMedian;
    emit sendResult(m_NoreduceResult);
    m_Noreduce =m_NoreduceResult;
}

void DialogNoReduce::on_pushButton_Bilateral_clicked()
{
    Mat imageBilater;
    bilateralFilter(m_Noreduce, imageBilater, 25, 25 * 2, 25 / 2);
    m_NoreduceResult = imageBilater;
    emit sendResult(m_NoreduceResult);
    m_Noreduce =m_NoreduceResult;
}

void DialogNoReduce::on_pushButton_reset_clicked()
{
   emit sendResult(m_mask);
   m_Noreduce = m_mask;
}

void DialogNoReduce::on_pushButton_OK_clicked()
{
    this->close();
}

void DialogNoReduce::on_pushButton_Cancel_clicked()
{
    emit sendResult(m_mask);
    m_Noreduce = m_mask;
    this->close();
}

