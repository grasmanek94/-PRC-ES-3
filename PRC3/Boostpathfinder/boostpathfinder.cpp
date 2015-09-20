//          Copyright W.P. McNeill 2010.
//          Copyright Georg Gast 2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


// This program uses the A-star search algorithm in the Boost Graph Library to
// solve a maze.  It is an example of how to apply Boost Graph Library
// algorithms to filtered graphs.
//
// This program generates a random maze and then tries to find the shortest
// path from the lower left-hand corner to the upper right-hand corner.  Mazes
// are represented by two-dimensional grids where a cell in the grid may
// contain a barrier.  You may move up, down, right, or left to any adjacent
// cell that does not contain a barrier.
//
// Once a maze solution has been attempted, the maze is printed.  If a
// solution was found it will be shown in the maze printout. 
// Note that not all mazes have solutions.
//
// The default maze size is 20x10, though different dimensions may be
// specified on the command line.

// Boost
#include <boost/array.hpp>
#include <boost/graph/grid_graph.hpp>
#include <boost/graph/filtered_graph.hpp>
#include <boost/graph/astar_search.hpp>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include <boost/lexical_cast.hpp>

// STL
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

// ------------------------------------------------------------------------------
// Types and filters
// ------------------------------------------------------------------------------

#define DIMS 2

// Distance traveled in the maze
typedef double distance;

// the graph types
typedef boost::grid_graph < DIMS > graph_t;
typedef boost::graph_traits < graph_t > traits_t;

typedef traits_t::vertex_descriptor vertex_t;
typedef traits_t::edge_descriptor edge_t;

typedef std::vector < vertex_t > vertex_path;

// the property types
typedef boost::property_map<graph_t, boost::vertex_index_t>::const_type index_map_type_t;
typedef boost::vector_property_map < bool, index_map_type_t > barrier_map_t;
typedef boost::vector_property_map < vertex_t, index_map_type_t > predessor_map_t;
typedef boost::vector_property_map < distance, index_map_type_t > distance_map_t;

// the filter
template <typename BarrierMap>
struct vertex_filter_no_barrier
{
	vertex_filter_no_barrier() {}
	vertex_filter_no_barrier(const BarrierMap& b) : m_barrier(b) {}

	template <typename Vertex>
	bool operator()(const Vertex& v) const
	{
		return boost::get(m_barrier, v) == false;
	}

	BarrierMap m_barrier;
};
struct edge_filter_dummy
{
	edge_filter_dummy() {}

	template <typename Edge>
	bool operator()(const Edge& e) const
	{
		return true;
	}
};

// the fitered grid
typedef boost::filtered_graph < graph_t, edge_filter_dummy, vertex_filter_no_barrier<barrier_map_t> > filtered_graph_t;

// ------------------------------------------------------------------------------
// Helper
// ------------------------------------------------------------------------------
vertex_t start_vertex(const graph_t& /*graph*/)
{
	/*
	size_t size_x = graph.length(0);
	size_t size_y = graph.length(1);
	*/
	vertex_t v = { 0, 0 };
	return v;
}
vertex_t goal_vertex(const graph_t& graph)
{
	size_t size_x = graph.length(0);
	size_t size_y = graph.length(1);

	vertex_t v = { size_x - 1, size_y - 1 };
	return v;
}

#define BARRIER "#"
void print_maze(const graph_t& graph, const barrier_map_t& barrier, const vertex_path& solution)
{
	size_t size_x = graph.length(0);
	size_t size_y = graph.length(1);

	// Header
	for (size_t i = 0; i < size_x + 2; i++)
		std::cout << BARRIER;
	std::cout << std::endl;

	vertex_t s = start_vertex(graph);
	vertex_t g = goal_vertex(graph);

	// body
	// x: left to right
	// y: bottom to top (0 bottom, growing upwards)
	for (size_t y = size_y - 1; y < size_y; --y) // underflow intended
	{
		for (size_t x = 0; x < size_x; ++x)
		{
			// barrier on the left side
			if (x == 0)
			{
				//std::cout << BARRIER;
			}

			vertex_t v = { x, y };
			bool is_solution_vtx =
				(std::find(solution.begin(), solution.end(), v) != solution.end());

			if (get(barrier, v))
			{
				std::cout << "#";
			}
			else if (is_solution_vtx)
			{
				std::cout << ".";
			}
			else if (v == s)
			{
				std::cout << "S";
			}
			else if (v == g)
			{
				std::cout << "G";
			}
			else
			{
				std::cout << " ";
			}

			// barrier on the right side
			if (x == size_x - 1)
			{
				std::cout << BARRIER;
			}

		}
		std::cout << std::endl;
	}

	// footer
	for (size_t i = 0; i < size_x + 2; i++)
		std::cout << BARRIER;
	std::cout << std::endl;

}

