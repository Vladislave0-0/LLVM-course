grammar lang;

prog: expr EOF;

expr: left=NUM '+' right=NUM   # Add
    | NUM                      # SingleNum
    ;

NUM: [0-9]+;
PLUS: '+';
WS: [ \t\r\n]+ -> skip;
