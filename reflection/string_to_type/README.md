g++    -c -o main.o main.cpp
In file included from Test.h:3:0,
                 from main.cpp:1:
Metadata.h:64:10: error: explicit specialization in non-namespace scope ‘struct Test’
 template<> class Init_I<var_index> \
          ^

Use solution of `explicit specialization in non-namespace scope` (here)[https://stackoverflow.com/questions/3746419/c-error-explicit-specialization-in-non-namespace-scope], but still cannot compile.
