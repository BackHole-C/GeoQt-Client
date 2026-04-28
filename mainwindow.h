#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MapCanvas;
class QDockWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    void initLayout();

private:
    Ui::MainWindow *ui;
    MapCanvas *m_mapCanvas;
    QDockWidget *m_dockPanel;
};
#endif // MAINWINDOW_H
