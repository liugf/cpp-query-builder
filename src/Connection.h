//
// Created by gavin on 20/11/2016.
//

#ifndef CPP_QUERY_BUILDER_CONNECTION_H
#define CPP_QUERY_BUILDER_CONNECTION_H

#include <string>
#include "Builder.h"

using std::string;

namespace cpp_query_builder {

    class Connection {
    public:
        /**
         * Get a new query builder instance.
         * @return
         */
        Builder* Query();

        /**
         * Begin a fluent query against a database table.
         * @param table
         * @return
         */
        Builder* Table(const string &table);

    private:

    };
}

#endif //CPP_QUERY_BUILDER_CONNECTION_H
