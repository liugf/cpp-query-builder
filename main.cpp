#include <iostream>
#include "src/Connection.h"

using namespace cpp_query_builder;

int main() {
    int ret;

    Connection conn;
    Collection collection;
    std::unique_ptr<Builder> query(conn.Table("users"));

    ret = query->Where("name", "gavin")->Where("country", "=", "China")->Where("age", 30)->Get(collection);
    if (ret) {
        return ret;
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}