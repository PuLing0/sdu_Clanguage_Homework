#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindialog.h"
#include "regdialog.h"
#include "chgpddialog.h"

framelessWidget::framelessWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::framelessWidget)
{
    ui->setupUi(this);

    ui->mainWidget->setMouseTracking(true); // 允许鼠标跟踪
    ui->mainDisplayWidget->setMouseTracking(true);
    setMouseTracking(true);

    QTimer *t = new QTimer(this);
    connect(t, &QTimer::timeout, this, [=](){Init();});
    t->setSingleShot(true);
    t->start(10);


    connect(ui->Button_min, &QPushButton::clicked, this,[=]()   // 点击最小化按钮
    {
        this->showMinimized();
    });
    connect(ui->Button_close,&QPushButton::clicked, this,[=]()  // 点击关闭按钮
    {
        this->close();
    });

    // 在类的头文件中定义成员变量
    QAction *showPasswordAction;

    // 在类的构造函数或初始化函数中进行初始化
    showPasswordAction = new QAction(this);

    // 将图标添加到密码输入框的尾部位置
    connect(ui->L_Psd, &QtMaterialAutoComplete::textEdited, this, [=]() {
        static bool first = true;
        if (first) {
            ui->L_Psd->addAction(showPasswordAction, QLineEdit::TrailingPosition);
            first = false;
        }
    });

    // 切换图标和密码显示模式
    int stat =1;
    showPasswordAction->setIcon(QIcon(QStringLiteral(":/eyes-open.png")));
    connect(showPasswordAction, &QAction::triggered, this, [=]() mutable {
        if (stat == 0) {
            showPasswordAction->setIcon(QIcon(QStringLiteral(":/eyes-open.png")));
            //            qDebug() << "Icon file exists: " << QFile::exists(":/pic/eyes-open.png");
            ui->L_Psd->removeAction(showPasswordAction);
            ui->L_Psd->addAction(showPasswordAction, QLineEdit::TrailingPosition);
            ui->L_Psd->setEchoMode(QLineEdit::Normal);
            stat = 1;
        } else if (stat == 1) {
            showPasswordAction->setIcon(QIcon(QStringLiteral(":/preview-close.png")));
            ui->L_Psd->removeAction(showPasswordAction);
            ui->L_Psd->addAction(showPasswordAction, QLineEdit::TrailingPosition);
            ui->L_Psd->setEchoMode(QLineEdit::Password);
            stat = 0;
        }
    });
}

framelessWidget::~framelessWidget()
{
    delete ui;
}

/* 给centralwidget添加一个mainwidget，设置遮罩及遮挡锯齿边缘的board*/
void framelessWidget::Init()
{
// 获取遮罩的轮廓并给mainWidget设置遮罩
// 遮罩的作用是重叠的部分才可以看到
    QPainterPath path;
    path.addRoundedRect(ui->mainWidget->rect(), cornerRadius-1 , cornerRadius-1 );
    QRegion mask(path.toFillPolygon().toPolygon());
    ui->mainWidget->setMask(mask);
    // 给mainwidget添加样式
    QString mainStyle;
    ui->mainWidget->setObjectName("mainWidget");
    mainStyle = "QWidget#mainWidget{background-color:rgb(251, 251, 251)"  + QString::asprintf(";border-radius:%dpx", cornerRadius) + "}";
    ui->mainWidget->setStyleSheet(mainStyle);
}

// 鼠标按下事件(记录拉伸窗口或移动窗口时的起始坐标（左上角）)
void framelessWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mousePressed = true;
        lastPos = event->globalPos() - this->frameGeometry().topLeft();
    }
}

