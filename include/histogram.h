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

  /** This constructs a histogram object that plots the speed of the particles
   * at the location described by line bounds and for the particles that are passed
   * in as the particles vector. **/
  Histogram(const std::vector<Particle>& particles, const vec2& line_bound_1, const vec2& line_bound_2, const ci::Color& color, const std::string& title, const size_t number_bins);

  /** This method draws out the histogram with the Axes, Labels and the
   * bars for the histogram plot. **/
  void DrawHistogram() const;

  /** This Creates the Axes and the Labels that are needed with the necessary
   * labels for the graph. **/
  void DrawAxesAndLabels() const;

  /** This updates the bin_heights_ vector based on the new speeds of the vector
   * of particles that is passed through. **/
  std::vector<size_t> UpdateHistogram();

  /** This calculates the Maximum speed that is present within the particles
   * vector in order to decide what the ranges on the x-axis will be. **/
  float FindMaximumSpeed() const;

  /** Calculates the largest number of particles that are present in a bin. This
   * is mainly used to set the y-axis labels. **/
  size_t FindMaximumNumberOfParticlesInBin() const;

  /** This draws the tick marks that are present on the x and y axis of the
   * graphs and is dynamically updated based on the maximum bin size and the
   * maximum speed.**/
  void DrawTickMarks() const;

  /** Getter for the Particles Vector. **/
  std::vector<Particle> particles() const;

  /** Getter for the Bin Heights Vector. **/
  std::vector<size_t> bin_heights() const;

  /** Setter for the Bin Heights vector. Mainly used to make testing easier. **/
  void set_bin_heights(const std::vector<size_t> bin_heights);

 private:
  /** These are all the instance fields needed to generate a histogram. **/
  std::vector<Particle> particles_;
  vec2 line_bound_1_;
  vec2 line_bound_2_;
  std::vector<size_t> bin_heights_;
  ci::Color color_;
  std::string title_;
  size_t number_bins_;
};
}
//namespace idealgas


