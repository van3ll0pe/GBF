# GBF
An fast BrainFuck interpretor

Brainfuck instructions :
'+' -> +1 on the memory case value where the pointer is
'-' -> -1 on the memory case value where the pointer is
'>' -> the pointer up on the memory case
'<' -> the pointer down on the memory case
'.' -> print the ascii value of the memory case where the pointer is
',' -> give a ascii value of the memory case where the pointer is
'[' -> the "while loop" while the memory case value where the pointer is isn't 0
']' -> '}'

An example :
+++++[>+++++++++++<-]>. -> 7
