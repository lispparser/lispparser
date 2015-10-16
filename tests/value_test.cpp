// SExp - A S-Expression Parser for C++
// Copyright (C) 2015 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <gtest/gtest.h>

#include <sstream>

#include "sexp/value.hpp"
#include "sexp/parser.hpp"
#include "sexp/io.hpp"

TEST(ValueTest, construct)
{
  using sexp::Value;

  auto sx_bool = Value::boolean(true);
  ASSERT_EQ(true, sx_bool.as_bool());

  auto sx_integer = Value::integer(12345789);
  ASSERT_EQ(12345789, sx_integer.as_int());

  auto sx_real = Value::real(12345.0f);
  ASSERT_EQ(12345.0f, sx_real.as_float());

  auto sx_symbol = Value::symbol("Symbol");
  ASSERT_EQ("Symbol", sx_symbol.as_string());

  auto sx_string = Value::string("HelloWorld");
  ASSERT_EQ("HelloWorld", sx_string.as_string());

  auto sx_cons = Value::cons(Value::integer(5), Value::nil());
  auto sx_cons2 = Value::cons(std::move(sx_integer), Value::nil());

  ASSERT_EQ(12345789, sx_cons2.get_car().as_int());
  ASSERT_EQ(Value::nil(), sx_cons2.get_cdr());
}

TEST(ValueTest, copy)
{
  sexp::Value sx = sexp::Parser::from_string("(a-symbol #f #t 1 2 3 (4 5 (6 7 8) (9 . 10) \"Hello world\"))");
  sexp::Value sx_copy = sexp::Value(sx);
  ASSERT_EQ(sx, sx_copy);
}

/* EOF */
