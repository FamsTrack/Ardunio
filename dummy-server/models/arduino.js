'use strict';
const {
  Model
} = require('sequelize');
module.exports = (sequelize, DataTypes) => {
  class Arduino extends Model {
    /**
     * Helper method for defining associations.
     * This method is not a part of Sequelize lifecycle.
     * The `models/index` file will call this method automatically.
     */
    static associate(models) {
      // define association here
    }
  };
  Arduino.init({
    ClientId: DataTypes.INTEGER,
    longitude: DataTypes.FLOAT,
    latitude: DataTypes.FLOAT,
    panic_btn: DataTypes.BOOLEAN,
    buzzer: DataTypes.BOOLEAN,
    arduino_unique_key: DataTypes.STRING
  }, {
    sequelize,
    modelName: 'Arduino',
  });
  return Arduino;
};