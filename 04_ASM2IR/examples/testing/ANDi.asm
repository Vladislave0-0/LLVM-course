; 00111111 = 63
; &
; 00000111 = 7
; 00000111 = 7

app
    MOVi x1 7
    ANDi x2 x1 63
    DUMP_REG x2
    EXIT
