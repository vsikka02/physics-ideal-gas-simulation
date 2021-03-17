#include "gas_container.h"
#include <iostream>

namespace idealgas {

using glm::vec2;
using std::vector;

GasContainer::GasContainer(int number_particle) {
  if (number_particle < 0) {
    throw std::invalid_argument("Cannot have negative particles");
  }
  std::srand(std::time(nullptr));
  for (int i = 0; i < number_particle; i++) {
    int rad = 10;
    int x_position = rand() % static_cast<int>(kOutOfBounds2.x - kOutOfBounds1.x - rad) + kOutOfBounds1.x + rad;
    int y_position = rand() % static_cast<int>(kOutOfBounds2.y - kOutOfBounds1.y - rad) + kOutOfBounds1.y + rad;
    float x_velocity = (static_cast<float>(rand() % 100) / static_cast<float>(25)) - 2.0;
    float y_velocity = (static_cast<float>(rand() % 100) / static_cast<float>(25)) - 2.0;
    particle_vector_.emplace_back(vec2(x_position, y_position), vec2(x_velocity, y_velocity), ci::Color("green"), 0, rad);
  }
}

void GasContainer::Display() const {
  // This function has a lot of magic numbers; be sure to design your code in a way that avoids this.
  ci::gl::color(ci::Color("black"));
  ci::gl::drawStrokedRect(
      ci::Rectf(kOutOfBounds1,kOutOfBounds2));

  for (Particle particle : particle_vector_) {
    ci::gl::color(particle.GetColor());
    ci::gl::drawSolidCircle(vec2(particle.GetPosition()), particle.GetRadius());
  }
}

void GasContainer::AdvanceOneFrame() {
  for (Particle& particle : particle_vector_) {
    particle.UpdateVelocityAfterWallCollision(kOutOfBounds1, kOutOfBounds2);
    particle.UpdatePosition();
  }

  for (int i = 0; i < particle_vector_.size() - 1; i++) {
    for (int j = i + 1; j < particle_vector_.size(); j++) {
      if(particle_vector_[i].IsColliding(particle_vector_[j])) {
        particle_vector_[i].SetCollidedVelocity(particle_vector_[j]);
      }
    }
  }
}

std::vector<Particle> GasContainer::GetParticleVector() {
  return particle_vector_;
}
}  // namespace idealgas
