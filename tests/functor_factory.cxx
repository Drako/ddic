/*********************************************************************
 * Copyright © 2015 - 2016, Felix Bytow <felix.bytow@googlemail.com> *
 *                                                                   *
 * See the file COPYING for copying permissions.                     *
 *********************************************************************/

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <ddic.hxx>

namespace {
  struct IntCreator {
    int* operator()(ddic::container& c) const
    {
      return new int(23);
    }
  };
}

TEST(FunctorFactory, AlwaysNewReturnsDistincObjects)
{
  using ::testing::Ne;

  ddic::container c;
  ddic::functor_factory<ddic::container, int, ddic::creation_policy::always_new> factory(::IntCreator(), c);

  auto obj1 = factory.create();
  auto obj2 = factory.create();

  EXPECT_THAT(obj1, Ne(obj2));
}

TEST(FunctorFactory, AlwaysSameReturnsOneObject)
{
  using ::testing::Eq;

  ddic::container c;
  ddic::functor_factory<ddic::container, int, ddic::creation_policy::always_same> factory(::IntCreator(), c);

  auto obj1 = factory.create();
  auto obj2 = factory.create();

  EXPECT_THAT(obj1, Eq(obj2));
}

TEST(FunctorFactory, ConstructsObjectsUsingFunctor)
{
  using ::testing::Eq;

  ddic::container c;
  ddic::functor_factory<ddic::container, int, ddic::creation_policy::always_new> factory(::IntCreator(), c);
  auto pn = std::static_pointer_cast<int>(factory.create());

  EXPECT_THAT(*pn, Eq(23));
}
