## Dependencies

-> https://github.com/redboltz/mqtt_cpp
-> https://github.com/Tencent/rapidjson/
-> https://mariadb.com/docs/server/connect/programming-languages/cpp/install/

The instructions for the installation of the C++ MariaDB connector are in the last link. Version: arm64 Debian 11

## Compilation

g++ -std=c++14 -I mqtt_cpp/include -I rapidjson/include client.cpp -pthread -lmariadbcpp -o collector
