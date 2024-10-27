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
    send_delivery_func_order(CATEGORY);
    connect(loginWidget, &Login::user_info_signal, this, &MainWindow::send_login_func_order); // 회원가입 정보 전송 connect
    connect(loginWidget, &Login::login_success_signal, this, &MainWindow::get_login_user_id);

    connect(this, &MainWindow::operate_info_signal, loginWidget, &Login::signUp_operate);
    connect(this, &MainWindow::login_info_signal, loginWidget, &Login::login_operate);

    connect(ui->shopSearchButton, &QPushButton::clicked, this, [this](){shop_search_chk = true; send_delivery_func_order(SHOPLIST);});
    connect(ui->chicken_btn, &QToolButton::clicked, this, [this](){shop_search_chk = false; clicked_food_type = CHICKEN; send_delivery_func_order(SHOPLIST);});
    connect(ui->pizza_btn, &QToolButton::clicked, this, [this](){shop_search_chk = false; clicked_food_type = PIZZA; send_delivery_func_order(SHOPLIST);});
    connect(ui->kFood_btn, &QToolButton::clicked, this, [this](){shop_search_chk = false; clicked_food_type = KFOOD; send_delivery_func_order(SHOPLIST);});
    connect(ui->jFood_btn, &QToolButton::clicked, this, [this](){shop_search_chk = false; clicked_food_type = JFOOD; send_delivery_func_order(SHOPLIST);});
    connect(ui->cFood_btn, &QToolButton::clicked, this, [this](){shop_search_chk = false; clicked_food_type = CFOOD; send_delivery_func_order(SHOPLIST);});
    connect(ui->cafe_btn, &QToolButton::clicked, this, [this](){shop_search_chk = false; clicked_food_type = CAFE; send_delivery_func_order(SHOPLIST);});
    connect(ui->toshop_backBtn, &QPushButton::clicked, this, [this]()
    {
        basketlist_model->clear();
        if (bookmarkview_chk)
        {
            send_delivery_func_order(BOOKMARKLIST, "", USER, present_clnt.clnt_num);
            ui->mainStackedWidget->setCurrentWidget(ui->user_main_page);
            ui->user_mainTabWidget->setCurrentWidget(ui->shopBookmarkTab);
            bookmarkview_chk = false;
        }
        else
        {
            send_delivery_func_order(SHOPLIST);
        }
    });
    connect(ui->to_order_btn, &QPushButton::clicked, this, &MainWindow::to_order_page);
    connect(ui->pay_btn, &QPushButton::clicked, this, &MainWindow::user_final_order);

    connect(ui->shopList_tableView, &QTableView::doubleClicked, this, &MainWindow::shop_view_double_clicked);
    connect(ui->searchTableView, &QTableView::doubleClicked, this, &MainWindow::shop_view_double_clicked);
    connect(ui->bookmark_tableView, &QTableView::doubleClicked, this, [this](const QModelIndex &index){bookmarkview_chk = true; shop_view_double_clicked(index);});
    connect(ui->menu_tableView, &QTableView::doubleClicked, this, &MainWindow::menu_view_double_clicked);
    connect(ui->menu_basket_tableView, &QTableView::doubleClicked, this, &MainWindow::basket_view_double_clicked);
    connect(ui->order_accept_btn, &QPushButton::clicked, this, [this](){order_accept_or_deny(true);});
    connect(ui->order_deny_btn, &QPushButton::clicked, this, [this](){order_accept_or_deny(false);});
    connect(ui->deliWait_tableView, &QTableView::doubleClicked, this, &MainWindow::delivery_tableView_double_clicked);
    connect(ui->del_complete_btn, &QPushButton::clicked, this, &MainWindow::delivery_complete);
    connect(ui->bookmark_btn, &QPushButton::clicked, this,[this](){send_delivery_func_order(BOOKMARK, clicked_shop_num+"/click", USER, present_clnt.clnt_num);});
    connect(ui->user_mainTabWidget, &QTabWidget::currentChanged, this, &MainWindow::change_bookmark_tab);

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
    delete basketlist_model;
    delete orderWaitList_model;
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
        QString sender_str = header.split(",")[1].split(":")[1];
        QString sender_num_str = header.split(",")[2].split(":")[1];
        QString receiver_str = header.split(",")[3].split(":")[1];
        QString receiver_num_str = header.split(";")[0].split(",")[4].split(":")[1];
        int sender = sender_str.toInt();
        int sender_num = sender_num_str.toInt();
        int receiver = receiver_str.toInt();
        int receiver_num = receiver_num_str.toInt();

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
                present_clnt.clnt_num = sender_num;

                if (sender == USER) // 유저 로그인 성공
                {
                    send_delivery_func_order(MENULIST);
                    send_delivery_func_order(UORDERLIST, present_clnt.clnt_id, USER, present_clnt.clnt_num);
                    send_delivery_func_order(UORDER_HISTORYLIST, present_clnt.clnt_id, USER, present_clnt.clnt_num);
                    present_clnt.type = USER;
                    this->window()->show();
                    ui->title_label->setText("거기요 고객");
                    ui->mainStackedWidget->setCurrentWidget(ui->user_main_page);
                    ui->user_mainTabWidget->setCurrentWidget(ui->foodCategoryTab);
                    create_food_category();
                }
                else if (sender == SHOP) // 가게 로그인 성공
                {
                    send_delivery_func_order(SORDERLIST_WAITING, "", SHOP, present_clnt.clnt_num);
                    send_delivery_func_order(SORDERLIST_ENTIRE, "", SHOP, present_clnt.clnt_num);
                    send_delivery_func_order(SHOPTITLE, "", SHOP, present_clnt.clnt_num);
                    present_clnt.type = SHOP;
                    this->window()->show();
                    ui->title_label->setText("거기요 업주");
                    ui->mainStackedWidget->setCurrentWidget(ui->shop_main_page);
                    ui->shopTabWidget->setCurrentWidget(ui->shop_orderWait_tab);
                }
                else // 라이더 로그인 성공
                {
                    send_delivery_func_order(DELIVERYLIST, present_clnt.clnt_id, RIDER, present_clnt.clnt_num);
                    send_delivery_func_order(DELIACCEPTLIST, "", RIDER, present_clnt.clnt_num);
                    send_delivery_func_order(DELIHISTORYLIST, "",  RIDER, present_clnt.clnt_num);
                    present_clnt.type = RIDER;
                    this->window()->show();
                    ui->title_label->setText("거기요 라이더");
                    ui->mainStackedWidget->setCurrentWidget(ui->rider_main_page);
                    ui->delTabWidget->setCurrentWidget(ui->delivery_sate_tab);
                }
            }
            else if (msg == "login fail")
            {
                emit login_info_signal("login fail");
            }
        }
        else if (fileType == "shopLogout")
        {
            shop_renewal_chk = true;
            send_delivery_func_order(SHOPLIST);
        }
        else if (fileType == "shoptitle")
        {
            ui->shop_title_text_label->setText(msg);
        }
        else if (fileType == "categoryImg")
        {
            category_img_to_item(buffer);
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
        else if (fileType == "userorder")
        {
            send_delivery_func_order(SORDERLIST_WAITING, "", SHOP, present_clnt.clnt_num);
            QMessageBox::information(this, "정보", "음식 주문이 들어왔습니다");
        }
        else if (fileType == "uOrderList")
        {
            show_user_state_tableView(msg);
        }
        else if (fileType == "sOrderListW")
        {
            show_order_wait_tableView(msg);
        }
        else if (fileType == "sOrderListE")
        {
            show_order_entire_tableView(msg);
        }
        else if (fileType == "orderAccept")
        {
            send_delivery_func_order(UORDERLIST, present_clnt.clnt_id, USER, present_clnt.clnt_num);
            QMessageBox::information(this, "정보", "주문이 접수되었습니다");
        }
        else if (fileType == "orderDeny")
        {
            user_orderlist_model->clear();
            send_delivery_func_order(UORDERLIST, present_clnt.clnt_id, USER, present_clnt.clnt_num);
            send_delivery_func_order(UORDER_HISTORYLIST, present_clnt.clnt_id, USER, present_clnt.clnt_num);
            QMessageBox::information(this, "정보", "주문이 거절되었습니다");
        }
        else if (fileType == "putDelivery")
        {
            send_delivery_func_order(DELIVERYLIST, present_clnt.clnt_id, RIDER, present_clnt.clnt_num);
        }
        else if (fileType == "deliveryList")
        {
            show_delivery_wait_tableView(msg);
        }
        else if (fileType == "deliAccept")
        {
            qDebug() << receiver;
            switch (receiver)
            {
            case USER:
                send_delivery_func_order(UORDERLIST, present_clnt.clnt_id, USER, present_clnt.clnt_num);
                QMessageBox::information(this, "정보", "라이더가 배달을 시작했습니다");
                break;
            case SHOP:
                send_delivery_func_order(SORDERLIST_ENTIRE, "", SHOP, present_clnt.clnt_num);
                break;
            case RIDER:
                deliveryWaitList_model->clear();
                send_delivery_func_order(DELIVERYLIST, present_clnt.clnt_id, RIDER, present_clnt.clnt_num);
                break;
            default:
                break;
            }
        }
        else if (fileType == "deliAcceptList")
        {
            show_delivery_accept_tableView(msg);
        }
        else if (fileType == "deliComplete")
        {
            switch (receiver)
            {
            case USER:
                user_orderlist_model->clear();
                send_delivery_func_order(UORDERLIST, present_clnt.clnt_id, USER, present_clnt.clnt_num);
                send_delivery_func_order(UORDER_HISTORYLIST, present_clnt.clnt_id, USER, present_clnt.clnt_num);
                QMessageBox::information(this, "정보", "배달이 완료되었습니다");
                break;
            case SHOP:
                send_delivery_func_order(SORDERLIST_ENTIRE, "", SHOP, present_clnt.clnt_num);
                break;
            default:
                break;
            }
        }
        else if (fileType == "deliHistoryList")
        {
            show_delivery_complete_tableView(msg);
        }
        else if (fileType == "orderHistoryList")
        {
            show_user_history_tableView(msg);
        }
        else if (fileType == "bookmark")
        {
            bookmark_operate(msg);
        }
        else if (fileType == "bookmarkList")
        {
            create_bookmark_list_model(msg);
        }
    }
}

