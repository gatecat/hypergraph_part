#include "hypergraph.h"
#include "hypergraph_util.h"

#include <sstream>
#include <algorithm>

namespace HyperPart {
	void Hypergraph::dump(std::ostream &out) const {
		out << GetSize(nodes) << " " << GetSize(edges) << std::endl;
		for (const auto &n : nodes) {
			out << "N " << n.partition << " " << n.fixed << std::endl;
		}
		for (const auto &e : edges) {
			out << "E " << e.weight;
			for (int n : e.nodes)
				out << " " << n;
			out << std::endl;
		}
	}

	void Hypergraph::read(std::istream &in) {
		nodes.clear();
		edges.clear();
		int nedges = 0 , nnodes = 0, type = 0;
		std::string line;

		auto next_line = [&]() {
			HYPER_ASSERT(in);
			std::getline(in, line);
		};

		next_line();

		std::stringstream header(line);
		header >> nedges >> nnodes >> type;

		nodes.resize(nnodes);
		edges.resize(nedges);

		std::cerr << "|E|=" << nedges << " |V|=" << nnodes << " type=" << type << std::endl;

		for (int i = 0; i < nedges; i++) {
			next_line();
			std::stringstream edge(line);
			if (type == 1 || type == 11) {
				edge >> edges.at(i).weight;
			} else {
				edges.at(i).weight = 1;
			}
			int node;
			while (edge >> node) {
				edges.at(i).nodes.push_back(node);
				nodes.at(node).edges.push_back(i);
			}
		}
		for (int i = 0; i < nnodes; i++) {
			nodes.at(i).partition = -1;
			nodes.at(i).fixed = false;
			nodes.at(i).area = 1;
		}
		if (type == 10 || type == 11) {
			for (int i = 0; i < nnodes; i++) {
				next_line();
				std::stringstream node(line);
				node >> nodes.at(i).area;
			}
		}
	}
}

