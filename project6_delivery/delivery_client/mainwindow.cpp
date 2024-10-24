#include "mainwindow.h"
#include "ui_mainwindow.h"

// [ex.02.1]
// MainWindow 생성자 실행
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // [ex.02.1.1]
    // MainWindow 객체 생성과 동시에 생성자에서 서버로 연결 요청을 보내도록 실행
    m_socket = new QTcpSocket(this);

    m_socket->connectToHost(QHostAddress::LocalHost,8080);
    if(m_socket->waitForConnected())
    {
        // 연결 성공시 출력
        ui->statusBar->showMessage("Connected to Server");
    }
    else
    {
        QMessageBox::critical(this,"QTCPClient", QString("The following error occurred: %1.").arg(m_socket->errorString()));
        exit(EXIT_FAILURE);
    }

    // loginWidget 객체 생성!!!
    loginWidget = new Login();
    loginWidget->show();

    connect(loginWidget, &Login::user_info_signal, this, &MainWindow::send_login_func_order); // 회원가입 정보 전송 connect
    connect(loginWidget, &Login::login_success_signal, this, &MainWindow::get_login_user_id);

    connect(this, &MainWindow::operate_info_signal, loginWidget, &Login::signUp_operate);
    connect(this, &MainWindow::login_info_signal, loginWidget, &Login::login_operate);

    connect(ui->shopSearchButton, &QPushButton::clicked, this, [this](){shop_search_chk = true; send_delivery_func_order(SHOPLIST);});
    connect(ui->chicken_btn, &QPushButton::clicked, this, [this](){shop_search_chk = false; clicked_food_type = CHICKEN; send_delivery_func_order(SHOPLIST);});
    connect(ui->pizza_btn, &QPushButton::clicked, this, [this](){shop_search_chk = false; clicked_food_type = PIZZA; send_delivery_func_order(SHOPLIST);});
    connect(ui->kFood_btn, &QPushButton::clicked, this, [this](){shop_search_chk = false; clicked_food_type = KFOOD; send_delivery_func_order(SHOPLIST);});
    connect(ui->jFood_btn, &QPushButton::clicked, this, [this](){shop_search_chk = false; clicked_food_type = JFOOD; send_delivery_func_order(SHOPLIST);});
    connect(ui->cFood_btn, &QPushButton::clicked, this, [this](){shop_search_chk = false; clicked_food_type = CFOOD; send_delivery_func_order(SHOPLIST);});
    connect(ui->cafe_btn, &QPushButton::clicked, this, [this](){shop_search_chk = false; clicked_food_type = CAFE; send_delivery_func_order(SHOPLIST);});
    connect(ui->toshop_backBtn, &QPushButton::clicked, this, [this](){send_delivery_func_order(SHOPLIST);});

    connect(ui->shopList_tableView, &QTableView::doubleClicked, this, &MainWindow::shop_view_double_clicked);
    connect(ui->searchTableView, &QTableView::doubleClicked, this, &MainWindow::shop_view_double_clicked);
    connect(ui->menu_tableView, &QTableView::doubleClicked, this, &MainWindow::menu_view_double_clicked);
    connect(ui->menu_basket_tableView, &QTableView::doubleClicked, this, &MainWindow::basket_view_double_clicked);

    // [ex.02.1.2]
    // 연결된 socket에 read 할 데이터가 들어오면,
    // 이 객체의(MainWindow) slot_readSocket 실행하여 처리
    connect(m_socket, &QTcpSocket::readyRead,
            this,     &MainWindow::slot_readSocket);

    // [ex.02.1.3]
    // signal_newMessage 시그널이 발생하면 (socket read 가 아닌, MainWindow 시그널)
    // slot_displayMessage 실행하여 UI에 출력
    // connect(this, &MainWindow::signal_newMessage,
    //         this, &MainWindow::slot_displayMessage);

    // [ex.02.1.4]
    // 연결된 소켓과 연결이 해제되면,
    // 이 객체의(MainWindow) slot_discardSocket 슬롯 함수 실행하여 처리
    connect(m_socket, &QTcpSocket::disconnected,
            this,     &MainWindow::slot_discardSocket);

    // [ex.02.1.4]
    // 연결된 소켓에 문제가 발생하면,
    // 이 객체의(MainWindow) slot_displayError 슬롯 함수 실행하여 처리
    connect(m_socket, &QAbstractSocket::errorOccurred,
            this,     &MainWindow::slot_displayError);

}

// [ex.02.2]
MainWindow::~MainWindow()
{
    // socket 해제
    if(m_socket->isOpen())
        m_socket->close();
    delete ui;
    delete shoplist_model;
    delete menulist_model;
}

