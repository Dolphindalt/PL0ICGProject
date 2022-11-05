# CPSC 323 Project 3: Intermediate Code Generation [PL/0 -> AST]

## Group Members

Please modify this section and list your group members in this format.

Example Name ename@nowhere.com (delete me)

## Instructions

Please refer to the this [document](https://docs.google.com/document/d/1i-A17VCVgMtAZljrA0M7LkDqdoRwgaPuSl1Fizp5-wk/edit?usp=sharing).

## How to build

Ensure you have a C/C++ compiler, make, and CMake installed. Executed the follow commands in terminal in the repository directory.

```
mkdir build
cd build
cmake ../
make
```

The resulting executables are populated within the build directory, which include `Compiler.out` and `Test.out`.

`Compiler.out` takes one argument, the file path of the file to perform syntax directed translation on. You are not graded on the test cases, so the `Compiler.out` driver will produce a textual representation of the ASTs that you will create. `Test.out` executes test cases, in which you may create your own.

```
./Compiler.out ../test/test_code/test1.p0
```

`Test.out` is executed without arguments.

```
./Test.out
```

This test executable does not contain tests that verify correctness of your 
AST. You must build the AST to the specification and verify the results. Feel 
free to write your own tests this time.
