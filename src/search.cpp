#include "../include/search.h"

using namespace std;

Search::Search(const Problem &problem) : problem(problem), searchType(0) {}

Search::Search(const Problem &problem, int searchType) : problem(problem), searchType(searchType) {}

//compares nodes, used in the frontier priority queue to properly order the nodes within the frontier based on their total cost (h(n) + g(n))
struct compare {
    bool operator()(Node* a, Node* b) {
        return a->getTotalCost() > b->getTotalCost();
    }
};

void Search::generalSearch(Problem puzzle, int searchType) {
    //initialize frontier using initial state of problem
    Node* initialNode = new Node(puzzle.getInitialState(), nullptr); 
    int numNodesExpanded = 0;
    int maxNodesQueue = 1;
    int goalDepth = 0;
    
    //create queue of Node pointers for the frontier
    //elements are node objects, vector is used to store the node objects
    //compare is used to determine priority within the prio queue
    priority_queue<Node*, vector<Node*>, compare> frontier;
    //create explored set to show the nodes already explored (initialized to be empty)
    set<vector<vector<int>>> exploredSet;
    set<vector<vector<int>>> frontierSet;

    frontier.push(initialNode);
    frontierSet.insert(initialNode->cloneState());

    while (true) {
        // cout << "here";
        // cout << exploredSet.size();
        // cout << frontierSet.size();
        // //if the frontier is empty (exits while without reaching goalstate) then return failure
        if (frontier.empty()) {
            cout << "Failure" << endl;
            return;
        }

        maxNodesQueue = max(maxNodesQueue, static_cast<int>(frontier.size()));
        
        //choose a leaf node and remove it from the frontier
        Node* currentNode = frontier.top();
        frontier.pop();
        frontierSet.erase(currentNode->cloneState());

        //if the node contains a goal state then return thhe corresponding solution
        if (currentNode->isGoal(puzzle.getGoalState())) {
            goalDepth = currentNode->getG();
            vector<Node*> solutionPath;
            while (currentNode != nullptr) {
                solutionPath.push_back(currentNode);
                currentNode = currentNode->getParent();
            }
            for (auto it = solutionPath.rbegin(); it != solutionPath.rend(); ++it) {
                (*it)->printState();
            }

            cout << "Goal!!!" << endl << endl;
            cout << "To solve this problem the search algorithm expanded a total of " << numNodesExpanded << " nodes." << endl;
            cout << "The maximum number of nodes in the queue at any one time: " << maxNodesQueue << endl; //not sure what this is
            cout << "The depth of goal node was " << goalDepth << endl;

            return;
            // currentNode->printState();
            // return;
        }

        //add the node to the explored set
        exploredSet.insert(currentNode->cloneState());

        //expand the chosen node, 
        vector<Node*> children = currentNode->generateChildren();
        numNodesExpanded++;

        //add the resulting nodes to the frontier only if not in the frontier or explored set
        for (Node* curr : children) {
            if (exploredSet.find(curr->cloneState()) == exploredSet.end() &&   
                frontierSet.find(curr->cloneState()) == frontierSet.end()) {
                if (searchType == 1) {
                    curr->setH(0);
                } else if (searchType == 2) {
                    curr->setH(curr->calculateMisplacedTiles());
                } else if (searchType == 3) {
                    curr->setH(static_cast<int>(curr->calculateEuclideanDistance()));
                }

                curr->setTotalCost(curr->getG() + curr->getH());

                frontier.push(curr);
                frontierSet.insert(curr->cloneState());
            }
        }   
    }
}





