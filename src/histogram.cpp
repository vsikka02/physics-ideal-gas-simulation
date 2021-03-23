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
    Histogram::Histogram(std::vector<Particle> particles, vec2 line_bound_1, vec2 line_bound_2, ci::Color color, std::string title) {
        particles_ = particles;
        line_bound_1_ = line_bound_1;
        line_bound_2_ = line_bound_2;
        color_ = color;
        bin_heights_ = std::vector<int>(kNumberOfBins);
        title_ = title;
    }

    void Histogram::DrawHistogram() const {
      DrawAxesAndLabels();
        DrawTickMarks();
    }

    void Histogram::UpdateHistogram() {
      for (int i = 0; i < bin_heights_.size(); i++) {
        bin_heights_[i] = 0;
      }
      for (Particle particle: particles_) {
        for (int i = 0; i < bin_heights_.size(); i++) {
          if (glm::length(particle.GetVelocity()) >= i * (GetMaximumSpeed() / kNumberOfBins) && glm::length(particle.GetVelocity()) <= (i+1) * (GetMaximumSpeed()/kNumberOfBins)) {
            bin_heights_[i] += 1;
          }
        }
      }
    };

    float Histogram::GetMaximumSpeed() const {
        float maximum_speed = -1;
        for (Particle particle: particles_) {
            if (glm::length(particle.GetVelocity()) > maximum_speed) {
                maximum_speed = glm::length(particle.GetVelocity());
            }
        }
        return maximum_speed;
    }

    int Histogram::GetMaximumNumberOfParticlesInABin() const {
      int max_number_of_particles = 0;
      for (int i = 0; i < bin_heights_.size(); i++) {
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

      //https://discourse.libcinder.org/t/what-is-the-best-way-to-rotate-rectangles-images/410/2
      ci::gl::pushModelMatrix();
      ci::gl::translate(line_bound_1_.x - 30, line_bound_2_.y - 150);
      ci::gl::rotate(1.57);
      ci::gl::drawString("Number of Particles", vec2(0, 0));
      ci::gl::popModelMatrix();

      ci::gl::drawString("Speed Ranges", vec2(line_bound_1_.x + 75, line_bound_2_.y + 40));
    }

    void Histogram::DrawTickMarks() const {
      int mult = (line_bound_2_.y - line_bound_1_.y)/GetMaximumNumberOfParticlesInABin();

      for (int i = 0; i <= GetMaximumNumberOfParticlesInABin(); i++) {
        ci::gl::color(ci::Color("white"));
        ci::gl::drawLine(vec2(line_bound_1_.x - 5, line_bound_2_.y - (i) * mult), vec2(line_bound_1_.x, line_bound_2_.y -(i) * mult));
        ci::gl::drawString(std::to_string(i), vec2(line_bound_1_.x - 20, line_bound_2_.y - (i) * mult));
      }

      for (int i = 0; i < kNumberOfBins; i++) {
        ci::gl::color(ci::Color("white"));
        ci::gl::drawLine(vec2(line_bound_1_.x + (i+1) * (line_bound_2_.x - line_bound_1_.x)/kNumberOfBins, line_bound_2_.y), vec2(line_bound_1_.x + (i+1) * (line_bound_2_.x - line_bound_1_.x)/kNumberOfBins, line_bound_2_.y + 5));
        float num = i * (GetMaximumSpeed()/kNumberOfBins);
        //https://stackoverflow.com/questions/29200635/convert-float-to-string-with-precision-number-of-decimal-digits-specified
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << num;
        std::string s = stream.str();
        ci::gl::drawString(s , vec2(line_bound_1_.x + (i+1) * (line_bound_2_.x - line_bound_1_.x)/kNumberOfBins - 10, line_bound_2_.y + 20));
        ci::gl::color(color_);
        ci::gl::drawSolidRect(ci::Rectf(vec2(line_bound_1_.x + i * (line_bound_2_.x - line_bound_1_.x)/kNumberOfBins, line_bound_2_.y), vec2(line_bound_1_.x + (i+1) * (line_bound_2_.x - line_bound_1_.x)/kNumberOfBins, line_bound_2_.y - mult*bin_heights_[i])));
      }
    }
}