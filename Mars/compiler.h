#ifndef COMPILER_H
#define COMPILER_H

#include "code.h"
#include "scope.h"
#include "ast.h"

struct Code* 
CompileProgram
(struct Ast *ast, struct Environment *env);

struct Code* 
Compile
(struct Ast *ast, struct Environment *env);

struct Code* 
CompileBinaryExpression
(struct Ast *ast, struct Environment *env);

struct Code* 
CompileIdentifier
(struct Ast *ast, struct Environment *env);

struct Code* 
CompileNumberLiteral
(struct Ast *ast, struct Environment *env);

struct Code* 
CompilePrintStatement
(struct Ast *ast, struct Environment *env);

struct Code* 
CompilePushStatement
(struct Ast *ast, struct Environment *env);

struct Code* 
CompilePopStatement
(struct Ast *ast, struct Environment *env);


#endif // COMPILER_H
