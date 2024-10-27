#include "mainwindow.h"
#include "ui_mainwindow.h"

// [ex.02.1]
// MainWindow 생성자 실행
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_server = new QTcpServer();



    // [ex.02.1.1]
    // 생성자 실행과 동시에 m_server의 listening을 시작하고
    // newMessage 가 들어오면, slot_displayMessage 실행하여 UI에 출력
    if(m_server->listen(QHostAddress::Any, 8080))
    {
        // [ex.02.1.3]
        // 서버로 클라이언트의 새 연결 요청이 들어오면,
        // slot_newConnection 슬롯 실행하여 대기중인 요청 처리
        connect(m_server, &QTcpServer::newConnection,
                this,     &MainWindow::slot_newConnection);

        // [ex.02.1.4]
        // signal_newMessage 시그널이 발생하면 (서버 socket read 가 아닌, MainWindow 시그널)
        // slot_displayMessage 실행하여 UI에 출력
        connect(this, &MainWindow::singal_newMessage,
                this, &MainWindow::slot_displayMessage);

        // [ex.02.1.5]
        // 상태바(하단 출력) 서버 실행 상태 표시
        ui->statusBar->showMessage("Server is listening...");
    }
    // [ex.02.1.2]
    // listening 실행이 안되면 실행
    else
    {
        QMessageBox::critical(this,"QTCPServer",QString("Unable to start the server: %1.").arg(m_server->errorString()));
        exit(EXIT_FAILURE);
    }

    initializeDataBase(); // DB 연결하는 함수!!!
}

// [ex.02.2]
MainWindow::~MainWindow()
{
    // 서버에 연결된 모든 연결 소켓 해제
    foreach (QTcpSocket* socket, qset_connectedSKT)
    {
        socket->close();
        socket->deleteLater();
    }
    // 서버 소켓 해제
    m_server->close();
    m_server->deleteLater();

    foreach (Client* client, login_clnt_list)
    {
        delete client;
    }
    login_clnt_list.clear();

    QSqlQuery qry;
    qry.prepare("UPDATE shop SET s_state = :state");
    qry.bindValue(":state", "영업대기");
    if(!qry.exec())
    {
        qDebug() << "DB 가게 상태 변경 오류";
    }

    delete ui;
}

bool MainWindow::initializeDataBase() // DB 연결 함수
{
    m_db = QSqlDatabase::addDatabase("QODBC");
    m_db.setHostName("127.0.0.1");
    m_db.setDatabaseName("delivery");
    m_db.setUserName("root");
    m_db.setPassword("1234");

    if( !m_db.open() ) {
        qDebug() << Q_FUNC_INFO << m_db.lastError().text();
        return false;
    }
    else
    {
        qDebug() << "연결 성공\n";
        return true;
    }

}

// [ex.02.3]
void MainWindow::slot_newConnection()
{
    // appendToSocketList 함수로 연결 객체 관리 처리
    while (m_server->hasPendingConnections())
        appendToSocketList(m_server->nextPendingConnection());
}

// [ex.02.4]
void MainWindow::appendToSocketList(QTcpSocket* socket)
{
    // [ex.02.4.1]
    // 연결된 소켓을 qset으로 관리
    qset_connectedSKT.insert(socket);

    // [ex.02.4.2]
    // 연결된 소켓에 read 할 데이터가 들어오면,
    // 이 객체의(MainWindow) slot_readSocket 실행하여 처리
    connect(socket, &QTcpSocket::readyRead,
            this,   &MainWindow::slot_readSocket);

    // [ex.02.4.3]
    // 연결된 소켓과 연결이 해제되면,
    // 이 객체의(MainWindow) slot_discardSocket 슬롯 함수 실행하여 처리
    connect(socket, &QTcpSocket::disconnected,
            this,   &MainWindow::slot_discardSocket);

    // [ex.02.4.4]
    // 연결된 소켓에 문제가 발생하면,
    // 이 객체의(MainWindow) slot_displayError 슬롯 함수 실행하여 처리
    connect(socket, &QAbstractSocket::errorOccurred,
            this,   &MainWindow::slot_displayError);

    // [ex.02.4.5]
    // 소켓 디스크립터로 대상 선택 가능하도록 ui 표시
    ui->comboBox_receiver->addItem(QString::number(socket->socketDescriptor()));

    // [ex.02.4.6]
    // 연결된 클라이언트 정보와, 소켓 디스크립터(정수 식별자) 출력
    slot_displayMessage(QString("INFO :: Client with sockd:%1 has just entered the room").arg(socket->socketDescriptor()));
}

// [ex.02.5]
// 연결된 소켓에서 연결이 끊어지면 동작
void MainWindow::slot_discardSocket()
{
    // 연결된 socket 의 disconnected 시그널을 발생시킨 socket 객체를 찾아서
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());

    // 해당 소켓을 qset_connectedSKT 에서 제거하고, 메시지 출력
    QSet<QTcpSocket*>::iterator it = qset_connectedSKT.find(socket);
    if (it != qset_connectedSKT.end()){
        slot_displayMessage(QString("INFO :: A client has just left the room").arg(socket->socketDescriptor()));
        qset_connectedSKT.remove(*it);
    }

    for (int i = 0; i < login_clnt_list.size(); i++)
    {
        if (login_clnt_list[i]->clnt_socket == socket)
        {
            if (login_clnt_list[i]->type == SHOP)
            {
                QSqlQuery qry;
                qry.prepare("UPDATE shop SET s_state = :state WHERE s_num = :s_num");
                qry.bindValue(":state", "영업대기");
                qry.bindValue(":s_num", login_clnt_list[i]->clnt_num);
                if(!qry.exec())
                {
                    qDebug() << "DB 가게 상태 변경 오류";
                }
                foreach (Client *client, login_clnt_list)
                {
                    if (client->type == USER)
                    {
                        sendMessage(client->clnt_socket, SHOPLOGOUT);
                    }
                }
            }

            delete login_clnt_list[i];
            login_clnt_list.removeAt(i);
        }
    }
    // ui 콤보박스 재설정
    refreshComboBox();

    socket->deleteLater();
}

