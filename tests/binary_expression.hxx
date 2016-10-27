#pragma once

/*********************************************************************
 * Copyright © 2015 - 2016, Felix Bytow <felix.bytow@googlemail.com> *
 *                                                                   *
 * See the file COPYING for copying permissions.                     *
 *********************************************************************/

#ifndef BINARY_EXPRESSION_HXX
#define BINARY_EXPRESSION_HXX

struct BinaryExpression
{
    virtual ~BinaryExpression() = default;
    virtual int combine(int a, int b) const = 0;
};

#endif // BINARY_EXPRESSION_HXX
