#include "savepathdialog.h"
#include "ui_savepathdialog.h"
#include <QComboBox>
#include <QStandardPaths>
#include <QFileDialog>
#include <QDebug>
savePathDialog::savePathDialog(QString &picPath,QString &movPath,QWidget *parent) :
    QDialog(parent),
    m_picPath(picPath),
    m_movPath(movPath),
    ui(new Ui::savePathDialog)
{
    ui->setupUi(this);

    ui->picBox->addItem("桌面", 1);
    ui->picBox->addItem("默认图片路径", 2);
    ui->picBox->addItem("自定义", 3);

    ui->movBox->addItem("桌面", 1);
    ui->movBox->addItem("默认影片路径", 2);
    ui->movBox->addItem("自定义", 3);


    m_picPath=QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    m_movPath=QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

    ui->picEdit->setText(m_picPath);
    ui->movEdit->setText(m_movPath);
    setWindowTitle("存储路径设置");

}

savePathDialog::~savePathDialog()
{
    delete ui;
}

QString savePathDialog::getpicSavePath()
{
    return m_picPath;
}

QString savePathDialog::getmovSavePath()
{
    return m_movPath;
}

void savePathDialog::on_okBtn_clicked()
{
    close();
}

void savePathDialog::on_cancelBtn_clicked()
{
    m_picPath=nullptr;
    m_movPath=nullptr;
    close();
}

void savePathDialog::on_picBox_activated(const QString &arg1)
{
    switch (ui->picBox->currentData().toInt()) {
    case 1:
    {
        m_picPath=QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        ui->picEdit->setText(m_picPath);
    }
        break;
    case 2:
    {
        m_picPath=QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
        ui->picEdit->setText(m_picPath);
    }
        break;
    case 3:
    {
        QString file_path = QFileDialog::getExistingDirectory(this, "请选择文件路径...", "./");
        if(file_path.isEmpty())
        {
            return;
        }
        m_picPath=file_path;
        ui->picEdit->setText(m_picPath);
    }
        break;
    default:
        break;

    }
}

void savePathDialog::on_movBox_activated(const QString &arg1)
{
    switch (ui->movBox->currentData().toInt()) {
    case 1:
    {
        m_movPath=QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        ui->movEdit->setText(m_movPath);
    }
        break;
    case 2:
    {
        m_movPath=QStandardPaths::writableLocation(QStandardPaths::MoviesLocation);
        ui->movEdit->setText(m_movPath);
    }
        break;
    case 3:
    {
        QString file_path = QFileDialog::getExistingDirectory(this, "请选择文件路径...", "./");
        if(file_path.isEmpty())
        {
            return;
        }
        m_movPath=file_path;
        ui->movEdit->setText(m_movPath);
    }
        break;
    default:
        break;

    }
}
