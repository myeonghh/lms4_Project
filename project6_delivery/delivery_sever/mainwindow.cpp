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
    qry.bindValue(":state", "영업종료");
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
        // 이 buffer는 나중에 클라이언트로부터 수신한 전체 데이터를 저장하게 됨.
        QByteArray buffer;

        // [ex.02.7.3]
        // QDataStream을 사용하여 소켓으로부터 데이터를 읽어들임.
        // 데이터 스트림에서 버전을 설정하는 이유는 서버와 클라이언트가 같은 Qt 버전을 사용해 데이터 형식을 호환하도록 하기 위함.
        QDataStream socketStream(socket);
        socketStream.setVersion(QDataStream::Qt_5_15);

        // 트랜잭션을 시작.
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
        // 데이터의 첫 128바이트는 헤더로 사용됨.
        // 헤더는 전송된 데이터가 메시지인지 파일인지를 구분하는 정보를 포함하고 있음.
        // mid(0, 128)을 통해 buffer의 처음 128바이트를 추출하여 header 변수에 저장함.
        QString header = buffer.mid(0,128);

        // 헤더를 파싱하여 첫 번째 값인 fileType(데이터 타입: message 또는 attachment)을 확인.
        // header는 "fileType:attachment,fileName:example.txt,fileSize:1024;" 형식으로 데이터를 담고 있으며,
        // 이를 콤마(,)와 콜론(:)으로 분리하여 fileType을 추출.
        QString fileType = header.split(",")[0].split(":")[1];
        QString sender = header.split(",")[1].split(":")[1];
        QString sender_num = header.split(",")[2].split(":")[1];
        QString receiver = header.split(",")[3].split(":")[1];
        QString receiver_num = header.split(",")[4].split(":")[1];

        // 나머지 데이터는 실제 전송된 파일 또는 메시지 데이터
        // 128바이트 이후부터는 실제 파일 혹은 메시지이므로 buffer에서 그 부분만 남김.
        buffer = buffer.mid(128);

        QString msg = buffer;
        QString id, pw, phone_num;
        QSqlQuery qry;
        QSqlQuery qry2;
        QStringList msgParts;


        if (fileType == "login")
        {
            msgParts = msg.split(",");
            id = msgParts[0];
            pw = msgParts[1];

            if (sender == "user")
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
            else if (sender == "shop")
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
                }
                else // 아이디 or 비밀번호 불일치
                {
                    sendMessage(socket, LOGININFO, "login fail");
                }

            }
            else if (sender == "rider")
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

            if (sender == "user")
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
            else if (sender == "rider")
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

            if (sender == "user")
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
            else if (sender == "rider")
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

            if (sender == "user")
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
            else if (sender == "rider")
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
                if (login_clnt_list[i]->type == sender.toInt() && login_clnt_list[i]->clnt_num == sender_num.toInt())
                {
                    delete login_clnt_list[i];
                    login_clnt_list.removeAt(i);
                }
            }
        }
        else if (fileType == "category")
        {
            QStringList imagePaths;

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
    }

        // else if (fileType == "tooninfo")
        // {
        //     QStringList toon_info_list;
        //     QString toon_info_str;
        //     QStringList imagePaths;

        //     qDebug() << "여기야11";
        //     qry.prepare("SELECT * FROM TOON_INFO");

        //     if (qry.exec())
        //     {
        //         while(qry.next())
        //         {
        //             QString t_id = qry.value(0).toString();
        //             QString t_title = qry.value(1).toString();
        //             QString t_author = qry.value(2).toString();
        //             QString t_day = qry.value(3).toString();
        //             toon_info_list << QString("%1/%2/%3/%4").arg(t_id).arg(t_title).arg(t_author).arg(t_day);
        //             imagePaths.append(qry.value(4).toString());
        //         }
        //         for (const QString &imagePath : imagePaths)
        //         {
        //             QFile file(imagePath); // 이미지 파일 열기
        //             if (file.open(QIODevice::ReadOnly))
        //             {
        //                 QByteArray imageData = file.readAll();
        //                 QByteArray header;
        //                 header.prepend(QString("fileType:thumbnail,fileName:null,fileSize:null;").toUtf8());
        //                 header.resize(128);
        //                 // 헤더와 이미지 데이터 합치기
        //                 QByteArray image_info = header + imageData;
        //                 socketStream << image_info;
        //             }
        //             else
        //             {
        //                 // 파일을 열 수 없는 경우 에러 처리
        //                 qDebug() << "파일 오픈 실패:" << imagePath;
        //             }
        //         }

        //         toon_info_str = toon_info_list.join("\n");
        //         sendMessage(socket, TOONINFO, toon_info_str);
        //     }
        //     else
        //     {
        //         qDebug() << "쿼리실행 실패" << qry.lastError().text();
        //     }
        // }
        // else if (fileType == "toonlist")
        // {
        //     QStringList toon_list;
        //     QString toon_list_str;
        //     QString toon_id = msg;
        //     qry.prepare("SELECT * FROM WEBTOON.TOON_EPI A JOIN WEBTOON.TOON_INFO B ON A.TOON_ID = B.TOON_ID "
        //                 "WHERE A.TOON_ID = :toon_id");
        //     qry.bindValue(":toon_id", toon_id);

        //     if (qry.exec())
        //     {
        //         while(qry.next())
        //         {
        //             QString epi_id = qry.value(0).toString();
        //             QString t_id = qry.value(1).toString();
        //             QString epi_num = qry.value(2).toString();
        //             QString like_num = qry.value(3).toString();
        //             QString view_num = qry.value(4).toString();
        //             QString epi_title = qry.value(5).toString();
        //             QString t_title = qry.value(7).toString();
        //             QString t_author = qry.value(8).toString();
        //             QString t_day = qry.value(9).toString();

        //             toon_list << QString("%1/%2/%3/%4/%5/%6/%7/%8/%9").arg(epi_id).arg(t_id).arg(t_title).arg(epi_title).arg(t_author).arg(t_day).arg(epi_num).arg(view_num).arg(like_num);
        //         }
        //         toon_list_str = toon_list.join("\n");
        //         sendMessage(socket, TOONLIST, toon_list_str);
        //     }
        //     else
        //     {
        //         qDebug() << "쿼리실행 실패" << qry.lastError().text();
        //     }
        // }
        // else if (fileType == "toonimage")
        // {
        //     QStringList imagePaths;

        //     QString epi_id = msg;
        //     QSqlQuery query;
        //     query.prepare("SELECT IMG_SRC FROM TOON_IMG WHERE EPI_ID = :epi_id");
        //     query.bindValue(":epi_id", epi_id);

        //     if (query.exec())
        //     {
        //         while (query.next())
        //         {
        //             imagePaths.append(query.value(0).toString());
        //         }
        //     }

        //     for (const QString &imagePath : imagePaths)
        //     {
        //         QFile file(imagePath); // 이미지 파일 열기
        //         if (file.open(QIODevice::ReadOnly))
        //         {
        //             QByteArray imageData = file.readAll();
        //             QByteArray header;
        //             header.prepend(QString("fileType:toonimage,fileName:null,fileSize:null;").toUtf8());
        //             header.resize(128);
        //             // 헤더와 이미지 데이터 합치기
        //             QByteArray image_info = header + imageData;
        //             socketStream << image_info;
        //         }
        //         else
        //         {
        //             // 파일을 열 수 없는 경우 에러 처리
        //             qDebug() << "파일 오픈 실패:" << imagePath;
        //         }
        //     }
        //     // 조회수 증가 로직
        //     query.prepare("UPDATE TOON_EPI SET VIEW_NUM = VIEW_NUM+1 WHERE EPI_ID = :epi_id");
        //     query.bindValue(":epi_id", epi_id);
        //     if (!query.exec())
        //     {
        //         qDebug() << "조회수 업데이트 오류";
        //     }
        // }
        // else if (fileType == "bookmark")
        // {
        //     msgParts = msg.split(",");
        //     QString user_id = msgParts[0];
        //     QString epi_id = msgParts[1];

        //     qry.prepare("SELECT * FROM BOOKMARK WHERE ID = :id AND EPI_ID = :epi_id");
        //     qry.bindValue(":id", user_id);
        //     qry.bindValue(":epi_id", epi_id);
        //     qry.exec();

        //     if (qry.next()) // 북마크 있을때
        //     {
        //         sendMessage(socket, LOGININFO, "login success");
        //     }
        //     else // 북마크 없을때
        //     {
        //         sendMessage(socket, LOGININFO, "login fail");
        //     }
        // }


        // // [ex.02.7.5]
        // // fileType이 attachment(첨부 파일)인 경우, 파일을 수신.
        // if (fileType == "attachment")
        // {

        //     // 헤더에서 파일 이름을 추출.
        //     // "fileName:example.txt" 형식으로 되어 있으므로 이를 분리하여 실제 파일 이름을 얻는다.
        //     QString fileName = header.split(",")[1].split(":")[1];

        //     // 파일 확장자를 추출. 파일 이름에서 "."을 기준으로 확장자를 분리하여 저장한다.
        //     QString ext = fileName.split(".")[1];

        //     // 헤더에서 파일 크기 추출.  "fileSize:1024;"와 같은 형식에서 파일 크기를 추출한다.
        //     QString size = header.split(",")[2].split(":")[1].split(";")[0];

        //     // 새 파일 이름을 만듦. 기존 파일 이름에 소켓 디스크립터를 덧붙여 이름을 유일하게 만든다.
        //     // 이렇게 하면 여러 클라이언트가 동시에 파일을 전송할 때 덮어 씌워지는 것을 방지할 수 있음.
        //     QString newFileName = QString("%1_%2.%3").arg(fileName.split(".")[0]).arg(socket->socketDescriptor()).arg(ext);

        //     // 파일을 저장할 경로를 지정.
        //     // QFile 객체를 사용하여 새 파일을 만듦.
        //     QFile file("C:/Users/DELL/" + newFileName);

        //     if (file.open(QFile::WriteOnly))
        //     {
        //         file.write(buffer);
        //         // 데이터를 파일에 쓴 후, 파일을 안전하게 닫음.
        //         file.flush();
        //         file.close();
        //     }

        //     // 파일이 성공적으로 저장되었다는 메시지를 생성하여 signal_newMessage 시그널을 emit함.
        //     QString message = QString("%1 :: %2 of size: %3 bytes has been received").arg(socket->socketDescriptor()).arg(newFileName).arg(size);
        //     emit singal_newMessage(message);
        // }
        // // [ex.02.7.6]
        // // fileType이 message(메시지)일 경우, 해당 메시지를 UI에 출력.
        // else
        // {
        //     // buffer에 있는 메시지를 출력.  소켓 디스크립터와 메시지 내용을 포함하여 출력한다.
        //     QString message = QString("%1 :: %2").arg(socket->socketDescriptor()).arg(QString(buffer));
        //     emit singal_newMessage(message);
        // }

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
                                   .arg(client_type_to_string(sender), QString::number(senderNum), client_type_to_string(receiver), QString::number(receiverNum)).toUtf8());
                break;
            case LOGININFO:
                header.prepend(QString("fileType:loginInfo,sender:%1,senderNum:%2,receiver:%3,recieverNum:%4;")
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
            qDebug()<<"서버 바이트 어레이" <<QString(byteArray);
        }
        else
            QMessageBox::critical(this,"QTCPServer","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPServer","Not connected");
}

