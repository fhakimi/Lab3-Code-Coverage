#include "expr.h"
#include <stdexcept>
#include "catch.h"

// ---------------- NumExpr ----------------

NumExpr::NumExpr(int val) : val(val) {}

int NumExpr::interp() {
    // A number already represents its value, so just return it.
    // No recursion needed here.
    return val;
}

bool NumExpr::has_variable() {
    // A number can never contain a variable.
    return false;
}

Expr* NumExpr::subst(std::string name, Expr* replacement) {
    (void)name;
    (void)replacement;
    // Numbers are unaffected by substitution.
    // Return a new NumExpr with the same value.
    return new NumExpr(val);
}

bool NumExpr::equals(Expr* e) {
    auto* other = dynamic_cast<NumExpr*>(e);
    return other != nullptr && other->val == val;
}

// ---------------- VarExpr ----------------

VarExpr::VarExpr(std::string name) : name(name) {}

int VarExpr::interp() {
    // A variable has no numeric value by itself.
    // Interpreting a variable is an error, so throw an exception.
    throw std::runtime_error("no value for variable");
}

bool VarExpr::has_variable() {
    // This expression is a variable, so return true.
    return true;
}

Expr* VarExpr::subst(std::string name, Expr* replacement) {
    // If this variable matches the name we are substituting,
    // replace it with the given expression.
    // Otherwise, return a new variable with the same name.
    if (this->name == name) {
        return replacement;  // see warning below
    }
    return new VarExpr(this->name);
}

bool VarExpr::equals(Expr* e) {
    auto* other = dynamic_cast<VarExpr*>(e);
    return other != nullptr && other->name == name;
}

// ---------------- AddExpr ----------------

AddExpr::AddExpr(Expr* lhs, Expr* rhs) : lhs(lhs), rhs(rhs) {}

int AddExpr::interp() {
    // To interpret an addition, interpret both subexpressions
    // and add their results together.
    return lhs->interp() + rhs->interp();
}

bool AddExpr::has_variable() {
    // An addition has a variable if either subexpression has one.
    return lhs->has_variable() || rhs->has_variable();
}

Expr* AddExpr::subst(std::string name, Expr* replacement) {
    // Perform substitution recursively on both sides
    // and return a new AddExpr with the results.
    return new AddExpr(lhs->subst(name, replacement),
                       rhs->subst(name, replacement));
}

bool AddExpr::equals(Expr* e) {
    auto* other = dynamic_cast<AddExpr*>(e);
    return other != nullptr && lhs->equals(other->lhs) && rhs->equals(other->rhs);
}

// ---------------- MultExpr ----------------

MultExpr::MultExpr(Expr* lhs, Expr* rhs) : lhs(lhs), rhs(rhs) {}

int MultExpr::interp() {
    // To interpret a multiplication, interpret both sides
    // and multiply their results.
    return lhs->interp() * rhs->interp();
}

bool MultExpr::has_variable() {
    // A multiplication has a variable if either side has one.
    return lhs->has_variable() || rhs->has_variable();
}

Expr* MultExpr::subst(std::string name, Expr* replacement) {
    // Perform substitution recursively on both sides
    // and return a new MultExpr with the results.
    return new MultExpr(lhs->subst(name, replacement),
                        rhs->subst(name, replacement));
}

bool MultExpr::equals(Expr* e) {
    auto* other = dynamic_cast<MultExpr*>(e);
    return other != nullptr && lhs->equals(other->lhs) && rhs->equals(other->rhs);
}


