'use strict';

module.exports = {
  up: async (queryInterface, Sequelize) => {
    const data = [{
      ClientId: 1,
      longitude: 0,
      latitude: 0,
      panic_btn: false,
      buzzer: false,
      arduino_unique_key: 'arduino1',
      updatedAt: new Date(),
      createdAt: new Date()
    },
    {
      ClientId: 2,
      longitude: 0,
      latitude: 0,
      panic_btn: false,
      buzzer: false,
      arduino_unique_key: 'arduino2',
      updatedAt: new Date(),
      createdAt: new Date()
    }]
   await queryInterface.bulkInsert('Arduinos',data,{})
  },

  down: async (queryInterface, Sequelize) => {
    await queryInterface.bulkDelete('Arduinos',null,{})
  }
};