// [ex.02.3]
// 서버에서 연결이 끊어지면 동작
void MainWindow::slot_discardSocket()
{
    m_socket->deleteLater();
    m_socket=nullptr;

    ui->statusBar->showMessage("Disconnected!");
}

// [ex.02.4]
// 연결된 소켓에서 에러 발생하면 출력
void MainWindow::slot_displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, "QTCPClient", "The host was not found. Please check the host name and port settings.");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, "QTCPClient", "The connection was refused by the peer. Make sure QTCPServer is running, and check that the host name and port settings are correct.");
        break;
    default:
        QMessageBox::information(this, "QTCPClient", QString("The following error occurred: %1.").arg(m_socket->errorString()));
        break;
    }
}

// [ex.02.5]
// 첨부파일 또는 메시지 수신 처리
void MainWindow::slot_readSocket()
{
    while (m_socket->bytesAvailable())
    {
        // QByteArray 타입의 buffer를 만들고
        QByteArray buffer;

        // 서버에 연결된 socket을 stream으로 연결한다.
        QDataStream socketStream(m_socket);
        socketStream.setVersion(QDataStream::Qt_5_15);

        // stream으로 데이터를 읽어들이고, buffer로 넘기면
        socketStream.startTransaction();
        socketStream >> buffer;

        // stream startTransaction 실행 문제시 에러 표시 후 함수 종료
        if(!socketStream.commitTransaction())
        {
            QString message = QString("%1 :: Waiting for more data to come..").arg(m_socket->socketDescriptor());
            emit signal_newMessage(message);
            return;
        }

        // client 에서 보낸 payload(순수한 데이터, 전달 메시지)를
        // buffer에서 처음 128 byte 부분만 읽어들여서 header 에 담고 fileType을 찾는다.
        QString header = buffer.mid(0,128);
        QString fileType = header.split(",")[0].split(":")[1];
        QString sender = header.split(",")[1].split(":")[1];
        QString sender_num = header.split(",")[2].split(":")[1];
        QString receiver = header.split(",")[3].split(":")[1];
        QString receiver_num = header.split(",")[4].split(":")[1];

        // buffer의 128 byte 이후 부분 buffer에 다시 담음.
        buffer = buffer.mid(128);
        QString msg = buffer;
        // qDebug() << "MSG!!! : " <<msg;
        if (fileType == "signUpInfo")
        {
            if (msg == "signUp success") // 회원가입 성공
            {
                emit operate_info_signal("signUp success");
            }
            else if (msg == "signUp error") // 회원가입 에러
            {
                emit operate_info_signal("signUp error");
            }
            else if (msg == "signUp idDup") // 아이디 중복
            {
                emit operate_info_signal("signUp idDup");
            }
            else if (msg == "signUp !idDup") // 아이디 중복 아님
            {
                emit operate_info_signal("signUp !idDup");
            }
            else if (msg == "signUp phoneNumDup") // 휴대폰 번호 중복
            {
                emit operate_info_signal("signUp phoneNumDup");
            }
            else if (msg == "signUp !phoneNumDup") // 휴대폰 번호 중복 아님
            {
                emit operate_info_signal("signUp !phoneNumDup");
            }
        }
        else if (fileType == "loginInfo")
        {
            if (msg == "login success") // 로그인 성공
            {
                emit login_info_signal("login success");
                loginWidget->hide();
                present_clnt.clnt_num = sender_num.toInt();

                if (sender == "user") // 유저 로그인 성공
                {
                    present_clnt.type = USER;
                    this->window()->show();
                    ui->title_label->setText("저기요");
                    ui->mainStackedWidget->setCurrentWidget(ui->user_main_page);
                    ui->user_mainTabWidget->setCurrentWidget(ui->foodCategoryTab);
                    send_delivery_func_order(MENULIST);
                }
                else if (sender == "shop") // 가게 로그인 성공
                {
                    present_clnt.type = SHOP;
                    this->window()->show();
                    ui->title_label->setText("저기요 업주");
                    ui->mainStackedWidget->setCurrentWidget(ui->shop_main_page);
                    ui->shopTabWidget->setCurrentWidget(ui->shop_orderWait_tab);
                }
                else // 라이더 로그인 성공
                {
                    present_clnt.type = RIDER;
                    this->window()->show();
                    ui->title_label->setText("저기요 라이더");
                    ui->mainStackedWidget->setCurrentWidget(ui->rider_main_page);
                }
            }
            else if (msg == "login fail")
            {
                emit login_info_signal("login fail");
            }
        }
        else if (fileType == "shopImg")
        {
            shop_img_to_item(buffer);
        }
        else if (fileType == "shoplist")
        {
            create_shop_list_model(msg);
        }
        else if (fileType == "menuImg")
        {
            menu_img_to_item(buffer);
        }
        else if (fileType == "menulist")
        {
            create_menu_list_model(msg);
        }
    }
}