//============================================== 라이더 클라이언트 함수 =================================================
void MainWindow::rider_view_design_setting(QTableView *view)
{
    for (int i = 0; i < 4; i++)
    {
        view->hideColumn(i);
    }
    view->resizeColumnsToContents();
    view->resizeRowsToContents();
    view->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);
    view->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Stretch);
    view->horizontalHeader()->setSectionResizeMode(8, QHeaderView::Stretch);
    view->horizontalHeader()->setSectionResizeMode(9, QHeaderView::Stretch);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->show();
}

void MainWindow::show_delivery_complete_tableView(QString orderlist)
{
    if (deliveryCompleteList_model)
    {
        delete deliveryCompleteList_model;
        deliveryCompleteList_model = nullptr;
    }
    deliveryCompleteList_model = new QStandardItemModel();
    deliveryCompleteList_model->setColumnCount(11);
    deliveryCompleteList_model->setHorizontalHeaderLabels(QStringList() <<"주문번호"<<"주문자번호"<<"가게번호"<<"라이더번호"<<"주문자ID"
                                                                      <<"가게이름"<<"주문내용"<<"가격"<<"배달주소"<<"주문요청사항"<<"주문상태");

    create_client_order_list_model(deliveryCompleteList_model, orderlist);
    ui->rider_history_tableView->setModel(deliveryCompleteList_model);
    rider_view_design_setting(ui->rider_history_tableView);
}

