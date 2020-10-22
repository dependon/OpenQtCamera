#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QList>
#include <QDebug>
#include <QSize>
#include "settingdialog.h"
#include <QDateTime>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initCamera();
    initConnect();
}

MainWindow::~MainWindow()
{
    m_mediaRecorder->stop();
    delete ui;
}

void MainWindow::initCamera()
{
    m_pCamera =new QCamera(QCameraInfo::defaultCamera());
    m_pCameraViewfinder=new QCameraViewfinder();
    ui->gridLayout->addWidget(m_pCameraViewfinder);
    m_pCameraImageCapture=new QCameraImageCapture(m_pCamera);
    //设置采集目标

    //        m_pCamera->setCaptureDestination(QCameraImageCapture::CaptureToFile);
//    m_pCameraImageCapture->setBufferFormat(QVideoFrame::Format_ARGB32_Premultiplied);
    //设置采集模式
//    m_pCamera->setCaptureMode(QCamera::CaptureViewfinder);//将其采集为图片
//    m_pCamera->setCaptureMode(QCamera::CaptureMode::CaptureStillImage);//将其采集到取景器中
    //设置取景器
    m_pCamera->setViewfinder(m_pCameraViewfinder);


    m_pCamera->setCaptureMode(QCamera::CaptureVideo);

    //dosomething about the resolution

    m_mediaRecorder=new QMediaRecorder(m_pCamera);


    connect(m_mediaRecorder, &QMediaRecorder::durationChanged, this, [=](qint64 index){
        QString str = QString("Recorded %1 sec").arg(m_mediaRecorder->duration()/1000);
        qDebug()<<str;

    });
    QVideoEncoderSettings videosetting = m_mediaRecorder->videoSettings();
    videosetting.setResolution(QSize(640,480));
    m_mediaRecorder->setVideoSettings (videosetting);

    //开启相机
    m_pCamera->start();

//    for (QSize resolution : m_pCamera->supportedViewfinderResolutions()){
//        qDebug()<<resolution;
//    }
//    for (QCameraInfo info :QCameraInfo::availableCameras()) {
//        qDebug()<<info.deviceName();
//        qDebug()<<info.description();
//        qDebug()<<info.orientation();
//    }


}

void MainWindow::initConnect()
{
    connect(ui->actionsetting,&QAction::triggered,this,[=]{
            settingDialog dialog(m_mediaRecorder);
            dialog.exec();
    });
}

void MainWindow::on_startBtn_clicked()
{
    qDebug()<<m_mediaRecorder->availableMetaData();
    qDebug()<<m_mediaRecorder->audioSettings().codec();
    qDebug()<<m_mediaRecorder->audioSettings().bitRate();
    qDebug()<<m_mediaRecorder->audioSettings().channelCount() ;
    qDebug()<<m_mediaRecorder->audioSettings().sampleRate();

    qDebug()<<m_mediaRecorder->videoSettings().codec();
    qDebug()<<m_mediaRecorder->videoSettings().bitRate();
    qDebug()<<m_mediaRecorder->videoSettings().frameRate() ;
    qDebug()<<m_mediaRecorder->videoSettings().resolution();

    qDebug()<<m_mediaRecorder->containerFormat();

//    qDebug()<<m_mediaRecorder->supportedContainers();

    m_mediaRecorder->stop();
//    QAudioEncoderSettings audioSettings() const;
//    QVideoEncoderSettings videoSettings() const;
//    QString containerFormat() const;
    m_mediaRecorder->setOutputLocation(QUrl("UOS"+QDateTime::currentDateTime().toString()));
    m_mediaRecorder->record();
}

void MainWindow::on_pauseBtn_clicked()
{
    m_mediaRecorder->pause();
}

void MainWindow::on_stopBtn_clicked()
{
    m_mediaRecorder->stop();
}


