/*********************************************************************
 * Copyright © 2015 - 2016, Felix Bytow <felix.bytow@googlemail.com> *
 *                                                                   *
 * See the file COPYING for copying permissions.                     *
 *********************************************************************/

#include "binary_expression.hxx"

#include <ddic.hxx>

class Adder
    : public BinaryExpression {
public:
  ~Adder() override = default;

  int combine(int a, int b) const override
  {
    return a+b;
  }
};

DDIC_REGISTER_TYPES(c)
{
  // default constructible
  // also has no special abilities, so there really is no use in having multiple instances ;-)
  c->register_type<Adder, ddic::creation_policy::always_same>().as<BinaryExpression>();
  // the alias is necessary because the application does not know about our concrete type
  // so the application requests a generic BinaryExpression... so we have to tell the container that an Adder is a BinaryExpression

  return true;
}
