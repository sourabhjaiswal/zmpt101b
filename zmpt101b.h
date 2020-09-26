#pragma once

#include "esphome/core/component.h"
#include "esphome/core/esphal.h"
#include "esphome/components/sensor/sensor.h"
#include "EmonLib.h"

namespace esphome {
namespace zmpt101b {

class ZMPT101BSensor : public sensor::Sensor, public PollingComponent {
 public:
  void setup() override;
  void update() override;
  void loop() override;
  void dump_config() override;
  float get_setup_priority() const override {
    // After the base sensor has been initialized
    return setup_priority::DATA - 1.0f;
  }
  void set_pin(uint8_t pin) { this->pin_ = pin; }

 protected:

  float phase_shift = 1.7;
  float calibration = 84;
  uint32_t num_samples_ = 2000;
  /// Calibrate offset value once at boot
  bool is_calibrating_offset_ = false;
  EnergyMonitor emon1;             // Create an instance
  uint8_t pin_;
};

}  // namespace zmpt101b
}  // namespace esphome