void MainWindow::delivery_complete()
{
    QMessageBox::StandardButton reply;
    if (!deliveryAcceptList_model)
    {
        QMessageBox::critical(this, "오류", "완료 할 배달을 선택하세요");
        return;
    }
    QModelIndex currentIndex = ui->deliAccept_tableView->selectionModel()->currentIndex();

    if (!currentIndex.isValid())
    {
        QMessageBox::critical(this, "오류", "완료 할 배달을 선택하세요");
        return;
    }
    QString o_num = currentIndex.sibling(currentIndex.row(), 0).data().toString();
    QString u_num = currentIndex.sibling(currentIndex.row(), 1).data().toString();
    QString s_num = currentIndex.sibling(currentIndex.row(), 2).data().toString();

    reply = QMessageBox::question(this, "질문", "해당 배달을 완료하셨나요?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No)
        return;
    send_delivery_func_order(DELICOMPLETE, o_num+"/"+u_num+"/"+s_num, RIDER, present_clnt.clnt_num);

    // 모델 초기화
    deliveryAcceptList_model->clear();
    send_delivery_func_order(DELIACCEPTLIST, "", RIDER, present_clnt.clnt_num);
    send_delivery_func_order(DELIHISTORYLIST, "",  RIDER, present_clnt.clnt_num);
}

void MainWindow::show_delivery_accept_tableView(QString orderlist)
{
    if (deliveryAcceptList_model)
    {
        delete deliveryAcceptList_model;
        deliveryAcceptList_model = nullptr;
    }
    deliveryAcceptList_model = new QStandardItemModel();
    deliveryAcceptList_model->setColumnCount(11);
    deliveryAcceptList_model->setHorizontalHeaderLabels(QStringList() <<"주문번호"<<"주문자번호"<<"가게번호"<<"라이더번호"<<"주문자ID"
                                                                    <<"가게이름"<<"주문내용"<<"가격"<<"배달주소"<<"주문요청사항"<<"주문상태");

    create_client_order_list_model(deliveryAcceptList_model, orderlist);
    ui->deliAccept_tableView->setModel(deliveryAcceptList_model);
    rider_view_design_setting(ui->deliAccept_tableView);
}

void MainWindow::delivery_tableView_double_clicked(const QModelIndex &index)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "질문", "해당 주문을 배달하시겠습니까?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No)
        return;

    int clicked_row = index.row();
    QString o_num = index.sibling(clicked_row, 0).data().toString();
    QString u_num = index.sibling(clicked_row, 1).data().toString();
    QString s_num = index.sibling(clicked_row, 2).data().toString();

    send_delivery_func_order(DELIACCEPT, o_num+"/"+u_num+"/"+s_num, RIDER, present_clnt.clnt_num);
    send_delivery_func_order(DELIACCEPTLIST, "", RIDER, present_clnt.clnt_num);
}

void MainWindow::show_delivery_wait_tableView(QString orderlist)
{
    if (deliveryWaitList_model)
    {
        delete deliveryWaitList_model;
        deliveryWaitList_model = nullptr;
    }
    deliveryWaitList_model = new QStandardItemModel();
    deliveryWaitList_model->setColumnCount(11);
    deliveryWaitList_model->setHorizontalHeaderLabels(QStringList() <<"주문번호"<<"주문자번호"<<"가게번호"<<"라이더번호"<<"주문자ID"
                                                                 <<"가게이름"<<"주문내용"<<"가격"<<"배달주소"<<"주문요청사항"<<"주문상태");

    create_client_order_list_model(deliveryWaitList_model, orderlist);
    ui->deliWait_tableView->setModel(deliveryWaitList_model);
    rider_view_design_setting(ui->deliWait_tableView);
}


