#include <fstream>
#include <iostream>
using namespace std;

// graf skierowany bez wag
string file_path = "graph.txt";
int** matrix; // V^2
int edges;
int nodes;

void create_graph_from_file();
void bfs(int node_number);

int main() {
    create_graph_from_file();
    bfs(0);

    for (int i = 0; i < nodes; i++)
        delete matrix[i];
    delete[] matrix;
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

    Node* head, * tail; // kolejka

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

        Node* neighbour;
        for (int i = 0; i < nodes; i++) { // sasiedzi do kolejki
            if ((matrix[current_node][i] == 1) && visited[i] == false) {
                neighbour = new Node;
                neighbour->next = NULL;
                neighbour->node_number = i;

                if (tail != NULL) {
                    tail->next = neighbour;
                    tail = neighbour;
                }
                else {
                    head = neighbour;
                    tail = neighbour;
                }
                visited[i] = true;
            }
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
            matrix = new int* [nodes];
            for (int i = 0; i < nodes; i++) {
                matrix[i] = new int[nodes];
            }
            for (int i = 0; i < nodes; i++)
                for (int j = 0; j < nodes; j++)
                    matrix[i][j] = 0;

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
                    matrix[start][end] = 1;
                }

            }
        }
        file.close();
    }
    else
        cout << "file error - OPEN" << endl;
}