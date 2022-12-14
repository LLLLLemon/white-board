#include "mycloud.h"
#include "ui_mycloud.h"
#include "Public/public_function.h"
#include "QMouseEvent"
#include <QButtonGroup>
#include <QDebug>
#include <QtDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QApplication>
#include <QGuiApplication>
#include <QScreen>

QString str_WhiteBoardTeacher = "wihteboardteacher";
QString str_WhiteBoardUser    = "wihteboarduser";

MyCloud::MyCloud(QWidget *parent) :
    CloudCoursewareInterFace(parent),
    ui(new Ui::MyCloud)
{
    ui->setupUi(this);
    ui->close->installEventFilter(this);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Dialog);
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background, QBrush(Qt::transparent));
    this->setPalette(palette);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->zhanghaokuang->setEditFocus();
    this->initWidget();
    initconnect();
    this->resizeWidget();
    loop = new QEventLoop(this);

    database = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE","Myphonenum"));
    database->setDatabaseName("MyPhoneNumber.db");
    database->setUserName("admin");
    database->setPassword("admin");
    if(!database->open("admin","admin"))
    {
        qDebug()<< " Error " << database->lastError() <<Qt::endl;
    }
    sql_query = new QSqlQuery(*database);
    if(!sql_query->exec("create table if not exists Phonenum(id int primary key,num varchar(18))"))
    {
        qDebug() << sql_query->lastError();
    }
}

MyCloud::~MyCloud()
{
    delete ui;
}

void MyCloud::show()
{
    QWidget::show();
}


