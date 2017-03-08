# Benchmark code

This code is designed to perform measurements on the algorithm.
It corresponds to the version used for the benchmarks in the reference paper.
In order to use SCoDA on practical applications,
please refer to the minimal version of the code.

### Compilation

Execute the following commands:

    mkdir build
    cd build
    cmake ..
    make

### Usage

The compiled program is located in the `build` directory.

    Usage: scoda <flags>
    Availaible flags:
        -f [graph file name] : Specifies the graph file.
        -o [output file name] : Specifies the output file for communities.
        -d [maximum degree] : Specifies the maximum degree for the aggregation phase.
        --filter-singletons [0/1] : Specifies if single-node communities must be filtered (default: 0).
        --leaf-aggregation [0/1] : Specifies if a pass of leaf aggregation must be applied (default: 0).
