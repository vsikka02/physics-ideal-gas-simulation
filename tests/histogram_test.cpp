//
// Created by Vansh Sikka on 3/22/21.
//
#include <gas_container.h>
#include <particle.h>

#include <catch2/catch.hpp>

using idealgas::GasContainer;
using idealgas::Histogram;
using idealgas::Particle;

TEST_CASE("Histogram Constructor Check") {
  SECTION("Particle Vector Set Properly") {
    std::vector<Particle> particles;
    particles.emplace_back(vec2(110, 110), vec2(1, 1), ci::Color("blue"), 0, 1);
    particles.emplace_back(vec2(120, 120), vec2(-1, -1), ci::Color("blue"), 0,
                           1);
    particles.emplace_back(vec2(150, 150), vec2(1, 1), ci::Color("blue"), 0, 1);
    particles.emplace_back(vec2(170, 170), vec2(-1, -1), ci::Color("blue"), 0,
                           1);

    Histogram histogram = Histogram(particles, vec2(100, 100), vec2(300, 300),
                                    ci::Color("red"), "Test Histogram", 5);

    REQUIRE(histogram.particles().size() == 4);
  }
  SECTION("Bin Heights Vector Set Properly") {
    std::vector<Particle> particles;
    particles.emplace_back(vec2(110, 110), vec2(1, 1), ci::Color("blue"), 0, 1);
    particles.emplace_back(vec2(120, 120), vec2(-1, -1), ci::Color("blue"), 0,
                           1);
    particles.emplace_back(vec2(150, 150), vec2(1, 1), ci::Color("blue"), 0, 1);
    particles.emplace_back(vec2(170, 170), vec2(-1, -1), ci::Color("blue"), 0,
                           1);

    Histogram histogram = Histogram(particles, vec2(100, 100), vec2(300, 300),
                                    ci::Color("red"), "Test Histogram", 5);

    REQUIRE(histogram.bin_heights().size() == 5);
  }
}

TEST_CASE("Test Maximum Speed Function") {
  SECTION("Check Maximum Speed is Calculating Properly") {
    std::vector<Particle> particles;
    particles.emplace_back(vec2(110, 110), vec2(1, 1), ci::Color("blue"), 0, 1);
    particles.emplace_back(vec2(120, 120), vec2(1, 1), ci::Color("blue"), 0, 1);
    particles.emplace_back(vec2(150, 150), vec2(1, 1), ci::Color("blue"), 0, 1);
    particles.emplace_back(vec2(170, 170), vec2(1, 1), ci::Color("blue"), 0, 1);

    Histogram histogram = Histogram(particles, vec2(100, 100), vec2(300, 300),
                                    ci::Color("red"), "Test Histogram", 5);

    REQUIRE(histogram.FindMaximumSpeed() == Approx(1.41421));
  }
}

TEST_CASE("Test Maximum Particles in Bin Function") {
  std::vector<Particle> particles;
  particles.emplace_back(vec2(110, 110), vec2(1, 1), ci::Color("blue"), 1, 1);
  particles.emplace_back(vec2(120, 120), vec2(1, -1), ci::Color("blue"), 1, 1);
  particles.emplace_back(vec2(150, 150), vec2(1, 1), ci::Color("blue"), 1, 1);
  particles.emplace_back(vec2(170, 170), vec2(-1, -1), ci::Color("blue"), 1, 1);

  Histogram histogram = Histogram(particles, vec2(100, 100), vec2(300, 300),
                                  ci::Color("red"), "Test Histogram", 5);
  histogram.set_bin_heights(std::vector<int>{2, 3, 4, 5, 8});

  REQUIRE(histogram.FindMaximumNumberOfParticlesInBin() == 8);
}

TEST_CASE("Test Update Histogram") {
  std::vector<Particle> particles;
  particles.emplace_back(vec2(110, 110), vec2(1, 1), ci::Color("blue"), 1, 1);
  particles.emplace_back(vec2(120, 120), vec2(1, 1), ci::Color("blue"), 1, 1);
  particles.emplace_back(vec2(150, 150), vec2(1, 1), ci::Color("blue"), 1, 1);
  particles.emplace_back(vec2(170, 170), vec2(0, 0), ci::Color("blue"), 1, 1);

  Histogram histogram = Histogram(particles, vec2(100, 100), vec2(300, 300),
                                  ci::Color("red"), "Test Histogram", 5);

  REQUIRE(histogram.UpdateHistogram()[0] == 1);
  REQUIRE(histogram.UpdateHistogram()[4] == 3);
}