void MainWindow::get_login_user_id(QString id)
{
    present_clnt.clnt_id = id;
    qDebug() << "현재 로그인유저 아이디: " << present_clnt.clnt_id;
}

void MainWindow::basket_view_double_clicked(const QModelIndex &index)
{
    int clicked_row = index.row();
    basketlist_model->removeRow(clicked_row);
    ui->menu_basket_tableView->setModel(basketlist_model);
    ui->menu_basket_tableView->show();
}

void MainWindow::menu_view_double_clicked(const QModelIndex &index)
{
    QStandardItem *m_num, *s_num, *m_title, *m_price, *f_cnt;
    int clicked_row = index.row();
    int food_cnt;
    // 어떤 칸을 클릭해도 해당 열의 웹툰 일련번호가 리턴됨
    QString clicked_m_num = index.sibling(clicked_row, 0).data().toString();
    QString clicked_s_num = index.sibling(clicked_row, 1).data().toString();
    QString clicekd_m_title = index.sibling(clicked_row, 4).data().toString();
    QString clicekd_m_price = index.sibling(clicked_row, 5).data().toString();

    QWidget *widget = ui->menu_tableView->indexWidget(proxyModel->index(index.row(), 6));
    food_cnt = qobject_cast<QSpinBox*>(widget)->value(); // spinBox의 현재 값 가져오기

    int rowCount = basketlist_model->rowCount();
    for (int row = 0; row < rowCount; row++)
    {
        int mnum = basketlist_model->item(row, 0)->data(Qt::DisplayRole).toInt();
        int fcnt = basketlist_model->item(row, 5)->data(Qt::DisplayRole).toInt();
        if (mnum == clicked_m_num.toInt())
        {
            basketlist_model->item(row, 5)->setData(QString::number(fcnt + food_cnt), Qt::DisplayRole);
            return;
        }
    }

    m_num = new QStandardItem(clicked_m_num);
    s_num = new QStandardItem(clicked_s_num);
    m_title = new QStandardItem(clicekd_m_title);
    m_price = new QStandardItem(clicekd_m_price);
    f_cnt = new QStandardItem(QString::number(food_cnt));

    QStandardItem *menu_img_item = new QStandardItem();
    menu_img_item->setIcon(QIcon(menu_img_list[clicked_m_num.toInt()-1]));

    m_title->setTextAlignment(Qt::AlignCenter);
    m_price->setTextAlignment(Qt::AlignCenter);
    f_cnt->setTextAlignment(Qt::AlignCenter);

    QList<QStandardItem*> items;
    items << m_num
          << s_num
          << menu_img_item
          << m_title
          << m_price
          << f_cnt;

    basketlist_model->appendRow(items);

    ui->menu_basket_tableView->setModel(basketlist_model);
    ui->menu_basket_tableView->setIconSize(QSize(100, 100));
    ui->menu_basket_tableView->resizeColumnsToContents();
    ui->menu_basket_tableView->resizeRowsToContents();
    ui->menu_basket_tableView->hideColumn(0);
    ui->menu_basket_tableView->hideColumn(1);
    ui->menu_basket_tableView->verticalHeader()->setVisible(false);
    ui->menu_basket_tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->menu_basket_tableView->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);

    ui->menu_basket_tableView->show();
}

void MainWindow::shop_search()
{
    QString search_shop_str = ui->shopSearchText->text().trimmed();
    if (search_shop_str.isEmpty())
    {
        QMessageBox::critical(this, "오류", "검색어를 입력하세요.");
        return;
    }

    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(shoplist_model);
    proxyModel->setFilterRegularExpression(QRegularExpression(search_shop_str));
    proxyModel->setFilterKeyColumn(2);// 필터링할 열
    // 필터링된 결과를 View에 출력
    ui->searchTableView->setModel(proxyModel);
    ui->searchTableView->setIconSize(QSize(100, 100));
    ui->searchTableView->resizeColumnsToContents();
    ui->searchTableView->resizeRowsToContents();
    ui->searchTableView->hideColumn(0);
    ui->searchTableView->verticalHeader()->setVisible(false);
    ui->searchTableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->searchTableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->searchTableView->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    ui->searchTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->searchTableView->show();
    ui->mainStackedWidget->setCurrentWidget(ui->user_main_page);
    ui->user_mainTabWidget->setCurrentWidget(ui->shopSearchTab);
}

