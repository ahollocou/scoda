#include "community.h"

int myrandom (int i) { return std::rand()%i; }

int RunAlgorithm(const std::vector< Edge >& edgeList,
                 std::vector< uint32_t >& nodeCommunity,
                 std::vector< uint32_t >& nodeDegree,
                 uint32_t degreeThreshold,
                 uint32_t randSeed) {
    // Random shuffle
    std::srand(unsigned (std::time(0) * (1 + randSeed)) ); // use current time as seed for random generator
    std::vector< Edge > shuffledEdgeList (edgeList);
    std::random_shuffle(shuffledEdgeList.begin(), shuffledEdgeList.end(), myrandom);
    // Aggregation
    uint32_t nextCommunityId = 1;
    for (Edge edge : shuffledEdgeList) {
        Node sourceNode = edge.first;
        Node targetNode = edge.second;
        if(nodeCommunity[sourceNode] == 0) {
            nodeCommunity[sourceNode] = nextCommunityId;
            nextCommunityId++;
        }
        if(nodeCommunity[targetNode] == 0) {
            nodeCommunity[targetNode] = nextCommunityId;
            nextCommunityId++;
        }
        if((nodeDegree[sourceNode] < degreeThreshold) && (nodeDegree[targetNode] < degreeThreshold)) {
            if(nodeDegree[sourceNode] < nodeDegree[targetNode]) {
                nodeCommunity[sourceNode] = nodeCommunity[targetNode];
            } else {
                nodeCommunity[targetNode] = nodeCommunity[sourceNode];
            }
        }
        nodeDegree[sourceNode]++;
        nodeDegree[targetNode]++;
    }
    return 0;
}

int GetCommunities(const std::vector< uint32_t > nodeCommunity,
                   Node maxNodeId,
                   std::map< uint32_t, std::set< Node > >& communities) {
    for (Node i = 0; i <= maxNodeId; i++) {
        if (nodeCommunity[i] > 0) {
            communities[nodeCommunity[i]].insert(i);
        }
    }
    return 0;
}

int LeafAggregation(const std::vector< Edge >& edgeList,
                    std::vector< uint32_t >& nodeCommunity,
                    std::vector< uint32_t >& nodeDegree) {
    // Aggregation
    for (Edge edge : edgeList) {
        Node sourceNode = edge.first;
        Node targetNode = edge.second;
        if(nodeDegree[sourceNode] == 1) {
            nodeCommunity[sourceNode] = nodeCommunity[targetNode];
        } else if (nodeDegree[targetNode] == 1) {
            nodeCommunity[targetNode] = nodeCommunity[sourceNode];
        }
    }
    return 0;
}
