#include "gas_simulation_app.h"

namespace idealgas {

IdealGasApp::IdealGasApp()
    : container_(GasContainer(25)) {
  ci::app::setWindowSize(kWindowSize, kWindowSize);
}

void IdealGasApp::draw() {
  ci::Color background_color("white");
  ci::gl::clear(background_color);

  container_.Display();
}

void IdealGasApp::update() {
  container_.AdvanceOneFrame();
}

}  // namespace idealgas
