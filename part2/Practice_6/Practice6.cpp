//
// Created by gribk on 10.11.2023.
//

#include "Practice6.h"

void Practice6::start() {
    cout << "Practice 6" << endl;
    cout << endl;

    unsigned int enter;
    vector<int> ans;
    MatrixGraph *graphAns;

    auto graph = createGraph();
    cout << endl;

    cout << "Information about operations numbers:" << endl
         << "0 - exit;" << endl
         << "1 - print information;" << endl
         << "2 - create new graph;" << endl
         << "3 - print graph;" << endl
         << "4 - print matrix of graph;" << endl
         << "5 - insert edges;" << endl
         << "6 - get Euler cycle;" << endl
         << "7 - get Prim tree." << endl
         << endl;

    while (true) {
        cout << "Enter operation number or 0 for exit: ";
        cin >> enter;

        switch (enter) {

            case 0:
                cout << "Exit from practice 6" << endl;
                delete graph;
                return;

            case 1:
                cout << "Information about operations numbers:" << endl
                     << "0 - exit;" << endl
                     << "1 - print information;" << endl
                     << "2 - create new graph;" << endl
                     << "3 - print graph;" << endl
                     << "4 - print matrix of graph;" << endl
                     << "5 - insert edges;" << endl
                     << "6 - get Euler cycle;" << endl
                     << "7 - get Prim tree." << endl;
                break;

            case 2:
                delete graph;
                graph = createGraph();
                break;

            case 3:
                cout << "Graph:" << endl;
                graph->print();
                break;

            case 4:
                cout << "Matrix of graph:" << endl;
                graph->printMatrix();
                break;

            case 5:
                insertEdges(graph);
                break;

            case 6:
                cout << "Euler cycle:" << endl;
                ans = graph->getEulerCycle();
                if (ans.empty()) {
                    cout << "No one!" << endl;
                } else {
                    cout << ans[0] + 1;
                    for (int i = 1; i < ans.size(); i++)
                        cout << ' ' << ans[i] + 1;
                    cout << endl;
                }
                break;

            case 7:
                cout << "Prim tree:" << endl;
                graphAns = graph->getPrimTree();

                if (graphAns->getEdgesCount() != 0) {
                    cout << "Graph:" << endl;
                    graphAns->print();
                    cout << "Edges:" << endl;
                    graphAns->printEdges();
                    cout << "Tree:" << endl;
                    graphAns->printLikeTree();
                } else {
                    cout << "No one!" << endl;
                }
                break;
            default:
                cout << "Error. Try again!" << endl;
        }
        cout << endl;
    }
}

MatrixGraph *Practice6::createGraph() {

    int enter;
    cout << "How many vortexes?: ";
    cin >> enter;
    auto graph = new MatrixGraph(enter);

    insertEdges(graph);

    cout << endl;
    cout << "Graph:" << endl;
    graph->print();

    return graph;
}

void Practice6::insertEdges(MatrixGraph *graph) {

    int enter, enter2;
    cout << "How many edges?: ";
    cin >> enter;
    cout << "Random? (1 - yes, 0 - no): ";
    cin >> enter2;

    int start, end;
    if (enter2 == 1) {
        for (int i = 0; i < enter; i++) {
            do {
                start = rand() % graph->getVertexCount();
                end = rand() % graph->getVertexCount();
            } while (start == end);
            graph->insertEdge(start, end, rand() % 98 + 1);
        }
    } else {
        int weight;
        for (int i = 0; i < enter; i++) {
            cout << i + 1 << ":" << endl;
            cout << "From vertex with num: ";
            cin >> start;
            cout << "To vertex with num: ";
            cin >> end;
            cout << "Weight: ";
            cin >> weight;
            graph->insertEdge(start - 1, end - 1, weight);
        }
    }
}
