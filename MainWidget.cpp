#include "MainWidget.hpp"
#include "ui_MainWidget.h"

#include "DatabaseThread.hpp"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    databaseThread = new DatabaseThread;
    databaseThread->start();
}

MainWidget::~MainWidget()
{
    databaseThread->quit();
    databaseThread->wait();
    delete databaseThread;

    delete ui;
}
