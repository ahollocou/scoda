# SCODA: A linear streaming algorithm for community detection in very large networks

This repository provides a reference implementation of the local community detection algorithms
described in the following research paper submitted to an upcomming conference:

**A linear streaming algorithm for community detection in very large networks**, Alexandre Hollocou, Julien Maudet, Thomas Bonald, Marc Lelarge

## Benchmark code

The code used for the benchmark in the research paper can be found in **benchmark_code**.

### Compilation

Execute the following commands in the **benchmark_code** directory:

    mkdir build
    cd build
    cmake ..
    make

Note: For MacOS X, install GCC with Homebrew and use:

    cmake -DCMAKE_CXX_COMPILER=/usr/local/Cellar/gcc/6.2.0/bin/g++-6 ..

### Usage

    Usage: scoda <flags>
    Availaible flags:
        -f [graph file name] : Specifies the graph file.
        -o [output file name] : Specifies the output file for communities.
        -d [maximum degree] : Specifies the maximum degree for the aggregation phase.
        --filter-singletons [0/1] : Specifies if single-node communities must be filtered (default: 0).
        --leaf-aggregation [0/1] : Specifies if a pass of leaf aggregation must be applied (default: 0).
