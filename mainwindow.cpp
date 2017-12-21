#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include "libmodbus/src/modbus.h"
#include "qdebug.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->resize(200, 60);
    this->setWindowTitle("libmodbus slave test");

    pbRtu=new QPushButton("以modbus rtu方式读取地址1中前20个寄存器值", this);
    pbRtu->resize(200, 30);

    pbTcp=new QPushButton("以modbus tcp方式读取地址1中前20个寄存器值", this);
    pbTcp->resize(200, 30);

    QWidget *w=new QWidget();

    QVBoxLayout *layout=new QVBoxLayout();
    layout->addWidget(pbRtu);
    layout->addWidget(pbTcp);

    w->setLayout(layout);

    this->setCentralWidget(w);

    connect(pbRtu, SIGNAL(clicked()), this, SLOT(doRtuQuery()));
    connect(pbTcp, SIGNAL(clicked()), this, SLOT(doTcpQuery()));
}

MainWindow::~MainWindow()
{

}

void myitoa(uint32_t num, uint8_t *str,uint8_t radix)
{
    uint8_t i,tmp;

    for(i=1; i<=radix; i++)//十进制数
    {
        tmp = num%radix;
        *(str+radix-i) = tmp+'0';
        num /= radix;
    }
}

void MainWindow::doRtuQuery()
{
    modbus_t *mb;
    uint16_t tab_reg[32]={0};

    mb = modbus_new_rtu("/dev/ttyUSB0", 9600, 'N', 8, 1);   //相同的端口只能同时打开一个
    modbus_set_slave(mb, 1);  //设置modbus从机地址

    int re = modbus_connect(mb);
    qDebug()<<re<<"\n";

    struct timeval t;
    t.tv_sec=0;
    t.tv_usec=1000000;   //设置modbus超时时间为1000毫秒0x7ffc561bc2a0
    u_int32_t timeout = 0;
    u_int32_t use_sec = 1000000;
    modbus_set_response_timeout(mb, timeout,use_sec);

    int regs = modbus_read_registers(mb, 0, 1, tab_reg);
    qDebug()<<"xxxxxx"<<tab_reg<<"\n";

    QMessageBox::about(NULL, "报告", QString("Rtu读取寄存器的个数:%1").arg(regs));
    modbus_close(mb);
    modbus_free(mb);
}

void MainWindow::doTcpQuery()
{
    modbus_t *mb;
    uint16_t tab_reg[32]={0};

    mb = modbus_new_tcp("127.0.0.1", 5101);  //由于是tcp client连接，在同一个程序中相同的端口可以连接多次。
    modbus_set_slave(mb, 1);  //从机地址

    modbus_connect(mb);

    struct timeval t;
    t.tv_sec=0;
    t.tv_usec=1000000;   //设置modbus超时时间为1000毫秒，注意：经测试，如果没有成功建立tcp连接，则该设置无效。
    u_int32_t timeout = 0;
    u_int32_t use_sec = 1000000;
    modbus_set_response_timeout(mb, timeout,use_sec);
    //modbus_set_response_timeout(mb, &t);

    int regs=modbus_read_registers(mb, 0, 10, tab_reg);

    QMessageBox::about(NULL, "报告", QString("Tcp读取寄存器的个数:%1").arg(regs));
    modbus_close(mb);
    modbus_free(mb);
}