// [ex.02.8]
// 서버에서 메시지를 보낼 때,
// 1) 서버에 연결된 특정 대상에게 전송하거나
// 2) 연결된 모든 대상에게 전송하도록 선택한다.(Broadcast)
// void MainWindow::on_pushButton_sendMessage_clicked()
// {
//     QString receiver = ui->comboBox_receiver->currentText();

//     // Broadcast 라면, qset_connectedSKT 에 저장된 모든 대상에게 메시지 전송
//     if(receiver=="Broadcast")
//     {
//         foreach (QTcpSocket* socket,qset_connectedSKT)
//         {
//             sendMessage(socket);
//         }
//     }
//     // 선택한 대상을 qset_connectedSKT에서 소켓을 찾아 메시지 전송
//     else
//     {
//         foreach (QTcpSocket* socket, qset_connectedSKT)
//         {
//             if(socket->socketDescriptor() == receiver.toLongLong())
//             {
//                 sendMessage(socket);
//                 break;
//             }
//         }
//     }

//     // 메시지 입력창 리셋
//     ui->lineEdit_message->clear();
// }

// [ex.02.9]
// 서버에서 파일을 보낼 때
// void MainWindow::on_pushButton_sendAttachment_clicked()
// {
//     // 보낼 대상 선택
//     QString receiver = ui->comboBox_receiver->currentText();