// [ex.02.6]
// 연결된 소켓에서 에러 발생하면 출력
void MainWindow::slot_displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, "QTCPServer", "The host was not found. Please check the host name and port settings.");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, "QTCPServer", "The connection was refused by the peer. Make sure QTCPServer is running, and check that the host name and port settings are correct.");
        break;
    default:
        QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
        QMessageBox::information(this, "QTCPServer", QString("The following error occurred: %1.").arg(socket->errorString()));
        break;
    }
}

// [ex.02.7]
// 클라이언트가 보낸 데이터를 소켓을 통해 읽고, 메시지인지 파일인지 확인한 후에 처리하는 함수
void MainWindow::slot_readSocket()
{
    // [ex.02.7.1]
    // sender() 함수를 사용하여 데이터를 보낸 소켓(QTcpSocket*)을 찾아서 포인터로 변환.
    // 이 소켓이 실제로 데이터를 보낸 클라이언트의 소켓.
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());

    while (socket->bytesAvailable())
    {

        // [ex.02.7.2]
        // 클라이언트로부터 수신한 데이터를 임시로 저장할 QByteArray 타입의 buffer를 생성.
        QByteArray buffer;

        // [ex.02.7.3]
        // QDataStream을 사용하여 소켓으로부터 데이터를 읽어들임.
        // 데이터 스트림에서 버전을 설정하는 이유는 서버와 클라이언트가 같은 Qt 버전을 사용해 데이터 형식을 호환하도록 하기 위함.
        QDataStream socketStream(socket);
        socketStream.setVersion(QDataStream::Qt_5_15);

        //  startTransaction()은 데이터의 완전성을 보장하기 위한 작업으로,  데이터를 읽는 동안 문제가 발생하면 롤백할 수 있음.
        socketStream.startTransaction();

        // 소켓으로부터 데이터를 읽어 buffer에 저장함.
        socketStream >> buffer;
        qDebug() << buffer;
        // 데이터를 모두 읽지 못한 경우(예: 데이터가 아직 모두 도착하지 않았을 때) 트랜잭션을 완료하지 않고 데이터를 기다리겠다는 메시지를 출력함.
        // commitTransaction()은 트랜잭션이 성공적으로 완료되었는지 확인하는 함수.
        if (!socketStream.commitTransaction())
        {
            // 소켓의 고유 소켓 디스크립터를 사용해 어떤 소켓이 데이터를 보내는지 식별하고, 대기 중이라는 메시지 시그널 emit.
            QString message = QString("%1 :: Waiting for more data to come..").arg(socket->socketDescriptor());
            emit singal_newMessage(message);
            return;
        }

        // [ex.02.7.4]
        // mid(0, 128)을 통해 buffer의 처음 128바이트를 추출하여 header 변수에 저장함.
        QString header = buffer.mid(0,128);


        // 콤마(,)와 콜론(:)으로 분리하여 fileType을 추출.
        QString fileType = header.split(",")[0].split(":")[1];
        QString sender_str = header.split(",")[1].split(":")[1];
        QString sender_num_str = header.split(",")[2].split(":")[1];
        QString receiver_str = header.split(",")[3].split(":")[1];
        QString receiver_num_str = header.split(";")[0].split(",")[4].split(":")[1];
        int sender = sender_str.toInt();
        int receiver = receiver_str.toInt();
        int sender_num = sender_num_str.toInt();
        int receiver_num = receiver_num_str.toInt();

        // 128바이트 이후부터는 실제 파일 혹은 메시지이므로 buffer에서 그 부분만 남김.
        buffer = buffer.mid(128);

        QString msg = buffer;
        QString id, pw, phone_num;
        QString o_text, o_price, o_addr, u_id, s_num, o_request, o_num, u_num;
        QSqlQuery qry;
        QSqlQuery qry2;
        QStringList msgParts;


        if (fileType == "login")
        {
            msgParts = msg.split(",");
            id = msgParts[0];
            pw = msgParts[1];

            if (sender == USER)
            {
                qry.prepare("SELECT u_num FROM user WHERE u_id = :id AND u_pw = :pw");
                qry.bindValue(":id", id);
                qry.bindValue(":pw", pw);
                qry.exec();

                if (qry.next()) // 아이디 비밀번호 일치
                {
                    login_clnt_list.append(new Client(USER, qry.value(0).toInt(), socket, id));
                    sendMessage(socket, LOGININFO, "login success", USER, qry.value(0).toInt());
                }
                else // 아이디 or 비밀번호 불일치
                {
                    sendMessage(socket, LOGININFO, "login fail");
                }

            }
            else if (sender == SHOP)
            {
                qry.prepare("SELECT s_num FROM shop WHERE s_id = :id AND s_pw = :pw");
                qry.bindValue(":id", id);
                qry.bindValue(":pw", pw);
                qry.exec();

                if (qry.next()) // 아이디 비밀번호 일치
                {
                    login_clnt_list.append(new Client(SHOP, qry.value(0).toInt(), socket, id));
                    sendMessage(socket, LOGININFO, "login success", SHOP, qry.value(0).toInt());

                    qry2.prepare("UPDATE shop SET s_state = :state WHERE s_id = :id");
                    qry2.bindValue(":state", "영업중");
                    qry2.bindValue(":id", id);
                    if(!qry2.exec())
                    {
                        qDebug() << "DB 가게 상태 변경 오류";
                    }

                    foreach (Client *client, login_clnt_list)
                    {
                        if (client->type == USER)
                        {
                            sendMessage(client->clnt_socket, SHOPLOGOUT);
                        }
                    }
                }
                else // 아이디 or 비밀번호 불일치
                {
                    sendMessage(socket, LOGININFO, "login fail");
                }

            }
            else if (sender == RIDER)
            {
                qry.prepare("SELECT r_num FROM rider WHERE r_id = :id AND r_pw = :pw");
                qry.bindValue(":id", id);
                qry.bindValue(":pw", pw);
                qry.exec();

                if (qry.next()) // 아이디 비밀번호 일치
                {
                    login_clnt_list.append(new Client(RIDER, qry.value(0).toInt(), socket, id));
                    sendMessage(socket, LOGININFO, "login success", RIDER, qry.value(0).toInt());
                }
                else // 아이디 or 비밀번호 불일치
                {
                    sendMessage(socket, LOGININFO, "login fail");
                }

            }
        }
        else if (fileType == "signUp")
        {
            msgParts = msg.split(",");
            id = msgParts[0];
            pw = msgParts[1];
            phone_num = msgParts[2];

            if (sender == USER)
            {
                qry.prepare("INSERT INTO user "
                            "(u_id, u_pw, u_pnum) "
                            "VALUES "
                            "(:id, :pw, :pnum)");

                qry.bindValue(":id", id);
                qry.bindValue(":pw", pw);
                qry.bindValue(":pnum", phone_num);

                if(qry.exec())
                {
                    sendMessage(socket, SIGNUPINFO, "signUp success");
                }
                else
                {
                    sendMessage(socket, SIGNUPINFO, "signUp error");
                }
            }
            else if (sender == RIDER)
            {
                qry.prepare("INSERT INTO rider "
                            "(r_id, r_pw, r_pnum) "
                            "VALUES "
                            "(:id, :pw, :pnum)");

                qry.bindValue(":id", id);
                qry.bindValue(":pw", pw);
                qry.bindValue(":pnum", phone_num);

                if(qry.exec())
                {
                    sendMessage(socket, SIGNUPINFO, "signUp success");
                }
                else
                {
                    sendMessage(socket, SIGNUPINFO, "signUp error");
                }
            }

        }
        else if (fileType == "idDupChk")
        {
            msgParts = msg.split(",");
            id = msgParts[0];

            if (sender == USER)
            {
                // 아이디 중복 확인
                qry.prepare("SELECT * FROM user WHERE u_id = :id");
                qry.bindValue(":id", id);
                qry.exec();

                if (qry.next()) // 중복일 경우
                {
                    sendMessage(socket, SIGNUPINFO, "signUp idDup");
                }
                else // 중복이 아닌 경우
                {
                    sendMessage(socket, SIGNUPINFO, "signUp !idDup");
                }
            }
            else if (sender == RIDER)
            {
                // 아이디 중복 확인
                qry.prepare("SELECT * FROM rider WHERE r_id = :id");
                qry.bindValue(":id", id);
                qry.exec();

                if (qry.next()) // 중복일 경우
                {
                    sendMessage(socket, SIGNUPINFO, "signUp idDup");
                }
                else // 중복이 아닌 경우
                {
                    sendMessage(socket, SIGNUPINFO, "signUp !idDup");
                }
            }

        }
        else if (fileType == "pNumDupChk")
        {
            msgParts = msg.split(",");
            phone_num = msgParts[2];

            if (sender == USER)
            {
                // 휴대폰 번호 중복 확인
                qry.prepare("SELECT * FROM user WHERE u_pnum = :phone_num");
                qry.bindValue(":phone_num", phone_num);
                qry.exec();

                if (qry.next()) // 중복일 경우
                {
                    sendMessage(socket, SIGNUPINFO, "signUp phoneNumDup");
                }
                else // 중복이 아닌 경우
                {
                    sendMessage(socket, SIGNUPINFO, "signUp !phoneNumDup");
                }
            }
            else if (sender == RIDER)
            {
                // 휴대폰 번호 중복 확인
                qry.prepare("SELECT * FROM rider WHERE r_pnum = :phone_num");
                qry.bindValue(":phone_num", phone_num);
                qry.exec();

                if (qry.next()) // 중복일 경우
                {
                    sendMessage(socket, SIGNUPINFO, "signUp phoneNumDup");
                }
                else // 중복이 아닌 경우
                {
                    sendMessage(socket, SIGNUPINFO, "signUp !phoneNumDup");
                }
            }
        }
        else if (fileType == "logout")
        {
            for (int i = 0; i < login_clnt_list.size(); i++)
            {
                if (login_clnt_list[i]->type == sender && login_clnt_list[i]->clnt_num == sender_num)
                {
                    delete login_clnt_list[i];
                    login_clnt_list.removeAt(i);
                }
            }
            if (sender == SHOP)
            {
                qry.prepare("UPDATE shop SET s_state = :state WHERE s_num = :s_num");
                qry.bindValue(":state", "영업대기");
                qry.bindValue(":s_num", sender_num);
                if(!qry.exec())
                {
                    qDebug() << "DB 가게 상태 변경 오류";
                }

                foreach (Client *client, login_clnt_list)
                {
                    if (client->type == USER)
                    {
                        sendMessage(client->clnt_socket, SHOPLOGOUT);
                    }
                }

            }
        }
        else if (fileType == "category")
        {
            qry.prepare("SELECT c_img FROM category");
            if (qry.exec())
            {
                while(qry.next())
                {
                    QString imagePath = qry.value(0).toString().remove("\""); // 쌍따옴표 제거
                    QFile file(imagePath); // 이미지 파일 열기
                    if (file.open(QIODevice::ReadOnly))
                    {
                        QByteArray imageData = file.readAll();
                        QByteArray header;
                        header.prepend(QString("fileType:categoryImg,sender:%1,senderNum:%2,receiver:%3,recieverNum:%4;").toUtf8());
                        header.resize(128);
                        // 헤더와 이미지 데이터 합치기
                        QByteArray image_info = header + imageData;
                        socketStream << image_info;
                    }
                    else
                    {
                        qDebug() << "파일 오픈 실패:" << imagePath;
                    }
                }
            }
            else
            {
                qDebug() << "쿼리실행 실패" << qry.lastError().text();
            }
        }
        else if (fileType == "shoptitle")
        {
            qry.prepare("SELECT s_title FROM shop WHERE s_num = :s_num");
            qry.bindValue(":s_num", sender_num);

            if (qry.exec() && qry.next())
            {
                QString s_title = qry.value(0).toString();
                sendMessage(socket, SHOPTITLE, s_title);
            }
            else
            {
                qDebug() << "쿼리실행 실패" << qry.lastError().text();
            }
        }
        else if (fileType == "shoplist")
        {
            QStringList shop_info_list;
            QString shop_info_str;
            QStringList imagePaths;

            qry.prepare("SELECT * FROM shop");

            if (qry.exec())
            {
                while(qry.next())
                {
                    QString s_num = qry.value(0).toString();
                    QString s_title = qry.value(4).toString();
                    QString s_type = qry.value(5).toString();
                    QString s_state = qry.value(6).toString();
                    shop_info_list << QString("%1/%2/%3/%4").arg(s_num, s_title, s_type, s_state);
                    imagePaths.append(qry.value(7).toString());
                }
                for (QString &imagePath : imagePaths)
                {
                    imagePath = imagePath.remove("\""); // 쌍따옴표 제거
                    QFile file(imagePath); // 이미지 파일 열기
                    if (file.open(QIODevice::ReadOnly))
                    {
                        QByteArray imageData = file.readAll();
                        QByteArray header;
                        header.prepend(QString("fileType:shopImg,sender:%1,senderNum:%2,receiver:%3,recieverNum:%4;").toUtf8());
                        header.resize(128);
                        // 헤더와 이미지 데이터 합치기
                        QByteArray image_info = header + imageData;
                        socketStream << image_info;
                    }
                    else
                    {
                        // 파일을 열 수 없는 경우 에러 처리
                        qDebug() << "파일 오픈 실패:" << imagePath;
                    }
                }
                shop_info_str = shop_info_list.join("\n");
                sendMessage(socket, SHOPLIST, shop_info_str);
                qDebug() << "서버 가게 리스트" << shop_info_str;
            }
            else
            {
                qDebug() << "쿼리실행 실패" << qry.lastError().text();
            }
        }
        else if (fileType == "menulist")
        {
            QStringList menu_info_list;
            QString menu_info_str;
            QStringList imagePaths;

            qry.prepare("SELECT * FROM menu");

            if (qry.exec())
            {
                while(qry.next())
                {
                    QString m_num = qry.value(0).toString();
                    QString s_num = qry.value(1).toString();
                    QString s_mnum = qry.value(2).toString();
                    QString m_title = qry.value(3).toString();
                    QString m_price = qry.value(4).toString();
                    menu_info_list << QString("%1/%2/%3/%4/%5").arg(m_num, s_num, s_mnum, m_title, m_price);
                    imagePaths.append(qry.value(5).toString());
                }
                for (QString &imagePath : imagePaths)
                {
                    imagePath = imagePath.remove("\""); // 쌍따옴표 제거
                    QFile file(imagePath); // 이미지 파일 열기
                    if (file.open(QIODevice::ReadOnly))
                    {
                        QByteArray imageData = file.readAll();
                        QByteArray header;
                        header.prepend(QString("fileType:menuImg,sender:%1,senderNum:%2,receiver:%3,recieverNum:%4;").toUtf8());
                        header.resize(128);
                        // 헤더와 이미지 데이터 합치기
                        QByteArray image_info = header + imageData;
                        socketStream << image_info;
                    }
                    else
                    {
                        // 파일을 열 수 없는 경우 에러 처리
                        qDebug() << "파일 오픈 실패:" << imagePath;
                    }
                }
                menu_info_str = menu_info_list.join("\n");
                sendMessage(socket, MENULIST, menu_info_str);
                qDebug() << "서버 메뉴 리스트" << menu_info_str;
            }
            else
            {
                qDebug() << "쿼리실행 실패" << qry.lastError().text();
            }
        }
        else if (fileType == "userorder")
        {
            msgParts = msg.split("/");
            o_text = msgParts[0];
            o_price = msgParts[1];
            o_addr = msgParts[2];
            o_request = msgParts[3];
            u_id = msgParts[4];

            foreach (Client * client, login_clnt_list)
            {
                if (client->type == SHOP && client->clnt_num == receiver_num)
                {
                    qry.prepare("INSERT INTO ordertable "
                                "(o_text, o_price, o_addr, u_num, s_num, o_request) "
                                "VALUES "
                                "(:text, :price, :addr, :u_num, :s_num, :request)");
                    qry.bindValue(":text", o_text);
                    qry.bindValue(":price", o_price.toInt());
                    qry.bindValue(":addr", o_addr);
                    qry.bindValue(":u_num", sender_num);
                    qry.bindValue(":s_num", receiver_num);
                    qry.bindValue(":request", o_request);

                    if(qry.exec())
                    {
                        sendMessage(client->clnt_socket, USERORDER);
                    }
                    else
                    {
                        qDebug() << "주문정보 insert 오류" << qry.lastError().text();
                        return;
                    }
                }
            }
        }
        else if (fileType == "uOrderList")
        {

            QStringList order_list;
            QString order_list_str;
            qry.prepare("SELECT o.*, s.s_title, u.u_id FROM delivery.ordertable o "
                        "JOIN delivery.shop s ON o.s_num = s.s_num "
                        "JOIN delivery.user u on o.u_num = u.u_num "
                        "WHERE o.u_num = :u_num AND o.o_state != :o_stateA AND o.o_state != :o_stateB");
            qry.bindValue(":u_num", sender_num);
            qry.bindValue(":o_stateA", "주문거절");
            qry.bindValue(":o_stateB", "배달완료");

            if (qry.exec())
            {
                while(qry.next())
                {
                    QString o_num = qry.value(0).toString();
                    QString o_text = qry.value(1).toString();
                    QString o_price = qry.value(2).toString();
                    QString o_addr = qry.value(3).toString();
                    QString u_num = qry.value(4).toString();
                    QString s_num = qry.value(5).toString();
                    QString r_num = qry.value(6).toString();
                    QString o_state = qry.value(7).toString();
                    QString o_request = qry.value(8).toString();
                    QString s_title = qry.value(9).toString();
                    QString u_id = qry.value(10).toString();

                    order_list << QString("%1/%2/%3/%4/%5/%6/%7/%8/%9/%10/%11")
                                      .arg(o_num, o_text, o_price, o_addr, u_num, s_num, r_num, o_state, o_request, s_title, u_id);
                }
                if (order_list.size() != 0)
                {
                    order_list_str = order_list.join("@");
                    sendMessage(socket, UORDERLIST, order_list_str);
                }
            }
            else
            {
                qDebug() << "쿼리실행 실패" << qry.lastError().text();
            }
        }
        else if (fileType == "sOrderListW")
        {
            QStringList order_list;
            QString order_list_str;

            qry.prepare("SELECT o.*, s.s_title, u.u_id FROM delivery.ordertable o "
                         "JOIN delivery.shop s ON o.s_num = s.s_num "
                         "JOIN delivery.user u on o.u_num = u.u_num "
                         "WHERE o.s_num = :s_num AND o.o_state = :o_state");
            qry.bindValue(":s_num", sender_num);
            qry.bindValue(":o_state", "주문대기");

            if (qry.exec())
            {
                while(qry.next())
                {
                    QString o_num = qry.value(0).toString();
                    QString o_text = qry.value(1).toString();
                    QString o_price = qry.value(2).toString();
                    QString o_addr = qry.value(3).toString();
                    QString u_num = qry.value(4).toString();
                    QString s_num = qry.value(5).toString();
                    QString r_num = qry.value(6).toString();
                    QString o_state = qry.value(7).toString();
                    QString o_request = qry.value(8).toString();
                    QString s_title = qry.value(9).toString();
                    QString u_id = qry.value(10).toString();


                    order_list << QString("%1/%2/%3/%4/%5/%6/%7/%8/%9/%10/%11")
                                      .arg(o_num, o_text, o_price, o_addr, u_num, s_num, r_num, o_state, o_request, s_title, u_id);
                }
                if (!order_list.isEmpty())
                {
                    order_list_str = order_list.join("@");
                    sendMessage(socket, SORDERLIST_WAITING, order_list_str);
                }
            }
            else
            {
                qDebug() << "쿼리실행 실패" << qry.lastError().text();
            }
        }
        else if (fileType == "sOrderListE")
        {
            QStringList order_list;
            QString order_list_str;

            qry.prepare("SELECT o.*, s.s_title, u.u_id FROM delivery.ordertable o "
                        "JOIN delivery.shop s ON o.s_num = s.s_num "
                        "JOIN delivery.user u on o.u_num = u.u_num "
                        "WHERE o.s_num = :s_num AND o.o_state != :o_stateA AND o.o_state != :o_stateB");
            qry.bindValue(":s_num", sender_num);
            qry.bindValue(":o_stateA", "주문대기");
            qry.bindValue(":o_stateB", "주문거절");


            if (qry.exec())
            {
                while(qry.next())
                {
                    QString o_num = qry.value(0).toString();
                    QString o_text = qry.value(1).toString();
                    QString o_price = qry.value(2).toString();
                    QString o_addr = qry.value(3).toString();
                    QString u_num = qry.value(4).toString();
                    QString s_num = qry.value(5).toString();
                    QString r_num = qry.value(6).toString();
                    QString o_state = qry.value(7).toString();
                    QString o_request = qry.value(8).toString();
                    QString s_title = qry.value(9).toString();
                    QString u_id = qry.value(10).toString();


                    order_list << QString("%1/%2/%3/%4/%5/%6/%7/%8/%9/%10/%11")
                                      .arg(o_num, o_text, o_price, o_addr, u_num, s_num, r_num, o_state, o_request, s_title, u_id);
                }
                if (!order_list.isEmpty())
                {
                    order_list_str = order_list.join("@");
                    sendMessage(socket, SORDERLIST_ENTIRE, order_list_str);
                }
            }
            else
            {
                qDebug() << "쿼리실행 실패" << qry.lastError().text();
            }
        }
        else if (fileType == "orderAccept")
        {
            qry.prepare("UPDATE ordertable SET o_state = :o_state WHERE o_num = :o_num");
            qry.bindValue(":o_state", "배달대기");
            qry.bindValue(":o_num", msg.toInt());
            if (!qry.exec())
            {
                qDebug() << "주문상태 업데이트 오류:" << qry.lastError().text();
                return;
            }

            foreach (Client *client, login_clnt_list)
            {
                if (client->type == RIDER)
                {
                    sendMessage(client->clnt_socket, PUTDELIVERY, "", SHOP, sender_num);
                }
                if (client->type == USER && client->clnt_num == receiver_num)
                {
                    sendMessage(client->clnt_socket, ORDERACCEPT, "", SHOP, sender_num);
                }
            }
        }
        else if (fileType == "orderDeny")
        {
            qry.prepare("UPDATE ordertable SET o_state = :o_state WHERE o_num = :o_num");
            qry.bindValue(":o_state", "주문거절");
            qry.bindValue(":o_num", msg.toInt());
            if (!qry.exec())
            {
                qDebug() << "주문상태 업데이트 오류:" << qry.lastError().text();
                return;
            }

            foreach (Client *client, login_clnt_list)
            {
                if (client->type == USER && client->clnt_num == receiver_num)
                {
                    sendMessage(client->clnt_socket, ORDERDENY, "", SHOP, sender_num);
                }
            }
        }
        else if (fileType == "deliveryList")
        {
            QStringList order_list;
            QString order_list_str;

            qry.prepare("SELECT o.*, s.s_title, u.u_id FROM delivery.ordertable o "
                         "JOIN delivery.shop s ON o.s_num = s.s_num "
                         "JOIN delivery.user u on o.u_num = u.u_num "
                         "WHERE o.o_state = :o_state");
            qry.bindValue(":o_state", "배달대기");

            if (qry.exec())
            {
                while(qry.next())
                {
                    QString o_num = qry.value(0).toString();
                    QString o_text = qry.value(1).toString();
                    QString o_price = qry.value(2).toString();
                    QString o_addr = qry.value(3).toString();
                    QString u_num = qry.value(4).toString();
                    QString s_num = qry.value(5).toString();
                    QString r_num = qry.value(6).toString();
                    QString o_state = qry.value(7).toString();
                    QString o_request = qry.value(8).toString();
                    QString s_title = qry.value(9).toString();
                    QString u_id = qry.value(10).toString();


                    order_list << QString("%1/%2/%3/%4/%5/%6/%7/%8/%9/%10/%11")
                                      .arg(o_num, o_text, o_price, o_addr, u_num, s_num, r_num, o_state, o_request, s_title, u_id);
                }
                if (!order_list.isEmpty())
                {
                    order_list_str = order_list.join("@");
                    sendMessage(socket, DELIVERYLIST, order_list_str);
                }
            }
            else
            {
                qDebug() << "쿼리실행 실패" << qry.lastError().text();
            }
        }
        else if (fileType == "deliAccept")
        {
            msgParts = msg.split("/");
            o_num = msgParts[0];
            u_num = msgParts[1];
            s_num = msgParts[2];

            qry.prepare("UPDATE ordertable "
                        "SET r_num = :r_num, o_state = :o_state "
                        "WHERE o_num = :o_num");
            qry.bindValue(":r_num", sender_num);
            qry.bindValue(":o_state", "배달중");
            qry.bindValue(":o_num", o_num.toInt());
            if (!qry.exec())
            {
                qDebug() << "주문상태 업데이트 오류:" << qry.lastError().text();
                return;
            }

            foreach (Client *client, login_clnt_list)
            {
                if (client->type == USER && client->clnt_num == u_num.toInt())
                {
                    sendMessage(client->clnt_socket, DELIACCEPT, "", RIDER, sender_num, USER, u_num.toInt());
                }
                else if (client->type == SHOP && client->clnt_num == s_num.toInt())
                {
                    sendMessage(client->clnt_socket, DELIACCEPT, "", RIDER, sender_num, SHOP, s_num.toInt());
                }
                else if (client->type == RIDER)
                {
                    sendMessage(client->clnt_socket, DELIACCEPT, "", RIDER, sender_num, RIDER);
                }
            }
        }
        else if (fileType == "deliAcceptList")
        {
            QStringList order_list;
            QString order_list_str;

            qry.prepare("SELECT o.*, s.s_title, u.u_id FROM delivery.ordertable o "
                        "JOIN delivery.shop s ON o.s_num = s.s_num "
                        "JOIN delivery.user u on o.u_num = u.u_num "
                        "WHERE o.o_state = :o_state AND o.r_num = :r_num");
            qry.bindValue(":o_state", "배달중");
            qry.bindValue(":r_num", sender_num);

            if (qry.exec())
            {
                while(qry.next())
                {
                    QString o_num = qry.value(0).toString();
                    QString o_text = qry.value(1).toString();
                    QString o_price = qry.value(2).toString();
                    QString o_addr = qry.value(3).toString();
                    QString u_num = qry.value(4).toString();
                    QString s_num = qry.value(5).toString();
                    QString r_num = qry.value(6).toString();
                    QString o_state = qry.value(7).toString();
                    QString o_request = qry.value(8).toString();
                    QString s_title = qry.value(9).toString();
                    QString u_id = qry.value(10).toString();


                    order_list << QString("%1/%2/%3/%4/%5/%6/%7/%8/%9/%10/%11")
                                      .arg(o_num, o_text, o_price, o_addr, u_num, s_num, r_num, o_state, o_request, s_title, u_id);
                }
                if (!order_list.isEmpty())
                {
                    order_list_str = order_list.join("@");
                    sendMessage(socket, DELIACCEPTLIST, order_list_str);
                }
            }
            else
            {
                qDebug() << "쿼리실행 실패" << qry.lastError().text();
            }
        }
        else if (fileType == "deliComplete")
        {
            msgParts = msg.split("/");
            o_num = msgParts[0];
            u_num = msgParts[1];
            s_num = msgParts[2];

            qry.prepare("UPDATE ordertable "
                        "SET o_state = :o_state "
                        "WHERE o_num = :o_num");
            qry.bindValue(":o_state", "배달완료");
            qry.bindValue(":o_num", o_num.toInt());
            if (!qry.exec())
            {
                qDebug() << "주문상태 업데이트 오류:" << qry.lastError().text();
                return;
            }

            foreach (Client *client, login_clnt_list)
            {
                if (client->type == USER && client->clnt_num == u_num.toInt())
                {
                    sendMessage(client->clnt_socket, DELICOMPLETE, "", RIDER, sender_num, USER, u_num.toInt());
                }
                else if (client->type == SHOP && client->clnt_num == s_num.toInt())
                {
                    sendMessage(client->clnt_socket, DELICOMPLETE, "", RIDER, sender_num, SHOP, s_num.toInt());
                }
            }
        }
        else if (fileType == "deliHistoryList")
        {
            QStringList order_list;
            QString order_list_str;

            qry.prepare("SELECT o.*, s.s_title, u.u_id FROM delivery.ordertable o "
                        "JOIN delivery.shop s ON o.s_num = s.s_num "
                        "JOIN delivery.user u on o.u_num = u.u_num "
                        "WHERE o.o_state = :o_state AND o.r_num = :r_num");
            qry.bindValue(":o_state", "배달완료");
            qry.bindValue(":r_num", sender_num);

            if (qry.exec())
            {
                while(qry.next())
                {
                    QString o_num = qry.value(0).toString();
                    QString o_text = qry.value(1).toString();
                    QString o_price = qry.value(2).toString();
                    QString o_addr = qry.value(3).toString();
                    QString u_num = qry.value(4).toString();
                    QString s_num = qry.value(5).toString();
                    QString r_num = qry.value(6).toString();
                    QString o_state = qry.value(7).toString();
                    QString o_request = qry.value(8).toString();
                    QString s_title = qry.value(9).toString();
                    QString u_id = qry.value(10).toString();


                    order_list << QString("%1/%2/%3/%4/%5/%6/%7/%8/%9/%10/%11")
                                      .arg(o_num, o_text, o_price, o_addr, u_num, s_num, r_num, o_state, o_request, s_title, u_id);
                }
                if (!order_list.isEmpty())
                {
                    order_list_str = order_list.join("@");
                    sendMessage(socket, DELIHISTORYLIST, order_list_str);
                }
            }
            else
            {
                qDebug() << "쿼리실행 실패" << qry.lastError().text();
            }
        }
        else if (fileType == "orderHistoryList")
        {
            QStringList order_list;
            QString order_list_str;

            qry.prepare("SELECT o.*, s.s_title, u.u_id FROM delivery.ordertable o "
                        "JOIN delivery.shop s ON o.s_num = s.s_num "
                        "JOIN delivery.user u on o.u_num = u.u_num "
                        "WHERE (o.o_state = :o_stateA OR o.o_state = :o_stateB) AND o.u_num = :u_num");
            qry.bindValue(":o_stateA", "주문거절");
            qry.bindValue(":o_stateB", "배달완료");
            qry.bindValue(":u_num", sender_num);

            if (qry.exec())
            {
                while(qry.next())
                {
                    QString o_num = qry.value(0).toString();
                    QString o_text = qry.value(1).toString();
                    QString o_price = qry.value(2).toString();
                    QString o_addr = qry.value(3).toString();
                    QString u_num = qry.value(4).toString();
                    QString s_num = qry.value(5).toString();
                    QString r_num = qry.value(6).toString();
                    QString o_state = qry.value(7).toString();
                    QString o_request = qry.value(8).toString();
                    QString s_title = qry.value(9).toString();
                    QString u_id = qry.value(10).toString();


                    order_list << QString("%1/%2/%3/%4/%5/%6/%7/%8/%9/%10/%11")
                                      .arg(o_num, o_text, o_price, o_addr, u_num, s_num, r_num, o_state, o_request, s_title, u_id);
                }
                if (!order_list.isEmpty())
                {
                    order_list_str = order_list.join("@");
                    sendMessage(socket, UORDER_HISTORYLIST, order_list_str);
                }
            }
            else
            {
                qDebug() << "쿼리실행 실패" << qry.lastError().text();
            }
        }
        else if (fileType == "bookmark")
        {
            msgParts = msg.split("/");
            QString s_num = msgParts[0];
            QString check = msgParts[1];

            qry.prepare("SELECT * FROM bookmark WHERE u_num = :u_num AND s_num = :s_num");
            qry.bindValue(":u_num", sender_num);
            qry.bindValue(":s_num", s_num.toInt());
            qry.exec();

            if (check == "click") // 즐겨찾기 버튼 클릭시
            {
                if (qry.next()) // 북마크 있을때
                {
                    qry.prepare("DELETE FROM bookmark WHERE u_num = :u_num AND s_num = :s_num");
                    qry.bindValue(":u_num", sender_num);
                    qry.bindValue(":s_num", s_num.toInt());
                    if (qry.exec())
                        sendMessage(socket, BOOKMARK, "bookmarkDel");
                }
                else // 북마크 없을때
                {
                    qry.prepare("INSERT INTO bookmark "
                                "(u_num, s_num) "
                                "VALUES "
                                "(:u_num, :s_num)");
                    qry.bindValue(":u_num", sender_num);
                    qry.bindValue(":s_num", s_num.toInt());
                    if(qry.exec())
                        sendMessage(socket, BOOKMARK, "bookmarkAdd");
                }
            }
            else // 즐겨찾기 체크
            {
                if (qry.next()) // 북마크 있을때
                {
                    sendMessage(socket, BOOKMARK, "bookmarkTrue");
                }
                else // 북마크 없을때
                {
                    sendMessage(socket, BOOKMARK, "bookmarkFalse");
                }
            }
        }
        else if (fileType == "bookmarkList")
        {

            QStringList shop_info_list;
            QString shop_info_str;
            QStringList imagePaths;

            qry.prepare("SELECT * FROM bookmark b "
                        "JOIN shop s ON b.s_num = s.s_num "
                        "WHERE u_num = :u_num");
            qry.bindValue(":u_num", sender_num);

            if (qry.exec())
            {
                while(qry.next())
                {
                    QString s_num = qry.value(3).toString();
                    QString s_title = qry.value(7).toString();
                    QString s_type = qry.value(8).toString();
                    QString s_state = qry.value(9).toString();
                    shop_info_list << QString("%1/%2/%3/%4").arg(s_num, s_title, s_type, s_state);
                    imagePaths.append(qry.value(10).toString());
                }
                if (shop_info_list.isEmpty())
                    return;
                for (QString &imagePath : imagePaths)
                {
                    imagePath = imagePath.remove("\""); // 쌍따옴표 제거
                    QFile file(imagePath); // 이미지 파일 열기
                    if (file.open(QIODevice::ReadOnly))
                    {
                        QByteArray imageData = file.readAll();
                        QByteArray header;
                        header.prepend(QString("fileType:shopImg,sender:%1,senderNum:%2,receiver:%3,recieverNum:%4;").toUtf8());
                        header.resize(128);
                        // 헤더와 이미지 데이터 합치기
                        QByteArray image_info = header + imageData;
                        socketStream << image_info;
                    }
                    else
                    {
                        // 파일을 열 수 없는 경우 에러 처리
                        qDebug() << "파일 오픈 실패:" << imagePath;
                    }
                }
                shop_info_str = shop_info_list.join("\n");
                sendMessage(socket, BOOKMARKLIST, shop_info_str);

            }
            else
            {
                qDebug() << "쿼리실행 실패" << qry.lastError().text();
            }
        }
    }
}

