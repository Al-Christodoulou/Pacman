#include "Graph.h"
#include <iostream>

void GraphPath::reversePath()
{
	for (size_t i{ 0 }; i < c.size() / 2; i++)
	{
		std::swap(c[i], c[c.size() - 1 - i]);
	}
}

const GraphNodeWPtr GraphPath::getDestNode() const
{
	return c.front();
}

// ================
// graph node code
// ================
GraphNode::GraphNode(unsigned int offset)
{
	m_offset = offset;
	for (size_t i = 0; i < m_relatives.size(); i++)
		m_relatives[i] = nullptr;
}

unsigned int GraphNode::getOffset() const
{
	return m_offset;
}

const Relatives& GraphNode::getRelatives() const
{
	return m_relatives;
}

const GraphNodeWPtr GraphNode::getRelative(Direction dir) const
{
	return m_relatives[dir];
}

void GraphNode::setRelative(Direction direction, GraphNodePtr node)
{
	m_relatives[direction] = std::move(node);
}

GraphNodeWPtr GraphNode::getParent() const
{
	return m_parent;
}

void GraphNode::setParent(GraphNodeWPtr parentNode)
{
	m_parent = parentNode;
}

void GraphNode::resetParent()
{
	m_parent.reset();
}

// ==================
// graph code below
// ==================
Graph::Graph(unsigned int offset, const char* space)
	: m_rootNode{ std::make_shared<GraphNode>(offset) }
{
	createGraph(offset, space);
}

void Graph::createGraph(unsigned int offset, const char* space)
{
	// create a copy of the space, so we can store what indices we've visited
	bool visited[gPlayableSpaceTotalPxs]{};

	// beginning of basic BFS here (basic meaning no parent calculations since
	// we don't need them here)
	std::queue<GraphNodeWPtr> queue{};
	visited[offset] = true; // root node is visited
	queue.push(m_rootNode);
	while (!queue.empty())
	{
		auto topNode{ queue.front() };
		queue.pop();

		// check all directions and see if we can explore the rest of the space
		for (size_t dir{ 0 }; dir < Direction::MAX_DIRECTIONS; dir++)
		{
			createConnection(static_cast<Direction>(dir), space, visited, topNode, queue);
		}
	}
}

void Graph::createConnection(const Direction direction,
							 const char* space,
							 bool* visited,
							 GraphNodeWPtr& topNode,
							 std::queue<GraphNodeWPtr>& queue) const
{
	// a helper lambda
	const auto isOutOfBounds{ [](unsigned int offset, int direction) {
		return offset + static_cast<unsigned int>(direction) > gPlayableSpaceTotalPxs;
	} };

	// temporary shared pointer of the node we're on right now
	auto tempNode{ topNode.lock() };
	const unsigned int offset{ tempNode->getOffset() };

	int delta{ DirectionDeltas[direction] };
	bool canMakeConnection{
		!isOutOfBounds(offset, delta) && visited[offset + delta] == false
		&& space[offset + delta] != 1 // don't check walls
	};

	switch (direction)
	{
	case Direction::Left:
		// if we're at the leftmost column, we can't go left
		canMakeConnection = canMakeConnection && offset % gScreenWidth != 0;
		break;
	case Direction::Right:
		// same as above but for the rightmost column
		canMakeConnection = canMakeConnection && (offset + 1) % gScreenWidth != 0;
		break;
	}

	if (canMakeConnection)
	{
		visited[offset + delta] = true;
		// create the new node
		std::shared_ptr<GraphNode> newNeighbor{
			std::make_shared<GraphNode>(offset + delta)
		};
		tempNode->setRelative(direction, newNeighbor);
		// direction ^ 1 essentially flips the direction (left -> right,
		// up -> down, down -> up, etc.)
		newNeighbor->setRelative(static_cast<Direction>(direction ^ 1), tempNode);

		queue.push(newNeighbor);
	}
}

// if startOffset is -1, we start from the root node
GraphPath Graph::BreadthFirstSearch(unsigned int goalOffset, int startOffset)
{
	GraphNodeWPtr startNode{};
	if (startOffset == -1) // if no startOffset was provided, start from root
		startNode = m_rootNode;
	else // otherwise execute BFS and find that start node
	{
		GraphPath startOffsetPath{ BreadthFirstSearch(startOffset) };
		startNode = startOffsetPath.getDestNode();
		// sometimes the destination node might have a parent that points to
		// the previous node, leading in an infinite loop at the end of BFS
		// where the endPath is constructed, this resetParent call prevents
		// this from happening
		startNode.lock()->resetParent();
	}

	// beginning of BFS here
	return BFSInner(goalOffset, startNode);
}

GraphPath Graph::BFSInner(unsigned int goalOffset, const GraphNodeWPtr& startNode)
{
	bool visited[gPlayableSpaceTotalPxs]{};
	// the final node that we wanted to get to
	GraphNodeWPtr goalNode{};

	std::queue<GraphNodeWPtr> queue{};
	visited[startNode.lock()->getOffset()] = true;
	queue.push(startNode);
	while (!queue.empty())
	{
		auto node{ queue.front() };
		queue.pop();

		auto tempNode{ node.lock() };
		if (tempNode->getOffset() == goalOffset)
		{
			goalNode = node;
			break;
		}
		for (const auto& neighbor : tempNode->getRelatives())
		{
			if (neighbor != nullptr && !visited[neighbor->getOffset()])
			{
				visited[neighbor->getOffset()] = true;
				neighbor->setParent(node);
				queue.push(neighbor);
			}
		}
	}

	GraphPath endPath{};
	GraphNodeWPtr curParent{ goalNode };
	while (!curParent.expired())
	{
		endPath.push(curParent);
		curParent = curParent.lock()->getParent();
	}
	return endPath;
}