; 01100011 = 99
; |
; 00000111 = 7
; 01100111 = 103

app
    MOVi x1 98
    MOVi x2 7
    OR x3 x1 x2
    DUMP_REG x3
    EXIT
