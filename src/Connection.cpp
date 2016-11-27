//
// Created by gavin on 20/11/2016.
//

#include "Connection.h"

namespace cpp_query_builder {

Builder *Connection::Query() {
  return new Builder;
}

Builder *Connection::Table(const string &table) {
  Builder *query = Query();
  return query->Table(table);
}

}