#ifndef GRAPH_H	
#define GRAPH_H



#include <list>
#include <queue>
#include <vector>
#include <functional>
#include <limits>
#include <cstddef>
#include <iostream>

using namespace std;

template <class NodeType, class ArcType> class GraphArc;
template <class NodeType, class ArcType> class GraphNode;


template <class NodeType, class ArcType>
class NodeSearchCostComparer
{
public:
	typedef GraphNode<NodeType, ArcType> Node;
	typedef GraphArc<NodeType, ArcType> Arcs;

	bool operator()(Node* n1, Node* n2)
	{
		NodeType ptOne = n1->data();
		NodeType ptTwo = n2->data();

		return (ptOne.second + n1->m_heuristic > ptTwo.second + n2->m_heuristic);
	}
};

// ----------------------------------------------------------------
//  Name:           Graph
//  Description:    This is the graph class, it contains all the
//                  nodes.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
class Graph
{
public:
	// typedef the classes to make our lives easier.
	typedef GraphArc<NodeType, ArcType> Arcs;
	typedef GraphNode<NodeType, ArcType> Node;


	// Constructor and destructor functions
	Graph(int size);
	~Graph();

	// Accessors
	Node* nodeIndex(int index) const {
		return m_nodes.at(index);
	}

	// Public member functions.
	bool addNode(NodeType data, int index);
	bool addNode(NodeType data, int xpos, int ypos, int type, int index);
	void removeNode(int index);
	bool addArc(int from, int to, ArcType weight);
	void removeArc(int from, int to);
	Arcs* getArc(int from, int to);
	void clearMarks();
	void depthFirst(Node* pNode, std::function<void(Node*)> f_visit);
	void breadthFirst(Node* pNode, std::function<void(Node*)> f_visit);
	void adaptedBreadthFirst(Node* pCurrent, Node* pGoal);
	//Commented out at the bottom
	//void aStar(Node* begining, Node* destination, std::function<void(Node*)> f_visit, std::vector<Node*>& path);

private:
	// ----------------------------------------------------------------
	//  Description:    A container of all the nodes in the graph.
	// ----------------------------------------------------------------

	std::vector<Node*> m_nodes;

};

// ----------------------------------------------------------------
//  Name:           Graph
//  Description:    Constructor, this constructs an empty graph
//  Arguments:      The maximum number of nodes.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
Graph<NodeType, ArcType>::Graph(int maxNodes) : m_nodes(maxNodes, nullptr)
{
}

// ----------------------------------------------------------------
//  Name:           ~Graph
//  Description:    destructor, This deletes every node
//  Arguments:      None.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
Graph<NodeType, ArcType>::~Graph() {
	for (int index = 0; index < m_nodes.size(); index++) {
		if (m_nodes[index] != nullptr) {
			delete m_nodes.at(index);
		}
	}
}



template<class NodeType, class ArcType>
bool Graph<NodeType, ArcType>::addNode(NodeType data, int index) {
	bool nodeNotPresent = false;
	// find out if a node does not exist at that index.
	if (nullptr == m_nodes.at(index)) {
		nodeNotPresent = true;
		// create a new node, put the data in it, and unmark it.
		m_nodes.at(index) = new Node;
		m_nodes.at(index)->setData(data);
		m_nodes.at(index)->setMarked(false);
	}

	return nodeNotPresent;
}


// ----------------------------------------------------------------
//  Name:           addNode
//  Description:    This adds a node at a given index in the graph.
//  Arguments:      The first parameter is the data to store in the node.
//                  The second parameter is the index to store the node.
//  Return Value:   true if successful
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
bool Graph<NodeType, ArcType>::addNode(NodeType data, int xpos, int ypos, int type, int index) {
	bool nodeNotPresent = false;
	// find out if a node does not exist at that index.
	if (nullptr == m_nodes.at(index)) {
		nodeNotPresent = true;
		// create a new node, put the data in it, and unmark it.
		m_nodes.at(index) = new Node;
		m_nodes.at(index)->setData(data);
		m_nodes.at(index)->setMarked(false);
		m_nodes.at(index)->m_x = xpos;
		m_nodes.at(index)->m_y = ypos;
		m_nodes.at(index)->m_type = type;
	}

	return nodeNotPresent;
}



