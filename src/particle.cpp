//
// Created by Vansh Sikka on 3/11/21.
//
#include "particle.h"

#include "cinder/gl/gl.h"

namespace idealgas {

using glm::vec2;

Particle::Particle(const vec2& position, const vec2& velocity,
                   const ci::Color& color, const float& mass,
                   const int& radius) {
  position_ = position;
  velocity_ = velocity;
  color_ = color;
  radius_ = radius;
  mass_ = mass;
}

int Particle::radius() const {
  return radius_;
}

glm::vec2 Particle::position() const {
  return position_;
}

glm::vec2 Particle::velocity() const {
  return velocity_;
}

ci::Color Particle::color() const {
  return color_;
}

float Particle::mass() const {
  return mass_;
}

void Particle::set_velocity(const glm::vec2& velocity) {
  velocity_ = velocity;
}

void Particle::UpdatePosition() {
  position_ += velocity_;
}

void Particle::set_collided_velocity(Particle& particle) {
  vec2 v_1 = velocity_;
  vec2 v_2 = particle.velocity();
  vec2 x_1 = position_;
  vec2 x_2 = particle.position();

  if (glm::dot(v_1 - v_2, x_1 - x_2) >= 0) {
    throw std::invalid_argument("Particles are not moving towards each other!");
  }

  vec2 collided_velocity_1 = CalculateCollidedVelocity(particle, 1);
  vec2 collided_velocity_2 = CalculateCollidedVelocity(particle, 2);

  particle.set_velocity(collided_velocity_2);
  velocity_ = collided_velocity_1;
}

void Particle::set_velocity_after_wall_collision(const vec2& bounds_1,
                                                const vec2& bounds_2) {
  if (position_.y - radius_ <= bounds_1.y ||
      position_.y + radius_ >= bounds_2.y) {
    velocity_ = vec2(velocity_.x, -velocity_.y);
  }

  if (position_.x - radius_ <= bounds_1.x ||
      position_.x + radius_ >= bounds_2.x) {
    velocity_ = vec2(-velocity_.x, velocity_.y);
  }

  return;
}

bool Particle::IsColliding(const Particle& particle) const {
  if (glm::distance(position_, particle.position()) <= radius_ + particle.radius()
      && glm::dot(velocity_ - particle.velocity(), position_ - particle.position()) < 0) {
    return true;
  }

  return false;
}

vec2 Particle::CalculateCollidedVelocity(const Particle particle_2, int particle_number) {
  vec2 v_1 = velocity_;
  vec2 v_2 = particle_2.velocity();
  vec2 x_1 = position_;
  vec2 x_2 = particle_2.position();
  float m_1 = mass_;
  float m_2 = particle_2.mass();

  if (particle_number == 1) {
    return v_1 - ((2 * m_2 / (m_1 + m_2)) *
                  (glm::dot((v_1 - v_2), (x_1 - x_2)) /
                   ((glm::length(x_1 - x_2)) * glm::length(x_1 - x_2))) *
                  (x_1 - x_2));
  } else if (particle_number == 2) {
    return v_2 - ((2 * m_1 / (m_2 + m_1)) *
                  (glm::dot((v_2 - v_1), (x_2 - x_1)) /
                   ((glm::length(x_2 - x_1)) * glm::length(x_2 - x_1))) *
                  (x_2 - x_1));
  } else {
    throw std::invalid_argument("particle number can only be 1 or 2");
  }
}
}  // namespace idealgas