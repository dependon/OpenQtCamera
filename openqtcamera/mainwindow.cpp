#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QList>
#include <QDebug>
#include <QSize>
#include "mainwindow.h"
#include "settingdialog.h"
#include <QDateTime>
#include <QVideoProbe>
#include <QTimer>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initCamera();
    initConnect();
    setWindowTitle("相机");
}

MainWindow::~MainWindow()
{
    m_mediaRecorder->stop();
    delete ui;
}

void MainWindow::initCamera()
{

    m_graphicsVideoItem = new QGraphicsVideoItem();
//    m_graphicsVideoItem->setSize(QSizeF(640,480));
    m_graphicsVideoItem->setPos(0,0);

    m_graphicsScene = new QGraphicsScene(this);
    m_graphicsScene->addItem(m_graphicsVideoItem);

    m_graphicsView = new QGraphicsView(this);
    m_graphicsView->setScene(m_graphicsScene);


    m_pCamera =new QCamera(QCameraInfo::defaultCamera());

    ui->gridLayout->addWidget(m_graphicsView);
    m_pCameraImageCapture=new QCameraImageCapture(m_pCamera);
    //设置采集目标

    //        m_pCamera->setCaptureDestination(QCameraImageCapture::CaptureToFile);
//    m_pCameraImageCapture->setBufferFormat(QVideoFrame::Format_ARGB32_Premultiplied);
    //设置采集模式
//    m_pCamera->setCaptureMode(QCamera::CaptureViewfinder);//将其采集为图片
//    m_pCamera->setCaptureMode(QCamera::CaptureMode::CaptureStillImage);//将其采集到取景器中
    //设置取景器
    m_pCamera->setViewfinder(m_graphicsVideoItem);


    m_pCamera->setCaptureMode(QCamera::CaptureStillImage);

    //dosomething about the resolution

    m_mediaRecorder=new QMediaRecorder(m_pCamera);


    connect(m_mediaRecorder, &QMediaRecorder::durationChanged, this, [=](qint64 index){
        QString str = QString("Recorded %1 sec").arg(m_mediaRecorder->duration()/1000);
        qDebug()<<str;

    });
    m_pCameraImageCapture;
//    void imageCaptured(int id, const QImage &preview);
//    void imageMetadataAvailable(int id, const QString &key, const QVariant &value);
//    void imageAvailable(int id, const QVideoFrame &frame);
       connect(m_pCameraImageCapture, &QCameraImageCapture::imageAvailable, this, [=](int id, const QVideoFrame &frame){
           qDebug()<<"1111";

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

    ui->statusBar->hide();

    auto* probe = new QVideoProbe(m_pCamera);

    //一旦有探测到有视频，就触发了ProcessVideoFrame函数
    connect(probe, SIGNAL(videoFrameProbed(QVideoFrame)), this, SLOT(ProcessVideoFrame(QVideoFrame)));

}
void MainWindow::resizeMovieWindow()
{
    m_graphicsView->size();
    m_graphicsScene->setSceneRect(QRect(0, 0, (m_graphicsView->size().width()-2) * m_playMultiple,(m_graphicsView->size().height()-2)  *m_playMultiple));
    m_graphicsVideoItem->setSize(QSize(m_graphicsScene->width(),m_graphicsScene->height()));
}
void MainWindow::initConnect()
{
    connect(ui->actionsetting,&QAction::triggered,this,[=]{
            settingDialog dialog(m_mediaRecorder);
            dialog.exec();
    });
    QTabWidget a;
    connect(ui->tabWidget,&QTabWidget::tabBarClicked,this,[=](int index){
        if(0==index)
        {
            m_pCamera->searchAndLock();

            m_pCamera->setCaptureMode(QCamera::CaptureStillImage);

            m_pCamera->unlock();
        }
        else if(1==index){
            m_pCamera->searchAndLock();

            m_pCamera->setCaptureMode(QCamera::CaptureVideo);

            m_pCamera->unlock();
        }
    });
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    resizeMovieWindow();
    return QMainWindow::resizeEvent(event);
}
void MainWindow::showEvent(QShowEvent *event)
{
    resizeMovieWindow();
    return QMainWindow::showEvent(event);
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



void MainWindow::on_picBtn_clicked()
{

    if(QCamera::CaptureStillImage==m_pCamera->captureMode())
    {
        m_pCameraImageCapture->capture("UOS"+QDateTime::currentDateTime().toString());
    }
    else {
        qDebug()<<"111";
    }


}

void MainWindow::on_morePicBtn_clicked()
{

}

void MainWindow::ProcessVideoFrame(QVideoFrame frame)
{
    qDebug()<<111111;
}