// [ex.02.10]
// ============================ 서버에서 메시지 보내는 함수 ==================================================
void MainWindow::sendMessage(QTcpSocket* socket, int act_type, QString msg, int sender, int senderNum, int receiver, int receiverNum)
{
    if(socket)
    {
        if(socket->isOpen())
        {
            // ui에서 입력할 message를 가져와
            // QString str = ui->lineEdit_message->text();

            // stream으로 보내는데
            QDataStream socketStream(socket);
            socketStream.setVersion(QDataStream::Qt_5_15);

            // 헤더 부분에 fileType을 message로 설정한다.
            QByteArray header;

            switch (act_type) {
            case SIGNUPINFO:
                header.prepend(QString("fileType:signUpInfo,sender:%1,senderNum:%2,receiver:%3,recieverNum:%4;")
                                   .arg(QString::number(sender), QString::number(senderNum), QString::number(receiver), QString::number(receiverNum)).toUtf8());
                break;
            case LOGININFO:
                header.prepend(QString("fileType:loginInfo,sender:%1,senderNum:%2,receiver:%3,recieverNum:%4;")
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
            case SHOPLOGOUT:
                header.prepend(QString("fileType:shopLogout,sender:%1,senderNum:%2,receiver:%3,recieverNum:%4;")
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
            case PUTDELIVERY:
                header.prepend(QString("fileType:putDelivery,sender:%1,senderNum:%2,receiver:%3,recieverNum:%4;")
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
            qDebug()<<"서버 바이트 어레이" <<QString(byteArray);
        }
        else
            QMessageBox::critical(this,"QTCPServer","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPServer","Not connected");
}

// [ex.02.12]
void MainWindow::slot_displayMessage(const QString& str)
{
    ui->textBrowser_receivedMessages->append(str);
}

// [ex.02.13]
void MainWindow::refreshComboBox(){
    ui->comboBox_receiver->clear();
    ui->comboBox_receiver->addItem("Broadcast");
    foreach(QTcpSocket* socket, qset_connectedSKT)
        ui->comboBox_receiver->addItem(QString::number(socket->socketDescriptor()));
}
