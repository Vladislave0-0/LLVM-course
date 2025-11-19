; 01100011 = 99
; &
; 00000111 = 7
; 00000011 = 3

app
    MOVi x1 99
    MOVi x2 7
    AND x3 x2 x1
    DUMP_REG x3
    EXIT
