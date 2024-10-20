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

    connect(loginWidget, &Login::user_info_signal, this, &MainWindow::send_user_info); // 회원가입 정보 전송 connect
    connect(loginWidget, &Login::login_success_signal, this, &MainWindow::get_login_user_info);
    connect(this, &MainWindow::operate_info_signal, loginWidget, &Login::signUp_operate);
    connect(this, &MainWindow::login_info_signal, loginWidget, &Login::login_operate);
    connect(this, &MainWindow::idSearch_info_signal, loginWidget, &Login::idSearch_operate);
    connect(this, &MainWindow::pwSearch_info_signal, loginWidget, &Login::pwSearch_operate);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::toon_search);
    connect(ui->epiList_tableView, &QTableView::doubleClicked, this, &MainWindow::epi_view_double_clicked);
    connect(ui->b_tableView, &QTableView::doubleClicked, this, &MainWindow::epi_view_double_clicked);
    connect(ui->bookmark_add_btn, &QPushButton::clicked, this, &MainWindow::bookmark_control);
    connect(ui->like_btn, &QPushButton::clicked, this, &MainWindow::like_control);
    connect(ui->beforeEpi_btn, &QPushButton::clicked, this, &MainWindow::to_before_epi);
    connect(ui->afterEpi_btn, &QPushButton::clicked, this, &MainWindow::to_after_epi);

    QList<QTableView*> view_list;
    view_list.append(ui->e_tableView);
    view_list.append(ui->tableView_mon);
    view_list.append(ui->tableView_tue);
    view_list.append(ui->tableView_wed);
    view_list.append(ui->tableView_thu);
    view_list.append(ui->tableView_fri);
    view_list.append(ui->tableView_sat);
    view_list.append(ui->tableView_sun);
    view_list.append(ui->searchTableView);
    for (QTableView *tableView : view_list)
    {
        connect(tableView, &QTableView::doubleClicked, this, &MainWindow::view_double_clicked);
    }

    // [ex.02.1.2]
    // 연결된 socket에 read 할 데이터가 들어오면,
    // 이 객체의(MainWindow) slot_readSocket 실행하여 처리
    connect(m_socket, &QTcpSocket::readyRead,
            this,     &MainWindow::slot_readSocket);

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
    delete toonInfo_model;
    delete toonList_model;
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

        // buffer의 128 byte 이후 부분 buffer에 다시 담음.
        buffer = buffer.mid(128);
        QString msg = buffer;

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
                send_toon_info(TOONINFO); // 툰 정보 모델 생성위해 서버에 메시지 전송
                send_toon_info(BOOKMARKLIST, login_user_id);

                loginWidget->hide();
                this->window()->show();
                ui->stackedWidget->setCurrentWidget(ui->main_page);
                ui->mainTabWidget->setCurrentIndex(0);

            }
            else if (msg == "login fail")
            {
                emit login_info_signal("login fail");
            }
        }
        else if (fileType == "idInfo")
        {
            if (msg == "idSearch fail") // 아이디 찾기 실패
            {
                emit idSearch_info_signal("idSearch fail");
            }
            else
            {
                emit idSearch_info_signal(msg); // 아이디 찾기 성공
            }
        }
        else if (fileType == "pwInfo")
        {
            if (msg == "pwSearch fail") // 비밀번호 찾기 실패
            {
                emit pwSearch_info_signal("pwSearch fail");
            }
            else
            {
                emit pwSearch_info_signal(msg); // 아이디 찾기 성공
            }
        }
        else if (fileType == "tooninfo")
        {
            create_toonInfo_model(msg);
        }
        else if (fileType == "thumbnail")
        {
            thumbnail_to_item(buffer);
        }
        else if (fileType == "toonlist")
        {
            create_toonList_model(msg);
        }
        else if (fileType == "toonimage")
        {
            toon_img_show(buffer);
        }
        else if (fileType == "bookmark")
        {
            bookmark_ui_operate(msg);
        }
        else if (fileType == "bookmarklist")
        {
            create_bookmark_model(msg);
        }
        else if (fileType == "toonlike")
        {
            toonlike_ui_operate(msg);
        }
        else if (fileType == "epichange")
        {
            epi_move_denied_alarm(msg);
        }
        else if (fileType == "tooninfotext")
        {
            toon_info_text_show(msg);
        }

    }
}


