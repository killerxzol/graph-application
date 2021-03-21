#include "Graph.h"
#include "Edge.h"
#include "Node.h"

#include <fstream>

Graph::Graph()
{
    add_node(new Node());
    add_edge(new Edge());
}

Graph::Graph(std::string file_name, const int width, const int height)
{
    srand((unsigned int)time(NULL));

    int n;

    std::ifstream file(file_name);
    file >> n;

    int** matrix = new int* [n];
    for (int i = 0; i < n; ++i) matrix[i] = new int[n];

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            file >> matrix[i][j];

    for (int i = 1; i < n + 1; ++i)
    {
        float x = rand() % width;
        float y = rand() % height;
        add_node(new Node{ x, y, i });
    }

    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (matrix[i][j] != 0)
            {
                Edge* edge = new Edge{ node_list[i], node_list[j], matrix[i][j] };
                node_list[i]->add_neighbour(node_list[j], edge);
                edge_list.push_back(edge);
            }
        }
    }
}

std::vector<Node*> Graph::get_nodes() { return node_list; }
std::vector<Edge*> Graph::get_edges() { return edge_list; }
int Graph::nodes_number() { return node_list.size(); }

void Graph::add_node(Node* node) { node_list.push_back(node); }
void Graph::add_edge(Edge* edge) { edge_list.push_back(edge); }


void Graph::delete_node(Node* node)
{
    node_list.erase(std::find(node_list.begin(), node_list.end(), node));
}

void Graph::delete_edge(std::vector<Edge*> edges)
{
    for (auto edge : edges)
    {
        edge_list.erase(std::find(edge_list.begin(), edge_list.end(), edge));
    }
}

void Graph::show(sf::RenderWindow& window)
{
    for (auto node : node_list)
    {
        node->show(window);
    }

    for (auto edge : edge_list)
    {
        edge->show(window);
    }
}