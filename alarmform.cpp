#include "alarmform.h"
#include "ui_alarmform.h"

AlarmForm::AlarmForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlarmForm)
{
    ui->setupUi(this);
}

AlarmForm::~AlarmForm()
{
    delete ui;
}