void MainWindow::toon_info_text_show(QString msg)
{
    QStringList msgParts;
    msgParts = msg.split("/");
    QString toon_title = msgParts[0];
    QString epi_num = msgParts[1];
    QString epi_title = msgParts[2];

    ui->toon_info_text_label->setText("   ["+toon_title+"]  "+epi_num+"화 - '"+epi_title+"'");
}

void MainWindow::epi_move_denied_alarm(QString msg)
{
    if (msg == "firstepi")
    {
        QMessageBox::information(this, "정보", "현재 페이지는 첫번째화 입니다.");
        toonEpiNum_data = QString::number(toonEpiNum_data.toInt() + 1);
        present_toon_id = QString::number(present_toon_id.toInt() + 1);
        send_toon_info(TOONIMAGE, present_toon_id);
    }
    else
    {
        QMessageBox::information(this, "정보", "현재 페이지는 마지막화 입니다.");
        toonEpiNum_data = QString::number(toonEpiNum_data.toInt() - 1);
        present_toon_id = QString::number(present_toon_id.toInt() - 1);
        send_toon_info(TOONIMAGE, present_toon_id);
    }
}

void MainWindow::to_before_epi()
{
    // 동적으로 만든 imglabel 해제
    for (QLabel *imgLabel : imgLabel_list)
    {
        delete imgLabel;
    }
    imgLabel_list.clear(); // 리스트 요소 클리어
    send_toon_info(EPICHANGE, toonInfo_data+","+toonEpiNum_data+",before");
    toonEpiNum_data = QString::number(toonEpiNum_data.toInt() - 1);
    present_toon_id = QString::number(present_toon_id.toInt() - 1);
}

void MainWindow::to_after_epi()
{
    // 동적으로 만든 imglabel 해제
    for (QLabel *imgLabel : imgLabel_list)
    {
        delete imgLabel;
    }
    imgLabel_list.clear(); // 리스트 요소 클리어
    send_toon_info(EPICHANGE, toonInfo_data+","+toonEpiNum_data+",after");
    toonEpiNum_data = QString::number(toonEpiNum_data.toInt() + 1);
    present_toon_id = QString::number(present_toon_id.toInt() + 1);
}

void MainWindow::toonlike_ui_operate(QString msg)
{
    if (msg == "toonlikeDel")
    {
        send_toon_info(BOOKMARKLIST, login_user_id);
        ui->like_btn->setStyleSheet("background-color: #87CEFA; color: black; font-weight: bold;");
        ui->like_btn->setText("좋아요 🤍");
    }
    else if (msg == "toonlikeAdd")
    {
        send_toon_info(BOOKMARKLIST, login_user_id);
        ui->like_btn->setStyleSheet("background-color: #FF6347; color: white; font-weight: bold;");
        ui->like_btn->setText("좋아요 취소 🩷");
    }
    else if (msg == "toonlikeTrue")
    {
        ui->like_btn->setStyleSheet("background-color: #FF6347; color: white; font-weight: bold;");
        ui->like_btn->setText("좋아요 취소 🩷");
    }
    else if (msg == "toonlikeFalse")
    {
        ui->like_btn->setStyleSheet("background-color: #87CEFA; color: black; font-weight: bold;");
        ui->like_btn->setText("좋아요 🤍");
    }
}

