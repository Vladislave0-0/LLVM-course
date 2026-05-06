	.file	"LANG2IR"
	.text
	.globl	validCell                       ; -- Begin function validCell
	.type	validCell,@function
validCell:                              ; @validCell
; %bb.0:                                ; %entry
	ADDi ZAKROM ZAKROM -8
	SW BALALAIKA ZAKROM 4
	SW GUSLI ZAKROM 0
	CMP_GTi LAPTI GUSLI -1
	BR_COND LAPTI .LBB0_2
	B .LBB0_1
.LBB0_2:                                ; %afterIfBB
	LW LAPTI ZAKROM 4
	CMP_GTi LAPTI LAPTI -1
	BR_COND LAPTI .LBB0_3
	B .LBB0_1
.LBB0_3:                                ; %afterIfBB3
	LW LAPTI ZAKROM 0
	CMP_LTi LAPTI LAPTI 32
	BR_COND LAPTI .LBB0_4
	B .LBB0_1
.LBB0_4:                                ; %afterIfBB8
	LW LAPTI ZAKROM 4
	CMP_LTi LAPTI LAPTI 32
	BR_COND LAPTI .LBB0_5
.LBB0_1:                                ; %ifBodyBB
	MOVi GUSLI 0
	ADDi ZAKROM ZAKROM 8
	BR LESHY
.LBB0_5:                                ; %afterIfBB12
	MOVi GUSLI 1
	ADDi ZAKROM ZAKROM 8
	BR LESHY
.Lfunc_end0:
	.size	validCell, .Lfunc_end0-validCell
                                        ; -- End function
	.globl	drawLiveCell                    ; -- Begin function drawLiveCell
	.type	drawLiveCell,@function
drawLiveCell:                           ; @drawLiveCell
; %bb.0:                                ; %entry
	ADDi ZAKROM ZAKROM -36
	SW LESHY ZAKROM 32
	SW ZAKROM ZAKROM 28
	SW BALALAIKA ZAKROM 4
	SW GUSLI ZAKROM 0
	SW PLYAS ZAKROM 8
	LW BALALAIKA ZAKROM 4
	LW GUSLI ZAKROM 0
	CALL validCell
	CMP_NEi LAPTI GUSLI 0
	BR_COND LAPTI .LBB1_2
	B .LBB1_1
.LBB1_2:                                ; %afterIfBB
	MOVi LESHY 0
	SW LESHY ZAKROM 20
	LW LAPTI ZAKROM 0
	SHLi LAPTI LAPTI 4
	SW LAPTI ZAKROM 12
	LW LAPTI ZAKROM 4
	SHLi LAPTI LAPTI 4
	SW LAPTI ZAKROM 16
	B .LBB1_3
.LBB1_7:                                ; %afterWhileBB8
                                        ;   in Loop: Header=BB1_3 Depth=1
	LW LAPTI ZAKROM 20
	ADDi LAPTI LAPTI 1
	SW LAPTI ZAKROM 20
.LBB1_3:                                ; %whileCondBB
                                        ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB1_5 Depth 2
	LW LAPTI ZAKROM 20
	CMP_GTi LAPTI LAPTI 15
	BR_COND LAPTI .LBB1_1
; %bb.4:                                ; %whileBodyBB
                                        ;   in Loop: Header=BB1_3 Depth=1
	SW LESHY ZAKROM 24
.LBB1_5:                                ; %whileCondBB6
                                        ;   Parent Loop BB1_3 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	LW LAPTI ZAKROM 24
	CMP_GTi LAPTI LAPTI 15
	BR_COND LAPTI .LBB1_7
; %bb.6:                                ; %whileBodyBB7
                                        ;   in Loop: Header=BB1_5 Depth=2
	LW LAPTI ZAKROM 24
	LW TROPKA ZAKROM 12
	ADD GUSLI TROPKA LAPTI
	LW LAPTI ZAKROM 20
	LW TROPKA ZAKROM 16
	ADD BALALAIKA TROPKA LAPTI
	LW PLYAS ZAKROM 8
	CALL llvm.rus.simPutPixel
	LW LAPTI ZAKROM 24
	ADDi LAPTI LAPTI 1
	SW LAPTI ZAKROM 24
	B .LBB1_5
