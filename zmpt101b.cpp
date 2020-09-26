#include "zmpt101b_sensor.h"

#include "esphome/core/log.h"
#include <cmath>

namespace esphome {
namespace zmpt101b {

static const char *TAG = "zmpt101b";

void ZMPT101BSensor::setup() {

	this->emon1.voltage(34,this->calibration,this->phase_shift);
  });
}

void ZMPT101BSensor::dump_config() {
  LOG_SENSOR("", "ZMPT101B Sensor", this);
  ESP_LOGCONFIG(TAG, "  Phase Shift: %.2fs, Number of Samples: %f ", this->phase_shift,this->num_samples_);
  LOG_UPDATE_INTERVAL(this);
}

void ZMPT101BSensor::update() {
  float supplyVoltage   = this->emon1.Vrms;             //extract Vrms into Variable
  this->publish_state(supplyVoltage);
}

void ZMPT101BSensor::loop() {
  this->emon1.calcVI(20,2000);
}

}  // namespace zmpt101b
}  // namespace esphome