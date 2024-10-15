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
    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName("127.0.0.1");
    m_db.setDatabaseName("WEBTOON");
    m_db.setUserName("SMH");
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

    QStringList msgParts;

    if (fileType == "login")
    {

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
            qDebug() << "인서트 성공!!!!!";
            sendMessage(socket, INFO, "signUp success");
        }
        else
        {
            qDebug() << "인서트 실패!!!!!";
            sendMessage(socket, INFO, "signUp error");
        }

    }
    else if (fileType == "idSearch")
    {

    }
    else if (fileType == "pwSearch")
    {

    }
    else if (fileType == "idDupChk")
    {

    }
    else if (fileType == "pNumDupChk")
    {

    }


    // [ex.02.7.5]
    // fileType이 attachment(첨부 파일)인 경우, 파일을 수신.
    if (fileType == "attachment")
    {
        // 헤더에서 파일 이름을 추출.
        // "fileName:example.txt" 형식으로 되어 있으므로 이를 분리하여 실제 파일 이름을 얻는다.
        QString fileName = header.split(",")[1].split(":")[1];

        // 파일 확장자를 추출. 파일 이름에서 "."을 기준으로 확장자를 분리하여 저장한다.
        QString ext = fileName.split(".")[1];

        // 헤더에서 파일 크기 추출.  "fileSize:1024;"와 같은 형식에서 파일 크기를 추출한다.
        QString size = header.split(",")[2].split(":")[1].split(";")[0];

        // 새 파일 이름을 만듦. 기존 파일 이름에 소켓 디스크립터를 덧붙여 이름을 유일하게 만든다.
        // 이렇게 하면 여러 클라이언트가 동시에 파일을 전송할 때 덮어 씌워지는 것을 방지할 수 있음.
        QString newFileName = QString("%1_%2.%3").arg(fileName.split(".")[0]).arg(socket->socketDescriptor()).arg(ext);

        // 파일을 저장할 경로를 지정.
        // QFile 객체를 사용하여 새 파일을 만듦.
        QFile file("C:/Users/DELL/" + newFileName);

        if (file.open(QFile::WriteOnly))
        {
            file.write(buffer);
            // 데이터를 파일에 쓴 후, 파일을 안전하게 닫음.
            file.flush();
            file.close();
        }

        // 파일이 성공적으로 저장되었다는 메시지를 생성하여 signal_newMessage 시그널을 emit함.
        QString message = QString("%1 :: %2 of size: %3 bytes has been received").arg(socket->socketDescriptor()).arg(newFileName).arg(size);
        emit singal_newMessage(message);
    }
    // [ex.02.7.6]
    // fileType이 message(메시지)일 경우, 해당 메시지를 UI에 출력.
    else
    {
        // buffer에 있는 메시지를 출력.  소켓 디스크립터와 메시지 내용을 포함하여 출력한다.
        QString message = QString("%1 :: %2").arg(socket->socketDescriptor()).arg(QString(buffer));
        emit singal_newMessage(message);
    }
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
void MainWindow::on_pushButton_sendAttachment_clicked()
{
    // 보낼 대상 선택
    QString receiver = ui->comboBox_receiver->currentText();

    // 파일 경로 가져오고, 경로 문제시 경고 출력
    QString filePath = QFileDialog::getOpenFileName(this, ("Select an attachment"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), ("File (*.json *.txt *.png *.jpg *.jpeg)"));
    if(filePath.isEmpty())
    {
        QMessageBox::critical(this,"QTCPClient","You haven't selected any attachment!");
        return;
    }

    // 보낼 대상이 연결된 모든 socket일때 동작
    if(receiver=="Broadcast")
    {
        foreach (QTcpSocket* socket, qset_connectedSKT)
        {
            sendAttachment(socket, filePath);
        }
    }
    // 보낼 대상이 특정 socket일때 동작
    else
    {
        foreach (QTcpSocket* socket, qset_connectedSKT)
        {
            if(socket->socketDescriptor() == receiver.toLongLong())
            {
                sendAttachment(socket, filePath);
                break;
            }
        }
    }
    ui->lineEdit_message->clear();
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
            if (type == INFO)
            {
                header.prepend(QString("fileType:info,fileName:null,fileSize:%1;").arg(msg.size()).toUtf8());
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
            QMessageBox::critical(this,"QTCPServer","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPServer","Not connected");
}
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
