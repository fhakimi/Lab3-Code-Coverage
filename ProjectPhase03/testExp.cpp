#include "catch.h"
#include "expr.h"

TEST_CASE("NumExpr equals") {
    CHECK((new NumExpr(13))->equals(new NumExpr(13)));
    CHECK(!(new NumExpr(13))->equals(new NumExpr(14)));
}

TEST_CASE("VarExpr equals") {
    CHECK( (new VarExpr("x"))->equals(new VarExpr("x")));
    CHECK_FALSE( (new VarExpr("x"))->equals(new VarExpr("y")));
    CHECK_FALSE( (new NumExpr(1))->equals(new VarExpr("x")));
}

TEST_CASE("AddExpr equals") {
    CHECK( (new AddExpr(new NumExpr(2),new NumExpr(3)))->equals(new AddExpr(new NumExpr(2),new NumExpr(3)))==true );
    CHECK( (new AddExpr(new NumExpr(2),new NumExpr(3)))->equals(new AddExpr(new NumExpr(3),new NumExpr(2)))==false );
}

TEST_CASE("MultiplyExpr equals") {
    Expr* originalVariable = new VarExpr("test me");
    Expr* dupeVariable = originalVariable;

    CHECK(originalVariable->equals(dupeVariable));
    CHECK(!(new MultiplyExpr(new NumExpr(3), new NumExpr(15)))->equals(new MultiplyExpr(new NumExpr(15), new NumExpr(3))));
}

TEST_CASE("Nested expr") {
    Expr* nest1 = new AddExpr(new NumExpr(1), new MultiplyExpr(new NumExpr(2), new NumExpr(3)));
    Expr* nest2 = new AddExpr(new NumExpr(1), new MultiplyExpr(new NumExpr(2), new NumExpr(3)));
    Expr* nest3 = new AddExpr(new NumExpr(3), new MultiplyExpr(new NumExpr(1), new NumExpr(2)));

    CHECK(nest1->equals(nest2));
    CHECK(!nest1->equals(nest3));

}

TEST_CASE("Combo equals") {
    CHECK((new AddExpr(new VarExpr("x"), new NumExpr(500)))->equals(new AddExpr(new VarExpr("x"), new NumExpr(500))));
    CHECK(!(new AddExpr(new VarExpr("x"), new NumExpr(500)))->equals(new AddExpr(new VarExpr("xylophone"), new NumExpr(500))));
}

TEST_CASE("Exception raised") {
    CHECK_THROWS_WITH( (new VarExpr("x"))->interp(), "no value for variable" );
}


TEST_CASE("Interp test") {
    //--------new basic

    CHECK((new AddExpr(new NumExpr(100), new NumExpr(5)))->interp() == 105);
    CHECK((new MultiplyExpr(new AddExpr(new NumExpr(100), new NumExpr(5)), new NumExpr(2)))->interp() == 210);

    Expr* temp =new AddExpr(new NumExpr(100), new AddExpr(new NumExpr(5), new VarExpr("x")));
    CHECK_THROWS_WITH(temp->interp(), "Cannot interpret a variable as a number.");

    //--------provided

    CHECK( (new MultiplyExpr(new NumExpr(3), new NumExpr(2)))
    ->interp()==6 );
    CHECK( (new AddExpr(new AddExpr(new NumExpr(10), new NumExpr(15)),new AddExpr(new NumExpr(20),new NumExpr(20))))
            ->interp()==65);
}


TEST_CASE("Has_variable test.") {
    //------new

    CHECK_FALSE((new NumExpr(400))->has_variable());
    CHECK(!(new VarExpr("I am a variable!"))->has_variable());

    Expr* temp =new AddExpr(new NumExpr(100), new AddExpr(new NumExpr(5), new VarExpr("x")));
    CHECK(temp->has_variable());

    //------provided

    CHECK( (new AddExpr(new VarExpr("x"), new NumExpr(1)))->has_variable() == true );
    CHECK( (new MultiplyExpr(new NumExpr(2), new NumExpr(1)))->has_variable() == false );
}

TEST_CASE("Subst tests") {
    Expr* temp =new AddExpr(new NumExpr(100), new AddExpr(new NumExpr(5), new VarExpr("xyz")));
    Expr* replacement = temp->subst("xyz", new NumExpr(100));
    CHECK(replacement->equals(new AddExpr(new NumExpr(100), new AddExpr(new NumExpr(5), new VarExpr("100")))));

    Expr* original = new MultiplyExpr(new NumExpr(10), new NumExpr(54));
    Expr* dummyOriginal = original->subst("xyz", new NumExpr(10));
    CHECK(original->equals(new MultiplyExpr(new NumExpr(10), new NumExpr(54))));

    Expr* withVar = new AddExpr(new NumExpr(167), new VarExpr("yo"));
    Expr* replaceVar = withVar->subst("yo", new NumExpr(100));
    CHECK_FALSE(replaceVar->has_variable());
    CHECK(replaceVar->interp()==267);
}