.LBB1_1:                                ; %ifBodyBB
	MOVi GUSLI 0
	LW ZAKROM ZAKROM 28
	LW LESHY ZAKROM 32
	ADDi ZAKROM ZAKROM 36
	BR LESHY
.Lfunc_end1:
	.size	drawLiveCell, .Lfunc_end1-drawLiveCell
                                        ; -- End function
	.globl	drawGrid                        ; -- Begin function drawGrid
	.type	drawGrid,@function
drawGrid:                               ; @drawGrid
; %bb.0:                                ; %entry
	ADDi ZAKROM ZAKROM -44
	SW LESHY ZAKROM 40
	SW ZAKROM ZAKROM 36
	MOVi LAPTI 512
	SW LAPTI ZAKROM 4
	SW LAPTI ZAKROM 0
	MOVi LAPTI 6908265
	SW LAPTI ZAKROM 8
	MOVi LESHY 0
	SW LESHY ZAKROM 12
	B .LBB2_1
.LBB2_5:                                ; %afterWhileBB4
                                        ;   in Loop: Header=BB2_1 Depth=1
	LW LAPTI ZAKROM 12
	ADDi LAPTI LAPTI 1
	SW LAPTI ZAKROM 12
.LBB2_1:                                ; %whileCondBB
                                        ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB2_3 Depth 2
	LW LAPTI ZAKROM 12
	CMP_GTi LAPTI LAPTI 31
	BR_COND LAPTI .LBB2_6
; %bb.2:                                ; %whileBodyBB
                                        ;   in Loop: Header=BB2_1 Depth=1
	SW LESHY ZAKROM 20
	LW LAPTI ZAKROM 12
	SHLi LAPTI LAPTI 4
	SW LAPTI ZAKROM 16
.LBB2_3:                                ; %whileCondBB2
                                        ;   Parent Loop BB2_1 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	LW LAPTI ZAKROM 0
	LW TROPKA ZAKROM 20
	CMP_GE LAPTI TROPKA LAPTI
	BR_COND LAPTI .LBB2_5
; %bb.4:                                ; %whileBodyBB3
                                        ;   in Loop: Header=BB2_3 Depth=2
	LW PLYAS ZAKROM 8
	LW BALALAIKA ZAKROM 20
	LW GUSLI ZAKROM 16
	CALL llvm.rus.simPutPixel
	LW LAPTI ZAKROM 20
	ADDi LAPTI LAPTI 1
	SW LAPTI ZAKROM 20
	B .LBB2_3
.LBB2_6:                                ; %afterWhileBB
	MOVi LESHY 0
	SW LESHY ZAKROM 24
	B .LBB2_7
.LBB2_11:                               ; %afterWhileBB23
                                        ;   in Loop: Header=BB2_7 Depth=1
	LW LAPTI ZAKROM 24
	ADDi LAPTI LAPTI 1
	SW LAPTI ZAKROM 24
.LBB2_7:                                ; %whileCondBB14
                                        ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB2_9 Depth 2
	LW LAPTI ZAKROM 24
	CMP_GTi LAPTI LAPTI 31
	BR_COND LAPTI .LBB2_12
; %bb.8:                                ; %whileBodyBB15
                                        ;   in Loop: Header=BB2_7 Depth=1
	SW LESHY ZAKROM 32
	LW LAPTI ZAKROM 24
	SHLi LAPTI LAPTI 4
	SW LAPTI ZAKROM 28
.LBB2_9:                                ; %whileCondBB21
                                        ;   Parent Loop BB2_7 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	LW LAPTI ZAKROM 4
	LW TROPKA ZAKROM 32
	CMP_GE LAPTI TROPKA LAPTI
	BR_COND LAPTI .LBB2_11
; %bb.10:                               ; %whileBodyBB22
                                        ;   in Loop: Header=BB2_9 Depth=2
	LW PLYAS ZAKROM 8
	LW BALALAIKA ZAKROM 28
	LW GUSLI ZAKROM 32
	CALL llvm.rus.simPutPixel
	LW LAPTI ZAKROM 32
	ADDi LAPTI LAPTI 1
	SW LAPTI ZAKROM 32
	B .LBB2_9