void MainWindow::shop_view_double_clicked(const QModelIndex &index)
{
    int clicked_row = index.row();
    // 어떤 칸을 클릭해도 해당 열의 웹툰 일련번호가 리턴됨
    clicked_shop_num = index.sibling(clicked_row, 0).data().toString();
    clicked_shop_title = index.sibling(clicked_row, 2).data().toString();

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(menulist_model);

    // QRegularExpression을 사용하여 문자열의 시작(^)과 끝($)을 고정
    QRegularExpression exactMatch("^" + QRegularExpression::escape(clicked_shop_num) + "$");
    proxyModel->setFilterRegularExpression(exactMatch);
    proxyModel->setFilterKeyColumn(1); // 필터링할 열



    // 필터링된 결과를 View에 출력
    ui->menu_tableView->setModel(proxyModel);
    ui->menu_tableView->setIconSize(QSize(100, 100));
    ui->menu_tableView->resizeColumnsToContents();
    ui->menu_tableView->resizeRowsToContents();
    ui->menu_tableView->hideColumn(0);
    ui->menu_tableView->hideColumn(1);
    ui->menu_tableView->verticalHeader()->setVisible(false);
    ui->menu_tableView->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    ui->menu_tableView->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);

    int row_cnt = ui->menu_tableView->model()->rowCount();
    // 스핀박스 테이블 뷰에 집어넣는 방법!!

    for (int i = 0; i < row_cnt; i++)
    {
        QSpinBox *menu_spin_box = new QSpinBox();
        menu_spin_box->setRange(1, 100);
        menu_spin_box->setValue(1);
        ui->menu_tableView->setIndexWidget(proxyModel->index(i,6), menu_spin_box);
    }

    ui->menu_tableView->show();
    ui->menu_shopTitle->setText(clicked_shop_title);
    ui->mainStackedWidget->setCurrentWidget(ui->menuList_page);

    basketlist_model = new QStandardItemModel();
    basketlist_model->setColumnCount(6);
    basketlist_model->setHorizontalHeaderLabels(QStringList()<< "메뉴번호" << "가게번호" << "이미지"<< "이름" << "가격" << "개수");

}

void MainWindow::menu_img_to_item(QByteArray &img_buf)
{
    QPixmap thumbnailPixmap;
    thumbnailPixmap.loadFromData(img_buf);
    QPixmap resizedPixmap = thumbnailPixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    menu_img_list.append(resizedPixmap);
}

void MainWindow::create_menu_list_model(QString &menulist)
{
    QStringList str_list = menulist.split("\n");
    QStandardItem *m_num, *s_num, *s_mnum, *m_title, *m_price;
    int index = 0;
    menulist_model = new QStandardItemModel();
    menulist_model->setColumnCount(7);
    menulist_model->setHorizontalHeaderLabels(QStringList()<<"메뉴번호"<< "가게번호" << "번호" << "이미지"<< "이름" << "가격" << "개수");

    for (const QString &row: str_list)
    {
        QStringList columns = row.split("/");
        m_num = new QStandardItem(columns[0].trimmed());
        s_num = new QStandardItem(columns[1].trimmed());
        s_mnum = new QStandardItem(columns[2].trimmed());
        m_title = new QStandardItem(columns[3].trimmed());
        m_price = new QStandardItem(columns[4].trimmed());

        QStandardItem *menu_img_item = new QStandardItem();
        menu_img_item->setIcon(QIcon(menu_img_list[index++]));

        s_mnum->setTextAlignment(Qt::AlignCenter);
        m_title->setTextAlignment(Qt::AlignCenter);
        m_price->setTextAlignment(Qt::AlignCenter);

        QList<QStandardItem*> items;
        items << m_num
              << s_num
              << s_mnum
              << menu_img_item
              << m_title
              << m_price;

        menulist_model->appendRow(items);
    }
}

void MainWindow::shop_img_to_item(QByteArray &img_buf)
{
    QPixmap thumbnailPixmap;
    thumbnailPixmap.loadFromData(img_buf);
    QPixmap resizedPixmap = thumbnailPixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    shop_img_list.append(resizedPixmap);
}

