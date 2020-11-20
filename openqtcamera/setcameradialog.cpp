#include "setcameradialog.h"
#include "ui_setcameradialog.h"

setCameraDialog::setCameraDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setCameraDialog)
{
    ui->setupUi(this);
}

setCameraDialog::~setCameraDialog()
{
    delete ui;
}