.LBB2_12:                               ; %afterWhileBB16
	MOVi GUSLI 0
	LW ZAKROM ZAKROM 36
	LW LESHY ZAKROM 40
	ADDi ZAKROM ZAKROM 44
	BR LESHY
.Lfunc_end2:
	.size	drawGrid, .Lfunc_end2-drawGrid
                                        ; -- End function
	.globl	app                             ; -- Begin function app
	.type	app,@function
app:                                    ; @app
; %bb.0:                                ; %entry
	ADDi ZAKROM ZAKROM -8308
	SW LESHY ZAKROM 8304
	SW ZAKROM ZAKROM 8300
	SW SHALOPAY ZAKROM 8296
	SW YARILO ZAKROM 8292
	SW YAGA ZAKROM 8288
	SW VYAZ ZAKROM 8284
	MOVi LAPTI 512
	SW LAPTI ZAKROM 4
	SW LAPTI ZAKROM 0
	MOVi LAPTI 6591981
	SW LAPTI ZAKROM 8
	MOVi LAPTI -1
	SW LAPTI ZAKROM 12
	MOVi SHALOPAY 0
	SW SHALOPAY ZAKROM 8208
	ADDi LESHY ZAKROM 16
	B .LBB3_1
.LBB3_5:                                ; %afterWhileBB3
                                        ;   in Loop: Header=BB3_1 Depth=1
	LW LAPTI ZAKROM 8208
	ADDi LAPTI LAPTI 1
	SW LAPTI ZAKROM 8208
.LBB3_1:                                ; %whileCondBB
                                        ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB3_3 Depth 2
	LW LAPTI ZAKROM 8208
	CMP_GTi LAPTI LAPTI 31
	BR_COND LAPTI .LBB3_6
; %bb.2:                                ; %whileBodyBB
                                        ;   in Loop: Header=BB3_1 Depth=1
	SW SHALOPAY ZAKROM 8212
.LBB3_3:                                ; %whileCondBB1
                                        ;   Parent Loop BB3_1 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	LW LAPTI ZAKROM 8212
	CMP_GTi LAPTI LAPTI 31
	BR_COND LAPTI .LBB3_5
; %bb.4:                                ; %whileBodyBB2
                                        ;   in Loop: Header=BB3_3 Depth=2
	LW LAPTI ZAKROM 8208
	SHLi LAPTI LAPTI 7
	ADD LAPTI LESHY LAPTI
	LW TROPKA ZAKROM 8212
	SHLi TROPKA TROPKA 2
	ADD YARILO LAPTI TROPKA
	CALL llvm.rus.simRand
	SRLi LAPTI GUSLI 31
	ADD LAPTI GUSLI LAPTI
	ANDi LAPTI LAPTI -2
	SUB LAPTI GUSLI LAPTI
	SW LAPTI YARILO 0
	LW LAPTI ZAKROM 8212
	ADDi LAPTI LAPTI 1
	SW LAPTI ZAKROM 8212
	B .LBB3_3
.LBB3_6:                                ; %afterWhileBB
	MOVi SHALOPAY 0
	SW SHALOPAY ZAKROM 8216
	MOVi YARILO -1
	MOVi YAGA 1
	ADDi VYAZ ZAKROM 4112
	B .LBB3_7
.LBB3_52:                               ; %afterWhileBB135
                                        ;   in Loop: Header=BB3_7 Depth=1
	CALL drawGrid
	CALL llvm.rus.simFlush
	LW LAPTI ZAKROM 8216
	ADDi LAPTI LAPTI 1
	SW LAPTI ZAKROM 8216