//================================================가게 클라이언트 함수 ============================================================
void MainWindow::order_accept_or_deny(bool accept)
{
    QMessageBox::StandardButton reply;
    QModelIndex currentIndex = ui->orderWait_tableView->selectionModel()->currentIndex();

    QString o_num = currentIndex.sibling(currentIndex.row(), 0).data().toString();
    int u_num = currentIndex.sibling(currentIndex.row(), 1).data().toInt();

    if (accept)
    {
        reply = QMessageBox::question(this, "질문", "해당 주문을 승낙하시겠습니까?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::No)
            return;
        send_delivery_func_order(ORDERACCEPT, o_num, SHOP, present_clnt.clnt_num, USER, u_num);
    }
    else
    {
        reply = QMessageBox::question(this, "질문", "해당 주문을 거절하시겠습니까?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::No)
            return;
        send_delivery_func_order(ORDERDENY, o_num, SHOP, present_clnt.clnt_num, USER, u_num);
    }

    // 모델 초기화
    orderWaitList_model->clear();
    send_delivery_func_order(SORDERLIST_WAITING, "", SHOP, present_clnt.clnt_num);
    send_delivery_func_order(SORDERLIST_ENTIRE, "", SHOP, present_clnt.clnt_num);
}

void MainWindow::show_order_entire_tableView(QString orderlist)
{
    if (orderEntireList_model)
    {
        delete orderEntireList_model;
        orderEntireList_model = nullptr;
    }
    orderEntireList_model = new QStandardItemModel();
    orderEntireList_model->setColumnCount(11);
    orderEntireList_model->setHorizontalHeaderLabels(QStringList() <<"주문번호"<<"주문자번호"<<"가게번호"<<"라이더번호"<<"주문자ID"
                                                                 <<"가게이름"<<"주문내용"<<"가격"<<"배달주소"<<"주문요청사항"<<"주문상태");

    create_client_order_list_model(orderEntireList_model, orderlist);
    ui->orderAccept_tableView->setModel(orderEntireList_model);

    for (int i = 0; i < 4; i++)
    {
        ui->orderAccept_tableView->hideColumn(i);
    }
    ui->orderAccept_tableView->hideColumn(5);
    ui->orderAccept_tableView->resizeColumnsToContents();
    ui->orderAccept_tableView->resizeRowsToContents(); // 행 높이를 셀 내용에 맞게 자동 조정
    ui->orderAccept_tableView->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Stretch);
    ui->orderAccept_tableView->horizontalHeader()->setSectionResizeMode(8, QHeaderView::Stretch);
    ui->orderAccept_tableView->horizontalHeader()->setSectionResizeMode(9, QHeaderView::Stretch);
    ui->orderAccept_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->orderAccept_tableView->show();

    int total_sales = 0;
    int rowCount = orderEntireList_model->rowCount();
    for (int row = 0; row < rowCount; row++)
    {
        int price = orderEntireList_model->item(row, 7)->data(Qt::DisplayRole).toInt();
        total_sales += price;
    }
    ui->total_sales_text->setText(QString("%1 원").arg(total_sales));
}

void MainWindow::show_order_wait_tableView(QString orderlist)
{
    if (orderWaitList_model)
    {
        delete orderWaitList_model;
        orderWaitList_model = nullptr;
    }
    orderWaitList_model = new QStandardItemModel();
    orderWaitList_model->setColumnCount(11);
    orderWaitList_model->setHorizontalHeaderLabels(QStringList() <<"주문번호"<<"주문자번호"<<"가게번호"<<"라이더번호"<<"주문자ID"
                                                   <<"가게이름"<<"주문내용"<<"가격"<<"배달주소"<<"주문요청사항"<<"주문상태");

    create_client_order_list_model(orderWaitList_model, orderlist);
    ui->orderWait_tableView->setModel(orderWaitList_model);

    for (int i = 0; i < 4; i++)
    {
        ui->orderWait_tableView->hideColumn(i);
    }
    ui->orderWait_tableView->hideColumn(5);
    ui->orderWait_tableView->hideColumn(10);
    ui->orderWait_tableView->resizeColumnsToContents();
    ui->orderWait_tableView->resizeRowsToContents(); // 행 높이를 셀 내용에 맞게 자동 조정
    ui->orderWait_tableView->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Stretch);
    ui->orderWait_tableView->horizontalHeader()->setSectionResizeMode(8, QHeaderView::Stretch);
    ui->orderWait_tableView->horizontalHeader()->setSectionResizeMode(9, QHeaderView::Stretch);
    ui->orderWait_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->orderWait_tableView->show();
}

//============================================ 유저 클라이언트 함수 ============================================================================
void MainWindow::change_bookmark_tab(int index)
{
    if (index == 2)
    {
        send_delivery_func_order(BOOKMARKLIST, "", USER, present_clnt.clnt_num);
    }
}

void MainWindow::create_bookmark_list_model(QString &shoplist)
{
    QStringList str_list = shoplist.split("\n");
    QStandardItem *s_num, *s_title, *s_type, *s_state;
    int index = 0;

    // 만약 할당받은 모델이 있으면 동적해제
    if (bookmarkList_model)
    {
        delete bookmarkList_model;
        bookmarkList_model = nullptr;
    }

    bookmarkList_model = new QStandardItemModel();
    bookmarkList_model->setColumnCount(5);
    bookmarkList_model->setHorizontalHeaderLabels(QStringList()<<"가게번호"<< "이미지" << "가게이름" << "카테고리"<< "영업상태");

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
        bookmarkList_model->appendRow(items);

    }
    shop_img_list.clear();// 가게 이미지 리스트 초기화
    ui->bookmark_tableView->setModel(bookmarkList_model);
    s_view_design_setting(ui->bookmark_tableView);
}


