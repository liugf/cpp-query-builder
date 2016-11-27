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
    where.column = column; \
    where.op = op; \
    where.boolean = "and"; \
    BasicValue basic_value; \
    basic_value.type = BasicValueType::base_value_type; \
    basic_value.ptr = &value; \
    where.value = basic_value; \
    wheres_.push_back(where); \
    return this; \
  }

#define OR_WHERE(param_type, base_value_type) \
  Builder *Builder::OrWhere(const string &column, const string &op, const param_type &value) { \
    WhereItem where; \
    where.type = WhereType::Basic; \
    where.column = column; \
    where.op = op; \
    where.boolean = "or"; \
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

#define OR_WHERE_EQUAL(param_type) \
  Builder *Builder::OrWhere(const string &column, const param_type &value) { \
    return OrWhere(column, "=", value); \
  }

namespace cpp_query_builder {

Builder *Builder::Table(const string &table) {
  from_ = table;
  return this;
}

Builder *Builder::Select(const vector<string> columns) {
  columns_.clear();
  for (int i = 0; i < columns.size(); ++i) {
    columns_.push_back(columns[i]);
  }
  return this;
}

WHERE(string, String)
WHERE(int32_t, Int)
WHERE(uint32_t, UInt)
WHERE(int64_t, Long)
WHERE(uint64_t, ULong)
WHERE(float, Float)
WHERE(double, Double)

WHERE_EQUAL(string)
WHERE_EQUAL(int32_t)
WHERE_EQUAL(uint32_t)
WHERE_EQUAL(int64_t)
WHERE_EQUAL(uint64_t)
WHERE_EQUAL(float)
WHERE_EQUAL(double)

OR_WHERE(string, String)
OR_WHERE(int32_t, Int)
OR_WHERE(uint32_t, UInt)
OR_WHERE(int64_t, Long)
OR_WHERE(uint64_t, ULong)
OR_WHERE(float, Float)
OR_WHERE(double, Double)

OR_WHERE_EQUAL(string)
OR_WHERE_EQUAL(int32_t)
OR_WHERE_EQUAL(uint32_t)
OR_WHERE_EQUAL(int64_t)
OR_WHERE_EQUAL(uint64_t)
OR_WHERE_EQUAL(float)
OR_WHERE_EQUAL(double)

Builder *Builder::WhereNull(const string &column) {
  WhereItem where;
  where.type = WhereType::Null;
  where.column = column;
  where.boolean = "and";
  wheres_.push_back(where);
  return this;
}

Builder *Builder::WhereNotNull(const string &column) {
  WhereItem where;
  where.type = WhereType::NotNull;
  where.column = column;
  where.boolean = "and";
  wheres_.push_back(where);
  return this;
}

Builder *Builder::OrWhereNull(const string &column) {
  WhereItem where;
  where.type = WhereType::Null;
  where.column = column;
  where.boolean = "or";
  wheres_.push_back(where);
  return this;
}

Builder *Builder::OrWhereNotNull(const string &column) {
  WhereItem where;
  where.type = WhereType::NotNull;
  where.column = column;
  where.boolean = "or";
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
      const string *value_ptr = (const string *) where.value.ptr;
      std::cout << where.column << ":" << *value_ptr << std::endl;
    }
    if (where.value.type == BasicValueType::Int) {
      const int *value_ptr = (const int *) where.value.ptr;
      std::cout << where.column << ":" << *value_ptr << std::endl;
    }
    if (where.value.type == BasicValueType::Float) {
      const float *value_ptr = (const float *) where.value.ptr;
      std::cout << where.column << ":" << *value_ptr << std::endl;
    }
    if (where.value.type == BasicValueType::Double) {
      const double *value_ptr = (const double *) where.value.ptr;
      std::cout << where.column << ":" << *value_ptr << std::endl;
    }
  }

  return 0;
}

int Builder::BuildSql() {
  params_.clear();
  std::stringstream sql;
  sql << "select ";

  if (columns_.size()) {
    for (int i = 0; i < columns_.size(); ++i) {
      if (i == 0) {
        if (columns_.size() > 1) {
          sql << columns_[i];
        } else {
          sql << columns_[i] << " ";
        }
      } else {
        sql << ", " << columns_[i];
      }
    }
    sql << " ";
  } else {
    sql << "* ";
  }

  sql << "from " << from_ << " where ";

  for (int i = 0; i < wheres_.size(); ++i) {
    WhereItem where = wheres_[i];

    if (where.type == WhereType::Basic) {
      if (i == 0) {
        sql << where.column << " " << where.op << " ? ";
      } else {
        sql << where.boolean << " " << where.column << " " << where.op << " ? ";
      }
      params_.push_back(where.value);
    }


  }

  sql_ = sql.str();

  return 0;
}

}