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

    delete ui;
}

bool MainWindow::initializeDataBase() // DB 연결 함수
{
    m_db = QSqlDatabase::addDatabase("QODBC");
    m_db.setHostName("127.0.0.1");
    m_db.setDatabaseName("WEBTOON");
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

        // 나머지 데이터는 실제 전송된 파일 또는 메시지 데이터
        // 128바이트 이후부터는 실제 파일 혹은 메시지이므로 buffer에서 그 부분만 남김.
        buffer = buffer.mid(128);

        // QSqlQuery qry;
        // qry.prepare( "SELECT ID,PASSWORD FROM todo.tasks WHERE ID = :CHA AND PASSWORD = :SOOBIN" );
        // qry.bindValue(":CHA",id);
        // qry.bindValue(":SOOBIN",ps);
        QString msg = buffer;
        QString id, pw, phone_num, email;
        QSqlQuery qry;
        QSqlQuery qry2;
        QStringList msgParts;



        if (fileType == "login")
        {
            msgParts = msg.split(",");
            id = msgParts[0];
            pw = msgParts[1];

            qry.prepare("SELECT * FROM USERS WHERE ID = :id AND PW = :pw");
            qry.bindValue(":id", id);
            qry.bindValue(":pw", pw);
            qry.exec();

            if (qry.next()) // 아이디 비밀번호 일치
            {
                sendMessage(socket, LOGININFO, "login success");
            }
            else // 아이디 or 비밀번호 불일치
            {
                sendMessage(socket, LOGININFO, "login fail");
            }

        }
        else if (fileType == "signUp")
        {
            msgParts = msg.split(",");
            id = msgParts[0];
            pw = msgParts[1];
            phone_num = msgParts[2];
            email = msgParts[3];

            qry.prepare("INSERT INTO USERS "
                        "(ID, PW, PHONE_NUM, EMAIL) "
                        "VALUES "
                        "(:id, :pw, :pnum, :email)");

            qry.bindValue(":id", id);
            qry.bindValue(":pw", pw);
            qry.bindValue(":pnum", phone_num);
            qry.bindValue(":email", email);

            if(qry.exec())
            {
                sendMessage(socket, SIGNUPINFO, "signUp success");
            }
            else
            {
                sendMessage(socket, SIGNUPINFO, "signUp error");
            }

        }
        else if (fileType == "idSearch")
        {
            msgParts = msg.split(",");
            phone_num = msgParts[2];

            qry.prepare("SELECT ID FROM USERS WHERE PHONE_NUM = :phone_num");
            qry.bindValue(":phone_num", phone_num);
            qry.exec();

            if (qry.next()) // 휴대폰 번호로 아이디 찾음
            {
                sendMessage(socket, IDINFO, qry.value(0).toString());
            }
            else // 아이디 or 비밀번호 불일치
            {
                sendMessage(socket, IDINFO, "idSearch fail");
            }

        }
        else if (fileType == "pwSearch")
        {
            msgParts = msg.split(",");
            id = msgParts[0];
            phone_num = msgParts[2];
            email = msgParts[3];

            qry.prepare("SELECT PW FROM USERS WHERE ID = :id AND PHONE_NUM = :phone_num AND EMAIL = :email");
            qry.bindValue(":id", id);
            qry.bindValue(":phone_num", phone_num);
            qry.bindValue(":email", email);
            qry.exec();

            if (qry.next()) // 휴대폰 번호로 아이디 찾음
            {
                sendMessage(socket, PWINFO, qry.value(0).toString());
            }
            else // 아이디 or 비밀번호 불일치
            {
                sendMessage(socket, PWINFO, "pwSearch fail");
            }


        }
        else if (fileType == "idDupChk")
        {
            msgParts = msg.split(",");
            id = msgParts[0];

            // 아이디 중복 확인
            qry.prepare("SELECT * FROM USERS WHERE ID = :id");
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
        else if (fileType == "pNumDupChk")
        {
            msgParts = msg.split(",");
            phone_num = msgParts[2];

            // 휴대폰 번호 중복 확인
            qry.prepare("SELECT * FROM USERS WHERE PHONE_NUM = :phone_num");
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
        else if (fileType == "tooninfo")
        {
            QStringList toon_info_list;
            QString toon_info_str;
            QStringList imagePaths;

            qry.prepare("SELECT * FROM TOON_INFO");

            if (qry.exec())
            {
                while(qry.next())
                {
                    QString t_id = qry.value(0).toString();
                    QString t_title = qry.value(1).toString();
                    QString t_author = qry.value(2).toString();
                    QString t_day = qry.value(3).toString();
                    toon_info_list << QString("%1/%2/%3/%4").arg(t_id).arg(t_title).arg(t_author).arg(t_day);
                    imagePaths.append(qry.value(4).toString());
                }
                for (QString &imagePath : imagePaths)
                {
                    imagePath = imagePath.remove("\""); // 쌍따옴표 제거
                    // imagePath = imagePath.replace("\\", "/"); // 역슬래시를 슬래시로 변환
                    QFile file(imagePath); // 이미지 파일 열기
                    if (file.open(QIODevice::ReadOnly))
                    {
                        QByteArray imageData = file.readAll();
                        QByteArray header;
                        header.prepend(QString("fileType:thumbnail,fileName:null,fileSize:null;").toUtf8());
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

                toon_info_str = toon_info_list.join("\n");
                sendMessage(socket, TOONINFO, toon_info_str);
            }
            else
            {
                qDebug() << "쿼리실행 실패" << qry.lastError().text();
            }
        }
        else if (fileType == "toonlist")
        {
            QStringList toon_list;
            QString toon_list_str;
            QString toon_id = msg;
            qry.prepare("SELECT * FROM WEBTOON.TOON_EPI A JOIN WEBTOON.TOON_INFO B ON A.TOON_ID = B.TOON_ID "
                        "WHERE A.TOON_ID = :toon_id");
            qry.bindValue(":toon_id", toon_id);

            if (qry.exec())
            {
                while(qry.next())
                {
                    QString epi_id = qry.value(0).toString();
                    QString t_id = qry.value(1).toString();
                    QString epi_num = qry.value(2).toString();
                    QString like_num = qry.value(3).toString();
                    QString view_num = qry.value(4).toString();
                    QString epi_title = qry.value(5).toString();
                    QString t_title = qry.value(7).toString();
                    QString t_author = qry.value(8).toString();
                    QString t_day = qry.value(9).toString();

                    toon_list << QString("%1/%2/%3/%4/%5/%6/%7/%8/%9").arg(epi_id).arg(t_id).arg(t_title).arg(epi_title).arg(t_author).arg(t_day).arg(epi_num).arg(view_num).arg(like_num);
                }
                toon_list_str = toon_list.join("\n");
                sendMessage(socket, TOONLIST, toon_list_str);
            }
            else
            {
                qDebug() << "쿼리실행 실패" << qry.lastError().text();
            }
        }
        else if (fileType == "toonimage")
        {
            QStringList imagePaths;

            QString epi_id = msg;
            QSqlQuery query;
            query.prepare("SELECT IMG_SRC FROM TOON_IMG WHERE EPI_ID = :epi_id");
            query.bindValue(":epi_id", epi_id);

            if (query.exec())
            {
                while (query.next())
                {
                    imagePaths.append(query.value(0).toString());
                }
            }

            for (QString &imagePath : imagePaths)
            {
                imagePath = imagePath.remove("\""); // 쌍따옴표 제거
                QFile file(imagePath); // 이미지 파일 열기
                if (file.open(QIODevice::ReadOnly))
                {
                    QByteArray imageData = file.readAll();
                    QByteArray header;
                    header.prepend(QString("fileType:toonimage,fileName:null,fileSize:null;").toUtf8());
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
            // 조회수 증가 로직
            query.prepare("UPDATE TOON_EPI SET VIEW_NUM = VIEW_NUM+1 WHERE EPI_ID = :epi_id");
            query.bindValue(":epi_id", epi_id);
            if (!query.exec())
            {
                qDebug() << "조회수 업데이트 오류";
            }
        }
        else if (fileType == "bookmark")
        {
            msgParts = msg.split(",");
            QString user_id = msgParts[0];
            QString epi_id = msgParts[1];
            QString check = msgParts[2];

            qry.prepare("SELECT * FROM BOOKMARK WHERE ID = :id AND EPI_ID = :epi_id");
            qry.bindValue(":id", user_id);
            qry.bindValue(":epi_id", epi_id);
            qry.exec();

            if (check == "control") // 즐겨찾기 버튼 클릭시
            {
                if (qry.next()) // 북마크 있을때
                {
                    qry.prepare("DELETE FROM BOOKMARK WHERE ID = :id AND EPI_ID = :epi_id");
                    qry.bindValue(":id", user_id);
                    qry.bindValue(":epi_id", epi_id);
                    if (qry.exec())
                        sendMessage(socket, BOOKMARK, "bookmarkDel");
                }
                else // 북마크 없을때
                {
                    qry.prepare("INSERT INTO BOOKMARK "
                                "(ID, EPI_ID) "
                                "VALUES "
                                "(:id, :epi_id)");
                    qry.bindValue(":id", user_id);
                    qry.bindValue(":epi_id", epi_id);
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
        else if (fileType == "bookmarklist")
        {
            QStringList toon_list;
            QString toon_list_str;
            QString user_id = msg;
            qry.prepare("SELECT E.*, I.* FROM WEBTOON.BOOKMARK B "
                        "JOIN WEBTOON.TOON_EPI E ON B.EPI_ID = E.EPI_ID "
                        "JOIN WEBTOON.TOON_INFO I ON E.TOON_ID = I.TOON_ID "
                        "WHERE B.ID = :user_id");
            qry.bindValue(":user_id", user_id);

            if (qry.exec())
            {
                while(qry.next())
                {
                    QString epi_id = qry.value(0).toString();
                    QString t_id = qry.value(1).toString();
                    QString epi_num = qry.value(2).toString();
                    QString like_num = qry.value(3).toString();
                    QString view_num = qry.value(4).toString();
                    QString epi_title = qry.value(5).toString();
                    QString t_title = qry.value(7).toString();
                    QString t_author = qry.value(8).toString();
                    QString t_day = qry.value(9).toString();

                    toon_list << QString("%1/%2/%3/%4/%5/%6/%7/%8/%9").arg(epi_id).arg(t_id).arg(t_title).arg(epi_title).arg(t_author).arg(t_day).arg(epi_num).arg(view_num).arg(like_num);
                }
                toon_list_str = toon_list.join("\n");
                sendMessage(socket, BOOKMARKLIST, toon_list_str);
            }
            else
            {
                qDebug() << "쿼리실행 실패" << qry.lastError().text();
            }
        }
        else if (fileType == "toonlike")
        {
            msgParts = msg.split(",");
            QString user_id = msgParts[0];
            QString epi_id = msgParts[1];
            QString check = msgParts[2];

            qry.prepare("SELECT * FROM TOON_LIKE WHERE ID = :id AND EPI_ID = :epi_id");
            qry.bindValue(":id", user_id);
            qry.bindValue(":epi_id", epi_id);
            qry.exec();

            if (check == "control") // 좋아요 버튼 클릭시
            {
                if (qry.next()) // 이미 좋아요 했을때
                {
                    qry.prepare("DELETE FROM TOON_LIKE WHERE ID = :id AND EPI_ID = :epi_id");
                    qry.bindValue(":id", user_id);
                    qry.bindValue(":epi_id", epi_id);

                    qry2.prepare("UPDATE TOON_EPI SET LIKE_NUM = LIKE_NUM-1 WHERE EPI_ID = :epi_id");
                    qry2.bindValue(":epi_id", epi_id);

                    if (qry.exec() && qry2.exec())
                        sendMessage(socket, TOONLIKE, "toonlikeDel");
                }
                else // 좋아요 안했을때
                {
                    qry.prepare("INSERT INTO TOON_LIKE "
                                "(EPI_ID, ID) "
                                "VALUES "
                                "(:epi_id, :id)");
                    qry.bindValue(":epi_id", epi_id);
                    qry.bindValue(":id", user_id);

                    qry2.prepare("UPDATE TOON_EPI SET LIKE_NUM = LIKE_NUM+1 WHERE EPI_ID = :epi_id");
                    qry2.bindValue(":epi_id", epi_id);

                    if(qry.exec() && qry2.exec())
                        sendMessage(socket, TOONLIKE, "toonlikeAdd");
                }
            }
            else // 좋아요 체크
            {
                if (qry.next()) // 좋아요 이미 했을때
                {
                    sendMessage(socket, TOONLIKE, "toonlikeTrue");
                }
                else // 좋아요 안했을때
                {
                    sendMessage(socket, TOONLIKE, "toonlikeFalse");
                }
            }
        }
        else if (fileType == "epichange")
        {
            msgParts = msg.split(",");
            QString toon_id = msgParts[0];
            QString epi_num = msgParts[1];
            QString check = msgParts[2];
            int before_epi_num = epi_num.toInt()-1; // 이전화
            int after_epi_num = epi_num.toInt()+1; // 다음화

            if (check == "before") // 이전화 버튼 클릭했을 때
            {
                QStringList imagePaths;
                qry.prepare("SELECT I.IMG_SRC FROM TOON_IMG I "
                            "JOIN TOON_EPI E ON I.EPI_ID = E.EPI_ID "
                            "WHERE E.TOON_ID = :toon_id AND E.EPI_NUM = :epi_num");
                qry.bindValue(":toon_id", toon_id);
                qry.bindValue(":epi_num", before_epi_num);

                if (qry.exec())
                {
                    while (qry.next())
                    {
                        imagePaths.append(qry.value(0).toString());
                    }

                    if (imagePaths.size() == 0) // 현재 보고 있는 웹툰이 첫번째 화 일때
                    {
                        sendMessage(socket, EPICHANGE, "firstepi");
                        return;
                    }
                }

                for (QString &imagePath : imagePaths)
                {
                    imagePath = imagePath.remove("\""); // 쌍따옴표 제거
                    QFile file(imagePath); // 이미지 파일 열기
                    if (file.open(QIODevice::ReadOnly))
                    {
                        QByteArray imageData = file.readAll();
                        QByteArray header;
                        header.prepend(QString("fileType:toonimage,fileName:null,fileSize:null;").toUtf8());
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
                // 조회수 증가 로직
                qry.prepare("UPDATE TOON_EPI SET VIEW_NUM = VIEW_NUM+1 "
                            "WHERE TOON_ID = :toon_id AND EPI_NUM = :epi_num");
                qry.bindValue(":toon_id", toon_id);
                qry.bindValue(":epi_num", before_epi_num);
                if (!qry.exec())
                {
                    qDebug() << "조회수 업데이트 오류";
                    return;
                }
            }
            else if (check == "after")// 다음화 버튼 클릭했을 때
            {
                QStringList imagePaths;
                qry.prepare("SELECT I.IMG_SRC FROM TOON_IMG I "
                            "JOIN TOON_EPI E ON I.EPI_ID = E.EPI_ID "
                            "WHERE E.TOON_ID = :toon_id AND E.EPI_NUM = :epi_num");
                qry.bindValue(":toon_id", toon_id);
                qry.bindValue(":epi_num", after_epi_num);

                if (qry.exec())
                {
                    while (qry.next())
                    {
                        imagePaths.append(qry.value(0).toString());
                    }

                    if (imagePaths.size() == 0) // 현재 보고 있는 웹툰이 첫번째 화 일때
                    {
                        sendMessage(socket, EPICHANGE, "lastepi");
                        return;
                    }
                }

                for (QString &imagePath : imagePaths)
                {
                    imagePath = imagePath.remove("\""); // 쌍따옴표 제거
                    QFile file(imagePath); // 이미지 파일 열기
                    if (file.open(QIODevice::ReadOnly))
                    {
                        QByteArray imageData = file.readAll();
                        QByteArray header;
                        header.prepend(QString("fileType:toonimage,fileName:null,fileSize:null;").toUtf8());
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
                // 조회수 증가 로직
                qry.prepare("UPDATE TOON_EPI SET VIEW_NUM = VIEW_NUM+1 "
                            "WHERE TOON_ID = :toon_id AND EPI_NUM = :epi_num");
                qry.bindValue(":toon_id", toon_id);
                qry.bindValue(":epi_num", after_epi_num);
                if (!qry.exec())
                {
                    qDebug() << "조회수 업데이트 오류";
                    return;
                }
            }
        }
        else if (fileType == "tooninfotext")
        {
            QString epi_id = msg;
            qry.prepare("SELECT I.TOON_TITLE, E.EPI_NUM, E.EPI_TITLE FROM TOON_EPI E "
                        "JOIN TOON_INFO I ON E.TOON_ID = I.TOON_ID "
                        "WHERE E.EPI_ID = :epi_id");
            qry.bindValue(":epi_id", epi_id);

            if (qry.exec())
            {
                if (qry.next())
                {
                    QString t_title = qry.value(0).toString();
                    QString epi_num = qry.value(1).toString();
                    QString epi_title = qry.value(2).toString();

                    sendMessage(socket, TOONINFOTEXT, t_title+"/"+epi_num+"/"+epi_title);
                }
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
void MainWindow::sendMessage(QTcpSocket* socket, int type, QString msg = "")
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

            if (type == SIGNUPINFO)
            {
                header.prepend(QString("fileType:signUpInfo,fileName:null,fileSize:%1;").arg(msg.size()).toUtf8());
            }
            else if (type == LOGININFO)
            {
                header.prepend(QString("fileType:loginInfo,fileName:null,fileSize:%1;").arg(msg.size()).toUtf8());
            }
            else if (type == IDINFO)
            {
                header.prepend(QString("fileType:idInfo,fileName:null,fileSize:%1;").arg(msg.size()).toUtf8());
            }
            else if (type == PWINFO)
            {
                header.prepend(QString("fileType:pwInfo,fileName:null,fileSize:%1;").arg(msg.size()).toUtf8());
            }
            else if (type == TOONINFO)
            {
                header.prepend(QString("fileType:tooninfo,fileName:null,fileSize:%1;").arg(msg.size()).toUtf8());
            }
            else if (type == TOONLIST)
            {
                header.prepend(QString("fileType:toonlist,fileName:null,fileSize:%1;").arg(msg.size()).toUtf8());
            }
            else if (type == TOONIMAGE)
            {
                header.prepend(QString("fileType:toonimage,fileName:null,fileSize:%1;").arg(msg.size()).toUtf8());
            }
            else if (type == BOOKMARK)
            {
                header.prepend(QString("fileType:bookmark,fileName:null,fileSize:%1;").arg(msg.size()).toUtf8());
            }
            else if (type == BOOKMARKLIST)
            {
                header.prepend(QString("fileType:bookmarklist,fileName:null,fileSize:%1;").arg(msg.size()).toUtf8());
            }
            else if (type == TOONLIKE)
            {
                header.prepend(QString("fileType:toonlike,fileName:null,fileSize:%1;").arg(msg.size()).toUtf8());
            }
            else if (type == EPICHANGE)
            {
                header.prepend(QString("fileType:epichange,fileName:null,fileSize:%1;").arg(msg.size()).toUtf8());
            }
            else if (type == TOONINFOTEXT)
            {
                header.prepend(QString("fileType:tooninfotext,fileName:null,fileSize:%1;").arg(msg.size()).toUtf8());
            }

            header.resize(128);
            // message 인코딩 설정하고, QByteArray에 할당하고
            QByteArray byteArray = msg.toUtf8();
            // header 정보를 앞에 넣어준다.
            byteArray.prepend(header);

            // stream으로 byteArray 정보 전송
            socketStream << byteArray;
            // qDebug()<< QString(byteArray);
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
