//
// Created by gavin on 20/11/2016.
//

#include "Builder.h"

namespace cpp_query_builder {

    Builder *Builder::Table(const string &table) {
        from_ = &table;
        return this;
    }

    Builder *Builder::Where(const string &column, const string &value) {
        return Where(column, "=", value);
    }

    Builder *Builder::Where(const string &column, const string &op, const string &value) {
        return this;
    }

    Builder *Builder::Where(const string &column, const int &value) {
        return this;
    }

    int Builder::Get(Collection &collection) {
        return 0;
    }
}