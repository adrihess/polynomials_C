# polynomials_C
Big tast for IPP 2020/21 year at MIMUW - calculator of polynomials

In order to create executable file it is required to use following sequence of commands (from level of IPP-ah431481 directory):

mkdir release
cd release
cmake ..

After following:

make

>creates executable file called "poly" from all calculator.

make test

>creates executable file called "poly_test" with text files from directory "poly".

make doc

>generate documentation using Doxygen. In order to open that, go to the directory "html" and open file "annotated.html" to see the documentation.

It's possible to create debug version, usinng following sequence of commands:

mkdir debug
cd debug
cmake -D CMAKE_BUILD_TYPE=Debug ..
