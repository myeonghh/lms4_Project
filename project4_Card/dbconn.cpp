#include <iostream>
#include <cstring>
#include <mariadb/conncpp.hpp>


// ============================== DB 연결 =====================================
sql::Driver* driver = sql::mariadb::get_driver_instance();
sql::SQLString url("jdbc:mariadb://10.10.20.111:3306/todo");
sql::Properties properties({{"user", "asd"}, {"password", "1234"}});
std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
// ============================================================================

// Delete a task record (indicated by id)
// 미리 문장을 준비시키고 (prepareStatement),?자리에 변수를 대입시킨다.
// executeQuery() 마리아디비 로 쿼리를 문자열로 보내실행 시킨다. 
void deleteTask(std::unique_ptr<sql::Connection> &conn, int id) {
    try {
        // Create a new PreparedStatement
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("delete from User where id = ?"));
        // Bind values to SQL statement
        stmnt->setInt(1, id);
        // Execute query
        stmnt->executeQuery();
    }
    catch(sql::SQLException& e){
        std::cerr << "Error deleting task: " << e.what() << std::endl;
    }
}

// Update the completed value of a task record (indicated by id)
void updateTaskStatus(std::unique_ptr<sql::Connection> &conn, std::string id, std::string pw) {
    try {
        // Create a new PreparedStatement
        // ? 자리의 값은 매개변수로 받아옴 
        // setString(1, pw) : 첫번째 ?자리에 문자열 pw값을 넣겠다.
        
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("update User set pw = ? where id = ?"));
        // Bind values to SQL statement
        stmnt->setString(1, pw);
        stmnt->setString(2, id);
        // Execute query
        stmnt->executeQuery();
    }
    catch(sql::SQLException& e){
        std::cerr << "Error updating task status: " << e.what() << std::endl;
    }
}

// Create a new task record
void addTask(std::unique_ptr<sql::Connection> &conn, std::string id_insert, std::string pw_insert, std::string ph_insert) {
    try {
        std::cout << id_insert,pw_insert,ph_insert; 
        // Create a new PreparedStatement
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("insert into User (id, pw, phone) values (?,?,?)"));
        // Bind values to SQL statement
        stmnt->setString(1, id_insert);
        stmnt->setString(2, pw_insert);
        stmnt->setString(3, ph_insert);
        // Execute query
        stmnt->executeQuery();
    }
    catch(sql::SQLException& e){
        std::cerr << "Error inserting new task: " << e.what() << std::endl;
    }
}

// Print all records in tasks table
void showTasks(std::unique_ptr<sql::Connection> &conn) {
    try {
        // Create a new Statement
        std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
        // Execute query
        sql::ResultSet *res = stmnt->executeQuery("select id,pw,phone from User");
        // Loop through and print results
        //쿼리 실행 끝나고 next()함수를 사용하여 한줄한줄 실행되고 넘어감 
        // while에 next()가 한줄 끝나고 다음줄의 내용이 없을때까지 값을 읽어온다
        // select 쿼리문 사용 시 필요 
        while (res->next()) {
            std::cout << "id = " << res->getString(1);
            std::cout << ", pw = " << res->getString(2);
            std::cout << ", phone = " << res->getString(3) << "\n";
        }
    }
    catch(sql::SQLException& e){
        std::cerr << "Error selecting tasks: " << e.what() << std::endl;
    }
}


// 반환값을 받아서 쿼리문으로 보내는데 받을때는 어떤형태로 받아오는지 확인해야한다. (sql::ResultSet *res 출력해서 클래스에 넣을 거냐 구조체에 넣을거냐 내가 보기 편하게 만들어야한다.)
// 출력을 하게 되는데 ./testdb2 showTasks명령어를 치면 select 로 db쿼리를 보내면 값이 출력된다.
// 터미널 컴파일 명령어 QT는 profile안에서 알아서 찾아서 해라 를 포함시켜놨다.
// profile안에 라이브러리 찾는 옵션 추가해주심 (.pro가 profile) 추가를 안하면 터미널 명령어가 길어짐
// mariadb https://mariadb.com/resources/blog/how-to-connect-c-programs-to-mariadb/ 코드 설명 보면 참고 할 수 있다. 번역을 돌려서 봐보자

// Main Process
int main(int argc, char **argv){

    if (argc==1){
        std::cout << "Please provide an argument.\n";
    }
    else {
        try {
            // Instantiate Driver
            //mariadb 드라이버를 가져와서 시작
            sql::Driver* driver = sql::mariadb::get_driver_instance();

            // Configure Connection
            // (localhost부분)ip를 통해 외부에서 접속가능 / 포트는 마리아db접속 포트 / todo는 DB명 
            // SQLString : url를 통해 
            // Properties : DB 유저 아이디 와 비밀번호 
            sql::SQLString url("jdbc:mariadb://localhost:3306/todo");
            sql::Properties properties({{"user","root"}, { "password","1234"}});

            // Establish Connection
            // url / properties 를 driver 안에 연결 매개변수 url과 properties를 넘긴다. 
            // 연결 요청을 보내는곳 (mariadb와)
            // 
            std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));

            // Use arguments to determine execution next steps
            if (!strcmp(argv[1],"showTasks")) {
                showTasks(conn);
                return 1;
            }
            else if (!strcmp(argv[1],"addTask")) {
                if (argc != 5) {
                    std::cout << "Invalid arguments";
                    return 1;
                }
                addTask(conn, argv[2],argv[3],argv[4]);
            }
            else if (!strcmp(argv[1],"updateTaskStatus")) {
                if (argc != 4) {
                    std::cout << "Invalid arguments";
                    return 1;
                }
                updateTaskStatus(conn, argv[2], argv[3]);
            }
            else if (!strcmp(argv[1],"deleteTask")) {
                if (argc != 3) {
                    std::cout << "Invalid arguments";
                    return 1;
                }
                deleteTask(conn, atoi(argv[2]));
            }

            // Close Connection
            conn->close();
        }
        catch(sql::SQLException& e){
            std::cerr << "Error Connecting to MariaDB Platform: " << e.what() << std::endl;
            // Exit (Failed)
            return 1;
        }
    }

    // Exit (Success)
    return 0;
}
