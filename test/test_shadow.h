//
// Created by gavin on 27/11/2016.
//

#ifndef CPP_QUERY_BUILDER_TEST_SHADOW_H
#define CPP_QUERY_BUILDER_TEST_SHADOW_H

#include <Builder.h>

namespace cpp_query_builder {

class BuilderShadow : public Builder {
 public:
  const string &from() const {
    return from_;
  }

  const vector<WhereItem> &wheres() const {
    return wheres_;
  }

  const vector<string> &columns() const {
    return columns_;
  }

  const string &sql() const {
    return sql_;
  }

  const vector<BasicValue> &params() const {
    return params_;
  }
};

}

#endif //CPP_QUERY_BUILDER_TEST_SHADOW_H