void MyCloud::resizeWidget()
{
    this->setGeometry(QGuiApplication::primaryScreen()->geometry());
    if (ui->stackedWidget->currentWidget() == ui->page)
        ui->widget->setFixedSize(Public_Function::getScaleSize(378,466));
    else if (ui->stackedWidget->currentWidget() == ui->page_2)
        ui->widget->setFixedSize(Public_Function::getScaleSize(378,584));
    else
        ui->widget->setFixedSize(Public_Function::getScaleSize(378,542));

    ui->verticalLayout->setContentsMargins(0, 0, 0, 0);
    ui->verticalLayout->setSpacing(0);
    ui->horizontalLayout_22->setContentsMargins(0, 0, 0, 0);
    ui->horizontalLayout_22->setSpacing(0);

    ui->verticalLayout_5->setContentsMargins(0, Public_Function::getScaleSize(20), 0, Public_Function::getScaleSize(39));
    ui->verticalLayout_5->setSpacing(0);
    ui->horizontalLayout->setContentsMargins(0, 0, Public_Function::getScaleWidth(20), 0);
    ui->horizontalLayout->setSpacing(0);
    ui->horizontalLayout_4->setContentsMargins(0, 0, 0, Public_Function::getScaleWidth(38));
    ui->horizontalLayout_4->setSpacing(0);
    /**************************** page 1 *******************************************/
    ui->verticalLayout_2->setContentsMargins(0, 0, 0, 0);
    ui->verticalLayout_2->setSpacing(0);
    ui->horizontalLayout_2->setContentsMargins(0, 0, 0, Public_Function::getScaleSize(40));
    ui->horizontalLayout_5->setContentsMargins(0, 0, 0, Public_Function::getScaleSize(20));
    ui->horizontalLayout_6->setContentsMargins(0, 0, 0, Public_Function::getScaleSize(40));
    ui->horizontalLayout_7->setContentsMargins(0, 0, 0, Public_Function::getScaleSize(40));
    ui->horizontalLayout_3->setContentsMargins(0, 0, 0, 0);

    ui->close->setFixedSize(Public_Function::getScaleSize(18,18));
    ui->mingcheng->setFixedSize(Public_Function::getScaleSize(145,29));
    ui->account->setFixedSize(Public_Function::getScaleSize(80,26));
    ui->QR_code->setFixedSize(Public_Function::getScaleSize(80,26));

    ui->erweima->hide();
    ui->erweima->setFixedSize(Public_Function::getScaleSize(252,252));
    ui->zhanghaokuang->setFixedSize(Public_Function::getScaleSize(300,50));
    ui->zhanghaokuang->edit->setObjectName("zhanghaokuang");
    ui->zhanghaokuang->raise();

    ui->password->setFixedSize(Public_Function::getScaleSize(300,50));
    ui->password->edit->setObjectName("password");
    ui->login->setStyleSheet(QString("background-color:rgba(20,134,250,1);border-radius: %1px;color: #ffffff;").arg(Public_Function::getScaleWidth(8)));
    ui->login->setFixedSize(Public_Function::getScaleSize(300,50));
    ui->login->setFont(Public_Function::getFont(16));
    ui->registered->setStyleSheet("border-radius: 10px;color:rgba(20,134,250,1);");
    ui->registered->setFixedSize(Public_Function::getScaleSize(70,16));
    ui->registered->setFont(Public_Function::getFont(14));
    ui->forget->setStyleSheet("border-radius: 10px;color:rgba(170,170,170,1);");
    ui->forget->setFixedSize(Public_Function::getScaleSize(70,16));
    ui->forget->setFont(Public_Function::getFont(14));

    codeLab->setFixedSize(Public_Function::getScaleSize(252,252));
    /*************change123*************/
    coverWid->move(Public_Function::getScaleWidth(63),Public_Function::getScaleWidth(170));

    /**************************** page 2 *******************************************/
    ui->verticalLayout_3->setContentsMargins(0, 0, 0, 0);
    ui->verticalLayout_3->setSpacing(0);
    ui->horizontalLayout_8->setContentsMargins(0, 0, 0, Public_Function::getScaleSize(40));
    ui->horizontalLayout_9->setContentsMargins(0, 0, 0, Public_Function::getScaleSize(20));
    ui->horizontalLayout_10->setContentsMargins(0, 0, 0, Public_Function::getScaleSize(20));
    ui->horizontalLayout_11->setContentsMargins(0, 0, 0, Public_Function::getScaleSize(20));
    ui->horizontalLayout_12->setContentsMargins(0, 0, 0, Public_Function::getScaleSize(30));
    ui->horizontalLayout_13->setContentsMargins(0, 0, 0, 0);
    ui->label_change_title->setFixedSize(Public_Function::getScaleSize(100,20));
    ui->label_change_title->setStyleSheet(QString("color:rgb(20,134,250);font-size:%1px").arg(Public_Function::getScaleSize(16)));
    ui->widget_change_phone->setFixedSize(Public_Function::getScaleSize(300,50));
    ui->widget_change_phone->edit->setObjectName("widget_change_phone");
    ui->widget_change_code->setFixedSize(Public_Function::getScaleSize(300,50));
    ui->widget_change_code->edit->setObjectName("widget_change_code");
    ui->widget_change_passwd->setFixedSize(Public_Function::getScaleSize(300,50));
    ui->widget_change_passwd->edit->setObjectName("widget_change_passwd");
    ui->widget_change_repasswd->setFixedSize(Public_Function::getScaleSize(300,50));
    ui->widget_change_repasswd->edit->setObjectName("widget_change_repasswd");
    ui->pushButton_change_login->setStyleSheet(QString("background-color:rgba(20,134,250,1);border-radius: %1px;color: #ffffff;").arg(Public_Function::getScaleWidth(8)));
    ui->pushButton_change_login->setFixedSize(Public_Function::getScaleSize(300,50));
    ui->pushButton_change_login->setFont(Public_Function::getFont(16));

    /**************************** page 3 *******************************************/
    ui->verticalLayout_4->setContentsMargins(0, 0, 0, 0);
    ui->verticalLayout_4->setSpacing(0);
    ui->horizontalLayout_14->setContentsMargins(0, 0, 0, Public_Function::getScaleSize(40));
    ui->horizontalLayout_19->setContentsMargins(0, 0, 0, Public_Function::getScaleSize(20));
    ui->horizontalLayout_17->setContentsMargins(0, 0, 0, Public_Function::getScaleSize(20));
    ui->horizontalLayout_15->setContentsMargins(0, 0, 0, Public_Function::getScaleSize(20));
    ui->horizontalLayout_18->setContentsMargins(0, 0, 0, Public_Function::getScaleSize(30));
    ui->horizontalLayout_20->setContentsMargins(0, 0, 0, Public_Function::getScaleSize(30));
    ui->horizontalLayout_16->setContentsMargins(0, 0, 0, 0);
    ui->label_regist_title->setFixedSize(Public_Function::getScaleSize(80,20));
    ui->label_regist_title->setStyleSheet(QString("color:rgb(20,134,250);font-size:%1px").arg(Public_Function::getScaleSize(16)));
    ui->widget_regist_phone->setFixedSize(Public_Function::getScaleSize(300,50));
    ui->widget_regist_phone->edit->setObjectName("widget_regist_phone");
    ui->widget_regist_passwd->setFixedSize(Public_Function::getScaleSize(300,50));
    ui->widget_regist_passwd->edit->setObjectName("widget_regist_passwd");
    ui->widget_regist_repasswd->setFixedSize(Public_Function::getScaleSize(300,50));
    ui->widget_regist_repasswd->edit->setObjectName("widget_regist_repasswdv");
    ui->widget_regist_code->setFixedSize(Public_Function::getScaleSize(300,50));
    ui->widget_regist_code->edit->setObjectName("widget_regist_code");
    ui->label_regist_1->setStyleSheet(QString("color:rgb(68,68,68);font-size:%1px").arg(12));
    ui->label_regist_2->setStyleSheet(QString("color:rgb(20,134,250);font-size:%1px").arg(12));
    ui->label_regist_3->setStyleSheet(QString("color:rgb(68,68,68);font-size:%1px").arg(12));
    ui->label_regist_4->setStyleSheet(QString("color:rgb(20,134,250);font-size:%1px").arg(12));
    ui->pushButton_regist_login->setStyleSheet(QString("background-color:rgba(20,134,250,1);border-radius: %1px;color: #ffffff;").arg(Public_Function::getScaleWidth(8)));
    ui->pushButton_regist_login->setFixedSize(Public_Function::getScaleSize(300,50));
    ui->pushButton_regist_login->setFont(Public_Function::getFont(16));

}

