//
// Created by gavin on 20/11/2016.
//

#ifndef CPP_QUERY_BUILDER_BUILDER_H
#define CPP_QUERY_BUILDER_BUILDER_H

#include <string>
#include <vector>
#include "Collection.h"

using std::string;
using std::vector;

namespace cpp_query_builder {

    enum BasicValueType {
        String,
        Int,
        UInt,
        Long,
        ULong,
        Float,
        Double,
    };

    struct BasicValue {
        BasicValueType type;
        const void* ptr;
    };

    enum WhereType {
        Basic,
        Null,
        NotNull
    };

    struct WhereItem {
        WhereType type;
        const string* column;
        const string* op;
        BasicValue value;
        string boolean;
    };

    class Builder {
    public:
        Builder* Table(const string &table);
        Builder* Select(const vector<string> &columns);
        Builder* Where(const string &column, const string &value);
        Builder* Where(const string &column, const string &op, const string &value);
        Builder* Where(const string &column, const int &value);
        Builder* Where(const string &column, const string &op, const int &value);
        Builder* Where(const string &column, const unsigned int &value);
        Builder* Where(const string &column, const string &op, const unsigned int &value);
        Builder* Where(const string &column, const long &value);
        Builder* Where(const string &column, const string &op, const long &value);
        Builder* Where(const string &column, const unsigned long &value);
        Builder* Where(const string &column, const string &op, const unsigned long &value);
        Builder* Where(const string &column, const float &value);
        Builder* Where(const string &column, const string &op, const float &value);
        Builder* Where(const string &column, const double &value);
        Builder* Where(const string &column, const string &op, const double &value);
        Builder* WhereNull(const string &column);
        Builder* WhereNotNull(const string &column);
        int Get(Collection &collection);
        int BuildSql();

    private:
        const string* from_;
        vector<WhereItem> wheres_;
        vector<string> columns_;

        string sql_;
        vector<BasicValue> params_;
    };
}

#endif //CPP_QUERY_BUILDER_BUILDER_H
