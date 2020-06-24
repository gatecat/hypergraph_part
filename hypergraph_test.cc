#include "hypergraph.h"
#include "hypergraph_util.h"

#include <fstream>
#include <iostream>

using namespace HyperPart;

int main(int argc, char const *argv[])
{
	Hypergraph g;
	std::ifstream in(argv[1]);
	g.read(in);

	std::vector<PartitionConstraint> parts;
	for (int i = 0; i < 2; i++) {
		parts.emplace_back();
		parts.back().min_nodes = GetSize(g.nodes) * 0.49;
		parts.back().max_nodes = GetSize(g.nodes) * 0.51;
	}

	partition_hypergraph(g, parts);

	g.dump(std::cout);
	return 0;
}
