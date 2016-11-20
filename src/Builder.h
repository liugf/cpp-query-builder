//
// Created by gavin on 20/11/2016.
//

#ifndef CPP_QUERY_BUILDER_BUILDER_H
#define CPP_QUERY_BUILDER_BUILDER_H

#include <string>
#include "Collection.h"

using std::string;

namespace cpp_query_builder {

    class Builder {
    public:
        Builder* Table(const string &table);
        Builder* Where(const string &column, const string &value);
        Builder* Where(const string &column, const string &op, const string &value);
        Builder* Where(const string &column, const int &value);
        int Get(Collection &collection);

    private:
        const string* from_;
    };
}

#endif //CPP_QUERY_BUILDER_BUILDER_H
