#ifndef SETCAMERADIALOG_H
#define SETCAMERADIALOG_H

#include <QDialog>

namespace Ui {
class setCameraDialog;
}

class setCameraDialog : public QDialog
{
    Q_OBJECT

public:
    explicit setCameraDialog(QWidget *parent = nullptr);
    ~setCameraDialog();

private:
    Ui::setCameraDialog *ui;
};

#endif // SETCAMERADIALOG_H
