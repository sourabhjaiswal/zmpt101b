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
  void set_conf_calibration(float calibration) { this->calibration_ = calibration; }
  void set_conf_timeout(uint32_t timeout) { this->timeout_ = timeout; }
  void set_conf_phase_shift(float phase_shift) { this->phase_shift_ = phase_shift; }

 protected:

  float phase_shift_;
  float calibration_;
  uint32_t timeout_;
  EnergyMonitor emon1;             // Create an instance
  uint8_t pin_;
};

}  // namespace zmpt101b
}  // namespace esphome
