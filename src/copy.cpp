#include "ordonnancement.hpp"
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>
#include <vector>
#include <iterator>

using namespace std;

/*vector<unsigned int> days;
vector <unsigned int> marok;
vector<unsigned int>::iterator it;
#define N 3
vector<unsigned int> result(N, 0);*/
/*// You can include other libraries, as long as they come from the STL.
void effaceMoi(const std::vector<unsigned int> un_vecteur) { //vector
    // This function has two uses:
    // 1) Show you that we can declare and implement new ones
    // functions in a .cpp without declaring them in the .hpp file
    // (which you must not modify)
    // 2) Make you realize that this function which seems to do nothing
    // actually runs in Theta (n) since the vector is copy
    // (it is not passed by reference)
    // Now that you know, you can delete this function.
}*/

// Calculate the work scheduling.
// Inputs:
// stains: The stains to schedule
// Exit:
// solution: on day d, we execute the task tasks [solution [d]]

/*
struct Node
{
    Node* parent;
    int pathCost;
    int cost;
    int workerID;
    int jobID;
    bool assigned[N];
};

Node* newNode(int x, int y, bool assigned[],
              Node* parent)
{
    Node* node = new Node;

    for (int j = 0; j < N; j++)
        node->assigned[j] = assigned[j];

    node->assigned[y] = true;
    node->parent = parent;
    node->workerID = x;
    node->jobID = y;

    return node;
}
int calculateCost(int costMatrix[N][N], int x,
                  int y, bool assigned[])
{
    int cost = 0;
    bool available[N] = {true};
    for (int i = x + 1; i < N; i++)
    {
        int min = INT_MAX, minIndex = -1;
        for (int j = 0; j < N; j++)
        {
            if (!assigned[j] && available[j] &&
                costMatrix[i][j] < min)
            {
                minIndex = j;
                min = costMatrix[i][j];
            }
        }

        cost += min;
        available[minIndex] = false;
    }
    return cost;
}

struct comp
{
    bool operator()(const Node* lhs,
                    const Node* rhs) const
    {
        return lhs->cost > rhs->cost;
    }
};
void printAssignments(Node *min)
{
    if(min->parent==NULL){
        return;
    }
    printAssignments(min->parent);
}
vector<unsigned int> jobAssignments(Node *min)
{
    if(min->parent==NULL){
        return days;
    }
    vector<unsigned int> tmp = jobAssignments(min->parent);
    days.push_back(min->jobID);
    */
/*reverse(days.begin(), days.end());*//*

    return days;
}

vector<unsigned int> findMinCost(int costMatrix[N][N]) //uses branch & bound
{
    priority_queue<Node*, std::vector<Node*>, comp> pq;
    bool assigned[N] = {false};
    Node* root = newNode(-1, -1, assigned, NULL);
    root->pathCost = root->cost = 0;
    root->workerID = -1;
    pq.push(root);
    while (!pq.empty())
    {
        Node* min = pq.top();
        // cout << min->cost << "\n";
        pq.pop();
        int i = min->workerID + 1;
        if (i == N)
        {
            //printAssignments(min);
            marok = jobAssignments(min);
            for ( int i = 0; i < marok.size(); i++){
                   int d = marok.at(i);
                   result.at(d) = i;
            }
            return result;
        }
        for (int j = 0; j < N; j++) //do for each job
        {
            if (!min->assigned[j])
            {
                // cout << j << " ";
                Node* child = newNode(i, j, min->assigned, min);

                child->pathCost = min->pathCost + costMatrix[i][j];
                //cout << child -> pathCost << "\n";
                child->cost = child->pathCost +
                              calculateCost(costMatrix, i, j, child->assigned); //lower
                //cout << "child_cost:" << " " << child->cost << "\n";
                pq.push(child);
            }
        }
    }
}
void ordonnancement(const std::vector<Tache>& taches, std::vector<unsigned int>& solution) { //scheduling
    const unsigned int nb_taches = taches.size(); // There are as many days as there are jobs.
    for (unsigned int i = 0; i < nb_taches; i++) {
        assert(taches[i].numero() == i);
        assert(taches[i].echeance() < nb_taches);
        assert(0 < taches[i].penalite() && taches[i].penalite() <= nb_taches);
    }
    // You cannot modify the task vector, but nothing prevents you from creating a copy and modifying it.
    // Insert your code here.

    vector<int> deadline, penalty;
    for (auto i = taches.begin(); i != taches.end(); ++i){
        deadline.push_back(i->echeance());
        penalty.push_back(i->penalite());
    }
    int M[N][N];
    for (int i = 0; i < taches.size(); ++i){
        for (int j = 0; j < taches.size(); ++j){
            M[i][j] = 0;
        }
    }
    for (int i = 0; i < taches.size(); ++i){
        int d = deadline.at(i);
        for (int j = d+1; j < taches.size(); ++j){
            M[i][j] = penalty.at(i);
        }
    }
    deadline.clear();
    penalty.clear();
    for (int i = 0; i < taches.size(); ++i){
        for (int j = 0; j < taches.size(); ++j){
            cout << M[i][j] << " ";
        }
        cout << "\n";
    }
    solution = findMinCost(M);
}
*/
vector<unsigned int> days;
vector <unsigned int> marok;
vector<unsigned int>::iterator it;
//#define N 3

struct Node
{
    Node* parent;
    int pathCost;
    int cost;
    int workerID;
    int jobID;
    bool assigned[10];
};

