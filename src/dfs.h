#ifndef DFS_H_
#define DFS_H_

#include "list.h"
#include "digraph.h"

unsigned int dfs_digraph(List* walk, unsigned int root, Digraph* digraph);

#endif /* DFS_H_ */

