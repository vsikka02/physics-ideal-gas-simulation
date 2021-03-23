#include "gas_container.h"


namespace idealgas {

using glm::vec2;
using std::vector;

GasContainer::GasContainer(std::vector<size_t> num_different_particles) {
  if (num_different_particles.size() > 3) {
    throw std::invalid_argument("Cannot have more than 3 different particles!");
  }

  std::srand(std::time(nullptr));

  for (size_t i = 0; i <  num_different_particles.size(); i++) {
    for (size_t j = 0; j < num_different_particles[i]; j++) {
      int x_position = rand() % static_cast<size_t>(kOutOfBounds2.x -
                                                 kOutOfBounds1.x - 2 * kLargeParticleRadius) +
                       kOutOfBounds1.x + kLargeParticleRadius;

      int y_position = rand() % static_cast<size_t>(kOutOfBounds2.y -
                                                 kOutOfBounds1.y - 2 * kLargeParticleRadius) +
                       kOutOfBounds1.y + kLargeParticleRadius;

      float x_velocity =
          (static_cast<float>(rand() % 100) / static_cast<float>(25)) - 2.0;

      float y_velocity =
          (static_cast<float>(rand() % 100) / static_cast<float>(25)) - 2.0;

      if (i == 0) {
        Particle particle = Particle(vec2(x_position, y_position), vec2(x_velocity, y_velocity), kSmallParticleColor, kSmallParticleMass, kSmallParticleRadius);
        all_particles_.push_back(particle);
      } else if (i == 1) {
        Particle particle = Particle(vec2(x_position, y_position), vec2(x_velocity, y_velocity), kMediumParticleColor, kMediumParticleMass, kMediumParticleRadius);
        all_particles_.push_back(particle);
      } else if (i == 2) {
        Particle particle = Particle(vec2(x_position, y_position), vec2(x_velocity, y_velocity), kLargeParticleColor, kLargeParticleMass, kLargeParticleRadius);
        all_particles_.push_back(particle);
      }
    }
  }
}

void GasContainer::Display() const {
  // This function has a lot of magic numbers; be sure to design your code in a
  // way that avoids this.
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(kOutOfBounds1, kOutOfBounds2));

  for (Particle particle : all_particles_) {
    ci::gl::color(particle.GetColor());
    ci::gl::drawSolidCircle(vec2(particle.GetPosition()), particle.GetRadius());
  }

  for (Histogram histogram: histograms_) {
    histogram.DrawHistogram();
  }
}

void GasContainer::AdvanceOneFrame() {
  for (Particle& particle : all_particles_) {
    particle.UpdateVelocityAfterWallCollision(kOutOfBounds1, kOutOfBounds2);
    particle.UpdatePosition();
  }

  for (size_t i = 0; i < all_particles_.size() - 1; i++) {
    for (size_t j = i + 1; j < all_particles_.size(); j++) {
      if (all_particles_[i].IsColliding(all_particles_[j])) {
        all_particles_[i].SetCollidedVelocity(all_particles_[j]);
      }
    }
  }

  CreateSizeVectors();
  CreateHistograms();

  for (Histogram& histogram : histograms_) {
    histogram.UpdateHistogram();
  }
}

std::vector<Particle> GasContainer::GetAllParticles() {
  return all_particles_;
}

void GasContainer::CreateSizeVectors() {
  large_particles_.clear();
  medium_particles_.clear();
  small_particles_.clear();

  for (Particle particle: all_particles_) {
    if (particle.GetRadius() == kLargeParticleRadius) {
      large_particles_.push_back(particle);
    } else if (particle.GetRadius() == kMediumParticleRadius) {
      medium_particles_.push_back(particle);
    } else if (particle.GetRadius() == kSmallParticleRadius) {
      small_particles_.push_back(particle);
    }
  }
}

void GasContainer::CreateHistograms() {
  histograms_.clear();

  histograms_.push_back(Histogram(small_particles_, vec2(45, 500), vec2(245, 700), kSmallParticleColor, "Small Particles Histogram"));
  histograms_.push_back(Histogram(medium_particles_, vec2(295, 500), vec2(495, 700), kMediumParticleColor, "Medium Particles Histogram"));
  histograms_.push_back(Histogram(large_particles_, vec2(545, 500), vec2(745, 700), kLargeParticleColor, "Large Particles Histogram"));
}

}  // namespace idealgas