void create_maze(const graph_t& graph, barrier_map_t& barrier)
{
	//std::cout << "Creating Barriers ..." << std::endl;

	size_t size_x = graph.length(0);
	size_t size_y = graph.length(1);
	size_t total_space = size_x * size_y;

	size_t barriers_left = total_space / 4;
	boost::random::mt19937 gen;
	gen.seed(std::time(0));

	boost::random::uniform_int_distribution<> start_x(0, size_x - 1);
	boost::random::uniform_int_distribution<> start_y(0, size_y - 1);
	boost::random::uniform_int_distribution<> direction(0, 1);
	boost::random::uniform_int_distribution<> wall_length_x(1, size_x / 4);
	boost::random::uniform_int_distribution<> wall_length_y(1, size_y / 4);

	// start and goal vertex
	vertex_t s = start_vertex(graph);
	vertex_t g = goal_vertex(graph);

	while (barriers_left)
	{
		size_t sx = start_x(gen);
		size_t sy = start_y(gen);

		int dx, dy, wall;
		if (direction(gen) == 0)
		{
			// x
			dx = 1; dy = 0;
			wall = wall_length_x(gen);
		}
		else
		{
			// y
			dx = 0; dy = 1;
			wall = wall_length_y(gen);
		}

		// limit wall length to 20
		if (wall > 10) wall = 10;

		while (wall > 0 && barriers_left > 0)
		{
			vertex_t v = { sx, sy };

			// we dont put a barrier on start or goal
			if (v == s || v == g)
				break;

			bool current_value = boost::get(barrier, v);
			if (current_value == false)
			{
				boost::put(barrier, v, true);
				barriers_left--;
				wall--;
			}
			else
			{
				// stop this wall on this obstacle
				break;
			}
			// next vertex
			sx += dx; sy += dy;

			// we dont go outside of our grid
			if (sx >= size_x || sy >= size_y)
				break;
			/*if (barriers_left % 100 == 0)
			{
				std::cout << barriers_left << "...";
			}*/
		}
	}
	//std::cout << "Barriers done" << std::endl;
}
// ------------------------------------------------------------------------------
// AStar
// ------------------------------------------------------------------------------
// Visitor that terminates when we find the goal vertex
struct found_goal {}; // exception which is thrown when we find a solution
struct astar_goal_visitor :public boost::default_astar_visitor
{
	astar_goal_visitor(vertex_t goal) :m_goal(goal) {};

	void examine_vertex(vertex_t u, const filtered_graph_t&)
	{
		if (u == m_goal)
			throw found_goal();
	}

private:
	vertex_t m_goal;
};

// This calculates the Euclidean distance between a vertex and a goal vertex.
class euclidean_heuristic :
	public boost::astar_heuristic<filtered_graph_t, double>
{
public:
	euclidean_heuristic(vertex_t goal) :m_goal(goal) {};

	double operator()(vertex_t v) {
		return sqrt(pow(double(m_goal[0] - v[0]), 2) + pow(double(m_goal[1] - v[1]), 2));
	}

private:
	vertex_t m_goal;
};

void solve(vertex_t s, vertex_t g, filtered_graph_t& fg, vertex_path& solution)
{
	// get the index map for the associated properties
	index_map_type_t index_map(get(boost::vertex_index, fg));

	// The predecessor map is a vertex-to-vertex mapping.
	predessor_map_t predecessor(num_vertices(fg), index_map);

	// The distance map is a vertex-to-distance mapping.
	distance_map_t distances(num_vertices(fg), index_map);

	// finally the weight map
	boost::static_property_map<distance> weight(1);

	euclidean_heuristic heuristic(g);
	astar_goal_visitor visitor(g);

	try {
		astar_search(fg, s, heuristic,
			boost::weight_map(weight).
			predecessor_map(predecessor).
			distance_map(distances).
			visitor(visitor));
	}
	catch (const found_goal&  /*fg*/) {
		// Walk backwards from the goal through the predecessor chain adding
		// vertices to the solution path.
		for (vertex_t u = g; u != s; u = predecessor[u])
		{
			if (u != s && u != g)	solution.push_back(u);
		}
	}
}
// ------------------------------------------------------------------------------
// main
// ------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	// The default maze size is 20x10.  A different size may be specified on
	// the command line.
	std::size_t x = 20;
	std::size_t y = 10;

	if (argc == 3) {
		x = boost::lexical_cast<std::size_t>(argv[1]);
		y = boost::lexical_cast<std::size_t>(argv[2]);
	}

	// Define a grid which doesnt wrap
	boost::array<std::size_t, DIMS> lengths = { x, y };
	boost::array<bool, DIMS> wrapped = { false, false };
	graph_t graph(lengths, wrapped);

	// Get the index map of the grid graph
	index_map_type_t index_map(get(boost::vertex_index, graph));

	// create the property for the vertexes: Barrier
	barrier_map_t barrier_map(num_vertices(graph), index_map);

	{
		// create the walls
		create_maze(graph, barrier_map);

		// filter the graph
		filtered_graph_t fg(graph, edge_filter_dummy(), vertex_filter_no_barrier<barrier_map_t>(barrier_map));

		vertex_path solution;
		vertex_t s = start_vertex(graph);
		vertex_t g = goal_vertex(graph);

		std::cout << "Solving..." << std::endl;
		solve(s, g, fg, solution);
		print_maze(graph, barrier_map, solution);

		if (solution.size())
			std::cout << "Maze solved" << std::endl;
		else
			std::cout << "Maze _NOT_ solved" << std::endl;
	}
}