//     // 파일 경로 가져오고, 경로 문제시 경고 출력
//     QString filePath = QFileDialog::getOpenFileName(this, ("Select an attachment"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), ("File (*.json *.txt *.png *.jpg *.jpeg)"));
//     if(filePath.isEmpty())
//     {
//         QMessageBox::critical(this,"QTCPClient","You haven't selected any attachment!");
//         return;
//     }

//     // 보낼 대상이 연결된 모든 socket일때 동작
//     if(receiver=="Broadcast")
//     {
//         foreach (QTcpSocket* socket, qset_connectedSKT)
//         {
//             sendAttachment(socket, filePath);
//         }
//     }
//     // 보낼 대상이 특정 socket일때 동작
//     else
//     {
//         foreach (QTcpSocket* socket, qset_connectedSKT)
//         {
//             if(socket->socketDescriptor() == receiver.toLongLong())
//             {
//                 sendAttachment(socket, filePath);
//                 break;
//             }
//         }
//     }
//     ui->lineEdit_message->clear();
// }


// ===================================================================================================
// [ex.02.11]
void MainWindow::sendAttachment(QTcpSocket* socket, QString filePath)
{
    if(socket)
    {
        if(socket->isOpen())
        {
            // 전송 할 file 객체를 경로 지정해서 열고
            QFile m_file(filePath);
            if(m_file.open(QIODevice::ReadOnly))
            {
                // file 이름을 가져오고
                QFileInfo fileInfo(m_file.fileName());
                QString fileName(fileInfo.fileName());

                // stream으로 보내는데
                QDataStream socketStream(socket);
                socketStream.setVersion(QDataStream::Qt_5_15);

                // 헤더 부분에 fileType을 attachment로 설정한다.
                QByteArray header;
                header.prepend(QString("fileType:attachment,fileName:%1,fileSize:%2;").arg(fileName).arg(m_file.size()).toUtf8());
                header.resize(128);

                // QByteArray에 file을 byte로 할당하고
                QByteArray byteArray = m_file.readAll();
                // header 정보를 앞에 넣어준다.
                byteArray.prepend(header);

                // stream으로 byteArray 정보 전송
                socketStream << byteArray;

            }
            else
                QMessageBox::critical(this,"QTCPClient","Couldn't open the attachment!");
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
