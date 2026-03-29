#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void startBringup();          // 1. 启动机器人底层
    void stopRemoteProgram();     // 2. 停止机器人
    void startSLAM();              // 3. 启动建图
    void startKeyboardControl();   // 4. 启动键盘控制
    void saveMap();                // 5. 保存地图（指定路径）
    void startNavigation();        // 6. 启动导航
    void startCleaning();          // 7. 开始扫地
    void stopCleaning();           // 8. 停止扫地
    void startFullCoverage();      // 9. 开始全覆盖清扫
    void startLineSweeping();      // 10. 开始条带清扫
    void startAlongEdgeSweeping(); // 11. 开始沿边清扫
    void startArchSweeping();      // 12. 开始弓形清扫
    void startCamera();            // 13. 启动摄像机
    void startRosBridge();         // 14. 启动安卓服务器(rosbridge)
    void openRviz2();              // 15. 打开 RViz2

private:
    Ui::Widget *ui;
    QProcess *myProcess;

    void runSSHCommand(const QString &cmd);
    void runSSHInTerminal(const QString &cmd);
};

#endif // WIDGET_H