void MainWindow::bookmark_ui_operate(QString msg)
{
    if (msg == "bookmarkDel")
    {
        send_toon_info(BOOKMARKLIST, login_user_id);
        ui->bookmark_add_btn->setStyleSheet("background-color: #87CEFA; color: black; font-weight: bold;");
        ui->bookmark_add_btn->setText("즐겨찾기 추가 ☆");
        QMessageBox::information(this, "정보", "즐겨찾기에서 삭제되었습니다.");
    }
    else if (msg == "bookmarkAdd")
    {
        send_toon_info(BOOKMARKLIST, login_user_id);
        ui->bookmark_add_btn->setStyleSheet("background-color: #FF6347; color: white; font-weight: bold;");
        ui->bookmark_add_btn->setText("즐겨찾기 삭제 🌟");
        QMessageBox::information(this, "정보", "즐겨찾기에 추가되었습니다.");
    }
    else if (msg == "bookmarkTrue")
    {
        ui->bookmark_add_btn->setStyleSheet("background-color: #FF6347; color: white; font-weight: bold;");
        ui->bookmark_add_btn->setText("즐겨찾기 삭제 🌟");
    }
    else if (msg == "bookmarkFalse")
    {
        ui->bookmark_add_btn->setStyleSheet("background-color: #87CEFA; color: black; font-weight: bold;");
        ui->bookmark_add_btn->setText("즐겨찾기 추가 ☆");
    }
}


void MainWindow::create_bookmark_model(QString &toonlist)
{
    QStringList str_list = toonlist.split("\n");
    QStandardItem *epi_id, *t_id, *t_title, *epi_title, *t_author, *t_day, *epi_num, *view_num, *like_num;

    bookmarkList_model = new QStandardItemModel();
    bookmarkList_model->setColumnCount(9);
    bookmarkList_model->setHorizontalHeaderLabels(QStringList()<<"일련번호"<<"종류번호"<<"웹툰제목"<<"회차제목"<<"작가"<<"회차"<<"요일"<<"조회수"<<"좋아요수");

    for (const QString &row: str_list)
    {
        QStringList columns = row.split("/");
        if (columns.size() == 9)
        {
            epi_id = new QStandardItem(columns[0].trimmed());
            t_id = new QStandardItem(columns[1].trimmed());
            t_title = new QStandardItem(columns[2].trimmed());
            epi_title = new QStandardItem(columns[3].trimmed());
            t_author = new QStandardItem(columns[4].trimmed());
            t_day = new QStandardItem(columns[5].trimmed());
            epi_num = new QStandardItem(columns[6].trimmed());
            view_num = new QStandardItem(columns[7].trimmed());
            like_num = new QStandardItem(columns[8].trimmed());

            t_title->setTextAlignment(Qt::AlignCenter);
            epi_title->setTextAlignment(Qt::AlignCenter);
            t_author->setTextAlignment(Qt::AlignCenter);
            t_day->setTextAlignment(Qt::AlignCenter);
            epi_num->setTextAlignment(Qt::AlignCenter);
            view_num->setTextAlignment(Qt::AlignCenter);
            like_num->setTextAlignment(Qt::AlignCenter);

            QList<QStandardItem*> items;
            items << epi_id
                  << t_id
                  << t_title
                  << epi_title
                  << t_author
                  << epi_num
                  << t_day
                  << view_num
                  << like_num;

            bookmarkList_model->appendRow(items);
        }
    }
    ui->b_tableView->setModel(bookmarkList_model);
    ui->b_tableView->resizeColumnsToContents();
    ui->b_tableView->hideColumn(0);
    ui->b_tableView->hideColumn(1);
    ui->b_tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->b_tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->b_tableView->show();
}

void MainWindow::get_login_user_info(QString id)
{
    login_user_id = id;
    qDebug() << "현재 로그인유저 아이디: " << login_user_id;
}

void MainWindow::bookmark_control()
{
    send_toon_info(BOOKMARK, login_user_id+","+present_toon_id+",control");
}

void MainWindow::like_control()
{
    send_toon_info(TOONLIKE, login_user_id+","+present_toon_id+",control");
}

void MainWindow::epi_view_double_clicked(const QModelIndex &index)
{
    int return_column = 0; // 웹툰 에피소드 일련번호 컬럼 인덱스번호
    int clicked_row = index.row();

    toonInfo_data = index.sibling(clicked_row, 1).data().toString(); // 현재 보고있는 웹툰 일련번호 저장
    toonEpiNum_data = index.sibling(clicked_row, 5).data().toString(); // 현재 보고있는 웹툰 회차 저장
    // 어떤 칸을 클릭해도 해당 열의 웹툰 에피소드 일련번호가 리턴됨
    QString data = index.sibling(clicked_row, return_column).data().toString();
    present_toon_id = data;
    send_toon_info(TOONIMAGE, present_toon_id);
}

