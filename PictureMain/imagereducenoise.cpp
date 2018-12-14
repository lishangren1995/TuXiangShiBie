#include "imagereducenoise.h"
#include "ui_imagereducenoise.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

ImageReduceNoise::ImageReduceNoise(cv::Mat dst,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageReduceNoise)
{
    ui->setupUi(this);
}

ImageReduceNoise::~ImageReduceNoise()
{
    delete ui;
}
