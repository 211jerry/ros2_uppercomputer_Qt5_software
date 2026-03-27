#include "widget.h"
#include "ui_widget.h"

// ==================== 配置信息 ====================
const QString PI_USER     = "jerry";
const QString PI_IP       = "192.168.53.91";
const QString ROS2_DISTRO = "humble";
const QString WS_PATH     = "/home/jerry/AutoSweeperSystem/AutoSweeperSystem_ws";
const QString MAP_SAVE_PATH = WS_PATH + "/src/fishbot_navigation2/maps/room";

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    myProcess = new QProcess(this);

    connect(ui->pushButton,    &QPushButton::clicked, this, &Widget::startBringup);
    connect(ui->pushButton_2,  &QPushButton::clicked, this, &Widget::stopRemoteProgram);
    connect(ui->pushButton_3,  &QPushButton::clicked, this, &Widget::startSLAM);
    connect(ui->pushButton_4,  &QPushButton::clicked, this, &Widget::startKeyboardControl);
    connect(ui->pushButton_5,  &QPushButton::clicked, this, &Widget::saveMap);
    connect(ui->pushButton_6,  &QPushButton::clicked, this, &Widget::startNavigation);
    connect(ui->pushButton_7,  &QPushButton::clicked, this, &Widget::startCleaning);
    connect(ui->pushButton_8,  &QPushButton::clicked, this, &Widget::stopCleaning);
    connect(ui->pushButton_9,  &QPushButton::clicked, this, &Widget::startFullCoverage);
    connect(ui->pushButton_10, &QPushButton::clicked, this, &Widget::openRviz2);
}

Widget::~Widget()
{
    delete ui;
}

// ==================== 通用函数：后台执行SSH（强制source环境）====================
void Widget::runSSHCommand(const QString &cmd)
{
    QString fullCmd = QString(
        "cd %1 && source /opt/ros/%2/setup.bash && source install/setup.bash && %3"
    ).arg(WS_PATH).arg(ROS2_DISTRO).arg(cmd);

    QString program = "ssh";
    QStringList args;
    args << QString("%1@%2").arg(PI_USER).arg(PI_IP) << fullCmd;
    QProcess::startDetached(program, args);
}

// ==================== 通用函数：弹出终端执行SSH ====================
void Widget::runSSHInTerminal(const QString &cmd)
{
    QString sshInnerCmd = QString(
        "cd %1 && source /opt/ros/%2/setup.bash && source install/setup.bash && %3; exec bash"
    ).arg(WS_PATH).arg(ROS2_DISTRO).arg(cmd);

    QString gnomeCmd = QString("ssh -t %1@%2 \"%3\"").arg(PI_USER).arg(PI_IP).arg(sshInnerCmd);

    QString program = "gnome-terminal";
    QStringList args;
    args << "--" << "bash" << "-c" << gnomeCmd;
    QProcess::startDetached(program, args);
}

// ==================== 1. 启动机器人底层 ====================
void Widget::startBringup()
{
    QString cmd = "ros2 launch fishbot_bringup bringup.launch.py";
    runSSHInTerminal(cmd);
    ui->label->setText("状态：✅ 机器人底层已启动！");
}

// ==================== 2. 停止机器人 ====================
void Widget::stopRemoteProgram()
{
    QString program = "ssh";
    QStringList args;
    args << QString("%1@%2").arg(PI_USER).arg(PI_IP) << "pkill -SIGINT -f 'ros2 launch'";
    QProcess::startDetached(program, args);
    ui->label->setText("状态：✅ 机器人已停止！");
}

// ==================== 3. 启动建图（绝对路径，100%找到配置文件）=====================
void Widget::startSLAM()
{
    QString slam_file = WS_PATH + "/src/fishbot_bringup/config/slam_toolbox.yaml";
    QString cmd = QString(
        "ros2 launch slam_toolbox online_async_launch.py slam_params_file:=%1 use_sim_time:=False"
    ).arg(slam_file);

    runSSHInTerminal(cmd);
    ui->label->setText("状态：✅ 建图已启动！");
}

// ==================== 4. 启动键盘控制 ====================
void Widget::startKeyboardControl()
{
    QString cmd = "ros2 run teleop_twist_keyboard teleop_twist_keyboard";
    runSSHInTerminal(cmd);
    ui->label->setText("状态：✅ 键盘控制已启动！");
}

// ==================== 5. 保存地图到指定文件夹 ====================
void Widget::saveMap()
{
    QString cmd = QString("mkdir -p %1 && ros2 run nav2_map_server map_saver_cli -t map -f %2")
                      .arg(MAP_SAVE_PATH.left(MAP_SAVE_PATH.lastIndexOf('/')))
                      .arg(MAP_SAVE_PATH);
    runSSHCommand(cmd);
    ui->label->setText("状态：✅ 地图已保存到 maps 文件夹！");
}

// ==================== 6. 启动导航 ====================
void Widget::startNavigation()
{
    QString cmd = "ros2 launch fishbot_navigation2 navigation2.launch.py use_sim_time:=False";
    runSSHInTerminal(cmd);
    ui->label->setText("状态：✅ 导航已启动！");
}

// ==================== 7. 开始扫地 ====================
void Widget::startCleaning()
{
    QString cmd = "ros2 topic pub --once /clean std_msgs/msg/Bool \"{data: true}\"";
    runSSHCommand(cmd);
    ui->label->setText("状态：✅ 扫地已开始！");
}

// ==================== 8. 停止扫地 ====================
void Widget::stopCleaning()
{
    QString cmd = "ros2 topic pub --once /clean std_msgs/msg/Bool \"{data: false}\"";
    runSSHCommand(cmd);
    ui->label->setText("状态：✅ 扫地已停止！");
}

// ==================== 9. 全覆盖清扫 ====================
void Widget::startFullCoverage()
{
    QString cmd = "ros2 run autosweeper_robot sweeper_node";
    runSSHInTerminal(cmd);
    ui->label->setText("状态：✅ 全覆盖清扫已启动！");
}

// ==================== 10. 打开 RViz2 ====================
void Widget::openRviz2()
{
    QString program = "bash";
    QStringList args;
    args << "-c" << QString("source /opt/ros/%1/setup.bash && rviz2").arg(ROS2_DISTRO);
    QProcess::startDetached(program, args);
    ui->label->setText("状态：✅ RViz2 已在本地打开！");
}
