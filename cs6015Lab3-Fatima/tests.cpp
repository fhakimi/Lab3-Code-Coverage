#include "catch.h"
#include "expr.h"


//// ---------------- interp() (10) ----------------

TEST_CASE("interp_num_basic") {
    CHECK( (new NumExpr(7))->interp() == 7 );
}

TEST_CASE("interp_num_zero") {
    CHECK( (new NumExpr(0))->interp() == 0 );
}

TEST_CASE("interp_num_negative") {
    CHECK( (new NumExpr(-12))->interp() == -12 );
}

TEST_CASE("interp_add_simple") {
    CHECK( (new AddExpr(new NumExpr(2), new NumExpr(3)))->interp() == 5 );
}

TEST_CASE("interp_mult_simple") {
    CHECK( (new MultExpr(new NumExpr(4), new NumExpr(5)))->interp() == 20 );
}

TEST_CASE("interp_nested_add") {
    Expr* e = new AddExpr(new AddExpr(new NumExpr(1), new NumExpr(2)),
                          new NumExpr(3));
    CHECK( e->interp() == 6 );
}

TEST_CASE("interp_nested_mult") {
    Expr* e = new MultExpr(new MultExpr(new NumExpr(2), new NumExpr(3)),
                           new NumExpr(4));
    CHECK( e->interp() == 24 );
}

TEST_CASE("interp_mixed_add_mult") {
    Expr* e = new AddExpr(new NumExpr(10),
                          new MultExpr(new NumExpr(2), new NumExpr(3)));
    CHECK( e->interp() == 16 );
}

TEST_CASE("interp_mult_with_add") {
    Expr* e = new MultExpr(new NumExpr(2),
                           new AddExpr(new NumExpr(3), new NumExpr(4)));
    CHECK( e->interp() == 14 );
}

TEST_CASE("interp_var_throws_message") {
    CHECK_THROWS_WITH( (new VarExpr("x"))->interp(), "no value for variable" );
}

// ---------------- has_variable() (10) ----------------

TEST_CASE("has_variable_num_false") {
    CHECK_FALSE( (new NumExpr(5))->has_variable() );
}

TEST_CASE("has_variable_var_true") {
    CHECK( (new VarExpr("x"))->has_variable() );
}

TEST_CASE("has_variable_add_left_var") {
    CHECK( (new AddExpr(new VarExpr("x"), new NumExpr(1)))->has_variable() );
}

TEST_CASE("has_variable_add_right_var") {
    CHECK( (new AddExpr(new NumExpr(1), new VarExpr("x")))->has_variable() );
}

TEST_CASE("has_variable_add_no_var") {
    CHECK_FALSE( (new AddExpr(new NumExpr(1), new NumExpr(2)))->has_variable() );
}

TEST_CASE("has_variable_mult_left_var") {
    CHECK( (new MultExpr(new VarExpr("x"), new NumExpr(2)))->has_variable() );
}

TEST_CASE("has_variable_mult_right_var") {
    CHECK( (new MultExpr(new NumExpr(2), new VarExpr("x")))->has_variable() );
}

TEST_CASE("has_variable_nested_var_deep") {
    Expr* e = new AddExpr(new NumExpr(1),
                          new MultExpr(new NumExpr(2), new VarExpr("x")));
    CHECK( e->has_variable() );
}

TEST_CASE("has_variable_nested_no_var_deep") {
    Expr* e = new AddExpr(new NumExpr(1),
                          new MultExpr(new NumExpr(2), new NumExpr(3)));
    CHECK_FALSE( e->has_variable() );
}

TEST_CASE("has_variable_multiple_vars") {
    Expr* e = new AddExpr(new VarExpr("x"), new VarExpr("y"));
    CHECK( e->has_variable() );
}

// ---------------- subst() (10) ----------------
// These test *behavior* using equals, not pointer identity.

TEST_CASE("subst_num_unchanged") {
    Expr* e = new NumExpr(3);
    Expr* out = e->subst("x", new NumExpr(9));
    CHECK( out->equals(new NumExpr(3)) );
}

TEST_CASE("subst_var_match_to_num") {
    Expr* out = (new VarExpr("x"))->subst("x", new NumExpr(5));
    CHECK( out->equals(new NumExpr(5)) );
}

TEST_CASE("subst_var_no_match_stays_var") {
    Expr* out = (new VarExpr("y"))->subst("x", new NumExpr(5));
    CHECK( out->equals(new VarExpr("y")) );
}

TEST_CASE("subst_add_left") {
    Expr* e = new AddExpr(new VarExpr("x"), new NumExpr(1));
    Expr* out = e->subst("x", new NumExpr(7));
    CHECK( out->equals(new AddExpr(new NumExpr(7), new NumExpr(1))) );
}

TEST_CASE("subst_add_right") {
    Expr* e = new AddExpr(new NumExpr(1), new VarExpr("x"));
    Expr* out = e->subst("x", new NumExpr(7));
    CHECK( out->equals(new AddExpr(new NumExpr(1), new NumExpr(7))) );
}

TEST_CASE("subst_mult_left") {
    Expr* e = new MultExpr(new VarExpr("x"), new NumExpr(2));
    Expr* out = e->subst("x", new NumExpr(9));
    CHECK( out->equals(new MultExpr(new NumExpr(9), new NumExpr(2))) );
}

TEST_CASE("subst_mult_right") {
    Expr* e = new MultExpr(new NumExpr(2), new VarExpr("x"));
    Expr* out = e->subst("x", new NumExpr(9));
    CHECK( out->equals(new MultExpr(new NumExpr(2), new NumExpr(9))) );
}

TEST_CASE("subst_nested_two_occurrences") {
    Expr* e = new AddExpr(new VarExpr("x"),
                          new MultExpr(new NumExpr(2), new VarExpr("x")));
    Expr* out = e->subst("x", new NumExpr(3));
    CHECK( out->equals(new AddExpr(new NumExpr(3),
                                   new MultExpr(new NumExpr(2), new NumExpr(3)))) );
}

TEST_CASE("subst_replace_with_expression") {
    Expr* repl = new AddExpr(new NumExpr(1), new NumExpr(2));
    Expr* out = (new VarExpr("x"))->subst("x", repl);
    CHECK( out->equals(new AddExpr(new NumExpr(1), new NumExpr(2))) );
}

TEST_CASE("subst_no_change_on_tree_without_name") {
    Expr* e = new AddExpr(new NumExpr(1), new NumExpr(2));
    Expr* out = e->subst("x", new NumExpr(9));
    CHECK( out->equals(new AddExpr(new NumExpr(1), new NumExpr(2))) );
}
