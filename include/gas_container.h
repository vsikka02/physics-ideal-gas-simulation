#pragma once

#include "cinder/gl/gl.h"
#include "histogram.h"
#include "particle.h"

using glm::vec2;

namespace idealgas {

/**
 * The container in which all of the gas particles are contained. This class
 * stores all of the particles and updates them on each frame of the simulation.
 */
class GasContainer {
 public:
  /**
   * This is the constructor for the container. This takes in the amount of
   * gas-particles that you want inside the simulation and will place all of
   * these particles at random locations with random velocities.
   */
  GasContainer(std::vector<size_t> num_different_particles);

  /**
   * Displays the container walls and the current positions of the particles.
   */
  void Display() const;

  /**
   * Updates the positions and velocities of all particles (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();
  std::vector<idealgas::Particle> GetAllParticles();

  void set_size_vectors();

  void set_histogram_vector();

  std::vector<Particle> small_particles();
  std::vector<Particle> medium_particles();
  std::vector<Particle> large_particles();
  std::vector<Histogram> histograms();

 private:
  /**
   * This variable holds all the particles that need to be updated and checked
   * for collisions with walls and each other. This stores all the particles that
   * are inside the gas chamber.
   */
  std::vector<Particle> all_particles_;
  std::vector<Particle> small_particles_;
  std::vector<Particle> medium_particles_;
  std::vector<Particle> large_particles_;
  std::vector<Histogram> histograms_;

  /**
 * These 2 constants are used to generate the size of the rectangle that
 * represents the container for all of the gas particle. kOutOfBounds1
 * represents the top-left corner of the gas container. and the kOutOfBounds2
 * represents the lower-right corner of the rectangular gas container.
 */
  const vec2 kOutOfBounds1 = vec2(100, 25);
  const vec2 kOutOfBounds2 = vec2(700, 425);
  const int kLargeParticleRadius = 10;
  const int kMediumParticleRadius = 7;
  const int kSmallParticleRadius = 5;
  const ci::Color kLargeParticleColor = ci::Color("green");
  const ci::Color kMediumParticleColor = ci::Color("blue");
  const ci::Color kSmallParticleColor = ci::Color("pink");
  const float kLargeParticleMass = 100;
  const float kMediumParticleMass = 25;
  const float kSmallParticleMass = 5;
};

};  // namespace idealgas
