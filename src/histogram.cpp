//
// Created by Vansh Sikka on 3/22/21.
//

//
// Created by Vansh Sikka on 3/21/21.
//

#include "histogram.h"

#include "cinder/gl/gl.h"
#include "particle.h"

using glm::vec2;

namespace idealgas {

Histogram::Histogram(const std::vector<Particle>& particles, const vec2& line_bound_1,
                     const vec2& line_bound_2, const ci::Color& color, const std::string& title, const size_t number_bins) {
  particles_ = particles;
  line_bound_1_ = line_bound_1;
  line_bound_2_ = line_bound_2;
  color_ = color;
  number_bins_ = number_bins;
  bin_heights_ = std::vector<size_t>(number_bins_);
  title_ = title;
}

void Histogram::DrawHistogram() const {
  DrawAxesAndLabels();
  DrawTickMarks();
}

std::vector<size_t> Histogram::UpdateHistogram() {
  for (size_t i = 0; i < bin_heights_.size(); i++) {
    bin_heights_[i] = 0;
  }

  for (Particle particle : particles_) {
    if (glm::length(particle.velocity()) == FindMaximumSpeed()) {
      bin_heights_[number_bins_ - 1]++;
    }
    for (size_t i = 0; i < number_bins_; i++) {
      if (glm::length(particle.velocity()) >=
              i * (FindMaximumSpeed() / number_bins_) &&
          glm::length(particle.velocity()) <=
              (i + 1) * (FindMaximumSpeed() / number_bins_)) {
        bin_heights_[i] += 1;
      }
    }
  }

  return bin_heights_;
};

float Histogram::FindMaximumSpeed() const {
  float maximum_speed = -1;

  for (Particle particle : particles_) {
    if (glm::length(particle.velocity()) > maximum_speed) {
      maximum_speed = glm::length(particle.velocity());
    }
  }

  return maximum_speed;
}

size_t Histogram::FindMaximumNumberOfParticlesInBin() const {
  size_t max_number_of_particles = 0;

  for (size_t i = 0; i < bin_heights_.size(); i++) {
    if (bin_heights_[i] > max_number_of_particles) {
      max_number_of_particles = bin_heights_[i];
    }
  }

  return max_number_of_particles;
}

void Histogram::DrawAxesAndLabels() const {
  ci::gl::drawString(title_, vec2(line_bound_1_.x + 40, line_bound_1_.y - 20));

  ci::gl::color(ci::Color("white"));
  ci::gl::drawLine(vec2(line_bound_1_), vec2(line_bound_1_.x, line_bound_2_.y));
  ci::gl::drawLine(vec2(line_bound_2_), vec2(line_bound_1_.x, line_bound_2_.y));

  // https://discourse.libcinder.org/t/what-is-the-best-way-to-rotate-rectangles-images/410/2
  ci::gl::pushModelMatrix();
  ci::gl::translate(line_bound_1_.x - 30, line_bound_2_.y - 150);
  ci::gl::rotate(1.57);
  ci::gl::drawString("Number of Particles", vec2(0, 0));
  ci::gl::popModelMatrix();

  ci::gl::drawString("Speed Ranges",
                     vec2(line_bound_1_.x + 75, line_bound_2_.y + 40));
}

void Histogram::DrawTickMarks() const {
  size_t mult =
      (line_bound_2_.y - line_bound_1_.y) / FindMaximumNumberOfParticlesInBin();

  for (size_t i = 0; i <= FindMaximumNumberOfParticlesInBin(); i++) {
    ci::gl::color(ci::Color("white"));
    ci::gl::drawLine(vec2(line_bound_1_.x - 5, line_bound_2_.y - (i)*mult),
                     vec2(line_bound_1_.x, line_bound_2_.y - (i)*mult));
    ci::gl::drawString(std::to_string(i),
                       vec2(line_bound_1_.x - 20, line_bound_2_.y - (i)*mult));
  }

  for (size_t i = 0; i < number_bins_; i++) {
    ci::gl::color(ci::Color("white"));

    ci::gl::drawLine(
        vec2(line_bound_1_.x +
                 (i + 1) * (line_bound_2_.x - line_bound_1_.x) / number_bins_,
             line_bound_2_.y),
        vec2(line_bound_1_.x +
                 (i + 1) * (line_bound_2_.x - line_bound_1_.x) / number_bins_,
             line_bound_2_.y + 5));


    float num = i * (FindMaximumSpeed() / number_bins_);
    // https://stackoverflow.com/questions/29200635/convert-float-to-string-with-precision-number-of-decimal-digits-specified

    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << num;
    std::string s = stream.str();

    ci::gl::drawString(
        s,
        vec2(line_bound_1_.x +
                 (i + 1) * (line_bound_2_.x - line_bound_1_.x) / number_bins_ -
                 10,
             line_bound_2_.y + 20));
    ci::gl::color(color_);


    ci::gl::drawSolidRect(ci::Rectf(
        vec2(line_bound_1_.x +
                 i * (line_bound_2_.x - line_bound_1_.x) / number_bins_,
             line_bound_2_.y),
        vec2(line_bound_1_.x +
                 (i + 1) * (line_bound_2_.x - line_bound_1_.x) / number_bins_,
             line_bound_2_.y - mult * bin_heights_[i])));
  }
}

std::vector<Particle> Histogram::particles() const {
  return particles_;
}

std::vector<size_t> Histogram::bin_heights() const {
  return bin_heights_;
}

void Histogram::set_bin_heights(std::vector<size_t> bin_heights) {
  bin_heights_ = bin_heights;
}
}  // namespace idealgas