void MainWindow::create_shop_list_model(QString &shoplist)
{
    QStringList str_list = shoplist.split("\n");
    QStandardItem *s_num, *s_title, *s_type, *s_state;
    int index = 0;
    shoplist_model = new QStandardItemModel();
    shoplist_model->setColumnCount(5);
    shoplist_model->setHorizontalHeaderLabels(QStringList()<<"가게번호"<< "이미지" << "가게이름" << "카테고리"<< "영업상태");

    for (const QString &row: str_list)
    {
        QStringList columns = row.split("/");
        s_num = new QStandardItem(columns[0].trimmed());
        s_title = new QStandardItem(columns[1].trimmed());
        s_type = new QStandardItem(columns[2].trimmed());
        s_state = new QStandardItem(columns[3].trimmed());

        QStandardItem *shop_img_item = new QStandardItem();
        shop_img_item->setIcon(QIcon(shop_img_list[index++]));

        s_title->setTextAlignment(Qt::AlignCenter);
        s_type->setTextAlignment(Qt::AlignCenter);
        s_state->setTextAlignment(Qt::AlignCenter);

        QList<QStandardItem*> items;
        items << s_num
              << shop_img_item
              << s_title
              << s_type
              << s_state;
        shoplist_model->appendRow(items);

    }
    shop_img_list.clear();// 가게 이미지 리스트 초기화
    if (shop_search_chk)
    {
        shop_search();
    }
    else
    {
        to_shop_list_view(clicked_food_type);
    }
}

void MainWindow::to_shop_list_view(int foodType)
{
    // QSortFilterProxyModel을 생성하고 원본 모델과 사귐
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(shoplist_model);
    //음식 카테고리 항문으로 필터링
    switch (foodType)
    {
    case CHICKEN:
        proxyModel->setFilterRegularExpression(QRegularExpression("치킨"));
        break;
    case PIZZA:
        proxyModel->setFilterRegularExpression(QRegularExpression("피자"));
        break;
    case KFOOD:
        proxyModel->setFilterRegularExpression(QRegularExpression("한식"));
        break;
    case JFOOD:
        proxyModel->setFilterRegularExpression(QRegularExpression("일식"));
        break;
    case CFOOD:
        proxyModel->setFilterRegularExpression(QRegularExpression("중국집"));
        break;
    case CAFE:
        proxyModel->setFilterRegularExpression(QRegularExpression("카페"));
        break;
    default:
        break;
    }
    proxyModel->setFilterKeyColumn(3);// 필터링할 열
    // 필터링된 결과를 View에 출력
    ui->shopList_tableView->setModel(proxyModel);
    ui->shopList_tableView->setIconSize(QSize(100, 100));
    ui->shopList_tableView->resizeColumnsToContents();
    ui->shopList_tableView->resizeRowsToContents();
    ui->shopList_tableView->hideColumn(0);
    ui->shopList_tableView->verticalHeader()->setVisible(false);
    ui->shopList_tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->shopList_tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->shopList_tableView->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    ui->shopList_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->shopList_tableView->show();
    ui->mainStackedWidget->setCurrentWidget(ui->shopList_page);
}