void MyCloud::initconnect()
{
    m_pHttpThread = new DB_HttpThread;
    connect(m_pHttpThread, &DB_HttpThread::httpThreadFinished, this, &MyCloud::onHttpThreadFinished);

    /**************************** page 1 *******************************************/
    connect(ui->QR_code,&Custom_Btn1::clicked,this,[=](){
        ui->zhanghaokuang->hide();
        ui->erweima->show();
        ui->password->hide();
        ui->login->hide();
        ui->registered->hide();
        ui->jiange->hide();
        ui->forget->hide();
        codeLab->show();
        if(threadstop == 1)
        {
            threadstop =0;
            //???????????????
            m_pHttpThread->start(HttpFunction::GetQrCode, QList<QString>() << str_WhiteBoardUser);
        }
    });

    connect(ui->account,&Custom_Btn1::clicked,this,[=](){
        coverWid->hide();
        threadstop =1;
        ui->zhanghaokuang->show();
        ui->erweima->hide();
        ui->password->show();
        ui->login->show();
        ui->registered->show();
        ui->jiange->show();
        ui->forget->show();
    });

    connect(ui->login,&QPushButton::clicked,this,[=](){
#if  1
        if(loginflag ==0)
        {
            m_pMBoxToolTip->setText("");
            if(ui->zhanghaokuang->getEditText().isEmpty())
            {
               m_pMBoxToolTip->setText(tr("?????????????????????"));
            }
            else if(ui->zhanghaokuang->getEditText().length() != 11)
            {
               m_pMBoxToolTip->setText(tr("??????????????????????????????"));
            }
            else if(ui->password->getEditText().isEmpty())
            {
               m_pMBoxToolTip->setText(tr("???????????????"));
            }
            if(!m_pMBoxToolTip->getText().isEmpty())
            {
                m_pMBoxToolTip->showMBox(QPoint(ui->widget->x() + ui->login->x() + ui->login->width()/2,
                                                ui->widget->y() + ui->stackedWidget->y() + ui->login->y()));
                m_pMBoxToolTip->show();
                return ;
            }
            storageNumber(ui->zhanghaokuang->getEditText());
            m_AfterCheckedDo = 1;
            m_pHttpThread->start(HttpFunction::CheckRegistered, QList<QString>() << ui->zhanghaokuang->getEditText());
        }
#endif
    });

    connect(ui->registered,&QPushButton::clicked,this,[=](){
        ui->stackedWidget->setCurrentWidget(ui->page_3);
        ui->widget->setFixedSize(Public_Function::getScaleSize(378, 584));
    });

    connect(ui->forget, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentWidget(ui->page_2);
        ui->widget->setFixedSize(Public_Function::getScaleSize(378,542));
    });

    connect(ui->zhanghaokuang,&CustomWidget_1::getTelNumber,this,&MyCloud::addID);

    connect(coverWid,&CustomWidget_22::sendStateMessage,this,[=](int num){
        coverWid->hide();
        if( num == 2)//??????????????????????????????????????????????????????????????????,???????????????
            threadstop =2;
        else
        {//???????????????????????????????????????????????????
            m_pHttpThread->start(HttpFunction::GetQrCode, QList<QString>() << str_WhiteBoardUser);
        }
    });


    /**************************** page 2 ????????????*******************************************/
    connect(ui->widget_change_code, &CustomWidget_6::checkPhoneNumber, this, [=](){
        m_AfterCheckedDo = 2;
        m_pHttpThread->start(HttpFunction::CheckRegistered, QList<QString>() << ui->widget_change_phone->getEditText());
    });

     connect(ui->pushButton_change_login,&QPushButton::clicked, this, [=](){signAndLog();});
     /***************change123*****************/
     connect(ui->widget_change_phone->edit,&QLineEdit::editingFinished, this, [=](){
         if(!checkTelephone(ui->widget_change_phone->getEditText(),&tip))
         {
             m_pMBoxToolTip->setText(tip);
             m_pMBoxToolTip->showMBox(QPoint(ui->widget->x() + ui->pushButton_change_login->x() +ui->pushButton_change_login->width()/2,
                                             ui->widget->y() + ui->stackedWidget->y() + ui->pushButton_change_login->y()));
             m_pMBoxToolTip->show();
             return ;
         }
          ui->widget_change_code->enableBtn(true);
     });

     connect(ui->widget_change_phone->edit,&QLineEdit::textChanged, this, [=](QString str){
        if(str.length() == 11)
          ui->widget_change_code->enableBtn(true);
        else
          ui->widget_change_code->enableBtn(false);
     });

     /**************************** page 3 ????????????*******************************************/
     connect(ui->widget_regist_code,&CustomWidget_6::checkPhoneNumber,this,[=](){
         m_AfterCheckedDo = 3;
        m_pHttpThread->start(HttpFunction::CheckRegistered, QList<QString>() << ui->widget_regist_phone->getEditText());
     });

     connect(ui->pushButton_regist_login,&QPushButton::clicked, this, [=](){signAnLog_Regist();});
     connect(ui->widget_regist_phone->edit,&QLineEdit::editingFinished, this, [=](){
         if(checkTelephone(ui->widget_regist_phone->getEditText(),&tip))
         {
             ui->widget_regist_code->enableBtn(true);
             ui->widget_regist_code->getPhoneNumber(ui->widget_regist_phone->getEditText());
         }
     });

     connect(ui->widget_regist_phone->edit,&QLineEdit::textChanged, this, [=](QString str){
        if(str.length() == 11)
        {
             ui->widget_regist_code->enableBtn(true);
        }
        else
        {
             ui->widget_regist_code->enableBtn(false);
        }
     });
}

void MyCloud::stopHttpThread()
{
    m_pHttpThread->stop();
}

QWidget *MyCloud::createWidget(QWidget *parent)
{
    this->setParent(parent);
    return this;
}

void MyCloud::setKeyBoardShow()
{
    ui->zhanghaokuang->setEditFocus();
    keyboard->keyisshow =1;
}

