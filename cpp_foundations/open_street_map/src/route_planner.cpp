#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    // TODO 2: Use the m_Model.FindClosestNode method to find the closest nodes to the starting and ending coordinates.
    // Store the nodes you find in the RoutePlanner's start_node and end_node attributes.
    this->start_node = &m_Model.FindClosestNode(start_x, start_y);
    this->end_node = &m_Model.FindClosestNode(end_x, end_y);
}


// TODO 3: Implement the CalculateHValue method.
// Tips:
// - You can use the distance to the end_node for the h value.
// - Node objects have a distance method to determine the distance to another node.

float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
    return this->end_node->distance(*node);
}


// TODO 4: Complete the AddNeighbors method to expand the current node by adding all unvisited neighbors to the open list.
// Tips:
// - Use the FindNeighbors() method of the current_node to populate current_node.neighbors vector with all the neighbors.
// - For each node in current_node.neighbors, set the parent, the h_value, the g_value. 
// - Use CalculateHValue below to implement the h-Value calculation.
// - For each node in current_node.neighbors, add the neighbor to open_list and set the node's visited attribute to true.

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
    current_node->FindNeighbors();
    // could also do for (auto neighbor : current_node->neighbors) { ... }
    // or could use auto* or auto& to avoid copying
    for (RouteModel::Node * neighbor : current_node->neighbors) {
        neighbor->parent = current_node;
        neighbor->h_value = CalculateHValue(neighbor);
        neighbor->g_value = current_node->g_value + current_node->distance(*neighbor);
        open_list.push_back(neighbor);
        neighbor->visited = true;
    }
}


// TODO 5: Complete the NextNode method to sort the open list and return the next node.
// Tips:
// - Sort the open_list according to the sum of the h value and g value.
// - Create a pointer to the node in the list with the lowest sum.
// - Remove that node from the open_list.
// - Return the pointer.
bool Compare(RouteModel::Node* x, RouteModel::Node* y) {
    float xSum = x->g_value + x->h_value;
    float ySum = y->g_value + y->h_value;
    return xSum > xSum;
}

void CellSort(std::vector<RouteModel::Node*> *open_list) {
    std::sort(open_list->begin(), open_list->end(), Compare);
}

RouteModel::Node *RoutePlanner::NextNode() {
    // could have done this with a lambda
    // sort(open_list.begin(), open_list.end(), [](RouteModel::Node* x, RouteModel::Node* y) { return x->g_value + x->h_value > y->g_value + y->h_value; }
    CellSort(&this->open_list); // decreasing order
    RouteModel::Node* lowestSumNode = open_list.back();
    open_list.pop_back();
    return lowestSumNode;
}


// TODO 6: Complete the ConstructFinalPath method to return the final path found from your A* search.
// Tips:
// - This method should take the current (final) node as an argument and iteratively follow the 
//   chain of parents of nodes until the starting node is found.
// - For each node in the chain, add the distance from the node to its parent to the distance variable.
// - The returned vector should be in the correct order: the start node should be the first element
//   of the vector, the end node should be the last element.

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;

    // TODO: Implement your solution here.
    for(RouteModel::Node* node = current_node; node != nullptr; node = node->parent) {
        path_found.push_back(*node);
        if (node->parent != nullptr){ // only need n - 1 distances for n nodes
            distance += node->distance(*node->parent);
        }
    }
    std::reverse(path_found.begin(), path_found.end());

    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    return path_found;

}


// TODO 7: Write the A* Search algorithm here.
// Tips:
// - Use the AddNeighbors method to add all of the neighbors of the current node to the open_list.
// - Use the NextNode() method to sort the open_list and return the next node.
// - When the search has reached the end_node, use the ConstructFinalPath method to return the final path that was found.
// - Store the final path in the m_Model.path attribute before the method exits. This path will then be displayed on the map tile.

void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;

    // TODO: Implement your solution here.
    this->start_node->visited = true;
    this->open_list.push_back(this->start_node);
    
    // could have done while(!open_list.empty()) { ... }
    while(this->open_list.size() > 0) {
        current_node = this->NextNode();
        if(current_node->distance(*this->end_node) == 0) {
            this->m_Model.path = this->ConstructFinalPath(current_node);
            return;
        }
        this->AddNeighbors(current_node);
    };
}