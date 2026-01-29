#include <iostream>
#include <string>
#include <stdexcept>
#include "expr.h"

//-----------------------------------------VAR EXPR CLASS--------------------------------------------------
//------Class for variable declaration
VarExpr::VarExpr (std::string var){
    this->var = var;
}

bool VarExpr::equals(Expr * exp) {
    VarExpr *castExp = dynamic_cast<VarExpr*>(exp);
    if (castExp == NULL) return false;
    return this->var == castExp->var;
}

int VarExpr::interp() {
    throw std::runtime_error("Cannot interpret a variable as a number.");
}

bool VarExpr::has_variable() {
    return true;
}

Expr * VarExpr::subst(const std::string str, Expr * exp) {
    if (this->var == str) {
        return exp;
    } return this;
    //return new VarExpr(str);
}

//-----------------------------------------NUM EXPR CLASS--------------------------------------------------
//--------Class for integer declaration
bool NumExpr::equals (Expr * exp){
    NumExpr *castExp = dynamic_cast<NumExpr*>(exp);
    if (castExp == NULL) return false;
    return this->x ==castExp->x;
}

int NumExpr::interp() {
    return this->x;
}
bool NumExpr::has_variable() {
    return false;
}

Expr * NumExpr::subst(std::string str, Expr * exp) {
    //return new NumExpr(x);
    return this;
}

//-----------------------------------------ADD EXPR CLASS--------------------------------------------------
//---------Class for add behaviors
AddExpr::AddExpr(Expr* a, Expr* b){
    this->lhs = a;
    this->rhs = b;
}

bool AddExpr::equals(Expr * exp){
    AddExpr *castExp = dynamic_cast<AddExpr*>(exp);
    if (castExp == NULL) return false;

    return lhs->equals(castExp->lhs) && rhs->equals(castExp->rhs);
}

int AddExpr::interp() {
    return lhs->interp() + rhs->interp();
}

bool AddExpr::has_variable() {
    return lhs->has_variable() || rhs->has_variable();
}

Expr * AddExpr::subst(std::string str, Expr * exp) {
    return new AddExpr(lhs->subst(str, exp), rhs->subst(str, exp));
}

//-----------------------------------------MULTIPLY EXPR CLASS--------------------------------------------------
//--------Class for times behaviors
MultiplyExpr::MultiplyExpr (Expr* a, Expr* b){
    this->lhs = a;
    this->rhs = b;
}

bool MultiplyExpr::equals(Expr * exp){
    MultiplyExpr *castExp = dynamic_cast<MultiplyExpr*>(exp);
    if (castExp == NULL) return false;

    return lhs->equals(castExp->lhs) && rhs->equals(castExp->rhs);
}

int MultiplyExpr::interp() {
    return lhs->interp() * rhs->interp();
}

bool MultiplyExpr::has_variable() {
    return lhs->has_variable() || rhs->has_variable();
}

Expr * MultiplyExpr::subst(std::string str, Expr * exp) {
    return new MultiplyExpr(lhs->subst(str, exp), rhs->subst(str, exp));
}