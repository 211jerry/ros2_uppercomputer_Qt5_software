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

// ==================== 【修改】通用函数：后台执行SSH（强制source环境）====================
void Widget::runSSHCommand(const QString &cmd)
{
    // 【关键修复】在命令前强制加上 source ROS2 环境
    QString fullCmd = QString(
        "source /opt/ros/%1/setup.bash && source %2/install/setup.bash && %3"
    ).arg(ROS2_DISTRO).arg(WS_PATH).arg(cmd);

    QString program = "ssh";
    QStringList args;
    args << QString("%1@%2").arg(PI_USER).arg(PI_IP) << fullCmd;
    QProcess::startDetached(program, args);
}

// ==================== 通用函数：弹出终端执行SSH ====================
void Widget::runSSHInTerminal(const QString &cmd)
{
    QString sshInnerCmd = QString(
        "source /opt/ros/%1/setup.bash && source %2/install/setup.bash && %3; exec bash"
    ).arg(ROS2_DISTRO).arg(WS_PATH).arg(cmd);

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
    // 停止命令不需要 source，直接发信号即可
    QString program = "ssh";
    QStringList args;
    args << QString("%1@%2").arg(PI_USER).arg(PI_IP) << "pkill -SIGINT -f 'ros2 launch'";
    QProcess::startDetached(program, args);
    ui->label->setText("状态：✅ 机器人已停止！");
}

// ==================== 3. 启动建图 ====================
void Widget::startSLAM()
{
    QString cmd = "ros2 launch slam_toolbox online_async_launch.py slam_params_file:=src/fishbot_bringup/config/slam_toolbox.yaml use_sim_time:=False";
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
    runSSHCommand(cmd); // 这里会自动 source 环境
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
    runSSHCommand(cmd); // 这里会自动 source 环境
    ui->label->setText("状态：✅ 扫地已开始！");
}

// ==================== 8. 停止扫地 ====================
void Widget::stopCleaning()
{
    QString cmd = "ros2 topic pub --once /clean std_msgs/msg/Bool \"{data: false}\"";
    runSSHCommand(cmd); // 这里会自动 source 环境
    ui->label->setText("状态：✅ 扫地已停止！");
}

// ==================== 9. 开始全覆盖清扫 ====================
void Widget::startFullCoverage()
{
    QString cmd = "ros2 run autosweeper_robot sweeper_node.py";
    runSSHInTerminal(cmd);
    ui->label->setText("状态：✅ 全覆盖清扫已启动！");
}

// ==================== 10. 在电脑本地打开 RViz2 ====================
void Widget::openRviz2()
{
    QString program = "bash";
    QStringList args;
    args << "-c" << QString("source /opt/ros/%1/setup.bash && rviz2").arg(ROS2_DISTRO);
    QProcess::startDetached(program, args);
    ui->label->setText("状态：✅ RViz2 已在本地打开！");
}