void MainWindow::toon_img_show(QByteArray &img_buf)
{
    send_toon_info(TOONINFOTEXT, present_toon_id);
    send_toon_info(BOOKMARK, login_user_id+","+present_toon_id+",check");
    send_toon_info(TOONLIKE, login_user_id+","+present_toon_id+",check");
    ui->stackedWidget->setCurrentWidget(ui->webtoon_page);
    QPixmap image;
    image.loadFromData(img_buf);
    QLabel *imageLabel = new QLabel();
    imgLabel_list.append(imageLabel);
    imageLabel->setPixmap(image);
    ui->toon_scrollArea_contents->layout()->addWidget(imageLabel);
}

void MainWindow::toon_search()
{
    // QSortFilterProxyModel을 생성하고 원본 모델과 연결
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(toonInfo_model);

    if (ui->searchComboBox->currentText() == "제목")
    {
        //0번째 열에 위에서 받은 data가 포함된 항목만 필터링
        proxyModel->setFilterRegularExpression(QRegularExpression(ui->toonSearchText->text()));
        proxyModel->setFilterKeyColumn(2);// 필터링할 열
    }
    else
    {
        proxyModel->setFilterRegularExpression(QRegularExpression(ui->toonSearchText->text()));
        proxyModel->setFilterKeyColumn(3);// 필터링할 열
    }

    // 필터링된 결과를 View에 출력
    ui->searchTableView->setModel(proxyModel);
    ui->searchTableView->setIconSize(QSize(100, 100));
    ui->searchTableView->resizeColumnsToContents();
    ui->searchTableView->resizeRowsToContents();
    ui->searchTableView->hideColumn(0);
    ui->searchTableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->searchTableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->searchTableView->show();
}


void MainWindow::create_day_view()
{
    QStringList day_str_list;
    QList<QTableView*> day_view_list;

    day_str_list <<"월"<< "화"<< "수"<< "목"<< "금"<< "토"<< "일";
    day_view_list.append(ui->tableView_mon);
    day_view_list.append(ui->tableView_tue);
    day_view_list.append(ui->tableView_wed);
    day_view_list.append(ui->tableView_thu);
    day_view_list.append(ui->tableView_fri);
    day_view_list.append(ui->tableView_sat);
    day_view_list.append(ui->tableView_sun);

    for (int i = 0; i < day_view_list.size(); i++)
    {

        // QSortFilterProxyModel을 생성하고 원본 모델과 연결
        QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(toonInfo_model);
        //0번째 열에 위에서 받은 data가 포함된 항목만 필터링
        proxyModel->setFilterRegularExpression(QRegularExpression(day_str_list[i]));
        proxyModel->setFilterKeyColumn(4);// 필터링할 열
        // 필터링된 결과를 View에 출력
        day_view_list[i]->setModel(proxyModel);
        day_view_list[i]->setIconSize(QSize(100, 100));
        day_view_list[i]->resizeColumnsToContents();
        day_view_list[i]->resizeRowsToContents();
        day_view_list[i]->hideColumn(0);
        day_view_list[i]->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
        day_view_list[i]->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
        day_view_list[i]->show();
    }
}


void MainWindow::view_double_clicked(const QModelIndex &index)
{
    int return_column = 0; // 웹툰 일련번호 컬럼 인덱스번호
    int clicked_row = index.row();
    // 어떤 칸을 클릭해도 해당 열의 웹툰 일련번호가 리턴됨
    toonInfo_data = index.sibling(clicked_row, return_column).data().toString();
    send_toon_info(TOONLIST, toonInfo_data); // 툰 리스트 모델 생성위해 서버에 메시지 전송
}

