#include <particle.h>

#include <catch2/catch.hpp>

using glm::vec2;
using idealgas::Particle;

TEST_CASE("Particle Position Test") {
  SECTION("Particle Move Down") {
    Particle particle =
        Particle(vec2(150, 150), vec2(0, -1), ci::Color("blue"), 0, 10);
    particle.UpdatePosition();
    REQUIRE(particle.GetPosition() == vec2(150, 149));
  }

  SECTION("Particle Move") {
    Particle particle =
        Particle(vec2(150, 150), vec2(1, 1), ci::Color("blue"), 0, 10);
    particle.UpdatePosition();
    REQUIRE(particle.GetPosition() == vec2(151, 151));
  }

  SECTION("Particle Move Up") {
    Particle particle =
        Particle(vec2(150, 150), vec2(0, 1), ci::Color("blue"), 0, 10);
    particle.UpdatePosition();
    REQUIRE(particle.GetPosition() == vec2(150, 151));
  }

  SECTION("Particle Move Left") {
    Particle particle =
        Particle(vec2(150, 150), vec2(-1, 0), ci::Color("blue"), 0, 10);
    particle.UpdatePosition();
    REQUIRE(particle.GetPosition() == vec2(149, 150));
  }

  SECTION("Particle Move Right") {
    Particle particle =
        Particle(vec2(150, 150), vec2(1, 0), ci::Color("blue"), 0, 10);
    particle.UpdatePosition();
    REQUIRE(particle.GetPosition() == vec2(151, 150));
  }
}

TEST_CASE("Particle Velocity Test") {
  SECTION("Particle Check Top Wall Collision") {
    Particle particle =
        Particle(vec2(172, 161), vec2(1, -1), ci::Color("blue"), 0, 1);
    particle.UpdateVelocityAfterWallCollision(vec2(160, 160), vec2(190, 190));
    REQUIRE(particle.GetVelocity() == vec2(1, 1));
  }

  SECTION("Particle Check Left Wall Collision") {
    Particle particle =
        Particle(vec2(161, 172), vec2(-1, 1), ci::Color("blue"), 0, 1);
    particle.UpdateVelocityAfterWallCollision(vec2(160, 160), vec2(190, 190));
    REQUIRE(particle.GetVelocity() == vec2(1, 1));
  }

  SECTION("Particle Check Right Wall Collision") {
    Particle particle =
        Particle(vec2(189, 172), vec2(1, 1), ci::Color("blue"), 0, 1);
    particle.UpdateVelocityAfterWallCollision(vec2(160, 160), vec2(190, 190));
    REQUIRE(particle.GetVelocity() == vec2(-1, 1));
  }

  SECTION("Particle Check Bottom Wall Collision") {
    Particle particle =
        Particle(vec2(172, 189), vec2(-1, 1), ci::Color("blue"), 0, 1);
    particle.UpdateVelocityAfterWallCollision(vec2(160, 160), vec2(190, 190));
    REQUIRE(particle.GetVelocity() == vec2(-1, -1));
  }

  SECTION("Particle Check Top-Left Corner Collision") {
    Particle particle =
        Particle(vec2(161, 161), vec2(-1, -1), ci::Color("blue"), 0, 1);
    particle.UpdateVelocityAfterWallCollision(vec2(160, 160), vec2(190, 190));
    REQUIRE(particle.GetVelocity() == vec2(1, 1));
  }

  SECTION("Particle Check Top-Right Corner Collision") {
    Particle particle =
        Particle(vec2(189, 161), vec2(1, -1), ci::Color("blue"), 0, 1);
    particle.UpdateVelocityAfterWallCollision(vec2(160, 160), vec2(190, 190));
    REQUIRE(particle.GetVelocity() == vec2(-1, 1));
  }

  SECTION("Particle Check Bottom-Left Corner Collision") {
    Particle particle =
        Particle(vec2(161, 189), vec2(-1, 1), ci::Color("blue"), 0, 1);
    particle.UpdateVelocityAfterWallCollision(vec2(160, 160), vec2(190, 190));
    REQUIRE(particle.GetVelocity() == vec2(1, -1));
  }

  SECTION("Particle Check Bottom-Right Corner Collision") {
    Particle particle =
        Particle(vec2(189, 189), vec2(1, 1), ci::Color("blue"), 0, 1);
    particle.UpdateVelocityAfterWallCollision(vec2(160, 160), vec2(190, 190));
    REQUIRE(particle.GetVelocity() == vec2(-1, -1));
  }
}

TEST_CASE("Test if 2 particles are colliding") {
  SECTION("Particles are Colliding") {
    Particle particle_1 =
        Particle(vec2(169, 169), vec2(1, 1), ci::Color("blue"), 0, 1);
    Particle particle_2 =
        Particle(vec2(171, 169), vec2(-1, -1), ci::Color("blue"), 0, 1);
    REQUIRE(particle_1.IsColliding(particle_2) == true);
  }

  SECTION("Particles are not Colliding") {
    Particle particle_1 =
        Particle(vec2(165, 165), vec2(1, 0), ci::Color("blue"), 0, 1);
    Particle particle_2 =
        Particle(vec2(170, 170), vec2(1, 0), ci::Color("blue"), 0, 1);
    REQUIRE(particle_1.IsColliding(particle_2) == false);
  }
}

TEST_CASE("Check Velocity after collision") {
  SECTION("Particles Collided") {
    Particle particle_1 =
        Particle(vec2(169, 169), vec2(1, 1), ci::Color("blue"), 0, 1);
    Particle particle_2 =
        Particle(vec2(171, 169), vec2(-1, 1), ci::Color("blue"), 0, 1);
    REQUIRE(particle_1.IsColliding(particle_2) == true);
    particle_1.SetCollidedVelocity(particle_2);
    particle_2.SetCollidedVelocity(particle_1);
    REQUIRE(particle_1.GetVelocity() == vec2(-1, 1));
    REQUIRE(particle_2.GetVelocity() == vec2(1, 1));
  }

  SECTION(
      "Particles are not moving towards each other (Velocity should not "
      "change!)") {
    Particle particle_1 =
        Particle(vec2(169, 169), vec2(1, 1), ci::Color("blue"), 0, 1);
    Particle particle_2 =
        Particle(vec2(171, 169), vec2(1, 1), ci::Color("blue"), 0, 1);
    REQUIRE(particle_1.IsColliding(particle_2) == true);
    particle_1.SetCollidedVelocity(particle_2);
    particle_2.SetCollidedVelocity(particle_1);
    REQUIRE(particle_1.GetVelocity() == vec2(1, 1));
    REQUIRE(particle_2.GetVelocity() == vec2(1, 1));
  }
}
