#include <iostream>
#include <string>

//-----------------------------------------EXPR CLASS--------------------------------------------------
class Expr{
public:
    virtual bool equals(Expr * e) = 0;
    virtual ~Expr() {}

    virtual bool has_variable() = 0;
    virtual Expr * subst(std::string str, Expr * exp);
    virtual int interp() = 0;
};

//-----------------------------------------VAR EXPR CLASS--------------------------------------------------
class VarExpr: public Expr{
public:
    std::string var;

    VarExpr(std::string var);
    bool equals(Expr * exp) override;
    int interp() override;
    bool has_variable() override;
    Expr * subst(std::string str, Expr * exp) override;
};

//-----------------------------------------NUM EXPR CLASS--------------------------------------------------
class NumExpr: public Expr{
public:
    int x;

    NumExpr(int x){
        this->x = x; }

    bool equals(Expr * exp) override;
    int interp() override;
    bool has_variable() override;
    Expr * subst(std::string str, Expr * exp) override;
};

//-----------------------------------------ADD EXPR CLASS--------------------------------------------------
class AddExpr: public Expr{
public:
    Expr* lhs;
    Expr* rhs;

    AddExpr(Expr* a, Expr* b);
    bool equals(Expr * exp) override;
    int interp() override;
    bool has_variable() override;
    Expr * subst(std::string str, Expr * exp) override;
};

//-----------------------------------------MULTIPLY EXPR CLASS--------------------------------------------------
class MultiplyExpr: public Expr{
public:
    Expr* lhs;
    Expr* rhs;

    MultiplyExpr(Expr* a, Expr* b);
    bool equals(Expr * exp) override;
    int interp() override;
    bool has_variable() override;
    Expr * subst(std::string str, Expr * exp) override;
};
