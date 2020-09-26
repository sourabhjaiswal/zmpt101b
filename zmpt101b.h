#pragma once

#include "esphome/core/component.h"
#include "esphome/core/esphal.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/EmonLib.h"
#include "esphome/EmonLib.cpp"

namespace esphome {
namespace zmpt101b {

class CTClampSensor : public sensor::Sensor, public PollingComponent {
 public:
  void setup() override;
  void update() override;
  void loop() override;
  void dump_config() override;
  float get_setup_priority() const override {
    // After the base sensor has been initialized
    return setup_priority::DATA - 1.0f;
  }

 protected:

  float phase_shift = 1.7f;
  float calibration = 84f;
  uint32_t num_samples_ = 2000;
  /// Calibrate offset value once at boot
  bool is_calibrating_offset_ = false;
  EnergyMonitor emon1;             // Create an instance
};

}  // namespace zmpt101b
}  // namespace esphome