.LBB3_7:                                ; %whileCondBB11
                                        ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB3_9 Depth 2
                                        ;       Child Loop BB3_11 Depth 3
                                        ;         Child Loop BB3_13 Depth 4
                                        ;           Child Loop BB3_15 Depth 5
                                        ;     Child Loop BB3_30 Depth 2
                                        ;       Child Loop BB3_32 Depth 3
                                        ;     Child Loop BB3_36 Depth 2
                                        ;       Child Loop BB3_38 Depth 3
                                        ;     Child Loop BB3_42 Depth 2
                                        ;       Child Loop BB3_44 Depth 3
	LW LAPTI ZAKROM 8216
	CMP_GTi LAPTI LAPTI 9999
	BR_COND LAPTI .LBB3_48
; %bb.8:                                ; %whileBodyBB12
                                        ;   in Loop: Header=BB3_7 Depth=1
	SW SHALOPAY ZAKROM 8220
	B .LBB3_9
.LBB3_49:                               ; %afterWhileBB23
                                        ;   in Loop: Header=BB3_9 Depth=2
	LW LAPTI ZAKROM 8220
	ADDi LAPTI LAPTI 1
	SW LAPTI ZAKROM 8220
.LBB3_9:                                ; %whileCondBB16
                                        ;   Parent Loop BB3_7 Depth=1
                                        ; =>  This Loop Header: Depth=2
                                        ;       Child Loop BB3_11 Depth 3
                                        ;         Child Loop BB3_13 Depth 4
                                        ;           Child Loop BB3_15 Depth 5
	LW LAPTI ZAKROM 8220
	CMP_GTi LAPTI LAPTI 31
	BR_COND LAPTI .LBB3_29
; %bb.10:                               ; %whileBodyBB17
                                        ;   in Loop: Header=BB3_9 Depth=2
	SW SHALOPAY ZAKROM 8224
	B .LBB3_11
.LBB3_24:                               ; %afterIfBB85
                                        ;   in Loop: Header=BB3_11 Depth=3
	LW LAPTI ZAKROM 8220
	SHLi LAPTI LAPTI 7
	ADD LAPTI VYAZ LAPTI
	LW TROPKA ZAKROM 8224
	SHLi TROPKA TROPKA 2
	ADD LAPTI LAPTI TROPKA
	LW TROPKA ZAKROM 8256
	SW TROPKA LAPTI 0
	LW LAPTI ZAKROM 8224
	ADDi LAPTI LAPTI 1
	SW LAPTI ZAKROM 8224
.LBB3_11:                               ; %whileCondBB21
                                        ;   Parent Loop BB3_7 Depth=1
                                        ;     Parent Loop BB3_9 Depth=2
                                        ; =>    This Loop Header: Depth=3
                                        ;         Child Loop BB3_13 Depth 4
                                        ;           Child Loop BB3_15 Depth 5
	LW LAPTI ZAKROM 8224
	CMP_GTi LAPTI LAPTI 31
	BR_COND LAPTI .LBB3_49
; %bb.12:                               ; %whileBodyBB22
                                        ;   in Loop: Header=BB3_11 Depth=3
	SW YARILO ZAKROM 8232
	SW SHALOPAY ZAKROM 8228
	B .LBB3_13
.LBB3_50:                               ; %afterWhileBB32
                                        ;   in Loop: Header=BB3_13 Depth=4
	LW LAPTI ZAKROM 8232
	ADDi LAPTI LAPTI 1
	SW LAPTI ZAKROM 8232
.LBB3_13:                               ; %whileCondBB26
                                        ;   Parent Loop BB3_7 Depth=1
                                        ;     Parent Loop BB3_9 Depth=2
                                        ;       Parent Loop BB3_11 Depth=3
                                        ; =>      This Loop Header: Depth=4
                                        ;           Child Loop BB3_15 Depth 5
	LW LAPTI ZAKROM 8232
	CMP_GTi LAPTI LAPTI 1
	BR_COND LAPTI .LBB3_21
; %bb.14:                               ; %whileBodyBB27
                                        ;   in Loop: Header=BB3_13 Depth=4
	SW YARILO ZAKROM 8236
	B .LBB3_15
.LBB3_20:                               ; %afterIfBB43
                                        ;   in Loop: Header=BB3_15 Depth=5
	LW LAPTI ZAKROM 8236
	ADDi LAPTI LAPTI 1
	SW LAPTI ZAKROM 8236
