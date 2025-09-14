# Compiler Project

This project is a basic compiler built using **Flex** and **Bison**, developed as part of my coursework at KUET. It demonstrates how lexical analysis, parsing, and semantic rules can be combined to design a small custom programming language.

## ⚙️ Tools & Technologies
- **Flex**: For lexical analysis
- **Bison**: For parsing and CFG implementation
- **GCC**: For compiling generated C files

## 📚 Features

The compiler supports:
- Tokenization of keywords, identifiers, constants, operators, and symbols
- Variable declarations (`int`, `real`, `string`)
- Control structures (`if`, `else`, `elseif`, `while`, `repeat`, `switch`, `case`)
- Looping (`from - to - by step`, `while`, `repeat`)
- Functions and modules (`module`, `call`, `ret`)
- Arithmetic & logical operators (`+`, `-`, `*`, `/`, `%`, `**`, `==`, `<>`, `<=`, `>=`, `&`, `|`, `^`, `~`)
- Mathematical functions (`SIN`, `COS`, `TAN`, `LOG`, `LN`, `SQRT`, `MAX`, `MIN`, `FACTORIAL`)
- Input & output (`read`, `write`)
- Arrays and string literals
- Error handling for undeclared variables & invalid syntax

## 🚀 How to Run

Generate parser files with Bison
    
    bison -d project.y

Generate lexer files with Flex

    flex project.l

Compile everything with GCC

    gcc project.tab.c lex.yy.c -o compiler

Run the compiler

    compiler