bool MyCloud::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        if(watched == ui->close)
        {
            threadstop =1;
            m_pHttpThread->stop();
            //QApplication::exit(0);
            /*************chang123***************/
            ui->widget->setFixedSize(Public_Function::getScaleSize(378,466));
            ui->stackedWidget->setCurrentWidget(ui->page);
            clearChangeWidget();
            clearRegistWidget();
            ui->password->clearEditText();
            if(!keyboard->isHidden())keyboard->hide();
            keyboard->keyisshow =0;
            this->close();
        }
        else if(watched == ui->label_regist_2)
        {
            ui->widget->hide();
            /*****************change123******************/
            CustomWidget_7 *w = new CustomWidget_7(0,this);
            w->move(QPoint((this->width() - w->width())/2, (this->height() - w->height())/2));
            w->show();
            connect(w,&CustomWidget_7::sendCloseMassage7, this, [=](){
                w->hide();
                w->deleteLater();
                ui->widget->show();
            });
        }
        /*****************change123******************/
        else if(watched == ui->label_regist_4)
        {
            ui->widget->hide();
            /*****************change123******************/
            CustomWidget_7 *w = new CustomWidget_7(1,this);
            w->move(QPoint((this->width() - w->width())/2, (this->height() - w->height())/2));
            w->show();
            connect(w,&CustomWidget_7::sendCloseMassage7, this, [=](){
                w->hide();
                w->deleteLater();
                ui->widget->show();
            });
        }

        return true;
    }
    return QWidget::eventFilter(watched,event);
}

void MyCloud::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.fillRect(this->rect(), Qt::transparent);
}

void MyCloud::storageNumber(QString str)
{
#if  1
    if (!database->open("admin","admin"))
    {
        qDebug() << "Error: Failed to connect database." << database->lastError();
        return ;
    }
    if(sql_query->exec("select num from Phonenum"))
    {
        while(sql_query->next())
        {
            QString num = sql_query->value(0).toString();
            if(num == str)
            {
                return ;
            }
        }
    }
    if(!sql_query->exec(QString("insert into Phonenum values('%1','%2')").arg(getMaxId() +1).arg(str)))
    {
        qDebug() << sql_query->lastError();
    }
    database->close();
#endif
}

int MyCloud::getMaxId()
{
    int max_id = 0;
    if (!database->open("admin","admin"))
    {
        qDebug() << "Error: Failed to connect database." << database->lastError();
        return 0;
    }
    if(!sql_query->exec("select max(id) from Phonenum"))
    {
        qDebug() << sql_query->lastError();
    }
    else
    {
        while(sql_query->next())
        {
            max_id = sql_query->value(0).toInt();
            qDebug() << QString("max id:%1").arg(max_id);
        }
    }
    return max_id;
}

void MyCloud::addID(QListWidget *list)
{
#if  1
    list->clear();
    QString telnum;
    if (!database->open("admin","admin"))
    {
        qDebug() << database->lastError();
        return;
    }
    int num = getMaxId();
    if (!database->open("admin","admin"))
    {
        qDebug() << database->lastError();
        return;
    }
    for(int i=0; i< num ;i++)
    {
        QListWidgetItem *item=new QListWidgetItem(list,i);
        item->setSizeHint(Public_Function::getScaleSize(200,38));
        if(sql_query->exec("select id,num from Phonenum"))
        {
            while(sql_query->next())
            {
                int id = sql_query->value(0).toInt();
                telnum = sql_query->value(1).toString();
                if(id == i)break ;
            }
        }
        else
        {
            qDebug()<< "error " << sql_query->lastError() <<Qt::endl;
        }
        if( i == num -1)
        {
            QWidget *w = new CustomWidget_4(telnum,list);
            w->setObjectName(telnum);
            w->show();
            list->setItemWidget(item,w);
        }
        else
        {
            QWidget *w = new CustomWidget_5(telnum,list);
            w->setObjectName(telnum);
            w->show();
            list->setItemWidget(item,w);
        }
    }
    database->close();
#endif
}

void MyCloud::hideButton()
{
    ui->account->setDisabled(true);
    ui->QR_code->hide();
    ui->registered->hide();
    ui->jiange->hide();
    ui->forget->hide();
}

