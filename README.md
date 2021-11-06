# AVM
Anything VM. Pretty simple. I might make this a decently usefull vm with software written for it and also an OS maybe. We will see what happends. 

## Architecture

32-bit architecture.

Has swappable memory banks, each bank has a max ammount of 0xFFFF

ar-hr are general purpose registers

zr is the accumulator

ip is the instruction pointer

sp is the stack pointer

mb is the memory bank pointer

jr is the flag register

## Instructions

The format is

<instr><type><type>

For example

movir is mov immediate to register 

Another example is

movrm is mov reg to mem

### Moving types
What it does: Moves data from one place to another

Base instruction: mov

ir: Immediate to register

rr: Register to register

rm: Register to memory

im: Immediate to memory

mr: Memory to register

### Mathematical operation types
What they do: 
Preform the operation specified and stores the 
result in zr

Base instructions:
add, sub, mul

ir: Preform operation with an immediate to a register

rr: Preform operation with a register and a register

### Register only operation types
What they do:
Preforms an operation on a register

Base instructions:
inc, dec

r: Preform the operation on a single register

### Comparing instruction types
What they do:
They set the flag register

Base instruction: cmp

rr: Compares a register to a register

ir: Compares an immediate to a register

### Branching instruction types
What they do:
They branch to an address based on the flag register

Base instructions:
je, jne, jg, jl, jge, jle

### Stack operation types
What they do:
They preform operations to the stack

Base instructions;
push, pop

r: Preform that operation from or to a register

i: Preform that operation from a immediate

d: Delete value

### Misc instructions

mbir: Sets memory bank register to a immidiate value then resets the instruction pointer

