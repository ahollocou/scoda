#include "utils.h"

long unsigned StartClock() {
    timeval time;
    gettimeofday(&time, NULL);
    long unsigned initTime = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    return initTime;
}

long unsigned StopClock(long unsigned initTime) {
    timeval time;
    gettimeofday(&time, NULL);
    long unsigned endTime = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    return endTime - initTime;
}

int LoadGraph(char * graphFileName,
              std::vector< Edge >& edgeList,
              Node& maxNodeId) {
    // Opening file
    std::ifstream inFile;
    inFile.open((const char *)graphFileName);
    if(!inFile) {
        printf( "Graph: Error Openning Graph File\n" );
        return 1;
    }
    // Loading edges
    Node node1, node2;
    maxNodeId = 0;
    while( inFile >> node1 ) {
        inFile >> node2;
        edgeList.push_back(std::make_pair(node1, node2));
        if (node1 > maxNodeId) {
            maxNodeId = node1;
        }
        if (node2 > maxNodeId) {
            maxNodeId = node2;
        }
    }
    inFile.close();
    return 0;
}

int PrintPartition(const char* fileName,
                   std::map< uint32_t, std::set< Node > >& communities,
                   bool removeSingleton) {
    std::ofstream outFile;
    outFile.open(fileName);
    uint32_t nbCommunities = 0;
    for (auto kv : communities) {
        if (!removeSingleton || kv.second.size() > 1) {
            std::set<Node>::iterator it2 = kv.second.begin();
            Node nodeId;
            while ( true ) {
                nodeId = *it2;
                ++it2;
                if (it2 != kv.second.end()) {
                    outFile << nodeId << " ";
                } else {
                    break;
                }
            }
            outFile << nodeId << std::endl;
            nbCommunities++;
        }
    }
    printf("%-32s %i\n", "Number of Communities:", nbCommunities);
    outFile.close();
    return 0;
}