void MyCloud::onHttpThreadFinished(HttpFunction fun, QVariant variant)
{
    _HttpRetData data = variant.value<_HttpRetData>();
    switch(fun) {
    //?????????????????????
    case HttpFunction::GetQrCode: {
        if (1 == data.state) {  //????????????
            //????????????????????????
            QrCodeData codeData = data.variant.value<QrCodeData>();
            //???????????????????????????
            m_pQrCodeUUID = codeData.uuid;
            //???????????????
           codeLab->setString(codeData.url);
            //??????????????????
            m_pHttpThread->start(HttpFunction::QrCodeLogin, QList<QString>() << "2" <<m_pQrCodeUUID);
        }else { //????????????
        }
    }break;

    //????????????????????????(????????????:1???????????? 2???????????? 3????????? 4????????? 5????????? 6??????????????? 7???????????????)
    case HttpFunction::QrCodeLogin: {
        if (1== data.state) {    //????????????
            //???????????????????????????
            _UserInfoData userData = data.variant.value<_UserInfoData>();
            // ??????????????????http????????????????????????
            DB_HttpThread *httpThread = new DB_HttpThread(this);
            connect(httpThread,&DB_HttpThread::httpThreadFinished, this, &MyCloud::onHttpThreadFinished);
            httpThread->start(HttpFunction::GetUserIconData, QList<QString>() << userData.userIconPath);
            loop->exec();
            this->createUserPanel(userData.userName, userData.telephone);
        }
        else {     //?????????
                 if (5 == data.state){//???????????????
                m_pHttpThread->start(HttpFunction::CancelQrCodeLogin, QList<QString>() << m_pQrCodeUUID);
            }
            else if (6 == data.state){//???????????????
                coverWid->changePixAndText(QPixmap(":/pixmap/Expired-1@2x.png"),tr("??????????????????"),QString(),tr("???????????????"),1);
                if(coverWid->isHidden())coverWid->show();
                break;
            }
            else if (7 == data.state){//???????????????
                m_pMBoxToolTip->setText(tr("???????????????"));
                m_pMBoxToolTip->showMBox(QPoint(ui->widget->x() + ui->login->x() + ui->login->width()/2,
                                                ui->widget->y() + ui->stackedWidget->y() + ui->login->y()));
                break;
            }
            else if (8 == data.state){//???????????????
                m_pMBoxToolTip->setText(tr("???????????????"));
                m_pMBoxToolTip->showMBox(QPoint(ui->widget->x() + ui->login->x() + ui->login->width()/2,
                                                ui->widget->y() + ui->stackedWidget->y() + ui->login->y()));
                qDebug()<< " cancel"  <<Qt::endl;
                break;
            }//????????????
            else
            {
                if (4 == data.state){//???????????????
                     coverWid->changePixAndText(QPixmap(":/pixmap/success-1@2x.png"),tr("????????????"),tr("???????????????????????????"),tr("????????????"),2);
                     if(coverWid->isHidden())coverWid->show();
                }
                QEventLoop *loop = new QEventLoop(this);
                QTimer *timer = new QTimer(this);
                timer->start(100);
                connect(timer,&QTimer::timeout,this,[=](){
                    timer->stop();
                    loop->exit();
                });
               loop->exec();
               if(threadstop == 0)
               {
                   m_pHttpThread->start(HttpFunction::QrCodeLogin, QList<QString>() << "2" << m_pQrCodeUUID);
                   timer->deleteLater();
                   loop->deleteLater();
               }

               if(threadstop == 2)
               {
                   threadstop =0;
                   m_pHttpThread->start(HttpFunction::GetQrCode, QList<QString>() << str_WhiteBoardUser);
                   timer->deleteLater();
                   loop->deleteLater();
               }
            }
        }
    }break;

    // ???????????????????????????
    case HttpFunction::CancelQrCodeLogin: {
        if (1 == data.state) {    //????????????
            //????????????????????????
            qDebug()<< "???????????? "   <<Qt::endl;
            coverWid->changePixAndText(QPixmap(":/pixmap/cancel-1@2x.png"),tr("?????????"),QString(),tr("???????????????"),3);
            if(coverWid->isHidden())coverWid->show();
        }else { //????????????
            qDebug()<< "???????????? "  <<Qt::endl;
            m_pHttpThread->start(HttpFunction::CancelQrCodeLogin, QList<QString>() << m_pQrCodeUUID);
        }
    }break;

    //??????????????????
    case HttpFunction::CheckRegistered:{
        if (1 == data.state) {  //?????????
            /**********change123************/
            if(m_AfterCheckedDo == 3)
            {
                m_pHttpThread->start(HttpFunction::GetVerificationCode, QList<QString>() << ui->widget_regist_phone->getEditText());
            }
            else if(m_AfterCheckedDo == 2)
            {
                m_pMBoxToolTip->setText(tr("????????????????????????"));
                m_pMBoxToolTip->showMBox(QPoint(ui->widget->x() + ui->pushButton_change_login->x() + ui->pushButton_change_login->width()/2,
                                                ui->widget->y() + ui->stackedWidget->y() + ui->pushButton_change_login->y()));
            }
            else
            {
                m_pMBoxToolTip->setText(tr("????????????????????????"));
                if (ui->stackedWidget->currentWidget() == ui->page) {
                    m_pMBoxToolTip->showMBox(QPoint(ui->widget->x() + ui->login->x() + ui->login->width()/2,
                                                    ui->widget->y() + ui->stackedWidget->y() + ui->login->y()));
                }else if (ui->stackedWidget->currentWidget() == ui->page_2)
                    m_pMBoxToolTip->showMBox(QPoint(ui->widget->x() + ui->pushButton_change_login->x() + ui->pushButton_change_login->width()/2,
                                                    ui->widget->y() + ui->stackedWidget->y() + ui->pushButton_change_login->y()));
                else if (ui->stackedWidget->currentWidget() == ui->page_3)
                    m_pMBoxToolTip->showMBox(QPoint(ui->widget->x() + ui->pushButton_regist_login->x() + ui->pushButton_regist_login->width()/2,
                                                    ui->widget->y() + ui->stackedWidget->y() + ui->pushButton_regist_login->y()));
            }
        }else if (2 == data.state){ //?????????
            /**************change123*************/
            if (1 == m_AfterCheckedDo)
                m_pHttpThread->start(HttpFunction::LoginAccount, QList<QString>() << "2" << ui->password->getEditText() <<ui->zhanghaokuang->getEditText());
            else if (2 == m_AfterCheckedDo)
                m_pHttpThread->start(HttpFunction::GetVerificationCode, QList<QString>() << ui->widget_change_phone->getEditText());
            else if(3 == m_AfterCheckedDo)
            {
                m_pMBoxToolTip->setText(tr("???????????????????????????????????????"));
                m_pMBoxToolTip->showMBox(QPoint(ui->widget->x() + ui->pushButton_regist_login->x() + ui->pushButton_regist_login->width()/2,
                                                ui->widget->y() + ui->stackedWidget->y() + ui->pushButton_regist_login->y()));
            }
        }
    }break;

    //????????????????????????
    case HttpFunction::LoginAccount: {
        qDebug()<<"LoginAccount"<<data.state<<data.code;
        if (1 == data.state) {  //????????????
            loginflag =1;
            //???????????????????????????
            _UserInfoData userData = data.variant.value<_UserInfoData>();        
            //??????????????????
            m_pHttpThread->start(HttpFunction::GetUserIconData, QList<QString>() << userData.userIconPath);
            loop->exec();
            this->createUserPanel(userData.userName, ui->zhanghaokuang->getEditText());
            ui->password->clearEditText();
            ui->widget->hide();
        }else{
            if (2 == data.state)    //????????????
            {
                m_pMBoxToolTip->setText(tr("????????????"));
                ui->password->clearEditText();
            }
            else    //????????????
            {
                m_pMBoxToolTip->setText(tr("????????????"));
                m_pMBoxToolTip->showMBox(QPoint(ui->widget->x() + ui->login->x() + ui->login->width()/2,
                                                ui->widget->y() + ui->stackedWidget->y() + ui->login->y()));
            }

            if(!m_pMBoxToolTip->getText().isEmpty())
            {
                m_pMBoxToolTip->showMBox(QPoint(ui->widget->x() + ui->login->x() + ui->login->width()/2,
                                                ui->widget->y() + ui->stackedWidget->y() + ui->login->y()));
                m_pMBoxToolTip->show();
            }
        }
    }break;

    case HttpFunction::GetUserIconData: {
        if (1 == data.state) {
           _UsrIcoData icoData = data.variant.value<_UsrIcoData>();
           bool bo = pix.loadFromData(icoData.data);
           if(!bo) qDebug()<< " ??????????????????"<<Qt::endl;
           qDebug()<<"get icon finished";
        }
        loop->quit();
    }break;

    case HttpFunction::GetVerificationCode: {
        if (1 == data.state) {
            m_pMBoxToolTip->setText(tr("????????????"));
            if (2 == m_AfterCheckedDo)
                ui->widget_change_code->getCode();
            else if (3 == m_AfterCheckedDo)
                ui->widget_regist_code->getCode();
        }else {
            m_pMBoxToolTip->setText(tr("????????????"));
        }
        if (2 == m_AfterCheckedDo)
            m_pMBoxToolTip->showMBox(QPoint(ui->widget->x() + ui->pushButton_change_login->x() + ui->pushButton_change_login->width()/2,
                                            ui->widget->y() + ui->stackedWidget->y() + ui->pushButton_change_login->y()));
        else if (3 == m_AfterCheckedDo)
            m_pMBoxToolTip->showMBox(QPoint(ui->widget->x() + ui->pushButton_regist_login->x() + ui->pushButton_regist_login->width()/2,
                                            ui->widget->y() + ui->stackedWidget->y() + ui->pushButton_regist_login->y()));
    }break;

    //????????????????????????
    case HttpFunction::ChangePassword: {
        if (1 == data.state) {  //????????????
            ui->zhanghaokuang->setEditText(ui->widget_change_phone->getEditText());
            ui->password->setEditText(ui->widget_change_repasswd->getEditText());
            clearChangeWidget();
            m_pHttpThread->start(HttpFunction::LoginAccount, QList<QString>() << "2" << ui->password->getEditText() <<ui->zhanghaokuang->getEditText());
            ui->stackedWidget->setCurrentWidget(ui->page);
        }else{
            QString str =data.code;
            m_pMBoxToolTip->setText(str);
            //m_pMBoxToolTip->setText(tr("????????????"));
            m_pMBoxToolTip->showMBox(QPoint(ui->widget->x() + ui->pushButton_change_login->x() + ui->pushButton_change_login->width()/2,
                                            ui->widget->y() + ui->stackedWidget->y() + ui->pushButton_change_login->y()));
        }
    }break;

    case HttpFunction::RegisterAccount: {
        if (1 == data.state) {
            m_pMBoxToolTip->setText(tr("????????????"));
            ui->zhanghaokuang->setEditText(ui->widget_regist_phone->getEditText());
            ui->password->setEditText(ui->widget_regist_repasswd->getEditText());
            clearRegistWidget();
            m_pHttpThread->start(HttpFunction::LoginAccount, QList<QString>() << "2" << ui->password->getEditText() <<ui->zhanghaokuang->getEditText());
            ui->stackedWidget->setCurrentWidget(ui->page);
        }else {
            QString str =data.code;
            m_pMBoxToolTip->setText(str);
            m_pMBoxToolTip->showMBox(QPoint(ui->widget->x() + ui->pushButton_regist_login->x() + ui->pushButton_regist_login->width()/2,
                                            ui->widget->y() + ui->stackedWidget->y() + ui->pushButton_regist_login->y()));
        }
    }break;

    default:
        break;
    }
    keyboard->hide();
}

