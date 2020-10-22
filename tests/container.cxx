/*********************************************************************
 * Copyright © 2015 - 2016, Felix Bytow <felix.bytow@googlemail.com> *
 *                                                                   *
 * See the file COPYING for copying permissions.                     *
 *********************************************************************/

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <ddic.hxx>

#include "binary_expression.hxx"

TEST(Container, AllowsRegisteringDefaultConstructibleTypes)
{
  using ::testing::Eq;

  ddic::container c;
  c.register_type<int>();
  auto pn = c.resolve<int>();

  EXPECT_THAT(*pn, Eq(0));
}

TEST(Container, AllowsRegisteringCopyConstructiblePrototypes)
{
  using ::testing::Eq;

  ddic::container c;
  c.register_type<int>(42);
  auto pn = c.resolve<int>();

  EXPECT_THAT(*pn, Eq(42));
}

// lol, a really really bad test :>
class Aggregator {
public:
  typedef ddic::inject<BinaryExpression> autowire;

  Aggregator(std::shared_ptr<BinaryExpression>&& combiner)
      :combiner_(std::move(combiner))
  {
  }

  int aggregate(int a) { return a; }

  int aggregate(int a, int b) { return combiner_->combine(a, b); }

  template<typename Head1, typename Head2, typename... Tail>
  int aggregate(Head1 h1, Head2 h2, Tail... t)
  {
    int c = combiner_->combine(static_cast<int>(h1), static_cast<int>(h2));
    return aggregate(c, t...);
  }

private:
  std::shared_ptr<BinaryExpression> combiner_;
};

TEST(Container, SupportsPluginsAndAutoWiringAndAliasing)
{
  using ::testing::Eq;

  ddic::container c;
  bool plugin_loaded = c.load_types("ddic_test_plugin");
  ASSERT_THAT(plugin_loaded, Eq(true));

  c.autowire_type<Aggregator>().as("aggregator");
  auto agg = c.resolve<Aggregator>("aggregator");

  auto sum = agg->aggregate(1, 2, 3, 4, 5, 6, 7, 8, 9);
  EXPECT_THAT(sum, Eq(1+2+3+4+5+6+7+8+9));
}
