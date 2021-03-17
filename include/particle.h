//
// Created by Vansh Sikka on 3/11/21.
//
#pragma once

#include "cinder/gl/gl.h"
// IDEAL_GAS_PARTICLE_H

namespace idealgas {
class Particle {
 public:
  /**
   * This constructs a single particle that takes in a vector for the position,
   * vector for velocity, a color, a mass, and a radius.
   */
  Particle(const glm::vec2& position, const glm::vec2& velocity, const ci::Color& color, const float& mass_, const int& radius_);

  /**Return the color of a particle.**/
  ci::Color GetColor() const;

  /**Return the position vector of a particle.**/
  glm::vec2 GetPosition() const;

  /**Return the velocity vector of a particle.**/
  glm::vec2 GetVelocity() const;

  /**Sets the velocity of the particle.**/
  void SetVelocity(const glm::vec2& velocity);

  /**This is repeatedly called in order to add the velocity vector to the
   * position vector in order to make the particles move.
   */
  void UpdatePosition();

  /**Return the radius size.**/
  int GetRadius() const;

  /**
   * This functions intakes the bounds of the rectangle that the particles will
   * be stored in and will update the velocity based off of whether a given
   * particle hit the container's walls.
   */
  void UpdateVelocityAfterWallCollision(const glm::vec2& bounds_1, const glm::vec2& bounds_2);

  /**Return the mass of the particle.**/
  float GetMass() const;

  /**
   * Intakes the particle that it has collided with and sets the velocity for
   * this particle and for the inputted particle. This ensures that both the
   * velocities are altered after a collision.
   */
  void SetCollidedVelocity(Particle& particle);

  /**
   * This inputs a particle and returns a boolean based off of whether this
   * particle is colliding with the particle in the parameter.
   */
  bool IsColliding(const Particle& particle) const;

 private:
  glm::vec2 position_;
  glm::vec2 velocity_;
  ci::Color color_;
  float mass_;
  int radius_;
};
}