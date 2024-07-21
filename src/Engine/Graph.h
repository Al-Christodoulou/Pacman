#pragma once
#include <memory>
#include <array>
#include <vector>
#include <queue>
#include <stack>
// TODO: move Constants inside the Engine folder
#include "../Constants.h"

struct GraphNode;
using GraphNodePtr = std::shared_ptr<GraphNode>;
using GraphNodeWPtr = std::weak_ptr<GraphNode>;

enum Direction : size_t
{
	Left = 0,
	Right,
	Down,
	Up,
	MAX_DIRECTIONS
};

using Relatives = std::array<GraphNodePtr, Direction::MAX_DIRECTIONS>;

// graph path is a class that inherits from an std::stack that uses an
// std::vector as a container in its backend, with an extra method
// that reverses all the elements
class GraphPath : public std::stack<GraphNodeWPtr, std::vector<GraphNodeWPtr>>
{
public:
	void reversePath();
	// get the destination node weak pointer
	const GraphNodeWPtr getDestNode() const;
};

struct GraphNode
{
private:
	unsigned int m_offset{};

	// used only for DFS/BFS algorithm during pathfinding calculations
	GraphNodeWPtr m_parent{};
	Relatives m_relatives{};
public:
	GraphNode(unsigned int);
	unsigned int getOffset() const;
	const Relatives& getRelatives() const;
	const GraphNodeWPtr getRelative(Direction) const;
	void setRelative(Direction, GraphNodePtr);
	GraphNodeWPtr getParent() const;
	void setParent(GraphNodeWPtr);
	void resetParent();
};

struct Graph
{
private:
	const int DirectionDeltas[Direction::MAX_DIRECTIONS]{
		-1, // Left
		1,  // Right
		gScreenWidth,					  // Down
		-static_cast<int>(gScreenWidth)	  // Up
	};

private:
	GraphNodePtr const m_rootNode;

	void createGraph(unsigned int, const char*);
	void createConnection(
		const Direction,
		const char*,
		bool*,
		GraphNodeWPtr&,
		std::queue<GraphNodeWPtr>&) const;
	GraphPath BFSInner(unsigned int, const GraphNodeWPtr&);
public:
	Graph(unsigned int, const char*);

	// starts from the root node, unless the second parameter is specified
	GraphPath BreadthFirstSearch(unsigned int, int = -1);
};