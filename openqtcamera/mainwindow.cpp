#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QList>
#include <QDebug>
#include <QSize>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_pCamera =new QCamera(QCameraInfo::defaultCamera());
    m_pCameraViewfinder=new QCameraViewfinder();
    ui->gridLayout->addWidget(m_pCameraViewfinder);
    m_pCameraImageCapture=new QCameraImageCapture(m_pCamera);
    //设置采集目标

    //        m_pCamera->setCaptureDestination(QCameraImageCapture::CaptureToFile);

    //设置采集模式
    m_pCamera->setCaptureMode(QCamera::CaptureViewfinder);//将其采集为图片
    m_pCamera->setCaptureMode(QCamera::CaptureMode::CaptureViewfinder);//将其采集到取景器中
    //设置取景器
    m_pCamera->setViewfinder(m_pCameraViewfinder);


    //dosomething about the resolution

    //开启相机
    m_pCamera->start();

    for (QSize resolution : m_pCamera->supportedViewfinderResolutions()){
        qDebug()<<resolution;
    }
    for (QCameraInfo info :QCameraInfo::availableCameras()) {
        qDebug()<<info.deviceName();
        qDebug()<<info.description();
        qDebug()<<info.orientation();
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}
