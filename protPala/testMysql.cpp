#include <mysql/mysql.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

int main() {
    sql::Driver *driver;
    sql::Connection *con;
        sql::ConnectOptionsMap connection_properties;
        connection_properties["hostName"] = "tcp://127.0.0.1:3306";
        connection_properties["userName"] = "wow";
        connection_properties["password"] = "$herlock_H0lmes#";
        connection_properties["OPT_RECONNECT"] = true;
        connection_properties["OPT_CONNECT_TIMEOUT"] = 2147483647;
        sql::Statement *stmt;
        /* Create a connection */
        driver = get_driver_instance();
        con = driver->connect(connection_properties);
        /* Connect to the MySQL test database */
        con->setSchema("tbcGear");
        stmt = con->createStatement();
        // stmt->execute("DROP TABLE IF EXISTS tbcGear");
        delete stmt;
        cout<<__LINE__<<endl;
        con = driver->connect(connection_properties);
        cout<<__LINE__<<endl;
        delete con;
        cout<<__LINE__<<endl;
    return 0;
}