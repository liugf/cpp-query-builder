#include <iostream>
#include "src/Connection.h"

using namespace cpp_query_builder;

int main() {
    int ret;

    Connection conn;
    Collection collection;
    std::unique_ptr<Builder> query(conn.Query());

    query->Table("users")->Where("name", "=", "gavin")->Where("age", ">", 30);
    query->Select({"name", "age"});
    ret = query->Get(collection);
    if (ret) {
        return ret;
    }

    return 0;
}