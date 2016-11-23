//
// Created by gavin on 20/11/2016.
//

#include <sstream>
#include <iostream>
#include "Builder.h"

#define WHERE(param_type, base_value_type) \
    Builder *Builder::Where(const string &column, const string &op, const param_type &value) { \
        
        WhereItem where; \
        where.type = WhereType::Basic; \
        where.column = &column; \
        where.op = &op; \
        where.boolean = "and"; \
        BasicValue basic_value; \
        basic_value.type = BasicValueType::base_value_type; \
        basic_value.ptr = &value; \
        where.value = basic_value; \
        wheres_.push_back(where); \
        return this; \
    }

#define WHERE_EQUAL(param_type) \
    Builder *Builder::Where(const string &column, const param_type &value) { \
        return Where(column, "=", value); \
    }

namespace cpp_query_builder {

    Builder *Builder::Table(const string &table) {
        from_ = &table;
        return this;
    }

    Builder *Builder::Select(const vector<string> &columns) {
        for (int i = 0; i < columns.size(); ++i) {
            columns_.push_back(columns[i]);
        }
        return this;
    }

    WHERE(string, String)
    WHERE(int, Int)
    WHERE(unsigned int, UInt)
    WHERE(long, Long)
    WHERE(unsigned long, ULong)
    WHERE(float , Float)
    WHERE(double , Double)

    WHERE_EQUAL(string)
    WHERE_EQUAL(int)
    WHERE_EQUAL(unsigned int)
    WHERE_EQUAL(long)
    WHERE_EQUAL(unsigned long)
    WHERE_EQUAL(float)
    WHERE_EQUAL(double)

    Builder *Builder::WhereNull(const string &column) {
        WhereItem where;
        where.type = WhereType::Null;
        where.column = &column;
        where.boolean = "and";
        wheres_.push_back(where);
        return this;
    }

    Builder *Builder::WhereNotNull(const string &column) {
        WhereItem where;
        where.type = WhereType::NotNull;
        where.column = &column;
        where.boolean = "and";
        wheres_.push_back(where);
        return this;
    }

    int Builder::Get(Collection &collection) {
        int ret = BuildSql();
        if (ret) {
            return ret;
        }

        std::cout << sql_ << std::endl;


        for (int i = 0; i < wheres_.size(); ++i) {
            WhereItem where = wheres_[i];

            if (where.value.type == BasicValueType::String) {
                const string* value_ptr = (const string*)where.value.ptr;
                std::cout << *where.column << ":" << *value_ptr << std::endl;
            }
            if (where.value.type == BasicValueType::Int) {
                const int* value_ptr = (const int*)where.value.ptr;
                std::cout << *where.column << ":" << *value_ptr << std::endl;
            }
            if (where.value.type == BasicValueType::Float) {
                const float* value_ptr = (const float*)where.value.ptr;
                std::cout << *where.column << ":" << *value_ptr << std::endl;
            }
            if (where.value.type == BasicValueType::Double) {
                const double* value_ptr = (const double*)where.value.ptr;
                std::cout << *where.column << ":" << *value_ptr << std::endl;
            }
        }

        for (int j = 0; j < columns_.size(); ++j) {
            std::cout << columns_[j] << std::endl;
        }
        return 0;
    }

    int Builder::BuildSql() {
        std::stringstream sql;
        sql << "select ";

        if (columns_.size()) {
            for (int i = 0; i < columns_.size(); ++i) {
                if (i == 0) {
                    sql << columns_[i] << " ";
                } else {
                    sql << ", " << columns_[i] << " ";
                }
            }
        } else {
            sql << "* ";
        }

        sql << " from " << *from_ << " where ";

        for (int i = 0; i < wheres_.size(); ++i) {
            WhereItem where = wheres_[i];

            if (i == 0) {
                sql << *where.column << " " << *where.op << " ? ";
            } else {
                sql << where.boolean << " " << *where.column << " " << *where.op << " ? ";
            }

            params_.push_back(where.value);
        }

        sql_ = sql.str();

        return 0;
    }


}