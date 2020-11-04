#ifndef SAVEPATHDIALOG_H
#define SAVEPATHDIALOG_H

#include <QDialog>

namespace Ui {
class savePathDialog;
}

class savePathDialog : public QDialog
{
    Q_OBJECT

public:
    explicit savePathDialog(QString &picPath,QString &movPath,QWidget *parent = nullptr);
    ~savePathDialog();
    QString getpicSavePath();
    QString getmovSavePath();
private slots:
    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

    void on_picBox_activated(const QString &arg1);

    void on_movBox_activated(const QString &arg1);

private:
    Ui::savePathDialog *ui;
    QString m_picPath;
    QString m_movPath;
};

#endif // SAVEPATHDIALOG_H
