grammar lang;

program: funcList EOF;
funcList: funcInit*;

funcInit: 'func' NAME '(' argList? ')' '{' statements '}';
argList: NAME (',' NAME)*;

statements: statement*;
statement: varInit | arrInit | assignment | ifStatement | whileStatement | ( call SEMI ) | returnStatement ;

varInit: 'var' NAME '=' expr SEMI;
arrInit: 'array' NAME '[' INT ']' '[' INT ']' SEMI; 
assignment: (NAME | array) '=' expr SEMI;
ifStatement: 'if' '(' expr ')' '{' statements '}' elseStatement?;
elseStatement: 'else' '{' statements '}';
whileStatement: 'while' '(' expr ')' '{' statements '}';
call: NAME '(' callArgList? ')';
callArgList: expr (',' expr)*;
returnStatement: 'return' expr SEMI;

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
COMMENT: '//' ~[\r\n]* -> skip;