void MainWindow::bookmark_operate(QString msg)
{
    if (msg == "bookmarkDel")
    {
        bookmarkList_model->clear();
        send_delivery_func_order(BOOKMARKLIST, "", USER, present_clnt.clnt_num);
        ui->bookmark_btn->setStyleSheet("background-color: #87CEFA; color: black; font-weight: bold;");
        ui->bookmark_btn->setText("찜하기🤍");
        QMessageBox::information(this, "정보", "찜 목록에서 삭제되었습니다.");
    }
    else if (msg == "bookmarkAdd")
    {
        send_delivery_func_order(BOOKMARKLIST, "", USER, present_clnt.clnt_num);
        ui->bookmark_btn->setStyleSheet("background-color: #FF6347; color: white; font-weight: bold;");
        ui->bookmark_btn->setText("찜취소🩷");
        QMessageBox::information(this, "정보", "해당 가게를 찜 하였습니다.");
    }
    else if (msg == "bookmarkTrue")
    {
        ui->bookmark_btn->setStyleSheet("background-color: #FF6347; color: white; font-weight: bold;");
        ui->bookmark_btn->setText("찜취소🩷");
    }
    else if (msg == "bookmarkFalse")
    {
        ui->bookmark_btn->setStyleSheet("background-color: #87CEFA; color: black; font-weight: bold;");
        ui->bookmark_btn->setText("찜하기🤍");
    }
}

void MainWindow::create_client_order_list_model(QStandardItemModel *model, QString orderlist)
{
    QStringList str_list = orderlist.split("@");
    QStandardItem *o_num, *u_num, *s_num, *r_num, *u_id, *s_title, *o_text, *o_price, *o_addr, *o_request, *o_state;

    for (const QString &row: str_list)
    {
        QStringList columns = row.split("/");
        o_num = new QStandardItem(columns[0].trimmed());
        o_text = new QStandardItem(columns[1].trimmed());
        o_price = new QStandardItem(columns[2].trimmed());
        o_addr = new QStandardItem(columns[3].trimmed());
        u_num = new QStandardItem(columns[4].trimmed());
        s_num = new QStandardItem(columns[5].trimmed());
        r_num = new QStandardItem(columns[6].trimmed());
        o_state = new QStandardItem(columns[7].trimmed());
        o_request = new QStandardItem(columns[8].trimmed());
        s_title = new QStandardItem(columns[9].trimmed());
        u_id = new QStandardItem(columns[10].trimmed());

        o_text->setTextAlignment(Qt::AlignCenter);
        o_price->setTextAlignment(Qt::AlignCenter);
        o_addr->setTextAlignment(Qt::AlignCenter);
        o_state->setTextAlignment(Qt::AlignCenter);
        o_request->setTextAlignment(Qt::AlignCenter);
        s_title->setTextAlignment(Qt::AlignCenter);
        u_id->setTextAlignment(Qt::AlignCenter);

        QList<QStandardItem*> items;
        items << o_num
              << u_num
              << s_num
              << r_num
              << u_id
              << s_title
              << o_text
              << o_price
              << o_addr
              << o_request
              << o_state;

        model->appendRow(items);
    }
}

void MainWindow::show_user_history_tableView(QString orderlist)
{
    if (user_historyList_model)
    {
        delete user_historyList_model;
        user_historyList_model = nullptr;
    }
    user_historyList_model = new QStandardItemModel();
    user_historyList_model->setColumnCount(11);
    user_historyList_model->setHorizontalHeaderLabels(QStringList() <<"주문번호"<<"주문자번호"<<"가게번호"<<"라이더번호"<<"주문자ID"
                                                                  <<"가게이름"<<"주문내용"<<"가격"<<"배달주소"<<"주문요청사항"<<"주문상태");
    create_client_order_list_model(user_historyList_model, orderlist);
    ui->order_history_tableView->setModel(user_historyList_model);

    for (int i = 0; i < 5; i++)
    {
        ui->order_history_tableView->hideColumn(i);
    }
    ui->order_history_tableView->resizeColumnsToContents();
    ui->order_history_tableView->resizeRowsToContents(); // 행 높이를 셀 내용에 맞게 자동 조정
    ui->order_history_tableView->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);
    ui->order_history_tableView->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Stretch);
    ui->order_history_tableView->horizontalHeader()->setSectionResizeMode(8, QHeaderView::Stretch);
    ui->order_history_tableView->horizontalHeader()->setSectionResizeMode(9, QHeaderView::Stretch);
    ui->order_history_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->order_history_tableView->show();
}