.LBB3_15:                               ; %whileCondBB30
                                        ;   Parent Loop BB3_7 Depth=1
                                        ;     Parent Loop BB3_9 Depth=2
                                        ;       Parent Loop BB3_11 Depth=3
                                        ;         Parent Loop BB3_13 Depth=4
                                        ; =>        This Inner Loop Header: Depth=5
	LW LAPTI ZAKROM 8236
	CMP_GTi LAPTI LAPTI 1
	BR_COND LAPTI .LBB3_50
; %bb.16:                               ; %whileBodyBB31
                                        ;   in Loop: Header=BB3_15 Depth=5
	SW SHALOPAY ZAKROM 8240
	LW LAPTI ZAKROM 8232
	CMP_EQi LAPTI LAPTI 0
	BR_COND LAPTI .LBB3_17
	B .LBB3_18
.LBB3_17:                               ; %ifBodyBB
                                        ;   in Loop: Header=BB3_15 Depth=5
	LW LAPTI ZAKROM 8236
	CMP_EQi LAPTI LAPTI 0
	BR_COND LAPTI .LBB3_51
	B .LBB3_18
.LBB3_51:                               ; %ifBodyBB37
                                        ;   in Loop: Header=BB3_15 Depth=5
	SW YAGA ZAKROM 8240
.LBB3_18:                               ; %afterIfBB
                                        ;   in Loop: Header=BB3_15 Depth=5
	LW LAPTI ZAKROM 8240
	CMP_EQi LAPTI LAPTI 0
	BR_COND LAPTI .LBB3_19
	B .LBB3_20
.LBB3_19:                               ; %ifBodyBB42
                                        ;   in Loop: Header=BB3_15 Depth=5
	LW LAPTI ZAKROM 8236
	LW TROPKA ZAKROM 8220
	ADD LAPTI TROPKA LAPTI
	ADDi LAPTI LAPTI 32
	SRAi TROPKA LAPTI 31
	SRLi TROPKA TROPKA 27
	ADD TROPKA LAPTI TROPKA
	ANDi TROPKA TROPKA -32
	SUB LAPTI LAPTI TROPKA
	LW TROPKA ZAKROM 8232
	LW GUSLI ZAKROM 8224
	ADD TROPKA GUSLI TROPKA
	SW LAPTI ZAKROM 8248
	SHLi LAPTI LAPTI 7
	ADD LAPTI LESHY LAPTI
	ADDi TROPKA TROPKA 32
	SRAi GUSLI TROPKA 31
	SRLi GUSLI GUSLI 27
	ADD GUSLI TROPKA GUSLI
	ANDi GUSLI GUSLI -32
	SUB TROPKA TROPKA GUSLI
	SW TROPKA ZAKROM 8244
	SHLi TROPKA TROPKA 2
	ADD LAPTI LAPTI TROPKA
	LW LAPTI LAPTI 0
	LW TROPKA ZAKROM 8228
	ADD LAPTI TROPKA LAPTI
	SW LAPTI ZAKROM 8228
	B .LBB3_20
.LBB3_21:                               ; %afterWhileBB28
                                        ;   in Loop: Header=BB3_11 Depth=3
	LW LAPTI ZAKROM 8220
	SHLi LAPTI LAPTI 7
	ADD LAPTI LESHY LAPTI
	LW TROPKA ZAKROM 8224
	SHLi TROPKA TROPKA 2
	ADD LAPTI LAPTI TROPKA
	LW LAPTI LAPTI 0
	SW SHALOPAY ZAKROM 8256
	SW LAPTI ZAKROM 8252
	CMP_EQi LAPTI LAPTI 1
	BR_COND LAPTI .LBB3_25
	B .LBB3_22
.LBB3_25:                               ; %ifBodyBB70
                                        ;   in Loop: Header=BB3_11 Depth=3
	LW LAPTI ZAKROM 8228
	CMP_EQi LAPTI LAPTI 2
	BR_COND LAPTI .LBB3_26
	B .LBB3_27
