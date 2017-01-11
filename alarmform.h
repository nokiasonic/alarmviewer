#ifndef ALARMFORM_H
#define ALARMFORM_H

#include <QWidget>

namespace Ui {
class AlarmForm;
}

class AlarmForm : public QWidget
{
    Q_OBJECT

public:
    explicit AlarmForm(QWidget *parent = 0);
    ~AlarmForm();

private:
    Ui::AlarmForm *ui;
};

#endif // ALARMFORM_H
