#pragma once
#include <string>

class Expr {
public:
    virtual ~Expr() = default;

    // Evaluate the expression to an int.
    // (This does NOT modify the object.)
    virtual int interp() = 0;

    // Returns true if this expression is a variable
    // or contains any variable anywhere inside it.
    virtual bool has_variable() = 0;

    // Substitute every occurrence of `name` with `replacement`.
    // NOTE: subst must NOT mutate the current expression.
    // It returns a new expression tree.
    virtual Expr* subst(std::string name, Expr* replacement) = 0;

    // You likely already have this from earlier phases:
    virtual bool equals(Expr* e) = 0;
};

// ---- Subclasses ----

class NumExpr : public Expr {
public:
    int val;
    NumExpr(int val);

    int interp() override;
    bool has_variable() override;
    Expr* subst(std::string name, Expr* replacement) override;

    bool equals(Expr* e) override;
};

class VarExpr : public Expr {
public:
    std::string name;
    VarExpr(std::string name);

    int interp() override;
    bool has_variable() override;
    Expr* subst(std::string name, Expr* replacement) override;

    bool equals(Expr* e) override;
};

class AddExpr : public Expr {
public:
    Expr* lhs;
    Expr* rhs;
    AddExpr(Expr* lhs, Expr* rhs);

    int interp() override;
    bool has_variable() override;
    Expr* subst(std::string name, Expr* replacement) override;

    bool equals(Expr* e) override;
};

class MultExpr : public Expr {
public:
    Expr* lhs;
    Expr* rhs;
    MultExpr(Expr* lhs, Expr* rhs);

    int interp() override;
    bool has_variable() override;
    Expr* subst(std::string name, Expr* replacement) override;

    bool equals(Expr* e) override;
};
