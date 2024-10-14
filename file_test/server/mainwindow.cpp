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
// 첨부파일 또는 메시지 수신 처리
void MainWindow::slot_readSocket()
{
    // [ex.02.5.1]
    // 슬롯 함수가 실행되면, sender()를 통해 signal을 발생시킨 객체를 찾아 return
    // 이 슬롯(slot_readSocket)은 서버에 연결된 socket의 readyread 시그널에 대한 슬롯으로
    // 연결 메시지를 보낸 socket을 찾을 수 있다.
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());

    // QByteArray 타입의 buffer를 만들고
    QByteArray buffer;

    // 서버에 연결된 socket을 stream으로 연결한다.
    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    // stream으로 데이터를 읽어들이고, buffer로 넘기면
    socketStream.startTransaction();
    socketStream >> buffer;

    // stream startTransaction 실행 문제시 에러 표시 후 함수 종료
    if(!socketStream.commitTransaction())
    {
        QString message = QString("%1 :: Waiting for more data to come..").arg(socket->socketDescriptor());
        emit singal_newMessage(message);
        return;
    }

    // client 에서 보낸 payload(순수한 데이터, 전달 메시지)를
    // buffer에서 처음 128 byte 부분만 읽어들여서 header 에 담고 fileType을 찾는다.
    QString header = buffer.mid(0,128);
    QString fileType = header.split(",")[0].split(":")[1];

    // buffer의 128 byte 이후 부분을
    buffer = buffer.mid(128);

    // fileType이 attachment 라면 파일 수신 로직을 실행하고
    // fileType이 message 라면 문장 수신 로직을 실핸한다.

    if(fileType=="attachment")
    {
        // 파일 전송은, 1)저장될 파일 이름, 2) 파일 확장자 3) 파일 크기 정보가 필요하다.
        QString fileName = header.split(",")[1].split(":")[1];
        QString ext = fileName.split(".")[1];
        QString size = header.split(",")[2].split(":")[1].split(";")[0];

        // 파일 전송 메시지를 받으면, 메시지 박스를 띄워서 전송 받을 것인지 확인한다.
        // 메시지 박스에서 yes를 선택하면 파일을 읽는다.
        if (QMessageBox::Yes == (QMessageBox::question(this, "QTCPServer", QString("You are receiving an attachment from sd:%1 of size: %2 bytes, called %3. Do you want to accept it?").arg(socket->socketDescriptor()).arg(size).arg(fileName))))
        {
            // 저장될 파일의 경로를 설정하고, 파일 이름과, 확장자를 설정한다.
            QString filePath = QFileDialog::getSaveFileName(this, tr("Save File"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/"+fileName, QString("File (*.%1)").arg(ext));

            // file 객체를 위에서 설정한 경로를 기반으로 연결하고
            QFile file(filePath);

            // file 객체를 열고, buffer에 들어있는 byte를 쓴다(내보낸다. 통신이랑 같다).
            if(file.open(QIODevice::WriteOnly))
            {
                file.write(buffer);

                // 파일이 저장되는 것에 대한 메시지를 ui에 출력한다.
                QString message = QString("INFO :: Attachment from sd:%1 successfully stored on disk under the path %2").arg(socket->socketDescriptor()).arg(QString(filePath));
                emit singal_newMessage(message);
            }
            else
                QMessageBox::critical(this,"QTCPServer", "An error occurred while trying to write the attachment.");
        }
        else
        {
            // 메시지 박스에서 No 전송 거부시 메시지를 출력한다.
            QString message = QString("INFO :: Attachment from sd:%1 discarded").arg(socket->socketDescriptor());
            emit singal_newMessage(message);
        }
    }
    else if(fileType=="message")
    {
        // 전송된 메시지를 서버에서 출력한다.
        QString message = QString("%1 :: %2").arg(socket->socketDescriptor()).arg(QString::fromStdString(buffer.toStdString()));
        emit singal_newMessage(message);
    }
}

// [ex.02.8]
// 서버에서 메시지를 보낼 때,
// 1) 서버에 연결된 특정 대상에게 전송하거나
// 2) 연결된 모든 대상에게 전송하도록 선택한다.(Broadcast)
void MainWindow::on_pushButton_sendMessage_clicked()
{
    QString receiver = ui->comboBox_receiver->currentText();

    // Broadcast 라면, qset_connectedSKT 에 저장된 모든 대상에게 메시지 전송
    if(receiver=="Broadcast")
    {
        foreach (QTcpSocket* socket,qset_connectedSKT)
        {
            sendMessage(socket);
        }
    }
    // 선택한 대상을 qset_connectedSKT에서 소켓을 찾아 메시지 전송
    else
    {
        foreach (QTcpSocket* socket, qset_connectedSKT)
        {
            if(socket->socketDescriptor() == receiver.toLongLong())
            {
                sendMessage(socket);
                break;
            }
        }
    }

    // 메시지 입력창 리셋
    ui->lineEdit_message->clear();
}

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
void MainWindow::sendMessage(QTcpSocket* socket)
{
    if(socket)
    {
        if(socket->isOpen())
        {
            // 1. ui에서 입력할 message를 가져와
            QString str = ui->lineEdit_message->text();

            // 2. stream으로 보내는데
            QDataStream socketStream(socket);
            socketStream.setVersion(QDataStream::Qt_5_15);

            // 3. 헤더 부분에 fileType을 message로 설정한다.
            QByteArray header;
            header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
            header.resize(128);

            // 1.2 message 인코딩 설정하고, QByteArray에 할당하고
            QByteArray byteArray = str.toUtf8();

            // 3.2 header 정보를 앞에 넣어준다.
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

                // 2. stream으로 보내는데
                QDataStream socketStream(socket);
                socketStream.setVersion(QDataStream::Qt_5_15);

                // 3. 헤더 부분에 fileType을 attachment로 설정한다.
                QByteArray header;
                header.prepend(QString("fileType:attachment,fileName:%1,fileSize:%2;").arg(fileName).arg(m_file.size()).toUtf8());
                header.resize(128);

                // 1.2 QByteArray에 file을 byte로 할당하고
                QByteArray byteArray = m_file.readAll();

                // 3.1 header 정보를 앞에 넣어준다.
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