void MainWindow::send_delivery_func_order(int act_type, QString msg, int sender, int senderNum, int receiver, int receiverNum)
{
    if(m_socket)
    {
        if(m_socket->isOpen())
        {
            // stream으로 보내는데
            QDataStream socketStream(m_socket);
            socketStream.setVersion(QDataStream::Qt_5_15);

            // 헤더 부분에 fileType을 message로 설정한다.
            QByteArray header;

            switch (act_type)
            {
            case LOGOUT:
                header.prepend(QString("fileType:logout,sender:%1,senderNum:%2,receiver:%3,recieverNum:%4;")
                                   .arg(client_type_to_string(sender), QString::number(senderNum), client_type_to_string(receiver), QString::number(receiverNum)).toUtf8());
                break;
            case SHOPLIST:
                header.prepend(QString("fileType:shoplist,sender:%1,senderNum:%2,receiver:%3,recieverNum:%4;")
                                   .arg(client_type_to_string(sender), QString::number(senderNum), client_type_to_string(receiver), QString::number(receiverNum)).toUtf8());
                break;
            case MENULIST:
                header.prepend(QString("fileType:menulist,sender:%1,senderNum:%2,receiver:%3,recieverNum:%4;")
                                   .arg(client_type_to_string(sender), QString::number(senderNum), client_type_to_string(receiver), QString::number(receiverNum)).toUtf8());
                break;
            default:
                break;
            }
            header.resize(128);
            // message 인코딩 설정하고, QByteArray에 할당하고
            QByteArray byteArray = msg.toUtf8();
            // header 정보를 앞에 넣어준다.
            byteArray.prepend(header);
            // stream으로 byteArray 정보 전송
            socketStream << byteArray;

        }
        else
            QMessageBox::critical(this,"QTCPClient","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPClient","Not connected");
}

//============================== 회원 정보 메시지 서버에 전송 함수  ===================================
void MainWindow::send_login_func_order(int act_type, int client_type, QString id, QString pw, QString phone_num)
{
    if(m_socket)
    {
        if(m_socket->isOpen())
        {
            // ui에서 입력할 message를 가져와
            QString msg = id + "," + pw + "," + phone_num;

            // stream으로 보내는데
            QDataStream socketStream(m_socket);
            socketStream.setVersion(QDataStream::Qt_5_15);

            // 헤더 부분에 fileType을 message로 설정한다.
            QByteArray header;

            switch (act_type) {
            case LOGIN:
                header.prepend(QString("fileType:login,sender:%1,senderNum:%2,receiver:null,recieverNum:null;").arg(client_type_to_string(client_type), id).toUtf8());
                break;
            case SIGNUP:
                header.prepend(QString("fileType:signUp,sender:%1,senderNum:%2,receiver:null,recieverNum:null;").arg(client_type_to_string(client_type), id).toUtf8());
                break;
            case IDDUPCHK:
                header.prepend(QString("fileType:idDupChk,sender:%1,senderNum:%2,receiver:null,recieverNum:null;").arg(client_type_to_string(client_type), id).toUtf8());
                break;
            case PNUMDUPCHK:
                header.prepend(QString("fileType:pNumDupChk,sender:%1,senderNum:%2,receiver:null,recieverNum:null;").arg(client_type_to_string(client_type), id).toUtf8());
                break;
            default:
                break;
            }
            header.resize(128);
            // message 인코딩 설정하고, QByteArray에 할당하고
            QByteArray byteArray = msg.toUtf8();
            // header 정보를 앞에 넣어준다.
            byteArray.prepend(header);

            // stream으로 byteArray 정보 전송
            socketStream << byteArray;
        }
        else
            QMessageBox::critical(this,"QTCPClient","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPClient","Not connected");
}

QString MainWindow::client_type_to_string(int client_type) // 클라이언트 타입을 문자열로 바꿔주는 함수
{
    QString client_str;
    switch (client_type) {
    case USER:
        client_str = "user";
        break;
    case SHOP:
        client_str = "shop";
        break;
    case RIDER:
        client_str = "rider";
        break;
    default:
        break;
    }
    return client_str;
}

void MainWindow::on_logout_btn_clicked()
{
    send_delivery_func_order(LOGOUT, "", present_clnt.type, present_clnt.clnt_num);
    QMessageBox::information(this, "알림","로그아웃 하였습니다.");
    this->window()->hide();
    loginWidget->show();
}
//============================================================================================================
// void MainWindow::epi_view_double_clicked(const QModelIndex &index)
// {
//     int return_column = 0; // 웹툰 에피소드 일련번호 컬럼 인덱스번호
//     int clicked_row = index.row();
//     // 어떤 칸을 클릭해도 해당 열의 웹툰 에피소드 일련번호가 리턴됨
//     QString data = index.sibling(clicked_row, return_column).data().toString();
//     present_toon_id = data;
//     send_toon_info(TOONIMAGE, data);
// }

// void MainWindow::toon_img_show(QByteArray &img_buf)
// {
//     ui->stackedWidget->setCurrentWidget(ui->webtoon_page);
//     QPixmap image;
//     image.loadFromData(img_buf);
//     QLabel *imageLabel = new QLabel();
//     imgLabel_list.append(imageLabel);
//     imageLabel->setPixmap(image);
//     ui->toon_scrollArea_contents->layout()->addWidget(imageLabel);
// }

// void MainWindow::toon_search()
// {
//     // QSortFilterProxyModel을 생성하고 원본 모델과 연결
//     QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
//     proxyModel->setSourceModel(toonInfo_model);

//     if (ui->searchComboBox->currentText() == "제목")
//     {
//         //0번째 열에 위에서 받은 data가 포함된 항목만 필터링
//         proxyModel->setFilterRegularExpression(QRegularExpression(ui->toonSearchText->text()));
//         proxyModel->setFilterKeyColumn(2);// 필터링할 열
//     }
//     else
//     {
//         proxyModel->setFilterRegularExpression(QRegularExpression(ui->toonSearchText->text()));
//         proxyModel->setFilterKeyColumn(3);// 필터링할 열
//     }

//     // 필터링된 결과를 View에 출력
//     ui->searchTableView->setModel(proxyModel);
//     ui->searchTableView->setIconSize(QSize(100, 100));
//     ui->searchTableView->resizeColumnsToContents();
//     ui->searchTableView->resizeRowsToContents();
//     ui->searchTableView->hideColumn(0);
//     ui->searchTableView->show();
// }


// void MainWindow::create_day_view()
// {
//     QStringList day_str_list;
//     QList<QTableView*> day_view_list;

//     day_str_list <<"월"<< "화"<< "수"<< "목"<< "금"<< "토"<< "일";
//     day_view_list.append(ui->tableView_mon);
//     day_view_list.append(ui->tableView_tue);
//     day_view_list.append(ui->tableView_wed);
//     day_view_list.append(ui->tableView_thu);
//     day_view_list.append(ui->tableView_fri);
//     day_view_list.append(ui->tableView_sat);
//     day_view_list.append(ui->tableView_sun);

//     for (int i = 0; i < day_view_list.size(); i++)
//     {

//         // QSortFilterProxyModel을 생성하고 원본 모델과 연결
//         QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
//         proxyModel->setSourceModel(toonInfo_model);
//         //0번째 열에 위에서 받은 data가 포함된 항목만 필터링
//         proxyModel->setFilterRegularExpression(QRegularExpression(day_str_list[i]));
//         proxyModel->setFilterKeyColumn(4);// 필터링할 열
//         // 필터링된 결과를 View에 출력
//         day_view_list[i]->setModel(proxyModel);
//         day_view_list[i]->setIconSize(QSize(100, 100));
//         day_view_list[i]->resizeColumnsToContents();
//         day_view_list[i]->resizeRowsToContents();
//         day_view_list[i]->hideColumn(0);
//         day_view_list[i]->show();
//     }
// }


// void MainWindow::view_double_clicked(const QModelIndex &index)
// {
//     int return_column = 0; // 웹툰 일련번호 컬럼 인덱스번호
//     int clicked_row = index.row();
//     // 어떤 칸을 클릭해도 해당 열의 웹툰 일련번호가 리턴됨
//     toonInfo_data = index.sibling(clicked_row, return_column).data().toString();
//     send_toon_info(TOONLIST, toonInfo_data); // 툰 리스트 모델 생성위해 서버에 메시지 전송
// }

// void MainWindow::create_toonList_model(QString &toonlist)
// {
//     QStringList str_list = toonlist.split("\n");
//     QStandardItem *epi_id, *t_id, *t_title, *epi_title, *t_author, *t_day, *epi_num, *view_num, *like_num;

//     toonList_model = new QStandardItemModel();
//     toonList_model->setColumnCount(9);
//     toonList_model->setHorizontalHeaderLabels(QStringList()<<"일련번호"<<"종류번호"<<"웹툰제목"<<"회차제목"<<"작가"<<"회차"<<"요일"<<"조회수"<<"좋아요수");

//     for (const QString &row: str_list)
//     {
//         QStringList columns = row.split("/");
//         if (columns.size() == 9)
//         {
//             epi_id = new QStandardItem(columns[0].trimmed());
//             t_id = new QStandardItem(columns[1].trimmed());
//             t_title = new QStandardItem(columns[2].trimmed());
//             epi_title = new QStandardItem(columns[3].trimmed());
//             t_author = new QStandardItem(columns[4].trimmed());
//             t_day = new QStandardItem(columns[5].trimmed());
//             epi_num = new QStandardItem(columns[6].trimmed());
//             view_num = new QStandardItem(columns[7].trimmed());
//             like_num = new QStandardItem(columns[8].trimmed());

//             t_title->setTextAlignment(Qt::AlignCenter);
//             epi_title->setTextAlignment(Qt::AlignCenter);
//             t_author->setTextAlignment(Qt::AlignCenter);
//             t_day->setTextAlignment(Qt::AlignCenter);
//             epi_num->setTextAlignment(Qt::AlignCenter);
//             view_num->setTextAlignment(Qt::AlignCenter);
//             like_num->setTextAlignment(Qt::AlignCenter);

//             QList<QStandardItem*> items;
//             items << epi_id
//                   << t_id
//                   << t_title
//                   << epi_title
//                   << t_author
//                   << epi_num
//                   << t_day
//                   << view_num
//                   << like_num;

//             toonList_model->appendRow(items);
//         }
//     }
//     ui->epiList_tableView->setModel(toonList_model);
//     ui->epiList_tableView->resizeColumnsToContents();
//     ui->epiList_tableView->hideColumn(0);
//     ui->epiList_tableView->hideColumn(1);
//     ui->epiList_tableView->show();
//     ui->stackedWidget->setCurrentWidget(ui->toonList_page);
// }



// void MainWindow::create_toonInfo_model(QString &toonlist)
// {
//     QStringList str_list = toonlist.split("\n");
//     QStandardItem *num, *title, *author, *day;
//     int index = 0;

//     toonInfo_model = new QStandardItemModel();
//     toonInfo_model->setColumnCount(5);
//     toonInfo_model->setHorizontalHeaderLabels(QStringList()<<"번호"<< "썸네일" << "제목" << "작가"<< "요일");

//     for (const QString &row: str_list)
//     {
//         QStringList columns = row.split("/");
//         if (columns.size() == 4)
//         {
//             num = new QStandardItem(columns[0].trimmed());
//             title = new QStandardItem(columns[1].trimmed());
//             author = new QStandardItem(columns[2].trimmed());
//             day = new QStandardItem(columns[3].trimmed());

//             QStandardItem *thumbnail_item = new QStandardItem();
//             thumbnail_item->setIcon(QIcon(thumbnail_list[index++]));

//             title->setTextAlignment(Qt::AlignCenter);
//             author->setTextAlignment(Qt::AlignCenter);
//             day->setTextAlignment(Qt::AlignCenter);

//             QList<QStandardItem*> items;
//             items << num
//                   << thumbnail_item
//                   << title
//                   << author
//                   << day;
//             toonInfo_model->appendRow(items);
//         }
//     }

//     ui->e_tableView->setModel(toonInfo_model);
//     ui->e_tableView->setIconSize(QSize(100, 100));
//     ui->e_tableView->resizeColumnsToContents();
//     ui->e_tableView->resizeRowsToContents();
//     ui->e_tableView->hideColumn(0);
//     ui->e_tableView->show();
//     create_day_view();
// }



// [ex.02.5]
// 메시지를 보냄
// void MainWindow::on_pushButton_sendMessage_clicked()
// {
//     if(m_socket)
//     {
//         if(m_socket->isOpen())
//         {
//             // ui에서 입력할 message를 가져와
//             QString str = ui->lineEdit_message->text();

//             // stream으로 보내는데
//             QDataStream socketStream(m_socket);
//             socketStream.setVersion(QDataStream::Qt_5_15);

//             // 헤더 부분에 fileType을 message로 설정한다.
//             QByteArray header;
//             header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
//             header.resize(128);

//             // message 인코딩 설정하고, QByteArray에 할당하고
//             QByteArray byteArray = str.toUtf8();
//             // header 정보를 앞에 넣어준다.
//             byteArray.prepend(header);

//             // stream으로 byteArray 정보 전송
//             socketStream << byteArray;

//             // 메시지 입력창 리셋
//             ui->lineEdit_message->clear();
//         }
//         else
//             QMessageBox::critical(this,"QTCPClient","Socket doesn't seem to be opened");
//     }
//     else
//         QMessageBox::critical(this,"QTCPClient","Not connected");
// }

// void MainWindow::on_pushButton_sendAttachment_clicked()
// {
//     if(m_socket)
//     {
//         if(m_socket->isOpen())
//         {
//             // 파일 경로 가져오고, 경로 문제시 경고 출력
//             QString filePath = QFileDialog::getOpenFileName(this, ("Select an attachment"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), ("File (*.json *.txt *.png *.jpg *.jpeg)"));
//             if(filePath.isEmpty())
//             {
//                 QMessageBox::critical(this,"QTCPClient","You haven't selected any attachment!");
//                 return;
//             }

//             // 전송 할 file 객체를 경로 지정해서 열고
//             QFile m_file(filePath);
//             if(m_file.open(QIODevice::ReadOnly))
//             {
//                 // file 이름을 가져오고
//                 QFileInfo fileInfo(m_file.fileName());
//                 QString fileName(fileInfo.fileName());

//                 // stream으로 보내는데
//                 QDataStream socketStream(m_socket);
//                 socketStream.setVersion(QDataStream::Qt_5_15);

//                 // 헤더 부분에 fileType을 attachment로 설정한다.
//                 QByteArray header;
//                 header.prepend(QString("fileType:attachment,fileName:%1,fileSize:%2;").arg(fileName).arg(m_file.size()).toUtf8());
//                 header.resize(128);

//                 // QByteArray에 file을 byte로 할당하고
//                 QByteArray byteArray = m_file.readAll();
//                 // header 정보를 앞에 넣어준다.
//                 byteArray.prepend(header);

//                 // stream으로 byteArray 정보 전송
//                 socketStream << byteArray;
//             }
//             else
//                 QMessageBox::critical(this,"QTCPClient","Attachment is not readable!");
//         }
//         else
//             QMessageBox::critical(this,"QTCPClient","Socket doesn't seem to be opened");
//     }
//     else
//         QMessageBox::critical(this,"QTCPClient","Not connected");
// }

// void MainWindow::on_toList_backBtn_clicked()
// {
//     ui->stackedWidget->setCurrentWidget(ui->main_page);
// }

// void MainWindow::on_backList_btn_clicked()
// {
//     send_toon_info(TOONLIST, toonInfo_data);
//     // 동적으로 만든 imglabel 해제
//     for (QLabel *imgLabel : imgLabel_list)
//     {
//         delete imgLabel;
//     }
//     imgLabel_list.clear(); // 리스트 요소 클리어
// }





void MainWindow::on_pushButton_clicked()
{
    ui->mainStackedWidget->setCurrentWidget(ui->user_main_page);
}