// ----------------------------------------------------------------
//  Name:           removeNode
//  Description:    This removes a node from the graph
//  Arguments:      The index of the node to return.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::removeNode(int index) {
	// Only proceed if node does exist.
	if (nullptr != m_nodes.at(index)) {
		// now find every arc that points to the node that
		// is being removed and remove it.        
		Arcs* arc;

		// loop through every node
		for (int node = 0; node < m_nodes.size(); node++) {
			// if the node is valid...
			if (nullptr != m_nodes.at(node)) {
				// see if the node has an arc pointing to the current node.
				arc = m_nodes.at(node)->getArc(m_nodes.at(index));
			}
			// if it has an arc pointing to the current node, then
			// remove the arc.
			if (arc != 0) {
				removeArc(node, index);
			}
		}


		// now that every arc pointing to the current node has been removed,
		// the node can be deleted.
		delete m_nodes.at(index);
		m_nodes.at(index) = nullptr;
	}
}

// ----------------------------------------------------------------
//  Name:           addArd
//  Description:    Adds an arc from the first index to the 
//                  second index with the specified weight.
//  Arguments:      The first argument is the originating node index
//                  The second argument is the ending node index
//                  The third argument is the weight of the arc
//  Return Value:   true on success.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
bool Graph<NodeType, ArcType>::addArc(int from, int to, ArcType weight) {
	bool proceed = true;
	// make sure both nodes exist.
	if (nullptr == m_nodes.at(from) || nullptr == m_nodes.at(to)) {
		proceed = false;
	}

	// if an arc already exists we should not proceed
	if (m_nodes.at(from)->getArc(m_nodes.at(to)) != nullptr) {
		proceed = false;
	}

	if (proceed == true) {
		// add the arc to the "from" node.
		m_nodes.at(from)->addArc(m_nodes.at(to), weight);
	}

	return proceed;
}

// ----------------------------------------------------------------
//  Name:           removeArc
//  Description:    This removes the arc from the first index to the second index
//  Arguments:      The first parameter is the originating node index.
//                  The second parameter is the ending node index.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::removeArc(int from, int to) {
	// Make sure that the node exists before trying to remove
	// an arc from it.
	bool nodeExists = true;
	if (nullptr == m_nodes.at(from) || nullptr == m_nodes.at(to)) {
		nodeExists = false;
	}

	if (nodeExists == true) {
		// remove the arc.
		m_nodes.at(from)->removeArc(m_nodes.at(to));
	}
}


// ----------------------------------------------------------------
//  Name:           getArc
//  Description:    Gets a pointer to an arc from the first index
//                  to the second index.
//  Arguments:      The first parameter is the originating node index.
//                  The second parameter is the ending node index.
//  Return Value:   pointer to the arc, or 0 if it doesn't exist.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
GraphArc<NodeType, ArcType>* Graph<NodeType, ArcType>::getArc(int from, int to) {
	Arcs* arc = 0;
	// make sure the to and from nodes exist
	if (nullptr != m_nodes.at(from) && nullptr != m_nodes.at(to)) {
		arc = m_nodes.at(from)->getArc(m_nodes.at(to));
	}

	return arc;
}


// ----------------------------------------------------------------
//  Name:           clearMarks
//  Description:    This clears every mark on every node.
//  Arguments:      None.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::clearMarks() {
	for (int index = 0; index < m_nodes.size(); index++) {
		if (nullptr != m_nodes.at(index)) {
			m_nodes.at(index)->setMarked(false);
		}
	}
}


// ----------------------------------------------------------------
//  Name:           depthFirst
//  Description:    Performs a depth-first traversal on the specified 
//                  node.
//  Arguments:      The first argument is the starting node
//                  The second argument is the processing function.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::depthFirst(Node* node, std::function<void(Node*)> f_visit) {
	if (nullptr != node) {
		// process the current node and mark it
		f_visit(node);
		node->setMarked(true);

		// go through each connecting node
		auto iter = node->arcList().begin();
		auto endIter = node->arcList().end();

		for (; iter != endIter; ++iter) {
			// process the linked node if it isn't already marked.
			if ((*iter).node()->marked() == false) {
				depthFirst((*iter).node(), f_visit);
			}
		}
	}
}