// 鼠标移动事件
void framelessWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::NoButton) // 如果鼠标按钮没有被按下
        mousePressed = false; // 将鼠标按下状态标记为false
    if(!mousePressed)
    { // 如果鼠标没有按下（鼠标移动事件）
        mouseState = 0; // 鼠标状态初始化为0
        // 检测鼠标位置是否靠近主部件的边界，并根据情况更新鼠标状态
        if(!maximized && abs(event->pos().x() - ui->mainWidget->pos().x()) < 5)
            mouseState |= AT_LEFT; // 设置鼠标状态为左侧
        if(!maximized && abs(event->pos().y() - ui->mainWidget->pos().y()) < 5)
            mouseState |= AT_TOP; // 设置鼠标状态为顶部
        if(!maximized && abs(event->pos().x() - ui->mainWidget->pos().x() - ui->mainWidget->width()) < 5)
            mouseState |= AT_RIGHT; // 设置鼠标状态为右侧
        if(!maximized && abs(event->pos().y() - ui->mainWidget->pos().y() - ui->mainWidget->height()) < 5)
            mouseState |= AT_BOTTOM; // 设置鼠标状态为底部
        // 根据鼠标状态设置相应的光标形状
        if(mouseState == AT_TOP_LEFT || mouseState == AT_BOTTOM_RIGHT)
            setCursor(Qt::SizeFDiagCursor); // 设置光标为大小调整（向下和向右）的斜线形状
        else if(mouseState == AT_TOP_RIGHT || mouseState == AT_BOTTOM_LEFT)
            setCursor(Qt::SizeBDiagCursor); // 设置光标为大小调整（向下和向左）的斜线形状
        else if(mouseState & (AT_LEFT | AT_RIGHT))
            setCursor(Qt::SizeHorCursor); // 设置光标为水平调整大小的形状
        else if(mouseState & (AT_TOP | AT_BOTTOM))
            setCursor(Qt::SizeVerCursor); // 设置光标为垂直调整大小的形状
        else
            unsetCursor(); // 恢复默认光标形状
    }
    else
    { // 如果鼠标已按下并移动
        if(mouseState == 0)
        {
            // 如果鼠标状态为0（未调整大小）
            if(maximized)
            {
                // 如果窗口已最大化
                qreal wRatio = (double)event->pos().x() / (double)ui->mainWidget->width(); // 计算当前鼠标位置相对于主部件宽度的比例
                controlWindowScale(); // 恢复窗口的正常大小
                this->move(QPoint(event->globalPos().x() - ui->mainWidget->width() * wRatio, -30)); // 移动窗口到鼠标位置，并考虑标题栏的高度
                lastPos = QPoint(ui->mainWidget->width() * wRatio, event->pos().y()); // 保存最后的鼠标位置
            }
            else
                this->move(event->globalPos() - lastPos); // 移动窗口到鼠标位置
        }
        else
        {
            // 如果鼠标状态不为0（调整大小）
            QPoint d = event->globalPos() - frameGeometry().topLeft() - lastPos; // 计算鼠标移动的偏移量
            if(mouseState & AT_LEFT)
            {
                // 如果鼠标状态包含左侧
                this->move(this->frameGeometry().x() + d.x(), this->frameGeometry().y()); // 调整窗口的水平位置
                this->resize(this->width() - d.x(), this->height()); // 调整窗口的宽度
            }
            if(mouseState & AT_RIGHT)
            {
                // 如果鼠标状态包含右侧
                this->resize(this->width() + d.x(), this->height()); // 调整窗口的宽度
            }
            if(mouseState & AT_TOP)
            {
                // 如果鼠标状态包含顶部
                this->move(this->frameGeometry().x(), this->frameGeometry().y() + d.y()); // 调整窗口的垂直位置
                this->resize(this->width(), this->height() - d.y()); // 调整窗口的高度
            }
            if(mouseState & AT_BOTTOM)
            {
                // 如果鼠标状态包含底部
                this->resize(this->width(), this->height() + d.y()); // 调整窗口的高度
            }
        }
        lastPos = event->globalPos() - this->frameGeometry().topLeft(); // 更新最后的鼠标位置
    }
}

