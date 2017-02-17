#ifndef DYCOLA_COMMUNITY_H
#define DYCOLA_COMMUNITY_H

#include <ctime>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include "types.h"
#include "utils.h"

int myrandom (int i);
int RunAlgorithm(const std::vector< Edge >& edgeList,
                 std::vector< uint32_t >& nodeCommunity,
                 std::vector< uint32_t >& nodeDegree,
                 uint32_t degreeThreshold,
                 uint32_t randSeed=0);
int GetCommunities(const std::vector< uint32_t > nodeCommunity,
                   Node maxNodeId,
                   std::map< uint32_t, std::set< Node > >& communities);
int LeafAggregation(const std::vector< Edge >& edgeList,
                    std::vector< uint32_t >& nodeCommunity,
                    std::vector< uint32_t >& nodeDegree);

#endif
