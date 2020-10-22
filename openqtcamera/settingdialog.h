#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QMediaRecorder>

namespace Ui {
class settingDialog;
}

class settingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit settingDialog(QMediaRecorder* mediarecorder =nullptr,QWidget *parent = nullptr);
    ~settingDialog();

    void setAudio();

    void setVideo();

    void setFormat();

private slots:
    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::settingDialog *ui;
    QMediaRecorder* m_mediarecorder {nullptr};
};

#endif // SETTINGDIALOG_H
