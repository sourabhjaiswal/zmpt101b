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
  ESP_LOGCONFIG(TAG, "  Phase Shift: %f, Sample Duration: %d, Calibration: %f", this->phase_shift_,this->number_of_samples_*this->frequency_,this->calibration_);
  LOG_UPDATE_INTERVAL(this);
}

void ZMPT101BSensor::update() {
  // Set timeout for ending sampling phase
    this->set_timeout("read", this->number_of_samples_*this->frequency_, [this]() {
        this->is_sampling_ = false;
    
        if (this->num_samples_ == 0) {
          // Shouldn't happen, but let's not crash if it does.
          this->publish_state(NAN);
          return;
        }
    
        float sampled_voltage = this->sample_sum_ / this->num_samples_;
        //ESP_LOGD(TAG, "'%s' - Raw Value: %.2fA", this->name_.c_str(), irms);
        this->publish_state(sampled_voltage);
      });

  // Set sampling values
  this->is_sampling_ = true;
  this->num_samples_ = 0;
  this->sample_sum_ = 0.0f;
}

void ZMPT101BSensor::loop() {
    this->emon1.calcVI(20,this->frequency_);
    float supplyVoltage   = this->emon1.Vrms;             //extract Vrms into Variable
    if (isnan(supplyVoltage))
        return;
    this->sample_sum_ += supplyVoltage;
    this->num_samples_++;
}

}  // namespace zmpt101b
}  // namespace esphome
