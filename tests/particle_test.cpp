//
// Created by Vansh Sikka on 3/23/21.
//

#include <particle.h>

#include <catch2/catch.hpp>

using glm::vec2;
using idealgas::Particle;

TEST_CASE("Particle Position Test") {
  SECTION("Particle Move Down") {
    Particle particle =
        Particle(vec2(150, 150), vec2(0, -1), ci::Color("blue"), 0, 10);
    particle.UpdatePosition();
    REQUIRE(particle.position() == vec2(150, 149));
  }

  SECTION("Particle Move") {
    Particle particle =
        Particle(vec2(150, 150), vec2(1, 1), ci::Color("blue"), 0, 10);
    particle.UpdatePosition();
    REQUIRE(particle.position() == vec2(151, 151));
  }

  SECTION("Particle Move Up") {
    Particle particle =
        Particle(vec2(150, 150), vec2(0, 1), ci::Color("blue"), 0, 10);
    particle.UpdatePosition();
    REQUIRE(particle.position() == vec2(150, 151));
  }

  SECTION("Particle Move Left") {
    Particle particle =
        Particle(vec2(150, 150), vec2(-1, 0), ci::Color("blue"), 0, 10);
    particle.UpdatePosition();
    REQUIRE(particle.position() == vec2(149, 150));
  }

  SECTION("Particle Move Right") {
    Particle particle =
        Particle(vec2(150, 150), vec2(1, 0), ci::Color("blue"), 0, 10);
    particle.UpdatePosition();
    REQUIRE(particle.position() == vec2(151, 150));
  }
}

TEST_CASE("Particle Velocity Test") {
  SECTION("Particle Check Top Wall Collision") {
    Particle particle =
        Particle(vec2(172, 161), vec2(1, -1), ci::Color("blue"), 0, 1);
    particle.set_velocity_after_wall_collision(vec2(160, 160), vec2(190, 190));
    REQUIRE(particle.velocity() == vec2(1, 1));
  }

  SECTION("Particle Check Left Wall Collision") {
    Particle particle =
        Particle(vec2(161, 172), vec2(-1, 1), ci::Color("blue"), 0, 1);
    particle.set_velocity_after_wall_collision(vec2(160, 160), vec2(190, 190));
    REQUIRE(particle.velocity() == vec2(1, 1));
  }

  SECTION("Particle Check Right Wall Collision") {
    Particle particle =
        Particle(vec2(189, 172), vec2(1, 1), ci::Color("blue"), 0, 1);
    particle.set_velocity_after_wall_collision(vec2(160, 160), vec2(190, 190));
    REQUIRE(particle.velocity() == vec2(-1, 1));
  }

  SECTION("Particle Check Bottom Wall Collision") {
    Particle particle =
        Particle(vec2(172, 189), vec2(-1, 1), ci::Color("blue"), 0, 1);
    particle.set_velocity_after_wall_collision(vec2(160, 160), vec2(190, 190));
    REQUIRE(particle.velocity() == vec2(-1, -1));
  }

  SECTION("Particle Check Top-Left Corner Collision") {
    Particle particle =
        Particle(vec2(161, 161), vec2(-1, -1), ci::Color("blue"), 0, 1);
    particle.set_velocity_after_wall_collision(vec2(160, 160), vec2(190, 190));
    REQUIRE(particle.velocity() == vec2(1, 1));
  }

  SECTION("Particle Check Top-Right Corner Collision") {
    Particle particle =
        Particle(vec2(189, 161), vec2(1, -1), ci::Color("blue"), 0, 1);
    particle.set_velocity_after_wall_collision(vec2(160, 160), vec2(190, 190));
    REQUIRE(particle.velocity() == vec2(-1, 1));
  }

  SECTION("Particle Check Bottom-Left Corner Collision") {
    Particle particle =
        Particle(vec2(161, 189), vec2(-1, 1), ci::Color("blue"), 0, 1);
    particle.set_velocity_after_wall_collision(vec2(160, 160), vec2(190, 190));
    REQUIRE(particle.velocity() == vec2(1, -1));
  }

  SECTION("Particle Check Bottom-Right Corner Collision") {
    Particle particle =
        Particle(vec2(189, 189), vec2(1, 1), ci::Color("blue"), 0, 1);
    particle.set_velocity_after_wall_collision(vec2(160, 160), vec2(190, 190));
    REQUIRE(particle.velocity() == vec2(-1, -1));
  }
}

