#ifndef DYCOLA_UTILS_H
#define DYCOLA_UTILS_H

#include <stdlib.h>
#include <map>
#include <vector>
#include <set>
#include <utility>
#include <sys/time.h>
#include <fstream>
#include "types.h"

long unsigned StartClock();
long unsigned StopClock(long unsigned initTime);
int LoadGraph(char * graphFileName,
              std::vector< Edge >& edgeList,
              Node& maxNodeId);
int PrintPartition(const char* fileName,
                   std::map< uint32_t, std::set< Node > >& communities,
                   bool removeSingleton=false);

#endif