void MyCloud::initWidget()
{
    keyboard = new Keyboard(this);
    keyboard->hide();
    /**************************** page 1 *******************************************/
    ui->close->setScaledContents(true);
    ui->close->setPixmap(QPixmap(":/pixmap/guanbi@2x.png"));
    ui->mingcheng->setScaledContents(true);
    ui->mingcheng->setPixmap(QPixmap(":/pixmap/yunkejian1@2x.png"));
    ui->account->setText_m(tr("????????????"));
    ui->QR_code->setText_m(tr("????????????"));
    ui->login->setText(tr("????????????"));
    ui->registered->setText(tr("????????????"));
    ui->jiange->setText("???");
    ui->forget->setText(tr("????????????"));

    QButtonGroup *group = new QButtonGroup(this);
    group->setExclusive(true);
    group->addButton(ui->account);
    group->addButton(ui->QR_code);
    ui->account->setChecked(true);

    codeLab = new Custom_Lab3(ui->erweima);
    codeLab->setScaledContents(true);
    codeLab->setPixmap(QPixmap(":/pixmap/1.PNG"));
    codeLab->hide();

    //?????????
    m_pMBoxToolTip = new CustomWidget_21;
    m_pMBoxToolTip->setParent(this);
    m_pMBoxToolTip->hide();

    coverWid = new CustomWidget_22();
    /*************change123*************/
    coverWid->setParent(ui->widget);
    coverWid->hide();

    /**************************** page 2 *******************************************/
    ui->label_change_title->setText(tr("??????????????????"));
    ui->label_change_title->setAlignment(Qt::AlignCenter);
    ui->widget_change_phone->changeText(tr("??????:"),tr("?????????????????????"),1);
    ui->widget_change_passwd->changeText(tr("???????????????"),tr("??????????????????"),0);
    ui->widget_change_repasswd->changeText(tr("???????????????"),tr("??????????????????"),0);
    ui->pushButton_change_login->setText(tr("???????????????"));

    /**************************** page 3 *******************************************/
    ui->label_regist_title->setText(tr("???????????????"));
    ui->label_regist_title->setAlignment(Qt::AlignCenter);
    ui->widget_regist_phone->changeText(tr("??????:"),tr("?????????????????????"),1);
    ui->widget_regist_passwd->changeText(tr("???????????????"),tr("??????????????????"),0);
    ui->widget_regist_repasswd->changeText(tr("???????????????"),tr("??????????????????"),0);
    ui->label_regist_1->setText(tr("???????????????"));
    ui->label_regist_2->setText(tr("??????????????????"));
    ui->label_regist_2->installEventFilter(this);
    ui->label_regist_3->setText(tr("???"));
    ui->label_regist_4->setText(tr("??????????????????"));
    ui->label_regist_4->installEventFilter(this);
    ui->pushButton_regist_login->setText(tr("???????????????"));

    ui->stackedWidget->setCurrentWidget(ui->page);

    //hideButton();

}