Node* newNode(int x, int y, bool assigned[],
              Node* parent, int N)
{
    Node* node = new Node;

    for (int j = 0; j < N; j++)
        node->assigned[j] = assigned[j];

    node->assigned[y] = true;
    node->parent = parent;
    node->workerID = x;
    node->jobID = y;

    return node;
}
int calculateCost (vector<vector<int>> Vector, int x,
                  int y, bool assigned[], int N)
{
    int cost = 0;
    bool available[10];
    for (int i = 0; i < N; i++){
        available[i] = true;
    }

    for (int i = x + 1; i < N; i++)
    {
        int min = INT_MAX, minIndex = -1;
        for (int j = 0; j < N; j++)
        {
            if (!assigned[j] && available[j] &&
                Vector.at(i).at(j) < min)
            {
                minIndex = j;
                min = Vector.at(i).at(j);
            }
        }

        cost += min;
        available[minIndex] = false;
    }
    return cost;
}

struct comp
{
    bool operator()(const Node* lhs,
                    const Node* rhs) const
    {
        return lhs->cost > rhs->cost;
    }
};
void printAssignments(Node *min)
{
    if(min->parent==NULL){
        return;
    }
    printAssignments(min->parent);
}
vector<unsigned int> jobAssignments(Node *min)
{
    if(min->parent==NULL){
        return days;
    }
    vector<unsigned int> tmp = jobAssignments(min->parent);
    days.push_back(min->jobID);
    /*reverse(days.begin(), days.end());*/
    return days;
}

vector<unsigned int> findMinCost (vector<vector<int>> Vector, int N) //(int costMatrix[N][N])
{
    vector<unsigned int> result(N, 0);
    priority_queue<Node*, std::vector<Node*>, comp> pq;
    bool assigned[10] = {false};
    Node* root = newNode(-1, -1, assigned, NULL, N);
    root->pathCost = root->cost = 0;
    root->workerID = -1;
    pq.push(root);
    while (!pq.empty())
    {
        Node* min = pq.top();
        // cout << min->cost << "\n";
        pq.pop();
        int i = min->workerID + 1;
        if (i == N)
        {
            //printAssignments(min);
            marok = jobAssignments(min);
            for ( int i = 0; i < marok.size(); i++){
                int d = marok.at(i);
                result.at(d) = i;
            }
            return result;
        }
        for (int j = 0; j < N; j++) //do for each job
        {
            if (!min->assigned[j])
            {
                Node* child = newNode(i, j, min->assigned, min, N);

                child->pathCost = min->pathCost + Vector.at(i).at(j); //costMatrix[i][j];

                child->cost = child->pathCost +
                              calculateCost(Vector, i, j, child->assigned, N); //lower

                pq.push(child);
            }
        }
    }
}
void ordonnancement(const std::vector<Tache>& taches, std::vector<unsigned int>& solution) { //scheduling
    const unsigned int nb_taches = taches.size(); // There are as many days as there are jobs.
    for (unsigned int i = 0; i < nb_taches; i++) {
        assert(taches[i].numero() == i);
        assert(taches[i].echeance() < nb_taches);
        assert(0 < taches[i].penalite() && taches[i].penalite() <= nb_taches);
    }
    // You cannot modify the task vector, but nothing prevents you from creating a copy and modifying it.
    // Insert your code here.
    //int N = nb_taches;
    vector<int> deadline, penalty;
    for (auto i = taches.begin(); i != taches.end(); ++i){
        deadline.push_back(i->echeance());
        penalty.push_back(i->penalite());
    }
    int N = taches.size();
    vector<vector<int>> V;
    for (int i = 0; i < N; i++)
    {
        vector<int> v;
        for (int j = 0; j < N; j++)
            v.push_back(0);
        V.push_back(v);
    }
    for (int i = 0; i < taches.size(); ++i) {
        int d = deadline.at(i);
        for (int j = d + 1; j < taches.size(); ++j) {
            V.at(i).at(j) = penalty.at(i);
        }
    }

    solution = findMinCost(V, N);
    /*for (unsigned int i = 0; i < N; ++i){
        cout << solution.at(i) << " ";
    }*/
}



/*int main(){
    std::vector<unsigned int> solution_vorace;
    std::vector<Tache> taches = {Tache(0, 2, 4),
                                 Tache(1, 0, 3),
                                 Tache(2, 0, 2),
                                 Tache(3, 1, 1)
    };
    // ordonnancement(taches, solution_vorace);
    vector<int> deadline, penalty;
    for (auto i = taches.begin(); i != taches.end(); ++i){
        deadline.push_back(i->echeance());
        penalty.push_back(i->penalite());
    }
    //cout << taches.size() << "\n";
    int N = taches.size();
    vector<vector<int>> V;
    for (int i = 0; i < N; i++)
    {
        vector<int> v;
        for (int j = 0; j < N; j++)
            v.push_back(0);
        V.push_back(v);
    }
    for (int i = 0; i < taches.size(); ++i) {
        int d = deadline.at(i);
        for (int j = d + 1; j < taches.size(); ++j) {
            V.at(i).at(j) = penalty.at(i);
        }
    }
    solution_vorace = findMinCost(V, N);
    for (unsigned int i = 0; i < N; ++i){
        cout << solution_vorace.at(i) << " ";
    }
    *//*for (int i = 0; i < taches.size(); ++i){
        for (int j = 0; j < taches.size(); ++j){
            cout << V.at(i).at(j) << " ";
        }
        cout << "\n";
    }
*//*
    return 0;
}*/

