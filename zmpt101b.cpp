#include "zmpt101b.h"

#include "esphome/core/log.h"
#include <cmath>

namespace esphome {
namespace zmpt101b {

static const char *TAG = "zmpt101b";

void ZMPT101BSensor::setup() {
    GPIOPin(this->pin_, INPUT).setup();
	this->emon1.voltage(this->pin_,this->calibration_,this->phase_shift_);
}

void ZMPT101BSensor::dump_config() {
  LOG_SENSOR("", "ZMPT101B Sensor", this);
  ESP_LOGCONFIG(TAG, "  Phase Shift: %f, TimeOut: %d, Calibration: %f", this->phase_shift_,this->timeout_,this->calibration_);
  LOG_UPDATE_INTERVAL(this);
}

void ZMPT101BSensor::update() {
  float supplyVoltage   = this->emon1.Vrms;             //extract Vrms into Variable
  this->publish_state(supplyVoltage);
}

void ZMPT101BSensor::loop() {
  this->emon1.calcVI(20,this->timeout_);
}

}  // namespace zmpt101b
}  // namespace esphome