void MainWindow::create_toonList_model(QString &toonlist)
{
    QStringList str_list = toonlist.split("\n");
    QStandardItem *epi_id, *t_id, *t_title, *epi_title, *t_author, *t_day, *epi_num, *view_num, *like_num;

    toonList_model = new QStandardItemModel();
    toonList_model->setColumnCount(9);
    toonList_model->setHorizontalHeaderLabels(QStringList()<<"일련번호"<<"종류번호"<<"웹툰제목"<<"회차제목"<<"작가"<<"회차"<<"요일"<<"조회수"<<"좋아요수");

    for (const QString &row: str_list)
    {
        QStringList columns = row.split("/");
        if (columns.size() == 9)
        {
            epi_id = new QStandardItem(columns[0].trimmed());
            t_id = new QStandardItem(columns[1].trimmed());
            t_title = new QStandardItem(columns[2].trimmed());
            epi_title = new QStandardItem(columns[3].trimmed());
            t_author = new QStandardItem(columns[4].trimmed());
            t_day = new QStandardItem(columns[5].trimmed());
            epi_num = new QStandardItem(columns[6].trimmed());
            view_num = new QStandardItem(columns[7].trimmed());
            like_num = new QStandardItem(columns[8].trimmed());

            t_title->setTextAlignment(Qt::AlignCenter);
            epi_title->setTextAlignment(Qt::AlignCenter);
            t_author->setTextAlignment(Qt::AlignCenter);
            t_day->setTextAlignment(Qt::AlignCenter);
            epi_num->setTextAlignment(Qt::AlignCenter);
            view_num->setTextAlignment(Qt::AlignCenter);
            like_num->setTextAlignment(Qt::AlignCenter);

            QList<QStandardItem*> items;
            items << epi_id
                  << t_id
                  << t_title
                  << epi_title
                  << t_author
                  << epi_num
                  << t_day
                  << view_num
                  << like_num;

            toonList_model->appendRow(items);
        }
    }
    ui->epiList_tableView->setModel(toonList_model);
    ui->epiList_tableView->resizeColumnsToContents();
    ui->epiList_tableView->hideColumn(0);
    ui->epiList_tableView->hideColumn(1);
    ui->epiList_tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->epiList_tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->epiList_tableView->show();
    if(!(bmark_back_btn_clicked))
    {
        ui->stackedWidget->setCurrentWidget(ui->toonList_page);
    }
    bmark_back_btn_clicked = false;
}

void MainWindow::thumbnail_to_item(QByteArray &img_buf)
{
    QPixmap thumbnailPixmap;
    thumbnailPixmap.loadFromData(img_buf);
    QPixmap resizedPixmap = thumbnailPixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    thumbnail_list.append(resizedPixmap);
}

void MainWindow::create_toonInfo_model(QString &toonlist)
{
    QStringList str_list = toonlist.split("\n");
    QStandardItem *num, *title, *author, *day;
    int index = 0;

    toonInfo_model = new QStandardItemModel();
    toonInfo_model->setColumnCount(5);
    toonInfo_model->setHorizontalHeaderLabels(QStringList()<<"번호"<< "썸네일" << "제목" << "작가"<< "요일");

    for (const QString &row: str_list)
    {
        QStringList columns = row.split("/");
        if (columns.size() == 4)
        {
            num = new QStandardItem(columns[0].trimmed());
            title = new QStandardItem(columns[1].trimmed());
            author = new QStandardItem(columns[2].trimmed());
            day = new QStandardItem(columns[3].trimmed());

            QStandardItem *thumbnail_item = new QStandardItem();
            thumbnail_item->setIcon(QIcon(thumbnail_list[index++]));

            title->setTextAlignment(Qt::AlignCenter);
            author->setTextAlignment(Qt::AlignCenter);
            day->setTextAlignment(Qt::AlignCenter);

            QList<QStandardItem*> items;
            items << num
                  << thumbnail_item
                  << title
                  << author
                  << day;
            toonInfo_model->appendRow(items);
        }
    }

    ui->e_tableView->setModel(toonInfo_model);
    ui->e_tableView->setIconSize(QSize(100, 100));
    ui->e_tableView->resizeColumnsToContents();
    ui->e_tableView->resizeRowsToContents();
    ui->e_tableView->hideColumn(0);
    ui->e_tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->e_tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->e_tableView->show();
    create_day_view();
}


