#include <gas_container.h>
#include <particle.h>

#include <catch2/catch.hpp>

using idealgas::GasContainer;
using idealgas::Particle;

TEST_CASE("Check Constructor") {
  SECTION("Size of particle") {
    GasContainer gas_container = GasContainer({20});

    REQUIRE(gas_container.GetAllParticles().size() == 20);
  }
  SECTION("Invalid Particle Array Inputted") {
    REQUIRE_THROWS_AS(GasContainer({20,40,50,60}), std::invalid_argument);
  }
}

TEST_CASE("Movement Test") {
  SECTION("Test Position Movement and Direction of Single Particle") {
    GasContainer gas_container = GasContainer({1});
    vec2 position = gas_container.GetAllParticles()[0].position();
    gas_container.AdvanceOneFrame();
    vec2 velocity = gas_container.GetAllParticles()[0].velocity();

    REQUIRE(position + velocity ==
            gas_container.GetAllParticles()[0].position());
  }

  SECTION("Test Position Movement and Direction of Multiple Particles") {
    GasContainer gas_container = GasContainer({3});
    vec2 position_0 = gas_container.GetAllParticles()[0].position();
    vec2 position_1 = gas_container.GetAllParticles()[1].position();
    vec2 position_2 = gas_container.GetAllParticles()[2].position();
    gas_container.AdvanceOneFrame();
    vec2 velocity_0 = gas_container.GetAllParticles()[0].velocity();
    vec2 velocity_1 = gas_container.GetAllParticles()[1].velocity();
    vec2 velocity_2 = gas_container.GetAllParticles()[2].velocity();

    REQUIRE(position_0 + velocity_0 ==
            gas_container.GetAllParticles()[0].position());
    REQUIRE(position_1 + velocity_1 ==
            gas_container.GetAllParticles()[1].position());
    REQUIRE(position_2 + velocity_2 ==
            gas_container.GetAllParticles()[2].position());
  }
}

TEST_CASE("Test Set Size Vector") {
  GasContainer gas_container = GasContainer({10,20,20});
  gas_container.set_size_vectors();

  REQUIRE(gas_container.small_particles().size() == 10);
  REQUIRE(gas_container.large_particles().size() == 20);
  REQUIRE(gas_container.medium_particles().size() == 20);
}

TEST_CASE("Test Set Histogram Vector") {
  GasContainer gas_container = GasContainer({10,20,20});
  gas_container.set_histogram_vector();

  REQUIRE(gas_container.histograms().size() == 3);
}