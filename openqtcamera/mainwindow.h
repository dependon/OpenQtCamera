#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QCameraInfo>
#include <QMediaRecorder>
#include <QFileDialog>

#include <QGraphicsVideoItem>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initSence();
    void initCamera(QCameraInfo = QCameraInfo::defaultCamera());
    void initTimer();
    void initConnect();
    void resizeMovieWindow();


    bool isFile(const QString & path);

protected:
    virtual void showEvent(QShowEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
private slots:
    void on_startBtn_clicked();

    void on_pauseBtn_clicked();

    void on_stopBtn_clicked();


    void on_picBtn_clicked();

    void on_morePicBtn_clicked();

    void ProcessVideoFrame(QVideoFrame frame);

    void checkDeviceListInfo();


private:
    Ui::MainWindow *ui;
    QCamera *m_pCamera{nullptr};
    QCameraViewfinder *m_pCameraViewfinder{nullptr};
    QCameraImageCapture *m_pCameraImageCapture{nullptr};
    QMediaRecorder *m_mediaRecorder{nullptr};

    QGraphicsVideoItem* m_graphicsVideoItem{nullptr};
    QGraphicsScene* m_graphicsScene{nullptr};
    float m_playMultiple{1};
    float m_widthTheight{0};

    QString m_picSavePath=nullptr;
    QString m_movSavePath=nullptr;

    QTimer *m_timer{nullptr};

    QCameraInfo m_currentInfo{nullptr};
    QList<QCameraInfo >m_InfoList;
};

#endif // MAINWINDOW_H
