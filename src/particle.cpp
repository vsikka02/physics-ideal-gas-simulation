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

int Particle::GetRadius() const {
  return radius_;
}

glm::vec2 Particle::GetPosition() const {
  return position_;
}

glm::vec2 Particle::GetVelocity() const {
  return velocity_;
}

ci::Color Particle::GetColor() const {
  return color_;
}

float Particle::GetMass() const {
  return mass_;
}

void Particle::SetVelocity(const glm::vec2& velocity) {
  velocity_ = velocity;
}

void Particle::UpdatePosition() {
  position_ += velocity_;
}

void Particle::SetCollidedVelocity(Particle& particle) {
  vec2 v_1 = velocity_;
  vec2 v_2 = particle.GetVelocity();
  vec2 x_1 = position_;
  vec2 x_2 = particle.GetPosition();
  float m_1 = mass_;
  float m_2 = particle.GetMass();

  if (glm::dot(v_1 - v_2, x_1 - x_2) >= 0) {
    throw std::invalid_argument("Particles are not moving towards each other!");
  }

  vec2 collided_velocity_1 =
      v_1 - ((2*m_2/(m_1 + m_2)) * (glm::dot((v_1 - v_2), (x_1 - x_2)) /
             ((glm::length(x_1 - x_2)) * glm::length(x_1 - x_2))) *
                (x_1 - x_2));

  vec2 collided_velocity_2 =
      v_2 - ((2 * m_1/(m_1 + m_2)) * (glm::dot((v_2 - v_1), (x_2 - x_1)) /
             ((glm::length(x_2 - x_1)) * glm::length(x_2 - x_1))) *
                (x_2 - x_1));

  particle.SetVelocity(collided_velocity_2);
  velocity_ = collided_velocity_1;
}

void Particle::UpdateVelocityAfterWallCollision(const vec2& bounds_1,
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
  if (glm::distance(position_, particle.GetPosition()) <= radius_ + particle.GetRadius()
      && glm::dot(velocity_ - particle.GetVelocity(), position_ - particle.GetPosition()) < 0) {
    return true;
  }

  return false;
}
}  // namespace idealgas