#include "postfix.h"
#include "postfix.cpp"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
	ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, can_put_spaces_after_ops_const_and_alt_in_string)
{
	TPostfix pf;
	string a = { "a+a" };
	string res = StringDecoder(a);
	EXPECT_EQ("a + a", res);
}

TEST(TPostfix, can_set_and_decor_string)
{
	TPostfix pf;
	string a = { "a+a" };
	pf.SetInfix(a);
	EXPECT_EQ(StringDecoder(a), pf.GetInfix());
}


TEST(TPostfix, can_to_postfix_correct_string)
{
	TPostfix pf;
	string a = { "a+a" };
	pf.SetInfix(a);
	EXPECT_EQ("a a +", pf.ToPostfix());
}
TEST(TPostfix, throw_when_try_to_infix_with_incorrect_)
{
	TPostfix pf;
	string a = { "1a+a" };
	ASSERT_ANY_THROW(pf.SetInfix(a););
}
TEST(TPostfix, throw_when_try_to_infix_with_two_alts_or_const_in_row)
{
	TPostfix pf;
	string a = { "a 2" };
	ASSERT_ANY_THROW(pf.SetInfix(a););
}
TEST(TPostfix, throw_when_try_to_infix_with_incorrect_start)
{
	TPostfix pf;
	string a = { "+2-a" };
	ASSERT_ANY_THROW(pf.SetInfix(a););
}
TEST(TPostfix, can_calculate)
{
	TPostfix pf;
	string a = "(5+7)*4+2";
	pf.SetInfix(a);
	pf.ToPostfix();
	EXPECT_EQ(50, pf.Calculate());
}

TEST(TPostfix, correct_postfix)
{
	TPostfix pf;
	string a = "a+b*c/d-e+f";
	pf.SetInfix(a);
	EXPECT_EQ(pf.ToPostfix(), "a b c * d / + e - f +");
}

TEST(TPostfix, correct_ans_a_plus_a)
{
	TPostfix pf;
	string a = "a+a";
	pf.SetInfix(a);
	pf.ToPostfix();
	EXPECT_EQ(2, pf.Calculate("1 1"));
}


