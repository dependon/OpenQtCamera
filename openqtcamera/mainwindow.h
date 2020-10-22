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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initCamera();

    void initConnect();

private slots:
    void on_startBtn_clicked();

    void on_pauseBtn_clicked();

    void on_stopBtn_clicked();


private:
    Ui::MainWindow *ui;
    QCamera *m_pCamera{nullptr};
    QCameraViewfinder *m_pCameraViewfinder{nullptr};
    QCameraImageCapture *m_pCameraImageCapture{nullptr};
    QMediaRecorder *m_mediaRecorder{nullptr};
};

#endif // MAINWINDOW_H