void MainWindow::send_toon_info(int type, QString str)
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

            switch (type) {
            case TOONINFO:
                header.prepend(QString("fileType:tooninfo,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
                break;
            case TOONLIST:
                header.prepend(QString("fileType:toonlist,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
                break;
            case TOONIMAGE:
                header.prepend(QString("fileType:toonimage,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
                break;
            case BOOKMARK:
                header.prepend(QString("fileType:bookmark,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
                break;
            case BOOKMARKLIST:
                header.prepend(QString("fileType:bookmarklist,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
                break;
            case TOONLIKE:
                header.prepend(QString("fileType:toonlike,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
                break;
            case EPICHANGE:
                header.prepend(QString("fileType:epichange,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
                break;
            case TOONINFOTEXT:
                header.prepend(QString("fileType:tooninfotext,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
                break;
            default:
                break;
            }

            header.resize(128);
            // message 인코딩 설정하고, QByteArray에 할당하고
            QByteArray byteArray = str.toUtf8();
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
void MainWindow::send_user_info(int type, QString id = "", QString pw = "", QString phone_num = "", QString email= "")
{
    if(m_socket)
    {
        if(m_socket->isOpen())
        {
            // ui에서 입력할 message를 가져와
            QString str = id + "," + pw + "," + phone_num + "," + email;

            // stream으로 보내는데
            QDataStream socketStream(m_socket);
            socketStream.setVersion(QDataStream::Qt_5_15);

            // 헤더 부분에 fileType을 message로 설정한다.
            QByteArray header;

            switch (type) {
            case LOGIN:
                header.prepend(QString("fileType:login,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
                break;
            case SIGNUP:
                header.prepend(QString("fileType:signUp,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
                break;
            case IDSEARCH:
                header.prepend(QString("fileType:idSearch,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
                break;
            case PWSEARCH:
                header.prepend(QString("fileType:pwSearch,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
                break;
            case IDDUPCHK:
                header.prepend(QString("fileType:idDupChk,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
                break;
            case PNUMDUPCHK:
                header.prepend(QString("fileType:pNumDupChk,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
                break;
            default:
                break;
            }

            header.resize(128);
            // message 인코딩 설정하고, QByteArray에 할당하고
            QByteArray byteArray = str.toUtf8();
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
//============================================================================================================


// [ex.02.12]
void MainWindow::slot_displayMessage(const QString& str)
{
    ui->textBrowser_receivedMessages->append(str);
}

void MainWindow::on_toList_backBtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->main_page);
}


void MainWindow::on_backList_btn_clicked()
{
    send_toon_info(TOONLIST, toonInfo_data);
    // 동적으로 만든 imglabel 해제
    for (QLabel *imgLabel : imgLabel_list)
    {
        delete imgLabel;
    }
    imgLabel_list.clear(); // 리스트 요소 클리어
    ui->toon_info_text_label->setText("");
}

void MainWindow::on_logout_btn_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("로그아웃");
    msgBox.setText("로그아웃 하시겠습니까?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No); // 기본 선택은 '아니오'

    // 사용자 응답 처리
    if (msgBox.exec() == QMessageBox::Yes) {
        // 예를 선택하면 로그아웃 처리
        ui->toon_info_text_label->setText("");
        this->window()->hide();
        loginWidget->show();
    }

}

void MainWindow::on_bListMove_btn_clicked()
{
    bmark_back_btn_clicked = true;
    send_toon_info(TOONLIST, toonInfo_data);
    // 동적으로 만든 imglabel 해제
    for (QLabel *imgLabel : imgLabel_list)
    {
        delete imgLabel;
    }
    imgLabel_list.clear(); // 리스트 요소 클리어
    ui->toon_info_text_label->setText("");
    ui->stackedWidget->setCurrentWidget(ui->main_page);
    ui->mainTabWidget->setCurrentIndex(3);
}

