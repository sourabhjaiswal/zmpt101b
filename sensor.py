import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_SENSOR, CONF_ID, ICON_FLASH, UNIT_VOLT

CODEOWNERS = ['@sourabhjaiswal']

zmpt101b_ns = cg.esphome_ns.namespace('zmpt101b')
ZMPT101BSensor = zmpt101b_ns.class_('ZMPT101BSensor', sensor.Sensor, cg.PollingComponent)

CONFIG_SCHEMA = sensor.sensor_schema(UNIT_VOLT, ICON_FLASH, 2).extend({
    cv.GenerateID(): cv.declare_id(ZMPT101BSensor),
}).extend(cv.polling_component_schema('60s'))


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield sensor.register_sensor(var, config)
