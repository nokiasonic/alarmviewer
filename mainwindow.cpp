#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "alarmform.h"
#include "ui_alarmform.h"
#include <QFileDialog>
#include <QDebug>
#include <QTabWidget>
#include <QTableView>
#include "nsalarmmodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setTabsClosable(true);


}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString lineTXT;
    int i=0;
    int tab_count;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), " ",  tr("All file(*.*);;log file(*.log);;txt file(*.txt)"));
    qDebug()<<fileName;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Open file failed.";
    }

    else
    {
        QFileInfo fileinfo=QFileInfo(fileName);
        QString tabName=fileinfo.fileName();

        //ui->tabWidget->setTabText(1,tabName); //change tab name
        tab_count=ui->tabWidget->count();
        QTabWidget *alarmTab = new QTabWidget;
        ui->tabWidget->addTab(alarmTab,tabName);
        tab_count=ui->tabWidget->count();
        ui->tabWidget->setCurrentIndex(tab_count-1);
       //ui->tabWidget->setTabsClosable(true);


        QGridLayout *gridLayout = new QGridLayout(alarmTab);
        QTableView *alarmForm = new QTableView(alarmTab);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->addWidget(alarmForm, 0, 0, 1, 1);

        QStandardItemModel *model = new QStandardItemModel(100,8,this); //100 Rows and 8 Columns
        //NSalarmModel *model = new NSalarmModel(100,8,this);

        model->setHorizontalHeaderItem(0, new QStandardItem(QString("Consecutive Number")));
        model->setHorizontalHeaderItem(1, new QStandardItem(QString("Alarm Number")));
        model->setHorizontalHeaderItem(2, new QStandardItem(QString("Alarm Text")));
        model->setHorizontalHeaderItem(3, new QStandardItem(QString("Unit")));
        model->setHorizontalHeaderItem(4, new QStandardItem(QString("Severity")));
        model->setHorizontalHeaderItem(5, new QStandardItem(QString("Date")));
        model->setHorizontalHeaderItem(6, new QStandardItem(QString("Time")));
        model->setHorizontalHeaderItem(7, new QStandardItem(QString("Supplementary Info")));

        //model->setItem(1,3, new QStandardItem(QString("CPPU-3")));




        alarmForm->setModel(model);
        QFont font=alarmForm->horizontalHeader()->font();
        font.setBold(true);
        alarmForm->horizontalHeader()->setFont(font);
        alarmForm->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
        alarmForm->verticalHeader()->setDefaultSectionSize(20);
        //alarmForm->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        alarmForm->setShowGrid(false);
        alarmForm->setSelectionBehavior(QAbstractItemView::SelectRows);
        alarmForm->setSortingEnabled(true);
        alarmForm->setFocusPolicy(Qt::NoFocus);
        alarmForm->setEditTriggers(QAbstractItemView::NoEditTriggers);
        alarmForm->horizontalHeader()->setStretchLastSection(true);
        //ui->tableView->verticalHeader()->setVisible(false);  //Hide the vertical headers


        while (!file.atEnd())
        {
            //qDebug() << file.readLine();
            lineTXT=file.readLine();
            qDebug() << lineTXT;
            QString str("AHP;\n");
            if(lineTXT.contains(str,Qt::CaseInsensitive)==true)
            {
                qDebug() << "ZAHP Command is found!!!";
            }
            QString pattern="^\\s+<HIST>\\s+\\S+\\s+(\\S+)\\D+(\\d{4}-\\d{2}-\\d{2})\\W+(\\d{2}:\\d{2}:\\d{2}\\.\\d{2})";
            QRegExp rx(pattern);
            //QRegExp rx("AHP;");    //same function as the last two sentences.
            if(rx.indexIn(lineTXT)!=-1)
            {
                qDebug()<<rx.matchedLength();
                qDebug()<<rx.capturedTexts();//QStringList("a=100", "a", "100"),
                //0: text matching pattern
                //1: text captured by the 1st ()
                //2: text captured by the 2nd ()

                qDebug()<<rx.cap(0);//a=100, text matching pattern
                model->setItem(i,3, new QStandardItem(rx.cap(1)));
                qDebug()<<rx.cap(1);//a, text captured by the nth ()
                model->setItem(i,5, new QStandardItem(rx.cap(2)));
                qDebug()<<rx.cap(2);//a, text captured by the nth ()
                model->setItem(i,6, new QStandardItem(rx.cap(3)));
                qDebug()<<rx.cap(3);//a, text captured by the nth ()
                lineTXT=file.readLine();
                pattern="^(\\**|\\.*)\\s+(DISTUR|NOTICE|ALARM|CANCEL)";
                rx.setPattern(pattern);
                if(rx.indexIn(lineTXT)!=-1)
                {
                    model->setItem(i,4, new QStandardItem(rx.cap(2)+rx.cap(1)));
                    qDebug()<<rx.cap(1);//a, text captured by the nth ()
                    qDebug()<<rx.cap(2);//a, text captured by the nth ()
                }
            }

            pattern="^\\s+\\((\\d+)\\)\\s+(\\d+)\\s+(.+)$";
            rx.setPattern(pattern);
            //QRegExp rx("AHP;");    //same function as the last two sentences.
            if(rx.indexIn(lineTXT)!=-1)
            {
                qDebug()<<rx.matchedLength();
                qDebug()<<rx.capturedTexts();//QStringList("a=100", "a", "100"),
                //0: text matching pattern
                //1: text captured by the 1st ()
                //2: text captured by the 2nd ()

                qDebug()<<rx.cap(0);//a=100, text matching pattern
                model->setItem(i,0, new QStandardItem(rx.cap(1)));
                qDebug()<<rx.cap(1);//a, text captured by the nth ()
                model->setItem(i,1, new QStandardItem(rx.cap(2)));
                qDebug()<<rx.cap(2);//a, text captured by the nth ()
                model->setItem(i,2, new QStandardItem(rx.cap(3)));
                qDebug()<<rx.cap(3);//a, text captured by the nth ()
                lineTXT=file.readLine();
                pattern="^\\s+(.+)$";
                rx.setPattern(pattern);
                if(rx.indexIn(lineTXT)!=-1)
                {
                    model->setItem(i,7, new QStandardItem(rx.cap(1)));
                    qDebug()<<rx.cap(1);//a, text captured by the nth ()
                }
                i++;
            }


        }

        alarmForm->resizeColumnsToContents();
    }
}

void MainWindow::on_actionExit_triggered()
{
    QApplication *app;
    app->quit();
}
