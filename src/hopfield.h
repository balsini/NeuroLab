#ifndef HOPFIELD_H
#define HOPFIELD_H

#include <stdint.h>
#include <vector>
#include <string>

struct HopfieldNode {
		int **connections;
};

class Hopfield
{
		unsigned int _size;
		std::vector<int8_t> nodes;

		std::vector<int8_t> *weights;

		double energy(const std::vector<int8_t> &s) const;

	public:
		Hopfield(unsigned int size);
		~Hopfield();

		void step();
		void loadData(const std::string &s);
		void setState(const std::vector<int8_t> &s);
		void addNoise(unsigned int size);
		void printState(unsigned int rows, unsigned int columns) const;
};

#endif // HOPFIELD_H
