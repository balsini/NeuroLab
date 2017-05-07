#include "hopfield.h"

#include <iostream>
#include <random>
#include <chrono>
#include <fstream>

#include "matfun.h"

Hopfield::Hopfield(unsigned int size) :
  _size(size)
{
  nodes.resize(_size);
  for (unsigned int i=0; i<_size; ++i)
    nodes[i] = 0;

  weights = new std::vector<int8_t>[_size];
  for (unsigned int i=0; i<_size; ++i) {
    weights[i].resize(_size);
    for (unsigned int j=0; j<_size; ++j)
      weights[i][j] = 0;
  }
}

Hopfield::~Hopfield()
{
  delete[] weights;
}

double Hopfield::energy(const std::vector<int8_t> &s) const
{
  int v = 0;
  int sum;

  for (unsigned int i=0; i<_size; ++i) {
    sum = 0;
    for (unsigned int j=0; j<_size; ++j) {
      sum += weights[i][j] * s[j];
    }
    v += sum * s[i];
  }

  return -1.0 / 2.0 * v;
}

void Hopfield::loadData(const std::string &s)
{
  std::ifstream f(s, std::ifstream::in);

  for (unsigned int i=0; i<_size; ++i)
    for (unsigned int j=0; j<_size; ++j)
      f >> weights[i][j];
}

void Hopfield::step()
{
  auto old_state(nodes);
  int sum;

  for (unsigned int i=0; i<_size; ++i) {
    sum = 0;
    for (unsigned int j=0; j<_size; ++j) {
      sum += weights[i][j] * old_state[j];
    }
    nodes[i] = heaviside(sum);
  }
}

void Hopfield::setState(const std::vector<int8_t> &s)
{
  nodes = s;
}

void Hopfield::addNoise(unsigned int size)
{
  static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  static std::default_random_engine generator (seed);

  for (unsigned int i=0; i<size; ++i) {
    std::uniform_int_distribution<int> distribution(0, nodes.size() - 1);

    int index = distribution(generator);

    nodes[index] = nodes[index] > 0 ? 0 : 1;
  }
}

void Hopfield::printState(unsigned int rows, unsigned int columns) const
{
  for (unsigned int i=0; i<rows; ++i) {
    for (unsigned int j=0; j<columns; ++j) {
      if (nodes[i*columns + j] > 0)
        std::cout << "# ";
      else
        std::cout << "  ";
    }
    std::cout << std::endl;
  }
}