void MainWindow::show_user_state_tableView(QString orderlist)
{
    if (user_orderlist_model)
    {
        delete user_orderlist_model;
        user_orderlist_model = nullptr;
    }
    user_orderlist_model = new QStandardItemModel();
    user_orderlist_model->setColumnCount(11);
    user_orderlist_model->setHorizontalHeaderLabels(QStringList() <<"주문번호"<<"주문자번호"<<"가게번호"<<"라이더번호"<<"주문자ID"
                                                                 <<"가게이름"<<"주문내용"<<"가격"<<"배달주소"<<"주문요청사항"<<"주문상태");
    create_client_order_list_model(user_orderlist_model, orderlist);
    ui->user_order_state_tableView->setModel(user_orderlist_model);

    for (int i = 0; i < 5; i++)
    {
        ui->user_order_state_tableView->hideColumn(i);
    }
    ui->user_order_state_tableView->resizeColumnsToContents();
    ui->user_order_state_tableView->resizeRowsToContents();
    ui->user_order_state_tableView->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);
    ui->user_order_state_tableView->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Stretch);
    ui->user_order_state_tableView->horizontalHeader()->setSectionResizeMode(8, QHeaderView::Stretch);
    ui->user_order_state_tableView->horizontalHeader()->setSectionResizeMode(9, QHeaderView::Stretch);
    ui->user_order_state_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->user_order_state_tableView->show();
}

void MainWindow::m_view_design_setting(QTableView *view, int type)
{
    view->setIconSize(QSize(100, 100));
    view->resizeColumnsToContents();
    view->resizeRowsToContents();
    view->hideColumn(0);
    view->hideColumn(1);
    view->verticalHeader()->setVisible(false);
    view->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    if (type == TYPE1)
    {
        view->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    }
    else
    {
        view->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);
        view->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Stretch);
    }
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->show();
}

void MainWindow::s_view_design_setting(QTableView *view)
{
    view->setIconSize(QSize(100, 100));
    view->resizeColumnsToContents();
    view->resizeRowsToContents();
    view->hideColumn(0);
    view->verticalHeader()->setVisible(false);
    view->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    view->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    view->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->show();
}

