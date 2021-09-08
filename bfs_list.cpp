#include <fstream>
#include <iostream>
using namespace std;

struct Neighbour {
    int end_node;
    Neighbour* next;
};

// graf skierowany bez wag
string file_path = "graph.txt";
Neighbour** neighbours_lists; // ~V rzadki graf
int edges;
int nodes;

void create_graph_from_file();
void bfs(int node_number);

int main() {
    create_graph_from_file();
    bfs(0);

    Neighbour* to_delete;
    Neighbour* iterator;
    for (int i = 0; i < nodes; i++) {
        iterator = neighbours_lists[i];
        while (iterator != NULL) {
            to_delete = iterator;
            iterator = iterator->next;
            delete to_delete;
        }
    }
    delete[] neighbours_lists;
}

void bfs(int node_number)
{
    struct Node {
        int node_number;
        Node* next;
    };

    bool* visited = new bool[nodes]; // V
    for (int i = 0; i < nodes; i++)
        visited[i] = false;

    Node* head, * tail; 

    Node* start = new Node;
    start->node_number = node_number;
    start->next = NULL;
    head = start;
    tail = start;
    visited[node_number] = true;

    Node* current;
    int current_node;
    while (head != NULL) {
        current = head;
        current_node = current->node_number;
        cout << current_node << endl;
        head = head->next;
        if (head == NULL)
            tail = NULL;
        delete current;

        Neighbour* iterator = neighbours_lists[current_node];
        Node* neighbour;
        while (iterator != NULL) {
            if (visited[iterator->end_node] == false) {
                neighbour = new Node;
                neighbour->next = NULL;
                neighbour->node_number = iterator->end_node;

                if (tail != NULL) {
                    tail->next = neighbour;
                    tail = neighbour;
                }
                else {
                    head = neighbour;
                    tail = neighbour;
                }
                visited[iterator->end_node] = true;
            }
            iterator = iterator->next;
        }
    }
    delete[] visited;
}

void create_graph_from_file() {
    ifstream file;
    file.open(file_path);

    if (file.is_open())
    {
        file >> nodes;
        file >> edges;

        if (file.fail())
            cout << "file error" << endl;
        else {
            neighbours_lists = new Neighbour * [nodes];
            for (int i = 0; i < nodes; i++) {
                neighbours_lists[i] = NULL;
            }

            for (int i = 0; i < edges; i++)
            {
                int start, end;
                file >> start;
                file >> end;
                if (file.fail())
                {
                    cout << "file error - READ DATA" << endl;
                    break;
                }
                else {
                    Neighbour* s = new Neighbour;
                    s->next = neighbours_lists[start];
                    neighbours_lists[start] = s;
                    s->end_node = end;
                }
            }
        }
        file.close();
    }
    else
        cout << "file error - OPEN" << endl;
}