void MyCloud::signAndLog()
{
    QTimer *timer = new QTimer(this);
    ui->pushButton_change_login->setEnabled(false);
    connect(timer,&QTimer::timeout,this,[=](){timer->stop();ui->pushButton_change_login->setEnabled(true);timer->deleteLater();});
    timer->start(1000);
    m_pMBoxToolTip->setText("");
    if(ui->widget_change_phone->getEditText().isEmpty())
    {
       m_pMBoxToolTip->setText(tr("?????????????????????"));
    }
    else if(ui->widget_change_phone->getEditText().length() != 11)
    {
       m_pMBoxToolTip->setText(tr("??????????????????????????????"));
    }
    else if(ui->widget_change_code->getEditText().isEmpty())
    {
        m_pMBoxToolTip->setText(tr("??????????????????"));
    }
    else if(ui->widget_change_passwd->getEditText().isEmpty())
    {
        m_pMBoxToolTip->setText(tr("???????????????"));
    }
    else if(ui->widget_change_repasswd->getEditText().isEmpty())
    {
        m_pMBoxToolTip->setText(tr("?????????????????????"));
    }
    else if(QString::compare(ui->widget_change_passwd->getEditText(), ui->widget_change_repasswd->getEditText(), Qt::CaseSensitive) != 0)
    {
        m_pMBoxToolTip->setText(tr("???????????????????????????"));
    }

    /* ???????????????????????? */
    QString passwdRequireLLetter = QString("abcdefghijklmnopqrstuvwxyz");
    QString passwdRequireCLetter = QString("ABCDEFGHIJKLMNOPQRSTUVWSYZ");
    QString passwdRequireNum = QString("0123456789");
    QString passwdRequireSpecialChar = QString("!@#$%^&*()_+");
    QString inPassword = ui->widget_change_passwd->getEditText();
    bool isLLetter =false;
    bool isCLetter =false;
    bool isNum =false;
    bool isSpecialChar =false;
    //??????????????????6?????????16???(????????????????????????????????????)
    if (inPassword.length() < 6) {
        if(m_pMBoxToolTip->getText().isEmpty())
        m_pMBoxToolTip->setText(tr("???????????????????????????"));
        ui->widget_change_passwd->setFocus();
    }

    /* ?????????????????????????????????????????? */
    for (int i = 0; i < inPassword.length(); i++) {
        QChar ch = inPassword.at(i);
        if (passwdRequireLLetter.contains(ch))
            isLLetter = true;
        else if (passwdRequireCLetter.contains(ch))
            isCLetter = true;
        else if (passwdRequireNum.contains(ch))
            isNum = true;
        else if (passwdRequireSpecialChar.contains(ch))
            isSpecialChar = true;
    }

    int typeNum = 0;
    if (isLLetter)
        typeNum++;
    if (isCLetter)
        typeNum++;
    if (isNum)
        typeNum++;
    if (isSpecialChar)
        typeNum++;
    if (typeNum < 3) {
        if(m_pMBoxToolTip->getText().isEmpty())
        m_pMBoxToolTip->setText(tr("???????????????????????????????????????????????????????????????\r\n"
                                   "???!@#$%^&*()_+???????????????????????????6-16??????"));
        ui->widget_change_passwd->setFocus();
    }
   if(!m_pMBoxToolTip->getText().isEmpty())
   {
        m_pMBoxToolTip->showMBox(QPoint(ui->widget->x() + ui->pushButton_change_login->x() + ui->pushButton_change_login->width()/2,
                                        ui->widget->y() + ui->stackedWidget->y() + ui->pushButton_change_login->y()));
        m_pMBoxToolTip->show();
        return ;
   }

//    this->hide();
//    emit closeMassage();
   m_pHttpThread->start(HttpFunction::ChangePassword, QList<QString>() << ui->widget_change_code->getEditText() <<ui->widget_change_passwd->getEditText() <<ui->widget_change_phone->getEditText());
}

