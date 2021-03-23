//
// Created by Vansh Sikka on 3/21/21.
//

#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"

using glm::vec2;
using idealgas::Particle;

namespace idealgas {

class Histogram {
 public:
  Histogram(std::vector<Particle> particles, vec2 line_bound_1, vec2 line_bound_2, ci::Color color, std::string title);
  void DrawHistogram() const;
  void DrawAxesAndLabels() const;
  std::vector<int> UpdateHistogram();
  float FindMaximumSpeed() const;
  int FindMaximumNumberOfParticlesInBin() const;
  void DrawTickMarks() const;
  std::vector<Particle> particles() const;
  std::vector<int> bin_heights() const;
  void set_bin_heights(std::vector<int> bin_heights);

 private:
  std::vector<Particle> particles_;
  vec2 line_bound_1_;
  vec2 line_bound_2_;
  std::vector<int> bin_heights_;
  ci::Color color_;
  std::string title_;
  const int kNumberOfBins = 5;
};
}
//namespace idealgas


