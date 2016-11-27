//
// Created by gavin on 20/11/2016.
//

#ifndef CPP_QUERY_BUILDER_BUILDER_H
#define CPP_QUERY_BUILDER_BUILDER_H

#include <string>
#include <vector>
#include "Collection.h"
#include "gtest/gtest_prod.h"

using std::string;
using std::vector;
using std::stringstream;

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
  const void *ptr;
};

enum WhereType {
  Basic,
  Null,
  NotNull,
  In,
  NotIn
};

struct WhereItem {
  WhereType type;
  string column;
  string op;
  BasicValue value;
  string boolean;
};

class Builder {
 public:
  Builder *Table(const string &table);
  Builder *Select(const vector<string> columns);

  Builder *Where(const string &column, const string &value);
  Builder *Where(const string &column, const string &op, const string &value);
  Builder *Where(const string &column, const int32_t &value);
  Builder *Where(const string &column, const string &op, const int32_t &value);
  Builder *Where(const string &column, const uint32_t &value);
  Builder *Where(const string &column, const string &op, const uint32_t &value);
  Builder *Where(const string &column, const int64_t &value);
  Builder *Where(const string &column, const string &op, const int64_t &value);
  Builder *Where(const string &column, const uint64_t &value);
  Builder *Where(const string &column, const string &op, const uint64_t &value);
  Builder *Where(const string &column, const float &value);
  Builder *Where(const string &column, const string &op, const float &value);
  Builder *Where(const string &column, const double &value);
  Builder *Where(const string &column, const string &op, const double &value);
  Builder *WhereNull(const string &column);
  Builder *WhereNotNull(const string &column);

  Builder *OrWhere(const string &column, const string &value);
  Builder *OrWhere(const string &column, const string &op, const string &value);
  Builder *OrWhere(const string &column, const int32_t &value);
  Builder *OrWhere(const string &column, const string &op, const int32_t &value);
  Builder *OrWhere(const string &column, const uint32_t &value);
  Builder *OrWhere(const string &column, const string &op, const uint32_t &value);
  Builder *OrWhere(const string &column, const int64_t &value);
  Builder *OrWhere(const string &column, const string &op, const int64_t &value);
  Builder *OrWhere(const string &column, const uint64_t &value);
  Builder *OrWhere(const string &column, const string &op, const uint64_t &value);
  Builder *OrWhere(const string &column, const float &value);
  Builder *OrWhere(const string &column, const string &op, const float &value);
  Builder *OrWhere(const string &column, const double &value);
  Builder *OrWhere(const string &column, const string &op, const double &value);
  Builder *OrWhereNull(const string &column);
  Builder *OrWhereNotNull(const string &column);

  int Get(Collection &collection);
  int BuildSql();

 protected:

  string from_;
  vector<WhereItem> wheres_;
  vector<string> columns_;

  string sql_;
  vector<BasicValue> params_;
};
}

#endif //CPP_QUERY_BUILDER_BUILDER_H
