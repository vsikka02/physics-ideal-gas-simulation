#include "gas_simulation_app.h"

namespace idealgas {

std::vector<size_t> particle_numbers {20,10,10};

IdealGasApp::IdealGasApp()
    : container_(GasContainer(particle_numbers)) {
  ci::app::setWindowSize(kWindowSize, kWindowSize);
}

void IdealGasApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);

  container_.Display();
}

void IdealGasApp::update() {
  container_.AdvanceOneFrame();
}

}  // namespace idealgas
