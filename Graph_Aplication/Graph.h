#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"

#include <math.h>
#include <time.h>

void graph_constructor(std::vector<Node*>& nodes_list, int n, int width, int height, int** matrix)
{
    srand((unsigned int)time(NULL));

    for (int i = 0; i < n; ++i)
    {
        float x = rand() % width;
        float y = rand() % height;
        std::string text = std::to_string(i + 1);
        nodes_list.push_back(new Node{ x, y, text });
    }

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (matrix[i][j] != 0)
            {
                std::string text = std::to_string(matrix[i][j]);
                nodes_list[i]->add_neighbour(nodes_list[j], text);
            }
}

#endif
