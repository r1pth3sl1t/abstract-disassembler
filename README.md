# abstract-disassembler
## Computer's architecture lab
The task was to create disassembler for abstract instruction set where input is text file with hex codes and the output is abstract assembly instructions of mnemonics and operands.

Instruction subset:
- `MOV <reg>, <reg>`
- `MOV <reg>, <addr>`
- `MOV <addr>, <reg>`
- `SUB <reg>, <reg>`
- `SUB <addr>, <addr>`
- `JL <shift>`
- `JL <addr>`
- `MOV <reg>, <imm8>`
