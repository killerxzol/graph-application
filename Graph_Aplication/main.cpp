#include "Node.h"
#include "Edge.h"
#include "Graph.h"

#include "SFML-2.5.1/include/SFML/Graphics.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <limits.h> 


void path(std::vector<int> c, std::vector<Node*> nodes_list, int i) {
    if (c[i] == -1)
    {
        return;
    }
    path(c, nodes_list, c[i]);
    std::cout << nodes_list[i]->get_name() << " ";
}

void dijkstra_algorithm(std::vector<Node*> nodes_list, int begin_node_, int n) {

    int len, name;
    std::vector<int> a, b, c;

    int begin_node;
    for (begin_node = 0; nodes_list[begin_node]->get_name() != begin_node_; ++begin_node);

    for (int i = 0; i < n; ++i)
    {
        a.push_back(INT_MAX);
        b.push_back(0);
        c.push_back(-1);
    }

    a[begin_node] = 0;

    for (int i = 0; i < n - 1; ++i)
    {
        int index, min = INT_MAX;

        for (int j = 0; j < n; ++j)
        {
            if (!b[j] && a[j] < min)
            {
                min = a[j];
                index = j;
            }
        }

        if (min != INT_MAX)
        {
            b[index] = 1;

            for (auto neighbor : nodes_list[index]->get_neighbors())
            {
                len = neighbor.second->get_weight();
                for (name = 0; neighbor.first != nodes_list[name]; ++name);
                if (!b[name] && len && a[index] + len < a[name])
                {
                    c[name] = index;
                    a[name] = a[index] + len;
                }
            }
        }
    }

    std::cout << "From | To \t Distance \t Path" << std::endl;
    for (int i = 0; i < n; ++i)
    {
        std::cout << begin_node_ << "  ->  " << nodes_list[i]->get_name() << "\t\t";
        if (a[i] == INT_MAX)
        {
            std::cout << "No path" << "\t " << "No path";
            std::cout << std::endl;
            continue;
        }
        else
        {
            std::cout << a[i] << "\t ";
            std::cout << begin_node_ << " ";
            path(c, nodes_list, i);
            std::cout << std::endl;
        }
    }
}

int main() {

    bool __move__ = false, __remove__ = false, __create__ = false, __create_edge_first__ = true, __create_edge_second__ = false;
    int first = -1, second = -1, index;

    const float radius = 20;
    const int width = 640, height = 480;
    
    Graph* graph = new Graph{ "matrix.txt", width, height };

    int nodes_number = graph->nodes_number();
    int names = nodes_number;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(width, height), "Graph class", sf::Style::Default, settings);

    while (window.isOpen())
    {
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            /* ---------- MOVE NODE ---------- */

            if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
            {
                for (int i = 0; i < nodes_number; ++i)
                {
                    if (sqrt(pow(graph->get_nodes()[i]->get_x() - pos.x, 2) + pow(graph->get_nodes()[i]->get_y() - pos.y, 2)) < radius)
                    {
                        index = i;
                        __move__ = true;
                        break;
                    }
                }
            }

            /* ---------- DELETE NODE ---------- */

            if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Right)
            {
                for (int i = 0; i < nodes_number; ++i)
                {
                    if (sqrt(pow(graph->get_nodes()[i]->get_x() - pos.x, 2) + pow(graph->get_nodes()[i]->get_y() - pos.y, 2)) < radius)
                    {
                        index = i;
                        __remove__ = true;
                        break;
                    }
                }
            }

            /* ---------- CREATE NODE ---------- */

            if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
            {
                if (nodes_number == 0)
                {
                    __create__ = true;
                }
                else
                {
                    for (int i = 0; i < nodes_number; ++i)
                    {
                        if (sqrt(pow(graph->get_nodes()[i]->get_x() - pos.x, 2) + pow(graph->get_nodes()[i]->get_y() - pos.y, 2)) > radius)
                        {
                            __create__ = true;
                            break;
                        }
                    }
                }
            }

            /* ---------- CREATE EDGE ---------- */

            if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Middle)
            {
                for (int i = 0; i < nodes_number; ++i)
                {
                    if (__create_edge_first__ && sqrt(pow(graph->get_nodes()[i]->get_x() - pos.x, 2) + pow(graph->get_nodes()[i]->get_y() - pos.y, 2)) < radius)
                    {
                        first = i;
                        __create_edge_first__ = false;
                        __create_edge_second__ = true;
                        break;
                    }
                    if (__create_edge_second__ && sqrt(pow(graph->get_nodes()[i]->get_x() - pos.x, 2) + pow(graph->get_nodes()[i]->get_y() - pos.y, 2)) < radius)
                    {
                        second = i;
                        __create_edge_second__ = false;
                        break;
                    }
                }
            }

            /* ---------- DIJKSTRA ALGORITHM ---------- */

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                {
                    int enter_node;
                    std::cout << "Initial node: ";
                    std::cin >> enter_node;
                    dijkstra_algorithm(graph->get_nodes(), enter_node, nodes_number);
                }
            }

            /* ---------- MOVE NODE ---------- */

            if (event.type == sf::Event::MouseButtonReleased)
                if (event.key.code == sf::Mouse::Left)
                    __move__ = false;

            if (__move__)
            {
                graph->get_nodes()[index]->set_x((float)pos.x);
                graph->get_nodes()[index]->set_y((float)pos.y);
                __create__ = false;
            }

            /* ---------- DELETE NODE ---------- */
            
            if (__remove__)
            {
                Node* node = graph->get_nodes()[index];
                std::vector<Edge*> edges = node->delete_node();
                graph->delete_node(node);
                graph->delete_edge(edges);
                nodes_number--;
                __remove__ = false;

            }

            /* ---------- CREATE NODE ---------- */

            if (__create__)
            {
                graph->add_node(new Node{ (float)pos.x, (float)pos.y, names + 1 });
                ++nodes_number; ++names;
                __create__ = false;
            }

            /* ---------- CREATE EDGE ---------- */

            if (!__create_edge_first__ && !__create_edge_second__)
            {
                int weight;
                std::cout << "Edge weight:\t";
                std::cin >> weight;

                Edge* edge = new Edge{ graph->get_nodes()[first], graph->get_nodes()[second], weight };

                graph->add_edge(edge);
                graph->get_nodes()[first]->add_neighbour(graph->get_nodes()[second], edge);

                __create_edge_first__ = true;
            }
        }

        window.clear(sf::Color::White);

        graph->show(window);

        window.display();

    }

    return 0;
}