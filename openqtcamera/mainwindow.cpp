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
#include <QThread>
#include <QStandardPaths>
#include "savepathdialog.h"
#include "framesettingdialog.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initSence();
    initCamera();
    initConnect();
    initTimer();
    setWindowTitle("相机");
}

MainWindow::~MainWindow()
{
    m_mediaRecorder->stop();
    delete ui;
}

void MainWindow::initSence()
{
    if(!m_graphicsVideoItem)
    {
        m_graphicsVideoItem = new QGraphicsVideoItem();
        m_graphicsVideoItem->setPos(0,0);
    }
    if(!m_graphicsScene)
    {
        m_graphicsScene = new QGraphicsScene(this);
        m_graphicsScene->addItem(m_graphicsVideoItem);
        ui->graphicsView->setScene(m_graphicsScene);
        m_graphicsScene->setBackgroundBrush(Qt::black);
    }


}
//设置采集目标

//        m_pCamera->setCaptureDestination(QCameraImageCapture::CaptureToFile);
//    m_pCameraImageCapture->setBufferFormat(QVideoFrame::Format_ARGB32_Premultiplied);
//设置采集模式
//    m_pCamera->setCaptureMode(QCamera::CaptureViewfinder);//将其采集为图片
//    m_pCamera->setCaptureMode(QCamera::CaptureMode::CaptureStillImage);//将其采集到取景器中
void MainWindow::initCamera(QCameraInfo cameraInfo)
{
    if(m_mediaRecorder)
    {
        m_mediaRecorder->deleteLater();
        m_mediaRecorder=nullptr;
    }
    if(m_pCameraImageCapture)
    {
        m_pCameraImageCapture->deleteLater();
        m_pCameraImageCapture=nullptr;
    }
    if(m_pCamera)
    {
        m_pCamera->deleteLater();
        m_pCamera=nullptr;
    }

    m_pCamera =new QCamera(cameraInfo);
    m_pCameraImageCapture=new QCameraImageCapture(m_pCamera);

    //设置取景器
    m_pCamera->setViewfinder(m_graphicsVideoItem);
    m_pCamera->setCaptureMode(QCamera::CaptureVideo);

    //dosomething about the resolution

    m_mediaRecorder=new QMediaRecorder(m_pCamera);

    QCameraViewfinderSettings *m_finderSetting=new QCameraViewfinderSettings();
        m_finderSetting->setPixelAspectRatio(900,200);
    m_pCamera->setViewfinderSettings(*m_finderSetting);
    QVideoEncoderSettings videosetting = m_mediaRecorder->videoSettings();
    videosetting.setResolution(QSize(640,480));

    m_widthTheight=float(640)/float(480);
    m_mediaRecorder->setVideoSettings (videosetting);

    m_graphicsVideoItem->setAspectRatioMode(Qt::IgnoreAspectRatio);
    //开启相机
    m_pCamera->start();

    ui->statusBar->hide();

    auto* probe = new QVideoProbe(m_pCamera);

    m_currentInfo=cameraInfo;
    m_InfoList=QCameraInfo::availableCameras();

    connect(m_mediaRecorder, &QMediaRecorder::durationChanged, this, [=](qint64 index){
        QString str = QString("Recorded %1 sec").arg(m_mediaRecorder->duration()/1000);
        qDebug()<<str;

    });
//    void imageCaptured(int id, const QImage &preview);
//    void imageMetadataAvailable(int id, const QString &key, const QVariant &value);
//    void imageAvailable(int id, const QVideoFrame &frame);
       connect(m_pCameraImageCapture, &QCameraImageCapture::imageAvailable, this, [=](int id, const QVideoFrame &frame){
           qDebug()<<"1111";

       });


    //一旦有探测到有视频，就触发了ProcessVideoFrame函数
    connect(probe, SIGNAL(videoFrameProbed(QVideoFrame)), this, SLOT(ProcessVideoFrame(QVideoFrame)));

//    void stateChanged(QCamera::State state);
//    void captureModeChanged(QCamera::CaptureModes);
//    void statusChanged(QCamera::Status status);\
    QCamera::CaptureModes;
    connect(m_pCamera, &QCamera::stateChanged, this, [=](QCamera::State state){
        qDebug()<<state;
    });
    connect(m_pCamera, &QCamera::captureModeChanged, this, [=](QCamera::CaptureModes state){
        qDebug()<<state;
    });
    connect(m_pCamera, &QCamera::statusChanged, this, [=](QCamera::Status status){
        qDebug()<<status;
    });




}