// ----------------------------------------------------------------
//  Name:           breadthFirst
//  Description:    Performs a depth-first traversal the starting node
//                  specified as an input parameter.
//  Arguments:      The first parameter is the starting node
//                  The second parameter is the processing function.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::breadthFirst(Node* node, std::function<void(Node*)> f_visit) {
	if (nullptr != node) {
		queue<Node*> nodeQueue;
		// place the first node on the queue, and mark it.
		nodeQueue.push(node);
		node->setMarked(true);

		// loop through the queue while there are nodes in it.
		while (nodeQueue.size() != 0) {
			// process the node at the front of the queue.
			f_visit(nodeQueue.front());

			// add all of the child nodes that have not been 
			// marked into the queue
			auto iter = nodeQueue.front()->arcList().begin();
			auto endIter = nodeQueue.front()->arcList().end();

			for (; iter != endIter; iter++) {
				if ((*iter).node()->marked() == false) {
					// mark the node and add it to the queue.
					(*iter).node()->setMarked(true);
					nodeQueue.push((*iter).node());
				}
			}

			// dequeue the current node.
			nodeQueue.pop();
		}
	}
}


// ----------------------------------------------------------------
//  Name:           adaptedBreadthFirst
//  Description:    Performs a breadth-first traversal the starting node
//                  specified as an input parameter, terminating at the goal.
//  Arguments:      The first parameter is the starting node.
//                  The second parameter is the goal node.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::adaptedBreadthFirst(Node* current, Node* goal) {

	if (nullptr != current) {
		bool goalReached = false;

		queue<Node*> nodeQueue;
		// place the first node on the queue, and mark it.
		nodeQueue.push(current);
		current->setMarked(true);

		// loop through the queue while there are nodes in it.
		while ((nodeQueue.size() != 0) && (!goalReached)) {

			// add all of the child nodes that have not been 
			// marked into the queue
			auto iter = nodeQueue.front()->arcList().begin();
			auto endIter = nodeQueue.front()->arcList().end();

			for (; (iter != endIter) && (!goalReached); iter++) {

				if ((*iter).node() == goal)
				{

					goalReached = true;
					(*iter).node()->setPrevious(nodeQueue.front());

				}

				if ((*iter).node()->marked() == false) {
					(*iter).node()->setPrevious(nodeQueue.front());

					// mark the node and add it to the queue.
					(*iter).node()->setMarked(true);
					nodeQueue.push((*iter).node());
				}
			}

			// dequeue the current node.
			nodeQueue.pop();
		}
	}
}


//template<class NodeType, class ArcType>
//inline void Graph<NodeType, ArcType>::aStar(Node* t_start, Node* t_destination, std::function<void(Node*)> t_visit, std::vector<Node*>& t_path)
//{
//	priority_queue<Node*, std::vector<Node*>, NodeSearchCostComparer<NodeType, ArcType>> priQue;
//
//	for (Node* node : m_nodes)
//	{
//		if (node != t_start)
//		{
//			node->m_heuristic = sqrt(((t_destination->m_x - node->m_x) * (t_destination->m_x - node->m_x)
//				+ (t_destination->m_y - node->m_y) * (t_destination->m_y - node->m_y)));
//
//			NodeType& data = node->data();
//			data.second = (std::numeric_limits<int>::max()) - 10000;
//		
//		}
//	}
//
//	priQue.push(t_start);
//	t_start->setMarked(true);
//
//	while (priQue.size() != 0 && priQue.top() != t_destination)
//	{
//		auto iter = priQue.top()->arcList().begin();
//		auto endIter = priQue.top()->arcList().end();
//
//		cout << "expandinng : " << priQue.top()->data().first << endl;
//
//		for (; iter != endIter; iter++)
//		{
//			Arcs arc = *iter;
//
//			if ((*iter).node() != priQue.top()->previous())
//			{
//				cout << "visiting : " << (*iter).node()->data().first << endl;
//				int distC = arc.node()->m_heuristic + priQue.top()->data().second + arc.weight();
//
//				if (distC < (arc.node()->data().second + arc.node()->m_heuristic))
//				{
//					NodeType& data = arc.node()->data();
//					data.second = priQue.top()->data().second + arc.weight();
//					(*iter).node()->setPrevious(priQue.top());
//				}
//
//				if ((*iter).node()->marked() == false)
//				{
//					priQue.push((*iter).node());
//					((*iter).node()->setMarked(true));
//				}
//			}
//		}
//		priQue.pop();
//	}
//
//	Node* current = t_destination;
//	while (current != nullptr)
//	{
//		auto nodeName = current->data().first;
//		t_path.push_back(current);
//		current = current->previous();
//	}
//}

#include "GraphNode.h"
#include "GraphArc.h"

#endif // !GRAPH_H