.LBB3_26:                               ; %ifBodyBB74
                                        ;   in Loop: Header=BB3_11 Depth=3
	SW YAGA ZAKROM 8256
.LBB3_27:                               ; %afterIfBB75
                                        ;   in Loop: Header=BB3_11 Depth=3
	LW LAPTI ZAKROM 8228
	CMP_NEi LAPTI LAPTI 3
	BR_COND LAPTI .LBB3_22
; %bb.28:                               ; %ifBodyBB79
                                        ;   in Loop: Header=BB3_11 Depth=3
	SW YAGA ZAKROM 8256
.LBB3_22:                               ; %elseBodyBB
                                        ;   in Loop: Header=BB3_11 Depth=3
	LW LAPTI ZAKROM 8228
	CMP_EQi LAPTI LAPTI 3
	BR_COND LAPTI .LBB3_23
	B .LBB3_24
.LBB3_23:                               ; %ifBodyBB84
                                        ;   in Loop: Header=BB3_11 Depth=3
	SW YAGA ZAKROM 8256
	B .LBB3_24
.LBB3_29:                               ; %afterWhileBB18
                                        ;   in Loop: Header=BB3_7 Depth=1
	SW SHALOPAY ZAKROM 8260
	B .LBB3_30
.LBB3_34:                               ; %afterWhileBB102
                                        ;   in Loop: Header=BB3_30 Depth=2
	LW LAPTI ZAKROM 8260
	ADDi LAPTI LAPTI 1
	SW LAPTI ZAKROM 8260
.LBB3_30:                               ; %whileCondBB95
                                        ;   Parent Loop BB3_7 Depth=1
                                        ; =>  This Loop Header: Depth=2
                                        ;       Child Loop BB3_32 Depth 3
	LW LAPTI ZAKROM 8260
	CMP_GTi LAPTI LAPTI 31
	BR_COND LAPTI .LBB3_35
; %bb.31:                               ; %whileBodyBB96
                                        ;   in Loop: Header=BB3_30 Depth=2
	SW SHALOPAY ZAKROM 8264
.LBB3_32:                               ; %whileCondBB100
                                        ;   Parent Loop BB3_7 Depth=1
                                        ;     Parent Loop BB3_30 Depth=2
                                        ; =>    This Inner Loop Header: Depth=3
	LW LAPTI ZAKROM 8264
	CMP_GTi LAPTI LAPTI 31
	BR_COND LAPTI .LBB3_34
; %bb.33:                               ; %whileBodyBB101
                                        ;   in Loop: Header=BB3_32 Depth=3
	LW LAPTI ZAKROM 8260
	SHLi LAPTI LAPTI 7
	ADD TROPKA VYAZ LAPTI
	ADD LAPTI LESHY LAPTI
	LW GUSLI ZAKROM 8264
	SHLi GUSLI GUSLI 2
	ADD LAPTI LAPTI GUSLI
	ADD TROPKA TROPKA GUSLI
	LW TROPKA TROPKA 0
	SW TROPKA LAPTI 0
	LW LAPTI ZAKROM 8264
	ADDi LAPTI LAPTI 1
	SW LAPTI ZAKROM 8264
	B .LBB3_32
.LBB3_35:                               ; %afterWhileBB97
                                        ;   in Loop: Header=BB3_7 Depth=1
	SW SHALOPAY ZAKROM 8268
	B .LBB3_36
.LBB3_40:                               ; %afterWhileBB122
                                        ;   in Loop: Header=BB3_36 Depth=2
	LW LAPTI ZAKROM 8268
	ADDi LAPTI LAPTI 1
	SW LAPTI ZAKROM 8268
.LBB3_36:                               ; %whileCondBB114
                                        ;   Parent Loop BB3_7 Depth=1
                                        ; =>  This Loop Header: Depth=2
                                        ;       Child Loop BB3_38 Depth 3
	LW LAPTI ZAKROM 4
	LW TROPKA ZAKROM 8268
	CMP_GE LAPTI TROPKA LAPTI
	BR_COND LAPTI .LBB3_41
; %bb.37:                               ; %whileBodyBB115
                                        ;   in Loop: Header=BB3_36 Depth=2
	SW SHALOPAY ZAKROM 8272