void MainWindow::initTimer()
{
    if(!m_timer)
    {
        m_timer=new QTimer(this);
        connect(m_timer,&QTimer::timeout,this,&MainWindow::checkDeviceListInfo);
        m_timer->start(1000);
    }
}
void MainWindow::resizeMovieWindow()
{
    float width=ui->graphicsView->width();
    float height=ui->graphicsView->height();
    if(m_graphicsVideoItem->aspectRatioMode()==Qt::KeepAspectRatio)
    {
        if(width/height > m_widthTheight)
        {
            width=height*m_widthTheight;
        }
        else {
            height=width/m_widthTheight;
        }
    }
    m_graphicsScene->setSceneRect(QRect(0, 0, ( width-2) * m_playMultiple,( height-2)  *m_playMultiple));
    m_graphicsVideoItem->setSize(QSize(m_graphicsScene->width(),m_graphicsScene->height()));




}

bool MainWindow::isFile(const QString &path)
{

}
void MainWindow::initConnect()
{
    connect(ui->actionsetting,&QAction::triggered,this,[=]{
            settingDialog dialog(m_mediaRecorder);
            dialog.exec();
    });
    connect(ui->actionFrameSetting,&QAction::triggered,this,[=]{
            FrameSettingDialog dialog(m_graphicsVideoItem,m_mediaRecorder);
            dialog.exec();
    });
    connect(ui->actionFileSavePath,&QAction::triggered,this,[=]{
            savePathDialog dialog(m_picSavePath,m_movSavePath);
            dialog.exec();
            m_picSavePath=dialog.getpicSavePath();
            m_movSavePath=dialog.getmovSavePath();
    });

    connect(ui->tabWidget,&QTabWidget::tabBarClicked,this,[=](int index){
//        if(0==index)
//        {
//            m_pCamera->searchAndLock();

//            m_pCamera->setCaptureMode(QCamera::CaptureStillImage);

//            m_pCamera->unlock();
//        }
//        else if(1==index){
//            m_pCamera->searchAndLock();

//            m_pCamera->setCaptureMode(QCamera::CaptureVideo);

//            m_pCamera->unlock();
//        }
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
    QString path;
    if(m_movSavePath!=nullptr)
    {
         path = m_movSavePath +"/" + \
                 QDateTime::currentDateTime().toString()+QString::number(QDateTime::currentMSecsSinceEpoch());
    }
    else {
         path = QStandardPaths::writableLocation(QStandardPaths::MoviesLocation) +"/" + \
                 QDateTime::currentDateTime().toString()+QString::number(QDateTime::currentMSecsSinceEpoch());
    }
    m_mediaRecorder->setOutputLocation(QUrl(path));
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
    ui->picBtn->setChecked(false);
    if(QCamera::CaptureStillImage==m_pCamera->captureMode())
    {
        m_pCameraImageCapture->capture("UOS"+QDateTime::currentDateTime().toString());
    }
    else {
        qDebug()<<"video";
        QImage image(m_graphicsScene->sceneRect().size().toSize(), QImage::Format_ARGB32);
        QPainter painter(&image);
        m_graphicsScene->render(&painter);
        QString path;
        if(m_picSavePath!=nullptr)
        {
             path = m_picSavePath +"/" + \
                     QDateTime::currentDateTime().toString()+QString::number(QDateTime::currentMSecsSinceEpoch())+".png";
        }
        else {
             path = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation) +"/" + \
                     QDateTime::currentDateTime().toString()+QString::number(QDateTime::currentMSecsSinceEpoch())+".png";
        }

        image.save(path);
    }
    ui->picBtn->setChecked(true);


}

void MainWindow::on_morePicBtn_clicked()
{
    QThread *th1=QThread::create([ = ]() {
        int index=5;
        while(index>0)
        {
            on_picBtn_clicked();
            QThread::sleep(1);
            index--;
        }
    });
    connect(th1, &QThread::finished, th1, &QObject::deleteLater);
    th1->start();

}

void MainWindow::ProcessVideoFrame(QVideoFrame frame)
{
    qDebug()<<111111;
}

void MainWindow::checkDeviceListInfo()
{
QList<QCameraInfo> curCameraInfoList = QCameraInfo::availableCameras();
 if(m_InfoList.count()!=curCameraInfoList.count())
 {
     qDebug()<<m_InfoList.count();
     qDebug()<<curCameraInfoList.count();
 }
//    for (QCameraInfo info :QCameraInfo::availableCameras()) {
//        qDebug()<<info.deviceName();
//        qDebug()<<info.description();
//        qDebug()<<info.orientation();
//    }
}

