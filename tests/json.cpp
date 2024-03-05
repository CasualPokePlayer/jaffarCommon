#include "gtest/gtest.h"
#include <jaffarCommon/json.hpp>

using namespace jaffarCommon::json;

TEST(json, badObject)
{
  nlohmann::json input = std::vector<nlohmann::json>();

  EXPECT_THROW(getString(input, "Entry"), std::logic_error);
  EXPECT_THROW(getObject(input, "Entry"), std::logic_error);
  EXPECT_THROW(getArray<size_t>(input, "Entry"), std::logic_error);
  EXPECT_THROW(getNumber<size_t>(input, "Entry"), std::logic_error);
  EXPECT_THROW(getBoolean(input, "Entry"), std::logic_error);
}

TEST(json, badEntry)
{
  nlohmann::json input = nlohmann::json::parse("{ \"Entry\": { } }");

  EXPECT_THROW(getString(input, "Bad Entry"), std::logic_error);
  EXPECT_THROW(getObject(input, "Bad Entry"), std::logic_error);
  EXPECT_THROW(getArray<size_t>(input, "Bad Entry"), std::logic_error);
  EXPECT_THROW(getNumber<size_t>(input, "Bad Entry"), std::logic_error);
  EXPECT_THROW(getBoolean(input, "Bad Entry"), std::logic_error);
}

TEST(json, badType)
{
  nlohmann::json input = nlohmann::json::parse("{ \"Entry\": 1 }");

  EXPECT_THROW(getString(input, "Entry"), std::logic_error);
  EXPECT_THROW(getObject(input, "Entry"), std::logic_error);
  EXPECT_THROW(getArray<size_t>(input, "Entry"), std::logic_error);
  EXPECT_THROW(getBoolean(input, "Entry"), std::logic_error);

  input = nlohmann::json::parse("{ \"Entry\": \"Hello\" }");
  EXPECT_THROW(getNumber<size_t>(input, "Entry"), std::logic_error);
}

TEST(json, string)
{
  std::string result = "";
  std::string expected = "Hello, World!";
  nlohmann::json input = nlohmann::json::parse(std::string("{ \"Entry\": \"") + expected + std::string("\" }"));
  EXPECT_NO_THROW(result = getString(input, "Entry"));
  EXPECT_EQ(result, expected);
}

TEST(json, object)
{
  nlohmann::json input = nlohmann::json::parse(std::string("{ \"Object\": { \"Entry\": \"Hello, World!\" } }"));
  nlohmann::json result;
  EXPECT_NO_THROW(result = getObject(input, "Object"));
  EXPECT_TRUE(result.is_object());
}

TEST(json, arrayNumber)
{
  nlohmann::json input = nlohmann::json::parse(std::string("{ \"Array\": [0,1,2,3] }"));
  std::vector<int> result;
  EXPECT_NO_THROW(result = getArray<int>(input, "Array"));
  EXPECT_EQ(result.size(), 4);
  EXPECT_EQ(result[0], 0);
  EXPECT_EQ(result[1], 1);
  EXPECT_EQ(result[2], 2);
  EXPECT_EQ(result[3], 3);
}

TEST(json, arrayString)
{
  nlohmann::json input = nlohmann::json::parse(std::string("{ \"Array\": [ \"Hello,\",\" \", \"World!\" ] }"));
  std::vector<std::string> result;
  EXPECT_NO_THROW(result = getArray<std::string>(input, "Array"));
  EXPECT_EQ(result.size(), 3);
  EXPECT_EQ(result[0], "Hello,");
  EXPECT_EQ(result[1], " ");
  EXPECT_EQ(result[2], "World!");
}

TEST(json, number)
{
  int result = 0;
  nlohmann::json input = nlohmann::json::parse(std::string("{ \"Number\": 42 }"));
  EXPECT_NO_THROW(result = getNumber<int>(input, "Number"));
  EXPECT_EQ(result, 42);
}

TEST(json, boolean)
{
  bool result = false;
  nlohmann::json input = nlohmann::json::parse(std::string("{ \"Boolean\": true }"));
  EXPECT_NO_THROW(result = getBoolean(input, "Boolean"));
  EXPECT_EQ(result, true);
}