.LBB3_38:                               ; %whileCondBB120
                                        ;   Parent Loop BB3_7 Depth=1
                                        ;     Parent Loop BB3_36 Depth=2
                                        ; =>    This Inner Loop Header: Depth=3
	LW LAPTI ZAKROM 0
	LW TROPKA ZAKROM 8272
	CMP_GE LAPTI TROPKA LAPTI
	BR_COND LAPTI .LBB3_40
; %bb.39:                               ; %whileBodyBB121
                                        ;   in Loop: Header=BB3_38 Depth=3
	LW PLYAS ZAKROM 12
	LW BALALAIKA ZAKROM 8268
	LW GUSLI ZAKROM 8272
	CALL llvm.rus.simPutPixel
	LW LAPTI ZAKROM 8272
	ADDi LAPTI LAPTI 1
	SW LAPTI ZAKROM 8272
	B .LBB3_38
.LBB3_41:                               ; %afterWhileBB116
                                        ;   in Loop: Header=BB3_7 Depth=1
	SW SHALOPAY ZAKROM 8276
	B .LBB3_42
.LBB3_53:                               ; %afterWhileBB140
                                        ;   in Loop: Header=BB3_42 Depth=2
	LW LAPTI ZAKROM 8276
	ADDi LAPTI LAPTI 1
	SW LAPTI ZAKROM 8276
.LBB3_42:                               ; %whileCondBB133
                                        ;   Parent Loop BB3_7 Depth=1
                                        ; =>  This Loop Header: Depth=2
                                        ;       Child Loop BB3_44 Depth 3
	LW LAPTI ZAKROM 8276
	CMP_GTi LAPTI LAPTI 31
	BR_COND LAPTI .LBB3_52
; %bb.43:                               ; %whileBodyBB134
                                        ;   in Loop: Header=BB3_42 Depth=2
	SW SHALOPAY ZAKROM 8280
	B .LBB3_44
.LBB3_47:                               ; %afterIfBB145
                                        ;   in Loop: Header=BB3_44 Depth=3
	LW LAPTI ZAKROM 8280
	ADDi LAPTI LAPTI 1
	SW LAPTI ZAKROM 8280
.LBB3_44:                               ; %whileCondBB138
                                        ;   Parent Loop BB3_7 Depth=1
                                        ;     Parent Loop BB3_42 Depth=2
                                        ; =>    This Inner Loop Header: Depth=3
	LW LAPTI ZAKROM 8280
	CMP_GTi LAPTI LAPTI 31
	BR_COND LAPTI .LBB3_53
; %bb.45:                               ; %whileBodyBB139
                                        ;   in Loop: Header=BB3_44 Depth=3
	LW LAPTI ZAKROM 8276
	SHLi LAPTI LAPTI 7
	ADD LAPTI LESHY LAPTI
	LW TROPKA ZAKROM 8280
	SHLi TROPKA TROPKA 2
	ADD LAPTI LAPTI TROPKA
	LW LAPTI LAPTI 0
	CMP_EQi LAPTI LAPTI 1
	BR_COND LAPTI .LBB3_46
	B .LBB3_47
.LBB3_46:                               ; %ifBodyBB144
                                        ;   in Loop: Header=BB3_44 Depth=3
	LW PLYAS ZAKROM 8
	LW BALALAIKA ZAKROM 8276
	LW GUSLI ZAKROM 8280
	CALL drawLiveCell
	B .LBB3_47
.LBB3_48:                               ; %afterWhileBB13
	MOVi GUSLI 0
	LW VYAZ ZAKROM 8284
	LW YAGA ZAKROM 8288
	LW YARILO ZAKROM 8292
	LW SHALOPAY ZAKROM 8296
	LW ZAKROM ZAKROM 8300
	LW LESHY ZAKROM 8304
	ADDi ZAKROM ZAKROM 8308
	BR LESHY
.Lfunc_end3:
	.size	app, .Lfunc_end3-app
                                        ; -- End function
	.section	".note.GNU-stack","",@progbits
