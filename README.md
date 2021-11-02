# polynomials_C
Big tast for IPP 2020/21 year at MIMUW - calculator of polynomials

In order to create executable file it is required to use following sequence of commands (from level of IPP-ah431481 directory):

>mkdir release__
>cd release__
>cmake ..__

After following:

>make__

creates executable file called "poly" from all calculator.

>make test__

creates executable file called "poly_test" with text files from directory "poly".

>make doc__

generate documentation using Doxygen. In order to open that, go to the directory "html" and open file "annotated.html" to see the documentation.

It's possible to create debug version, usinng following sequence of commands:

>mkdir debug__
>cd debug__
>cmake -D CMAKE_BUILD_TYPE=Debug ..__