void MainWindow::user_final_order()
{
    QString total_order_str = "";
    QString order_menu_str, food_name, food_cnt;
    QMessageBox::StandardButton reply;
    QString address = ui->del_address_text->text().trimmed();
    QString request = ui->del_request_text->text().trimmed();
    int shop_num = basketlist_model->item(0, 1)->data(Qt::DisplayRole).toInt();

    if (address.isEmpty())
    {
        QMessageBox::critical(this, "오류", "주소를 입력하세요");
        return;
    }

    int rowCount = basketlist_model->rowCount();
    for (int row = 0; row < rowCount; row++)
    {
        food_name = basketlist_model->item(row, 3)->data(Qt::DisplayRole).toString();
        food_cnt = basketlist_model->item(row, 5)->data(Qt::DisplayRole).toString();
        order_menu_str = QString("%1 %2개\n").arg(food_name, food_cnt);
        total_order_str += order_menu_str;
    }
    total_order_str += "/" + QString::number(total_price) + "/" + address + "/" + request + "/" + present_clnt.clnt_id;

    reply = QMessageBox::question(this, "질문", "이대로 주문하시겠습니까?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No)
        return;

    send_delivery_func_order(USERORDER, total_order_str, USER, present_clnt.clnt_num, SHOP, shop_num);
    send_delivery_func_order(UORDERLIST, present_clnt.clnt_id, USER, present_clnt.clnt_num);
    basketlist_model->clear();
    ui->del_address_text->clear();
    ui->del_request_text->clear();
    ui->mainStackedWidget->setCurrentWidget(ui->user_main_page);
    ui->user_mainTabWidget->setCurrentWidget(ui->orderStateTab);
}

void MainWindow::to_order_page()
{
    if (basketlist_model->rowCount() == 0)
    {
        QMessageBox::critical(this, "오류", "주문 할 메뉴를 선택하세요");
        return;
    }

    total_price = 0;
    ui->pay_tableView->setModel(basketlist_model);
    m_view_design_setting(ui->pay_tableView, TYPE1);
    ui->menu_shopTitle2->setText(clicked_shop_title);
    ui->mainStackedWidget->setCurrentWidget(ui->pay_page);

    int rowCount = basketlist_model->rowCount();
    for (int row = 0; row < rowCount; row++)
    {
        int price = basketlist_model->item(row, 4)->data(Qt::DisplayRole).toInt();
        int fcnt = basketlist_model->item(row, 5)->data(Qt::DisplayRole).toInt();

        total_price += price * fcnt;
    }
    ui->menu_price_label->setText(QString("%1 원").arg(total_price));
}

void MainWindow::category_img_to_item(QByteArray &img_buf)
{
    QPixmap thumbnailPixmap;
    thumbnailPixmap.loadFromData(img_buf);
    QPixmap resizedPixmap = thumbnailPixmap.scaled(180, 140, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    category_img_list.append(resizedPixmap);
}

void MainWindow::create_food_category()
{
    category_btn_list.append(ui->chicken_btn);
    category_btn_list.append(ui->pizza_btn);
    category_btn_list.append(ui->kFood_btn);
    category_btn_list.append(ui->jFood_btn);
    category_btn_list.append(ui->cFood_btn);
    category_btn_list.append(ui->cafe_btn);
    int index = 0;

    foreach (QToolButton *button, category_btn_list)
    {
        button->setIcon(QIcon(category_img_list[index++]));
        button->setIconSize(QSize(180, 140));
        button->setStyleSheet("");
        button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    }
    category_btn_list.clear();
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
    m_view_design_setting(ui->menu_basket_tableView, TYPE1);
}

void MainWindow::shop_search()
{
    QString search_shop_str = ui->shopSearchText->text().trimmed();
    if (search_shop_str.isEmpty())
    {
        QMessageBox::critical(this, "오류", "검색어를 입력하세요.");
        return;
    }
    // 만약 할당받은 모델이 있으면 동적해제
    if (proxyModel)
    {
        delete proxyModel;
        proxyModel = nullptr;
    }
    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(shoplist_model);
    proxyModel->setFilterRegularExpression(QRegularExpression(search_shop_str));
    proxyModel->setFilterKeyColumn(2);// 필터링할 열
    // 필터링된 결과를 View에 출력
    ui->searchTableView->setModel(proxyModel);
    s_view_design_setting(ui->searchTableView);
    ui->mainStackedWidget->setCurrentWidget(ui->user_main_page);
    ui->user_mainTabWidget->setCurrentWidget(ui->shopSearchTab);
}

void MainWindow::shop_view_double_clicked(const QModelIndex &index)
{
    int clicked_row = index.row();
    // 어떤 칸을 클릭해도 해당 열의 웹툰 일련번호가 리턴됨
    clicked_shop_num = index.sibling(clicked_row, 0).data().toString();
    clicked_shop_title = index.sibling(clicked_row, 2).data().toString();
    QString clicked_shop_state = index.sibling(clicked_row, 4).data().toString();

    if (clicked_shop_state == "영업대기")
    {
        QMessageBox::critical(this, "오류", "영업중인 가게가 아닙니다");
        return;
    }

    // 만약 할당받은 모델이 있으면 동적해제
    if (proxyModel)
    {
        delete proxyModel;
        proxyModel = nullptr;
    }
    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(menulist_model);

    // QRegularExpression을 사용하여 문자열의 시작(^)과 끝($)을 고정
    QRegularExpression exactMatch("^" + QRegularExpression::escape(clicked_shop_num) + "$");
    proxyModel->setFilterRegularExpression(exactMatch);
    proxyModel->setFilterKeyColumn(1); // 필터링할 열

    // 필터링된 결과를 View에 출력
    ui->menu_tableView->setModel(proxyModel);

    int row_cnt = ui->menu_tableView->model()->rowCount();
    // 스핀박스 테이블 뷰에 집어넣기
    for (int i = 0; i < row_cnt; i++)
    {
        QSpinBox *menu_spin_box = new QSpinBox();
        menu_spin_box->setRange(1, 100);
        menu_spin_box->setValue(1);
        ui->menu_tableView->setIndexWidget(proxyModel->index(i,6), menu_spin_box);
    }
    m_view_design_setting(ui->menu_tableView, TYPE2);
    ui->menu_shopTitle->setText(clicked_shop_title);
    ui->mainStackedWidget->setCurrentWidget(ui->menuList_page);

    // 만약 할당받은 모델이 있으면 동적해제
    if (basketlist_model)
    {
        delete basketlist_model;
        basketlist_model = nullptr;
    }
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

    // 만약 할당받은 모델이 있으면 동적해제
    if (menulist_model)
    {
        delete menulist_model;
        menulist_model = nullptr;
    }
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

    // 만약 할당받은 모델이 있으면 동적해제
    if (shoplist_model)
    {
        delete shoplist_model;
        shoplist_model = nullptr;
    }

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
    // 만약 할당받은 모델이 있으면 동적해제
    if (proxyModel)
    {
        delete proxyModel;
        proxyModel = nullptr;
    }
    // QSortFilterProxyModel을 생성
    proxyModel = new QSortFilterProxyModel(this);
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
    s_view_design_setting(ui->shopList_tableView);

    if (!shop_renewal_chk)
        ui->mainStackedWidget->setCurrentWidget(ui->shopList_page);

    shop_renewal_chk = false;
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
                                    .arg(QString::number(sender), QString::number(senderNum), QString::number(receiver), QString::number(receiverNum)).toUtf8());
                break;
            case CATEGORY:
                header.prepend(QString("fileType:category,sender:%1,senderNum:%2,receiver:%3,recieverNum:%4;")
                                    .arg(QString::number(sender), QString::number(senderNum), QString::number(receiver), QString::number(receiverNum)).toUtf8());
                break;
            case SHOPTITLE:
                header.prepend(QString("fileType:shoptitle,sender:%1,senderNum:%2,receiver:%3,recieverNum:%4;")
                                    .arg(QString::number(sender), QString::number(senderNum), QString::number(receiver), QString::number(receiverNum)).toUtf8());
                break;
            case SHOPLIST:
                header.prepend(QString("fileType:shoplist,sender:%1,senderNum:%2,receiver:%3,recieverNum:%4;")
                                    .arg(QString::number(sender), QString::number(senderNum), QString::number(receiver), QString::number(receiverNum)).toUtf8());
                break;
            case MENULIST:
                header.prepend(QString("fileType:menulist,sender:%1,senderNum:%2,receiver:%3,recieverNum:%4;")
                                    .arg(QString::number(sender), QString::number(senderNum), QString::number(receiver), QString::number(receiverNum)).toUtf8());
                break;
            case USERORDER:
                header.prepend(QString("fileType:userorder,sender:%1,senderNum:%2,receiver:%3,recieverNum:%4;")
                                    .arg(QString::number(sender), QString::number(senderNum), QString::number(receiver), QString::number(receiverNum)).toUtf8());
                break;
            case UORDERLIST:
                header.prepend(QString("fileType:uOrderList,sender:%1,senderNum:%2,receiver:%3,recieverNum:%4;")
                                    .arg(QString::number(sender), QString::number(senderNum), QString::number(receiver), QString::number(receiverNum)).toUtf8());
                break;
            case SORDERLIST_WAITING:
                header.prepend(QString("fileType:sOrderListW,sender:%1,senderNum:%2,receiver:%3,recieverNum:%4;")
                                    .arg(QString::number(sender), QString::number(senderNum), QString::number(receiver), QString::number(receiverNum)).toUtf8());
                break;
            case SORDERLIST_ENTIRE:
                header.prepend(QString("fileType:sOrderListE,sender:%1,senderNum:%2,receiver:%3,recieverNum:%4;")
                                    .arg(QString::number(sender), QString::number(senderNum), QString::number(receiver), QString::number(receiverNum)).toUtf8());
                break;
            case ORDERACCEPT:
                header.prepend(QString("fileType:orderAccept,sender:%1,senderNum:%2,receiver:%3,recieverNum:%4;")
                                    .arg(QString::number(sender), QString::number(senderNum), QString::number(receiver), QString::number(receiverNum)).toUtf8());
                break;
            case ORDERDENY:
                header.prepend(QString("fileType:orderDeny,sender:%1,senderNum:%2,receiver:%3,recieverNum:%4;")
                                    .arg(QString::number(sender), QString::number(senderNum), QString::number(receiver), QString::number(receiverNum)).toUtf8());
                break;
            case DELIVERYLIST:
                header.prepend(QString("fileType:deliveryList,sender:%1,senderNum:%2,receiver:%3,recieverNum:%4;")
                                    .arg(QString::number(sender), QString::number(senderNum), QString::number(receiver), QString::number(receiverNum)).toUtf8());
                break;
            case DELIACCEPT:
                header.prepend(QString("fileType:deliAccept,sender:%1,senderNum:%2,receiver:%3,recieverNum:%4;")
                                    .arg(QString::number(sender), QString::number(senderNum), QString::number(receiver), QString::number(receiverNum)).toUtf8());
                break;
            case DELIACCEPTLIST:
                header.prepend(QString("fileType:deliAcceptList,sender:%1,senderNum:%2,receiver:%3,recieverNum:%4;")
                                    .arg(QString::number(sender), QString::number(senderNum), QString::number(receiver), QString::number(receiverNum)).toUtf8());
                break;
            case DELICOMPLETE:
                header.prepend(QString("fileType:deliComplete,sender:%1,senderNum:%2,receiver:%3,recieverNum:%4;")
                                   .arg(QString::number(sender), QString::number(senderNum), QString::number(receiver), QString::number(receiverNum)).toUtf8());
                break;
            case DELIHISTORYLIST:
                header.prepend(QString("fileType:deliHistoryList,sender:%1,senderNum:%2,receiver:%3,recieverNum:%4;")
                                   .arg(QString::number(sender), QString::number(senderNum), QString::number(receiver), QString::number(receiverNum)).toUtf8());
                break;
            case UORDER_HISTORYLIST:
                header.prepend(QString("fileType:orderHistoryList,sender:%1,senderNum:%2,receiver:%3,recieverNum:%4;")
                                   .arg(QString::number(sender), QString::number(senderNum), QString::number(receiver), QString::number(receiverNum)).toUtf8());
                break;
            case BOOKMARK:
                header.prepend(QString("fileType:bookmark,sender:%1,senderNum:%2,receiver:%3,recieverNum:%4;")
                                   .arg(QString::number(sender), QString::number(senderNum), QString::number(receiver), QString::number(receiverNum)).toUtf8());
                break;
            case BOOKMARKLIST:
                header.prepend(QString("fileType:bookmarkList,sender:%1,senderNum:%2,receiver:%3,recieverNum:%4;")
                                   .arg(QString::number(sender), QString::number(senderNum), QString::number(receiver), QString::number(receiverNum)).toUtf8());
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
                header.prepend(QString("fileType:login,sender:%1,senderNum:%2,receiver:null,recieverNum:null;").arg(QString::number(client_type), id).toUtf8());
                break;
            case SIGNUP:
                header.prepend(QString("fileType:signUp,sender:%1,senderNum:%2,receiver:null,recieverNum:null;").arg(QString::number(client_type), id).toUtf8());
                break;
            case IDDUPCHK:
                header.prepend(QString("fileType:idDupChk,sender:%1,senderNum:%2,receiver:null,recieverNum:null;").arg(QString::number(client_type), id).toUtf8());
                break;
            case PNUMDUPCHK:
                header.prepend(QString("fileType:pNumDupChk,sender:%1,senderNum:%2,receiver:null,recieverNum:null;").arg(QString::number(client_type), id).toUtf8());
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

void MainWindow::on_logout_btn_clicked()
{
    send_delivery_func_order(LOGOUT, "", present_clnt.type, present_clnt.clnt_num);
    QMessageBox::information(this, "알림","로그아웃 하였습니다.");
    this->window()->hide();
    loginWidget->show();
}

void MainWindow::on_to_mainBtn_clicked()
{
    ui->mainStackedWidget->setCurrentWidget(ui->user_main_page);
}

void MainWindow::on_to_menu_back_btn_clicked()
{
    ui->mainStackedWidget->setCurrentWidget(ui->menuList_page);
}
