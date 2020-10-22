#include "settingdialog.h"
#include "ui_settingdialog.h"

settingDialog::settingDialog(QMediaRecorder* mediarecorder,QWidget *parent) :
    QDialog(parent),
    m_mediarecorder(mediarecorder),
    ui(new Ui::settingDialog)
{
    ui->setupUi(this);
    if(m_mediarecorder)
    {
        //audio codecs
        foreach(const QString &codecName, m_mediarecorder->supportedAudioCodecs()) {
            QString description = m_mediarecorder->audioCodecDescription(codecName);
            ui->audiocodecBox->addItem(codecName+": "+description, QVariant(codecName));
        }

        //sample rate:
        foreach(int sampleRate, m_mediarecorder->supportedAudioSampleRates()) {
            ui->audioSampleRateBox->addItem(QString::number(sampleRate), QVariant(sampleRate));
        }


        //video codecs
        foreach(const QString &codecName, m_mediarecorder->supportedVideoCodecs()) {
            QString description = m_mediarecorder->videoCodecDescription(codecName);
            ui->videocodecBox->addItem(codecName+": "+description, QVariant(codecName));
        }

//        ui->videoQualitySlider->setRange(0, int(QMultimedia::VeryHighQuality));

//        ui->videoResolutionBox->addItem(tr("Default"));
        QList<QSize> supportedResolutions = m_mediarecorder->supportedResolutions();
        foreach(const QSize &resolution, supportedResolutions) {
            ui->videoResolutionBox->addItem(QString("%1x%2").arg(resolution.width()).arg(resolution.height()),
                                            QVariant(resolution));
        }
        if(supportedResolutions.size()>0)
        {
            ui->videoResolutionBox->setCurrentIndex(supportedResolutions.size()-1);
        }

//        ui->supportedFrameRatesBox->addItem(tr("Default"));
        QList<qreal> supportedFrameRates = m_mediarecorder->supportedFrameRates();
        qreal rate;
        foreach(rate, supportedFrameRates) {
            QString rateString = QString("%1").arg(rate, 0, 'f', 2);
            ui->supportedFrameRatesBox->addItem(rateString, QVariant(rate));
        }

        if(supportedFrameRates.size()>0)
        {
            ui->supportedFrameRatesBox->setCurrentIndex(supportedFrameRates.size()-1);
        }

//        foreach(const QString &format, m_mediarecorder->supportedContainers()) {
//            ui->formatBox->addItem(format+":"+m_mediarecorder->containerDescription(format),
//                                            QVariant(format));
//        }
        ui->formatLabel->hide();
        ui->formatBox->hide();
        ui->audioSampleRateLabel->hide();
        ui->audioSampleRateBox->hide();
        setWindowTitle("设置");
    }
}

settingDialog::~settingDialog()
{
    delete ui;
}

void settingDialog::setAudio()
{
    QAudioEncoderSettings settings = m_mediarecorder->audioSettings();
    qDebug()<<ui->audiocodecBox->currentData().toString();
    if(nullptr != ui->audiocodecBox->currentData().toString())
    {
        settings.setCodec(ui->audiocodecBox->currentData().toString());
    }
    if(nullptr != ui->audioSampleRateBox->currentData().toString())
    {
        settings.setSampleRate(ui->audioSampleRateBox->currentData().toInt());
    }
    settings.setQuality(QMultimedia::EncodingQuality(ui->audioQualitySlider->value()));
    m_mediarecorder->setAudioSettings(settings);
}

void settingDialog::setVideo()
{
    QVideoEncoderSettings settings = m_mediarecorder->videoSettings();
    if(nullptr != ui->audiocodecBox->currentData().toString())
    {
        settings.setCodec(ui->videocodecBox->currentData().toString());
    }
        settings.setQuality(QMultimedia::EncodingQuality(ui->videoQualitySlider->value()));
    if(nullptr != ui->videoResolutionBox->currentText())
    {
        settings.setResolution(ui->videoResolutionBox->currentData().toSize());
    }
    if(nullptr != ui->audiocodecBox->currentText())
    {
        settings.setFrameRate(ui->supportedFrameRatesBox->currentData().value<qreal>());
    }
    m_mediarecorder->setVideoSettings(settings);

}

void settingDialog::setFormat()
{
    qDebug()<<ui->formatBox->currentData().toString();
    m_mediarecorder->setContainerFormat(ui->formatBox->currentData().toString());
}

void settingDialog::on_okBtn_clicked()
{
    setAudio();
    setVideo();
//    setFormat();
    close();
}

void settingDialog::on_cancelBtn_clicked()
{
    close();
}
