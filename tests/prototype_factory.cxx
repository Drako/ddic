/*********************************************************************
 * Copyright © 2015 - 2016, Felix Bytow <felix.bytow@googlemail.com> *
 *                                                                   *
 * See the file COPYING for copying permissions.                     *
 *********************************************************************/

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <ddic.hxx>

TEST(PrototypeFactory, AlwaysNewReturnsDistincObjects)
{
  using ::testing::Ne;

  ddic::prototype_factory<int, ddic::creation_policy::always_new> factory(42);
  auto obj1 = factory.create();
  auto obj2 = factory.create();

  EXPECT_THAT(obj1, Ne(obj2));
}

TEST(PrototypeFactory, AlwaysSameReturnsOneObject)
{
  using ::testing::Eq;

  ddic::prototype_factory<int, ddic::creation_policy::always_same> factory(42);
  auto obj1 = factory.create();
  auto obj2 = factory.create();

  EXPECT_THAT(obj1, Eq(obj2));
}

TEST(PrototypeFactory, CopyConstructsObject)
{
  using ::testing::Eq;

  ddic::prototype_factory<int, ddic::creation_policy::always_new> factory(42);
  auto pn = std::static_pointer_cast<int>(factory.create());

  EXPECT_THAT(*pn, Eq(42));
}
