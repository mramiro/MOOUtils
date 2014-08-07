MOOUtils
=========

MOOUtils (Multi-Objective Optimization Utils) is a small C library for multi-objective algorithms quality assessment.
I originally intended to include generic versions of some optimization algorithms (hence the name),
but due to time constraints, only the quality indicators portion of the code is included... for now.

##Features

1. Quality indicators calculation
 * Generational distance
 * Inverted generational distance
 * Spread
 * Generalized spread
 * Epsilon (additive and multiplicative)

##Building instructions

I tested the code with gcc 4.6 on Linux, but it should work with any other compiler and OS. The only dependancy is
C's math library (_math.h_).

On Linux (and OS X?), you can use the provided makefile to build a static library, by using:

>make libmooutils.a

After that, you can just copy both the generated _libmooutils.a_ file and the _include_ folder into your project. Don't forget to
add the location of _libmooutils.a_ to your _LD\_LIBRARY\_PATH_ and including both it and the math.h library (_-lmooutils -lm_ flags)
when building your project.

There's also an example of the use of the library included. You can build it with:

>make example

This will build the library and the example's executable file. Then you can run it with:

>./example

The example program reads the data from the _example\_data.txt_ and _example\_truefront.txt_, performs calculations of some quality
indicators and outputs the results to stdout.

##About

I wrote most of this code during my Master's Degree studies at [Instituto Tecnol&oacute;gico de Ciudad Madero](http://www.itcm.edu.mx/).
My research there focused on multi-objective optimization techniques applied to a certain combinatorial problem (task scheduling
and voltage selection in heterogenous computing systems, for those wondering), and I wrote this functions as a way for me to evaluate
my algorithms.

Both as an exercise and hoping that my code is of any use to anyone in the same line of research, I decided to document
it and repurposed it as a C library. Feel free to use it (and maybe even expand it).

Special thanks to Nebro and Durillo's [jMetal framework](http://jmetal.sourceforge.net/), for providing me a way of comparing
implementations and results.

--Miguel &Aacute;. Ramiro 