// 窗口变化事件
void framelessWidget::resizeEvent(QResizeEvent *event)
{
    //边界变换大小
    if(border)
        border->resize(ui->mainWidget->size() + QSize(2, 2));

    //遮罩变换
    QPainterPath path;
    path.addRect(ui->mainWidget->rect());
    QRegion mask(path.toFillPolygon().toPolygon());
    ui->mainWidget->setMask(mask);
}

//点击最大化按钮事件
void framelessWidget::controlWindowScale()
{
#ifdef Q_OS_WIN
    if (!maximized)
    { // 如果窗口没有最大化
        lastGeometry = this->frameGeometry(); // 保存当前窗口的位置和大小
        // windowShadow->setEnabled(false); // 禁用窗口阴影效果（注释掉的代码）
        ui->verticalLayout->setContentsMargins(0, 0, 0, 0); // 设置主垂直布局的边距为0
        border->hide(); // 隐藏窗口边框
        QString mainStyle = "QWidget#mainWidget{background-color:rgb(251,251,251) border-radius:0px;}"; // 设置主部件的样式表
        ui->mainWidget->setStyleSheet(mainStyle); // 应用样式表到主部件
        this->showMaximized(); // 最大化窗口
        maximized = true; // 标记窗口已最大化
        QPainterPath path; // 创建绘图路径对象
        path.addRect(ui->mainWidget->rect()); // 在绘图路径中添加主部件的矩形区域
        QRegion mask(path.toFillPolygon().toPolygon()); // 将绘图路径转换为多边形并创建区域对象
        ui->mainWidget->setMask(mask); // 应用区域遮罩到主部件
    }
    else
    { // 如果窗口已经最大化
        ui->verticalLayout->setContentsMargins(30, 30, 30, 30); // 恢复主垂直布局的默认边距
        this->showNormal(); // 恢复窗口的正常大小
        QString mainStyle = "QWidget#mainWidget{background-color:rgb(251,251,251)" + QString::asprintf(";border-radius:%dpx", cornerRadius) + "}"; // 根据指定的圆角半径创建主部件的样式表
        ui->mainWidget->setStyleSheet(mainStyle); // 应用样式表到主部件
        QPainterPath path; // 创建绘图路径对象
        path.addRoundedRect(ui->mainWidget->rect(), cornerRadius - 1, cornerRadius - 1); // 在绘图路径中添加带圆角的矩形区域
        QRegion mask(path.toFillPolygon().toPolygon()); // 将绘图路径转换为多边形并创建区域对象
        ui->mainWidget->setMask(mask); // 应用区域遮罩到主部件
        border->show(); // 显示窗口边框
        // windowShadow->setEnabled(true); // 启用窗口阴影效果（注释掉的代码）
        this->resize(lastGeometry.width(), lastGeometry.height()); // 恢复窗口的上次大小
        this->move(lastGeometry.x(), lastGeometry.y()); // 恢复窗口的上次位置
        maximized = false; // 标记窗口未最大化
    }
#endif
}


//登录按钮
void framelessWidget::on_btn_login_clicked()
{
    LoginDialog *Log = new LoginDialog();
    QString account = ui->L_Ac->text();
    QString password = ui->L_Psd->text();
    if (Log->LoginUser(account , password))
    {
        //如果登录成功，将主页面隐藏
        this->hide();
    }
    //登录不成功重新输入,将输入栏清空
    else
    {
        ui->L_Ac->clear();
        ui->L_Psd->clear();
    }
}

//注册按钮
void framelessWidget::on_btn_reg_clicked()
{
    RegDialog *reg = new RegDialog();
    reg->show();
    this->hide();
}

//修改密码按钮
void framelessWidget::on_btn_chg_clicked()
{
    chgpdDialog *chg = new chgpdDialog();
    chg->show();
    this->hide();
}

// 鼠标释放事件处理函数
void framelessWidget::mouseReleaseEvent(QMouseEvent *event)
{
    mousePressed = false;
    if(event->globalPos().y() < 2)
        controlWindowScale();
}

// 鼠标双击事件处理函数
void framelessWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->y()<60)
        controlWindowScale();
}
