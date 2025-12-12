; ModuleID = 'LANG2IR'
source_filename = "LANG2IR"

define i32 @main() {
entry:
  ret i32 4
}

declare void @simFlush()

declare void @simPutPixel(i32, i32, i32)

declare i32 @simRand()