void MyCloud::signAnLog_Regist()
{
    QTimer *timer = new QTimer(this);
    ui->pushButton_regist_login->setEnabled(false);
    connect(timer,&QTimer::timeout,this,[=](){timer->stop();ui->pushButton_regist_login->setEnabled(true);timer->deleteLater();});
    timer->start(1000);
    m_pMBoxToolTip->setText("");
    if(ui->widget_regist_phone->getEditText().isEmpty())
    {
       m_pMBoxToolTip->setText(tr("?????????????????????"));
    }
    else if(ui->widget_regist_phone->getEditText().length() != 11)
    {
       m_pMBoxToolTip->setText(tr("??????????????????????????????"));
    }
    else if(ui->widget_regist_code->getEditText().isEmpty())
    {
        m_pMBoxToolTip->setText(tr("??????????????????"));
    }
    else if(ui->widget_regist_passwd->getEditText().isEmpty())
    {
        m_pMBoxToolTip->setText(tr("???????????????"));
    }
    else if(ui->widget_regist_repasswd->getEditText().isEmpty())
    {
        m_pMBoxToolTip->setText(tr("?????????????????????"));
    }
    else if(QString::compare(ui->widget_regist_passwd->getEditText(), ui->widget_regist_repasswd->getEditText(), Qt::CaseSensitive) != 0)
    {
        m_pMBoxToolTip->setText(tr("???????????????????????????"));
    }

    /* ???????????????????????? */
    QString passwdRequireLLetter = QString("abcdefghijklmnopqrstuvwxyz");
    QString passwdRequireCLetter = QString("ABCDEFGHIJKLMNOPQRSTUVWSYZ");
    QString passwdRequireNum = QString("0123456789");
    QString passwdRequireSpecialChar = QString("!@#$%^&*()_+");
    QString inPassword = ui->widget_regist_passwd->getEditText();
    bool isLLetter =false;
    bool isCLetter =false;
    bool isNum =false;
    bool isSpecialChar =false;
    //??????????????????6?????????16???(????????????????????????????????????)
    if (inPassword.length() < 6) {
        if(m_pMBoxToolTip->getText().isEmpty())
        m_pMBoxToolTip->setText(tr("???????????????????????????"));
        ui->widget_regist_passwd->setFocus();
    }

    /* ?????????????????????????????????????????? */
    for (int i = 0; i < inPassword.length(); i++) {
        QChar ch = inPassword.at(i);
        if (passwdRequireLLetter.contains(ch))
            isLLetter = true;
        else if (passwdRequireCLetter.contains(ch))
            isCLetter = true;
        else if (passwdRequireNum.contains(ch))
            isNum = true;
        else if (passwdRequireSpecialChar.contains(ch))
            isSpecialChar = true;
    }

    int typeNum = 0;
    if (isLLetter)
        typeNum++;
    if (isCLetter)
        typeNum++;
    if (isNum)
        typeNum++;
    if (isSpecialChar)
        typeNum++;
    if (typeNum < 3) {
        if(m_pMBoxToolTip->getText().isEmpty())
        m_pMBoxToolTip->setText(tr("???????????????????????????????????????????????????????????????\r\n"
                                   "???!@#$%^&*()_+???????????????????????????6-16??????"));
        ui->widget_regist_passwd->setFocus();
    }
   if(!m_pMBoxToolTip->getText().isEmpty())
   {
        m_pMBoxToolTip->showMBox(QPoint(ui->widget->x() + ui->pushButton_regist_login->x() + ui->pushButton_regist_login->width()/2,
                                        ui->widget->y() + ui->stackedWidget->y() + ui->pushButton_regist_login->y()));
        m_pMBoxToolTip->show();
        return ;
   }
   m_pHttpThread->start(HttpFunction::RegisterAccount, QList<QString>() << ui->widget_regist_code->getEditText() <<ui->widget_regist_passwd->getEditText() << ui->widget_regist_phone->getEditText());
}

bool MyCloud::checkTelephone(const QString &str, QString *tip)
{
    if (str.isEmpty()) {
        *tip = QString(tr("?????????????????????"));
        return false;
    }

    if (11 != str.length()) {
        *tip = QString(tr("??????????????????????????????"));
        return false;
    }
    return true;
}

void MyCloud::clearChangeWidget()
{
    ui->widget_change_phone->clearEditText();
    ui->widget_change_code->clearEditText();
    ui->widget_change_passwd->clearEditText();
    ui->widget_change_repasswd->clearEditText();
}

void MyCloud::clearRegistWidget()
{
    ui->widget_regist_phone->clearEditText();
    ui->widget_regist_code->clearEditText();
    ui->widget_regist_passwd->clearEditText();
    ui->widget_regist_repasswd->clearEditText();
}

void MyCloud::createUserPanel(const QString &name, const QString &url)
{
    MainInterface *  maininterface = new MainInterface(this);
    maininterface->changeName(name);
    maininterface->changePicture(pix);
    maininterface->getUrl(url);
    maininterface->move(QPoint((this->width() - maininterface->width())/2, (this->height() - maininterface->height())/2));
    maininterface->show();
    connect(maininterface,&MainInterface::cancellation,this,[=](){
        maininterface->hide();
        threadstop =0;
        loginflag =0;
        ui->account->setChecked(true);
        emit ui->account->clicked();
        ui->password->clearEditText();
        maininterface->deleteLater();
        ui->widget->show();
        ui->stackedWidget->setCurrentWidget(ui->page);
    });
    connect(maininterface, &MainInterface::widgetClosed, this, [=](){
        this->close();
    });
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(CloudCoursewareInterFace, MyCloud)//???????????????????????????????????????????????????????????????
#endif // QT_VERSION < 0x050000
