#ifndef GRAPH_H
#define GRAPH_H

#include "Draw.h"

#include <math.h>
#include <time.h>

class Node;
class Edge;
class Graph : public Draw
{
public:
    Graph();
    Graph(std::string file_name, const int width, const int height);

    std::vector<Node*> get_nodes();
    std::vector<Edge*> get_edges();
    int nodes_number();

    void add_node(Node* node);
    void add_edge(Edge* edge);

    void delete_node(Node* node);
    void delete_edge(std::vector<Edge*>);

    void show(sf::RenderWindow& window);

private:
    std::vector<Node*> node_list;
    std::vector<Edge*> edge_list;
};

#endif