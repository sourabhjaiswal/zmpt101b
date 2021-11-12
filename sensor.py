import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import sensor
from esphome.const import CONF_SENSOR, CONF_ID, CONF_PIN, ICON_PULSE, UNIT_VOLT, CONF_CALIBRATION, CONF_FREQUENCY 


CODEOWNERS = ['@sourabhjaiswal']
CONF_PHASE_SHIFT = 'phase_shift'
CONF_NUMBER_OF_SAMPLES = 'num_of_samples'

FREQUENCY_OPTIONS = {
    '50hz': 50,
    '60hz': 60,
}

def validate_adc_pin(value):
    vcc = str(value).upper()
    if vcc == 'VCC':
        return cv.only_on_esp8266(vcc)
    return pins.internal_gpio_input_pin_schema(value)



zmpt101b_ns = cg.esphome_ns.namespace('zmpt101b')
ZMPT101BSensor = zmpt101b_ns.class_('ZMPT101BSensor', sensor.Sensor, cg.PollingComponent)

CONFIG_SCHEMA = sensor.sensor_schema(UNIT_VOLT, ICON_PULSE, 2).extend({
    cv.GenerateID(): cv.declare_id(ZMPT101BSensor),
    cv.Required(CONF_PIN): validate_adc_pin,
    cv.Optional(CONF_CALIBRATION, default=84): cv.float_,
    cv.Optional(CONF_NUMBER_OF_SAMPLES, default='20'): cv.int_,
    cv.Optional(CONF_FREQUENCY, default='50hz'): cv.enum(FREQUENCY_OPTIONS),
    cv.Optional(CONF_PHASE_SHIFT, default=1.7): cv.float_,
}).extend(cv.polling_component_schema('60s'))


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)
    cg.add_library('EmonLib', None)
    pin = await cg.gpio_pin_expression(config[CONF_PIN])
    cg.add(var.set_pin(pin))
    cg.add(var.set_conf_calibration(config[CONF_CALIBRATION]))
    cg.add(var.set_conf_number_of_samples(config[CONF_NUMBER_OF_SAMPLES]))
    cg.add(var.set_conf_frequency(config[CONF_FREQUENCY]))
    cg.add(var.set_conf_phase_shift(config[CONF_PHASE_SHIFT]))
