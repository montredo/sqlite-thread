#ifndef MAINWIDGET_HPP
#define MAINWIDGET_HPP

#include <QWidget>

namespace Ui {
class MainWidget;
}

class DatabaseThread;

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private:
    Ui::MainWidget *ui;
    DatabaseThread *databaseThread;
};

#endif // MAINWIDGET_HPP
