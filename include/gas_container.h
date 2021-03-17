#pragma once

#include "cinder/gl/gl.h"
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
   * These 2 constants are used to generate the size of the rectangle that
   * represents the container for all of the gas particle. kOutOfBounds1
   * represents the top-left corner of the gas container. and the kOutOfBounds2
   * represents the lower-right corner for the rectangle gas container.
   */
  const vec2 kOutOfBounds1 = vec2(100, 100);
  const vec2 kOutOfBounds2 = vec2(650, 650);

  /**
   * This is the constructor for the container. This takes in the amount of
   * gas-particles that you want inside the simulation and will place all of
   * these particles at random locations with random velocities.
   */
  GasContainer(int number_particles);

  /**
   * Displays the container walls and the current positions of the particles.
   */
  void Display() const;

  /**
   * Updates the positions and velocities of all particles (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();
  std::vector<idealgas::Particle> GetParticleVector();

 private:
  /**
   * This variable holds all the particles that need to be updated and checked
   * for collisions with walls and each other. This stores all the particles that
   * are inside the gas chamber.
   */
  std::vector<idealgas::Particle> particle_vector_;
};

}  // namespace idealgas
