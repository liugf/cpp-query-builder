#include <iostream>
#include "src/Connection.h"

using namespace cpp_query_builder;

int main() {
    int ret;

    Connection conn;
    Collection collection;
    std::unique_ptr<Builder> query(conn.Query());

    query->Table("users")->Where("name", "gavin")->Where("weight", 137.56)
            ->Where("country", "=", "China")->Where("age", 30)->Select({"name", "age"});
    ret = query->Get(collection);
    if (ret) {
        return ret;
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}