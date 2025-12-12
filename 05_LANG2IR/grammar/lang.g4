grammar lang;

program: funcInit* EOF;

funcInit: 'func' NAME '(' argList? ')' funcBody;
argList: NAME (',' NAME)*;
funcBody: '{' statement* '}';

statements: statement*;
statement: varInit | arrInit | assignment | ifStatement | whileStatement | return | ( call SEMI );

varInit: 'var' NAME '=' expr SEMI;
arrInit: 'array' NAME '[' INT ']' '[' INT ']' SEMI; 
assignment: (NAME | array) '=' expr SEMI;
ifStatement: 'if' '(' expr ')' '{' statements '}' elseStatement?;
elseStatement: 'else' '{' statements '}';
whileStatement: 'while' '(' expr ')' '{' statements '}';
return: 'return' expr SEMI;
call: NAME '(' argList? ')';

array: NAME '[' expr ']' '[' expr ']';

expr: 
    '-' expr |
    expr ( '==' | '!=' | '>' | '>=' | '<' | '<=' ) expr |
    expr ( '*' | '/' | '%' ) expr |
    expr ( '+' | '-' ) expr |
    '(' expr ')' |
    array |
    INT |
    NAME |
    call;

SEMI: ';';
NAME: [a-zA-Z_]+;
INT: [0-9]+;
WS: [ \t\r\n]+ -> skip;
