#ifndef XIANGJI_H
#define XIANGJI_H
#include "SDK.h"
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//#include <Windows.h>
//#include <process.h>
class xiangji
{

private:
//    GENICAM_StreamSource *pStreamSource = NULL;
//    int32_t ret;
//    int32_t i;
//    GENICAM_System *pSystem = NULL;//设备发现创建
//    GENICAM_Camera *pCamera = NULL;//相机共用操作接口，包括相机的连接断开、判断连接、输出相机信息等
//    GENICAM_Camera *pCameraList = NULL;//
//    GENICAM_AcquisitionControl *pAcquisitionCtrl = NULL;//属性配置
//    uint32_t cameraCnt = 0;
//    HANDLE threadHandle;
//    unsigned threadID;


public:
    xiangji();
//    static int32_t GENICAM_connect(GENICAM_Camera *pGetCamera)//连接设备
//    {
//        int32_t isConnectSuccess;

//        isConnectSuccess = pGetCamera->connect(pGetCamera, accessPermissionControl);

//        if (isConnectSuccess != 0)
//        {
//            return -1;
//        }

//        return 0;
//    }

//    static int32_t GENICAM_CreateStreamSource(GENICAM_Camera *pGetCamera, GENICAM_StreamSource **ppStreamSource)//创建流
//    {
//        int32_t isCreateStreamSource;
//        GENICAM_StreamSourceInfo stStreamSourceInfo;


//        stStreamSourceInfo.channelId = 0;
//        stStreamSourceInfo.pCamera = pGetCamera;

//        isCreateStreamSource = GENICAM_createStreamSource(&stStreamSourceInfo, ppStreamSource);
//        //创建流通道对象，该对象由外部调用该接口创建，释放时调用release接口
//        //[in] pStreamSourceInfo 创建流对象的参数
//        //[out] ppStreamSource 返回的流对象

//        if (isCreateStreamSource != 0)
//        {
//            return -1;
//        }

//        return 0;
//    }

//    static int32_t GENICAM_startGrabbing(GENICAM_StreamSource *pStreamSource)//拉流
//    {
//        int32_t isStartGrabbingSuccess;
//        GENICAM_EGrabStrategy eGrabStrategy;

//        eGrabStrategy = grabStrartegySequential;
//        isStartGrabbingSuccess = pStreamSource->startGrabbing(pStreamSource, 1, eGrabStrategy);
//        //中间参数为允许最多的抓图数，达到指定抓图数后停止抓图，如果为0，表示忽略此参数，会连续抓图


//        if (isStartGrabbingSuccess != 0)
//        {
//            return -1;
//        }

//        return 0;
//    }

//    static int32_t GENICAM_stopGrabbing(GENICAM_StreamSource *pStreamSource)
//    {
//        int32_t isStopGrabbingSuccess;

//        isStopGrabbingSuccess = pStreamSource->stopGrabbing(pStreamSource);
//        if (isStopGrabbingSuccess != 0)
//        {
//            return -1;
//        }

//        return 0;
//    }

//    static int32_t modifyCamralExposureTime(GENICAM_Camera *pGetCamera)
//    {
//        int32_t isExposureTimeSuccess;
//        GENICAM_DoubleNode doubleNode;
//        double exposureTimeValue;
//        GENICAM_AcquisitionControl *pAcquisitionCtrl = NULL;
//        GENICAM_AcquisitionControlInfo acquisitionControlInfo = { 0 };


//        acquisitionControlInfo.pCamera = pGetCamera;
//        isExposureTimeSuccess = GENICAM_createAcquisitionControl(&acquisitionControlInfo, &pAcquisitionCtrl);
//        if (isExposureTimeSuccess != 0)
//        {
//            return -1;
//        }

//        exposureTimeValue = 0.0;
//        doubleNode = pAcquisitionCtrl->exposureTime(pAcquisitionCtrl);
//        isExposureTimeSuccess = doubleNode.getValue(&doubleNode, &exposureTimeValue);
//        if (isExposureTimeSuccess != 0)
//        {

//            //注意：需要释放pAcquisitionCtrl内部对象内存
//            pAcquisitionCtrl->release(pAcquisitionCtrl);

//            //注意：需要释放doubleNode内部对象内存
//            doubleNode.release(&doubleNode);
//            return -1;
//        }
//        else
//        {
//            //注意：需要释放pAcquisitionCtrl内部对象内存
//            pAcquisitionCtrl->release(pAcquisitionCtrl);
//        }

//        doubleNode.setValue(&doubleNode, (exposureTimeValue + 2));
//        if (isExposureTimeSuccess != 0)
//        {
//            //注意：需要释放doubleNode内部对象内存
//            doubleNode.release(&doubleNode);
//            return -1;
//        }

//        doubleNode.getValue(&doubleNode, &exposureTimeValue);
//        if (isExposureTimeSuccess != 0)
//        {
//            //注意：需要释放doubleNode内部对象内存
//            doubleNode.release(&doubleNode);
//            return -1;
//        }
//        else
//        {
//            //注意：需要释放doubleNode内部对象内存
//            doubleNode.release(&doubleNode);
//        }

//        return 0;
//    }

//    static int32_t GENICAM_disconnect(GENICAM_Camera *pGetCamera)
//    {
//        int32_t isDisconnectSuccess;

//        isDisconnectSuccess = pGetCamera->disConnect(pGetCamera);
//        if (isDisconnectSuccess != 0)
//        {
//            return -1;
//        }

//        return 0;
//    }


//        static unsigned __stdcall frameGrabbingProc(void*)
//        {
//            int i;
//            int32_t ret = -1;
//            uint64_t blockId = 0;

//            GENICAM_Frame* pFrame;

//            for (i = 0; i < 1; i++)
//            {
//                if (NULL == pStreamSource)
//                {
//                    return 0;
//                }


//                ret = pStreamSource->getFrame(pStreamSource, &pFrame, 1000);
//                if (ret < 0)
//                {
//                    continue;
//                }

//                ret = pFrame->valid(pFrame);
//                if (ret < 0)
//                {

//                    //Caution：release the frame after using it
//                    //注意：使用该帧后需要显示释放
//                    pFrame->release(pFrame);

//                    continue;
//                }

//                const void* pdata = pFrame->getImage(pFrame);
//                //cv::Mat imagemat(800,600,CV_8UC3,const_cast<void*>(pdata));

//                cv::Mat imagemat(2048, 3072, CV_8U, const_cast<void*>(pdata));
//                //image = imagemat;
//                imshow("1", imagemat);
//                //waitKey(6000);
//                imwrite("3.jpg",imagemat);

//                //Caution：release the frame after using it
//                //注意：使用该帧后需要显示释放
//                pFrame->release(pFrame);
//            }

//            return 1;
//        }


//};

#endif // XIANGJI_H