TEST_CASE("Test if Particles are colliding") {
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

  SECTION(
      "Particles are close to eachother but not moving towards, so they are "
      "not colliding") {
    Particle particle_1 =
        Particle(vec2(169, 169), vec2(1, 1), ci::Color("blue"), 0, 1);
    Particle particle_2 =
        Particle(vec2(171, 169), vec2(1, 1), ci::Color("blue"), 0, 1);
    REQUIRE(particle_1.IsColliding(particle_2) == false);
  }

  SECTION("More than 2 Particles in Container and it can detect more than one collision") {
    Particle particle_1 =
        Particle(vec2(169, 169), vec2(1, 1), ci::Color("blue"), 0, 1);
    Particle particle_2 =
        Particle(vec2(171, 169), vec2(-1, -1), ci::Color("blue"), 0, 1);
    REQUIRE(particle_1.IsColliding(particle_2) == true);

    Particle particle_3 =
        Particle(vec2(159, 159), vec2(1, 1), ci::Color("blue"), 0, 1);
    Particle particle_4 =
        Particle(vec2(161, 159), vec2(-1, -1), ci::Color("blue"), 0, 1);

    REQUIRE(particle_3.IsColliding(particle_4) == true);
  }

  SECTION("More than 2 Particles in Container and detects one collision, but other is not colliding") {
    Particle particle_1 =
        Particle(vec2(169, 169), vec2(1, 1), ci::Color("blue"), 0, 1);
    Particle particle_2 =
        Particle(vec2(171, 169), vec2(-1, -1), ci::Color("blue"), 0, 1);
    REQUIRE(particle_1.IsColliding(particle_2) == true);

    Particle particle_3 =
        Particle(vec2(159, 159), vec2(1, 1), ci::Color("blue"), 0, 1);
    Particle particle_4 =
        Particle(vec2(161, 179), vec2(-1, -1), ci::Color("blue"), 0, 1);

    REQUIRE(particle_3.IsColliding(particle_4) == false);
  }
}

TEST_CASE("Check Velocity after collision") {
  SECTION("Particles Collided") {
    Particle particle_1 =
        Particle(vec2(192, 110), vec2(-1, 1), ci::Color("blue"), 3, 3);
    Particle particle_2 =
        Particle(vec2(187, 110), vec2(1, 1), ci::Color("blue"), 2, 2);
    REQUIRE(particle_1.IsColliding(particle_2) == true);
    particle_1.set_collided_velocity(particle_2);
    REQUIRE(particle_1.velocity().x == Approx(0.6));
    REQUIRE(particle_1.velocity().y == Approx(1.0));
    REQUIRE(particle_2.velocity().x == Approx(-1.4));
    REQUIRE(particle_2.velocity().y == Approx(1.0));
  }

  SECTION(
      "Particles are not moving towards each other (Velocity should not "
      "change!)") {
    Particle particle_1 =
        Particle(vec2(169, 169), vec2(1, 1), ci::Color("blue"), 0, 1);
    Particle particle_2 =
        Particle(vec2(171, 169), vec2(1, 1), ci::Color("blue"), 0, 1);
    REQUIRE(particle_1.IsColliding(particle_2) == false);
    REQUIRE_THROWS_AS(particle_1.set_collided_velocity(particle_2),
                      std::invalid_argument);
  }
}

TEST_CASE("Test Collided Velocity Calculation") {
  SECTION("Check Calculated Collision Velocity") {
    Particle particle_1 =
        Particle(vec2(169, 169), vec2(-1, 1), ci::Color("blue"), 3, 1);
    Particle particle_2 =
        Particle(vec2(171, 169), vec2(1, 1), ci::Color("blue"), 2, 1);

    REQUIRE(particle_1.CalculateCollidedVelocity(particle_2, 1).x ==
            Approx(0.6));
    REQUIRE(particle_1.CalculateCollidedVelocity(particle_2, 1).y == Approx(1));
    REQUIRE(particle_1.CalculateCollidedVelocity(particle_2, 2).x == Approx(-1.4));
    REQUIRE(particle_1.CalculateCollidedVelocity(particle_2,2).y == Approx(1));
  }
  SECTION("Invalid Particle Number to Calculate Velocity") {
    Particle particle_1 =
        Particle(vec2(169, 169), vec2(-1, 1), ci::Color("blue"), 3, 1);
    Particle particle_2 =
        Particle(vec2(171, 169), vec2(1, 1), ci::Color("blue"), 2, 1);

    REQUIRE_THROWS_AS(particle_1.CalculateCollidedVelocity(particle_2, 3), std::invalid_argument);
  }
}