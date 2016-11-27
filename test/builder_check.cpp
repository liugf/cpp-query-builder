#include "gtest/gtest.h"
#include "test_shadow.h"

namespace cpp_query_builder {

class BuilderTest : public ::testing::Test {

 protected:
  virtual void SetUp() {
    builder_ = new BuilderShadow;
  }

  virtual void TearDown() {
    delete builder_;
  }

  BuilderShadow *builder_;
};

TEST_F(BuilderTest, Table) {
  builder_->Table("users");
  EXPECT_STREQ(builder_->from().c_str(), "users");
}

TEST_F(BuilderTest, Select) {
  builder_->Select({});
  EXPECT_EQ(builder_->columns().size(), 0);

  builder_->Select({"name"});
  EXPECT_EQ(builder_->columns().size(), 1);
  EXPECT_EQ(builder_->columns()[0], "name");

  builder_->Select({"name", "age"});
  EXPECT_EQ(builder_->columns().size(), 2);
  EXPECT_EQ(builder_->columns()[1], "age");
}

TEST_F(BuilderTest, Where) {
  builder_->Where("name", "foo");
  EXPECT_EQ(builder_->wheres().size(), 1);
  EXPECT_EQ(builder_->wheres()[0].type, WhereType::Basic);
  EXPECT_EQ(builder_->wheres()[0].column, "name");
  EXPECT_EQ(builder_->wheres()[0].op, "=");
  EXPECT_EQ(builder_->wheres()[0].boolean, "and");
  EXPECT_EQ(builder_->wheres()[0].value.type, BasicValueType::String);
  EXPECT_EQ(*(string*)builder_->wheres()[0].value.ptr, "foo");

  builder_->Where("nick", "like", "foo%");
  EXPECT_EQ(builder_->wheres().size(), 2);
  EXPECT_EQ(builder_->wheres()[1].type, WhereType::Basic);
  EXPECT_EQ(builder_->wheres()[1].column, "nick");
  EXPECT_EQ(builder_->wheres()[1].op, "like");
  EXPECT_EQ(builder_->wheres()[1].boolean, "and");
  EXPECT_EQ(builder_->wheres()[1].value.type, BasicValueType::String);
  EXPECT_EQ(*(string*)builder_->wheres()[1].value.ptr, "foo%");

  builder_->Where("age", ">", 18);
  EXPECT_EQ(builder_->wheres().size(), 3);
  EXPECT_EQ(builder_->wheres()[2].column, "age");
  EXPECT_EQ(builder_->wheres()[2].value.type, BasicValueType::Int);
  EXPECT_EQ(*(uint32_t*)builder_->wheres()[2].value.ptr, 18);
}

TEST_F(BuilderTest, OrWhere) {
  builder_->OrWhere("name", "foo");
  EXPECT_EQ(builder_->wheres().size(), 1);
  EXPECT_EQ(builder_->wheres()[0].type, WhereType::Basic);
  EXPECT_EQ(builder_->wheres()[0].column, "name");
  EXPECT_EQ(builder_->wheres()[0].op, "=");
  EXPECT_EQ(builder_->wheres()[0].boolean, "or");
  EXPECT_EQ(builder_->wheres()[0].value.type, BasicValueType::String);
  EXPECT_EQ(*(string*)builder_->wheres()[0].value.ptr, "foo");

  builder_->OrWhere("nick", "like", "foo%");
  EXPECT_EQ(builder_->wheres().size(), 2);
  EXPECT_EQ(builder_->wheres()[1].type, WhereType::Basic);
  EXPECT_EQ(builder_->wheres()[1].column, "nick");
  EXPECT_EQ(builder_->wheres()[1].op, "like");
  EXPECT_EQ(builder_->wheres()[1].boolean, "or");
  EXPECT_EQ(builder_->wheres()[1].value.type, BasicValueType::String);
  EXPECT_EQ(*(string*)builder_->wheres()[1].value.ptr, "foo%");

  builder_->OrWhere("age", ">", 18);
  EXPECT_EQ(builder_->wheres().size(), 3);
  EXPECT_EQ(builder_->wheres()[2].column, "age");
  EXPECT_EQ(builder_->wheres()[2].value.type, BasicValueType::Int);
  EXPECT_EQ(*(uint32_t*)builder_->wheres()[2].value.ptr, 18);
}

TEST_F(BuilderTest, WhereNull) {
  builder_->WhereNull("name");
  EXPECT_EQ(builder_->wheres()[0].column, "name");
  EXPECT_EQ(builder_->wheres()[0].type, WhereType::Null);
  EXPECT_EQ(builder_->wheres()[0].boolean, "and");
}

TEST_F(BuilderTest, WhereNotNull) {
  builder_->WhereNotNull("name");
  EXPECT_EQ(builder_->wheres()[0].column, "name");
  EXPECT_EQ(builder_->wheres()[0].type, WhereType::NotNull);
  EXPECT_EQ(builder_->wheres()[0].boolean, "and");
}

TEST_F(BuilderTest, OrWhereNull) {
  builder_->OrWhereNull("name");
  EXPECT_EQ(builder_->wheres()[0].column, "name");
  EXPECT_EQ(builder_->wheres()[0].type, WhereType::Null);
  EXPECT_EQ(builder_->wheres()[0].boolean, "or");
}

TEST_F(BuilderTest, OrWhereNotNull) {
  builder_->OrWhereNotNull("name");
  EXPECT_EQ(builder_->wheres()[0].column, "name");
  EXPECT_EQ(builder_->wheres()[0].type, WhereType::NotNull);
  EXPECT_EQ(builder_->wheres()[0].boolean, "or");
}

TEST_F(BuilderTest, BasicAndSql) {
  builder_->Table("users")->Where("name", "foo")->Where("age", ">", 18)->BuildSql();
  EXPECT_EQ(builder_->sql(), "select * from users where name = ? and age > ? ");
}

TEST_F(BuilderTest, BasicOrSql) {
  builder_->Table("users")->Where("name", "foo")->OrWhere("age", ">", 18)->BuildSql();
  EXPECT_EQ(builder_->sql(), "select * from users where name = ? or age > ? ");
}

}

