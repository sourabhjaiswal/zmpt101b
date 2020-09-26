import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import sensor
from esphome.const import CONF_SENSOR, CONF_ID, CONF_PIN, ICON_FLASH, UNIT_VOLT, CONF_CALIBRATION, CONF_TIMEOUT 


CODEOWNERS = ['@sourabhjaiswal']
CONF_PHASE_SHIFT = 'phase_shift'

def validate_adc_pin(value):
    vcc = str(value).upper()
    if vcc == 'VCC':
        return cv.only_on_esp8266(vcc)
    return pins.analog_pin(value)


zmpt101b_ns = cg.esphome_ns.namespace('zmpt101b')
ZMPT101BSensor = zmpt101b_ns.class_('ZMPT101BSensor', sensor.Sensor, cg.PollingComponent)

CONFIG_SCHEMA = sensor.sensor_schema(UNIT_VOLT, ICON_FLASH, 2).extend({
    cv.GenerateID(): cv.declare_id(ZMPT101BSensor),
    cv.Required(CONF_PIN): validate_adc_pin,
    cv.Optional(CONF_CALIBRATION, default=84): cv.float_,
    cv.Optional(CONF_TIMEOUT, default=2000): cv.int_,
    cv.Optional(CONF_PHASE_SHIFT, default=1.7): cv.float_,
}).extend(cv.polling_component_schema('60s'))


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield sensor.register_sensor(var, config)
    cg.add_library('EmonLib', '1.1.0')
    cg.add(var.set_pin(config[CONF_PIN]))
    cg.add(var.set_conf_calibration(config[CONF_CALIBRATION]))
    cg.add(var.set_conf_timeout(config[CONF_TIMEOUT]))
    cg.add(var.set_conf_phase_shift(config[CONF_PHASE_SHIFT]))
