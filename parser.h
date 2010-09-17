#ifndef _PARSER_H_
#define _PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Program;
struct ClassList;
struct ClassDeclaration;
struct ClassBlock;
struct TypeDenoter;
struct ArrayType;
struct VariableDeclarationList;
struct VariableDeclaration;
struct FunctionDeclarationList;
struct FunctionDeclaration;
struct FormalParameterSectionList;
struct FormalParameterSection;
struct IdentifierList;
struct FunctionHeading;
struct FunctionBlock;
struct StatementList;
struct Statement;
struct WhileStatement;
struct IfStatement;
struct AssignmentStatement;
struct PrintStatement;
struct Expression;
struct AdditiveExpression;
struct ObjectInstantiation;
struct VariableAccess;
struct IndexedVariable;
struct ExpressionList;
struct AttributeDesignator;
struct FunctionDesignator;
struct MethodDesignator;
struct ActualParameterList;
struct ActualParameter;
struct MultiplicativeExpression;
struct NegatableExpression;
struct PrimaryExpression;



struct Program {
    char * id;
    ClassList * class_list;
    Program(char* id, ClassList * class_list) : id(id), class_list(class_list) {}
};

struct ClassList {
    ClassDeclaration * item;
    ClassList * next;
    ClassList(ClassDeclaration * item, ClassList * next) : item(item), next(next) {}
};

struct ClassDeclaration {
    char * id;
    char * parent_id;
    ClassBlock * class_block;
    ClassDeclaration(char * id, char * parent_id, ClassBlock * class_block)
        : id(id), parent_id(parent_id), class_block(class_block) {}
};

struct ClassBlock {
    VariableDeclarationList * variables;
    FunctionDeclarationList * functions;
    ClassBlock(VariableDeclarationList * variables, FunctionDeclarationList * functions)
        : variables(variables), functions(functions) {}
};

struct VariableDeclarationList {
    VariableDeclaration * item;
    VariableDeclarationList * next;  
    VariableDeclarationList(VariableDeclaration * item, VariableDeclarationList * next)
        : item(item), next(next) {}
};

struct VariableDeclaration {
    IdentifierList * id_list;
    TypeDenoter * type;
    VariableDeclaration(IdentifierList * id_list, TypeDenoter * type)
        : id_list(id_list), type(type) {}
};

struct IdentifierList {
    char * item; 
    IdentifierList * next;
    IdentifierList(char * item, IdentifierList * next)
        : item(item), next(next) {}
};

struct TypeDenoter {
    enum Type {INTEGER, REAL, CHAR, BOOLEAN, CLASS, ARRAY};
    Type type;
    union {
        char * class_id;
        ArrayType * array_type;
    };
    TypeDenoter(Type type) : type(type) {}
    TypeDenoter(char * class_id) : type(CLASS), class_id(class_id) {}
    TypeDenoter(ArrayType * array_type) : type(ARRAY), array_type(array_type) {}
};

struct ArrayType {
    int min;
    int max;
    TypeDenoter * type;
    ArrayType(int min, int max, TypeDenoter * type) : min(min), max(max), type(type) {}
};

struct FunctionDeclarationList {
    FunctionDeclaration * item;
    FunctionDeclarationList * next;
    FunctionDeclarationList(FunctionDeclaration * item, FunctionDeclarationList * next)
        : item(item), next(next) {}
};

struct FunctionDeclaration {
    FunctionHeading * heading;
    FunctionBlock * block;
    FunctionDeclaration(FunctionHeading * heading, FunctionBlock * block)
        : heading(heading), block(block) {}
};

struct FunctionHeading {
    char * id;
    FormalParameterSectionList * parameter_list;
    FunctionHeading(char * id, FormalParameterSectionList * parameter_list)
        : id(id), parameter_list(parameter_list) {}
};

struct FormalParameterSectionList {
    FormalParameterSection * item;
    FormalParameterSectionList * next;
    FormalParameterSectionList(FormalParameterSection * item, FormalParameterSectionList * next)
        : item(item), next(next) {}
};

struct FormalParameterSection {
    IdentifierList * id_list;
    TypeDenoter * type;
    FormalParameterSection(IdentifierList * id_list, TypeDenoter * type)
        : id_list(id_list), type(type) {}
};

struct FunctionBlock {
    VariableDeclarationList * variables;
    StatementList * statements;
    FunctionBlock(VariableDeclarationList * variables, StatementList * statements)
        : variables(variables), statements(statements) {}
};

struct StatementList {
    Statement * item;
    StatementList * next;
    StatementList(Statement * item, StatementList * next) : item(item), next(next) {}
};

struct Statement {
    enum Type {ASSIGNMENT, IF, PRINT, WHILE, COMPOUND};
    Type type;
    union {
        AssignmentStatement * assignment;
        IfStatement * if_statement;
        PrintStatement * print_statement;
        WhileStatement * while_statement;
        StatementList * compound_statement;
    };
    // TODO: resume writing constructors here
};

struct AssignmentStatement {
    VariableAccess * variable;
    Expression * expression;
};

struct ObjectInstantiation {
    char * id;
    ActualParameterList * parameters;
};

struct IfStatement {
    Expression * expression;
    Statement * then_statement;
    Statement * else_statement;
};

struct PrintStatement {
    Expression * expression;
};

struct WhileStatement {
    Expression * expression;
    Statement * statement;
};

struct VariableAccess {
    enum Type {IDENTIFIER, INDEXED_VARIABLE, ATTRIBUTE};
    Type type;
    union {
        char * id;
        IndexedVariable * indexed_variable;
        AttributeDesignator * attribute;
    };
};

struct IndexedVariable {
    VariableAccess * variable;
    ExpressionList * expression_list;
};

struct ExpressionList {
    Expression * item;
    ExpressionList * next;
};

struct Expression {
    AdditiveExpression * left;
    int relop;
    AdditiveExpression * right;
};

struct AdditiveExpression {
    MultiplicativeExpression * left;
    int addop;
    AdditiveExpression * right;
};

struct MultiplicativeExpression {
    NegatableExpression * left;
    int mulop;
    MultiplicativeExpression * right;
};

struct NegatableExpression {
    enum Type {SIGN, PRIMARY};
    Type type;
    union {
        struct {
            int sign;
            NegatableExpression * next;
        };
        PrimaryExpression * primary_expression;
    };
};

struct PrimaryExpression {
    enum Type {VARIABLE, FUNCTION, METHOD, OBJECT_INSTANTIATION, PARENS, NOT};
    int type;
    union {
        VariableAccess * variable; 
        FunctionDesignator * function;
        MethodDesignator * method;
        Expression * parens_expression;
        PrimaryExpression * not_expression;
    };
};

struct FunctionDesignator {
    char *id;
    ActualParameterList *apl;
};

struct ActualParameterList {
    ActualParameter *ap;
    ActualParameterList *next;
};

struct ActualParameter {
    Expression *e1;
    Expression *e2;
    Expression *e3;
};


struct AttributeDesignator {
    VariableAccess *va;
    char *id;
};

struct MethodDesignator {
    VariableAccess *va;
    FunctionDesignator *fd;
};


Program * parse_input();

#endif

