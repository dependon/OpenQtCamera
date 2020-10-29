#ifndef FRAMESETTINGDIALOG_H
#define FRAMESETTINGDIALOG_H

#include <QDialog>
#include <QGraphicsVideoItem>
#include <QMediaRecorder>

namespace Ui {
class FrameSettingDialog;
}

class FrameSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FrameSettingDialog(QGraphicsVideoItem * videoItem=nullptr,QMediaRecorder* mediarecorder=nullptr,QWidget *parent = nullptr);
    ~FrameSettingDialog();

private slots:
    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::FrameSettingDialog *ui;
    QMediaRecorder *m_mediaRecorder{nullptr};
    QGraphicsVideoItem *m_videoItem{nullptr};
};

#endif // FRAMESETTINGDIALOG_H
