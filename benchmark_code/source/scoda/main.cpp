#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <sys/time.h>
#include <fstream>
#include <list>
#include <map>
#include <set>
#include <algorithm>
#include "types.h"
#include "utils.h"
#include "community.h"

#define CHECK_ARGUMENT_STRING(index, option,variable,setVariable) \
    if( strcmp(argv[index],option) == 0 ){ \
        setVariable = true; \
        if( (index+1) < argc ) { \
            variable = argv[index+1]; \
        } else { \
            printf( "Invalid options.\n" ); \
            return 1;\
        }\
    }

#define CHECK_ARGUMENT_FLOAT(index, option,variable,setVariable) \
    if( strcmp(argv[index],option) == 0 ){ \
        setVariable = true; \
        if( (index+1) < argc ) { \
            variable = atof(argv[index+1]); \
        } else { \
            printf( "Invalid options.\n" ); \
            return 1;\
        }\
    }

#define CHECK_ARGUMENT_INT(index, option,variable,setVariable) \
    if( strcmp(argv[index],option) == 0 ){ \
        setVariable = true; \
        if( (index+1) < argc ) { \
            variable = atoi(argv[index+1]); \
        } else { \
            printf( "Invalid options.\n" ); \
            return 1;\
        }\
    }

#define CHECK_FLAG(index, option,setVariable) \
    if( strcmp(argv[index],option) == 0 ){ \
        setVariable = true; \
    }

static void PrintUsage() {
    printf("Usage: scoda <flags>\n");
    printf("Availaible flags:\n");
    printf("\t-f [graph file name] : Specifies the graph file.\n");
    printf("\t-o [output file name] : Specifies the output file for communities.\n");
    printf("\t-d [maximum degree] : Specifies the maximum degree for the aggregation phase.\n");
    printf("\t--filter-singletons [0/1] : Specifies if single-node communities must be filtered (default: 0).\n");
    printf("\t--leaf-aggregation [0/1] : Specifies if a pass of leaf aggregation must be applied (default: 0).\n");

}

int main(int argc, char ** argv) {
    bool graphFileNameSet = false;
    bool outputFileNameSet = false;
    bool degreeThresholdSet = false;
    bool filterSingletonsSet = false;
    bool leafAggregationSet = false;
    char * graphFileName = NULL;
    char * outputFileName = NULL;
    uint32_t degreeThreshold = 3;
    int filterSingletons = 0;
    int leafAggregation = 0;

    for(int i = 1; i < argc; i++) {
        CHECK_ARGUMENT_STRING(i, "-f", graphFileName, graphFileNameSet);
        CHECK_ARGUMENT_STRING(i, "-o", outputFileName, outputFileNameSet)
        CHECK_ARGUMENT_INT(i, "-d", degreeThreshold, degreeThresholdSet);
        CHECK_ARGUMENT_INT(i, "--filter-singletons", filterSingletons, filterSingletonsSet);
        CHECK_ARGUMENT_INT(i, "--leaf-aggregation", leafAggregation, leafAggregationSet);
    }

    if (!graphFileNameSet) {
        printf("Graph filename not set\n");
        PrintUsage();
        return 1;
    }

    if (!outputFileNameSet) {
        printf("Output filename not set\n");
        PrintUsage();
        return 1;
    }

    printf("%-32s %i\n", "Degree threshold:", degreeThreshold);

    printf("%-32s %s\n", "Filter singleton:", (filterSingletons == 1 ? "ON" : "OFF"));
    printf("%-32s %s\n", "Leaf aggregation:", (leafAggregation == 1 ? "ON" : "OFF"));

    long unsigned totalTime = 0,
                  initTime = 0,
                  spentTime = 0,
                  loadingTime = 0,
                  algorithmTime = 0;

    // Allocating list for edges
    std::vector< Edge > edgeList;

    //==================== LOAD THE GRAPH ==================================
    initTime = StartClock();
    printf("%-32s %s\n", "Graph file name:", graphFileName);
    Node maxNodeId;
    LoadGraph(graphFileName, edgeList, maxNodeId);
    spentTime = StopClock(initTime);
    loadingTime = spentTime;
    totalTime += spentTime;
    printf("%-32s %lu\n", "Nb of edges:", edgeList.size());
    printf("%-32s %lu ms\n", "Loading time:", loadingTime);
    //======================================================================

    std::vector< uint32_t > nodeCommunity (maxNodeId + 1);
    std::vector< uint32_t > nodeDegree (maxNodeId + 1);
    std::map< uint32_t, std::set< Node > > communities;
    //=================== ALGORITHM  =======================================
    initTime = StartClock();
    RunAlgorithm(edgeList, nodeCommunity, nodeDegree, degreeThreshold);
    if (leafAggregation) {
        LeafAggregation(edgeList, nodeCommunity, nodeDegree);
    }
    spentTime  = StopClock(initTime);
    algorithmTime += spentTime;
    totalTime += spentTime;
    printf("%-32s %lu ms\n", "Algorithm time:", algorithmTime);
    //======================================================================

    //======================== PRINT RESULTS ===============================
    initTime = StartClock();
    GetCommunities(nodeCommunity, maxNodeId, communities);
    PrintPartition(outputFileName, communities, filterSingletons);
    spentTime = StopClock(initTime);
    totalTime += spentTime;
    printf("%-32s %lu ms\n", "Print partition time:", spentTime);
    //======================================================================

    printf("\n");
    printf("*******************************************************\n");
    printf("%-32s %-10lu ms\n", "Loading time:", loadingTime);
    printf("%-32s %-10lu ms\n", "Algorithm time:", algorithmTime);
    printf("%-32s %-10lu ms\n", "Total execution time:", totalTime);
    printf("*******************************************************\n");

    return 0;
}
