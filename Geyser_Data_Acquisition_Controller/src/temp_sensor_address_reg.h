#ifndef temp_sensor_address_reg_H
#define temp_sensor_address_reg_H

#include "geyser_daq_controller.h"

// Define the temperature sensor address register for the internal boiler temperature data acquisition system.
const int boilerProfileBusNumber = 8;    // Number of OneWire buses to use for the boiler DAQ
const int maxSensorsPerBus = 9;     // Physically the most sensors per bus (Not limited by this number)
double boilerProfileTempArray[boilerProfileBusNumber][maxSensorsPerBus] = {};

// Define the temperature sensor address register for the climatic chamber, outside the geyser.
enum climaticChamberTempNames   {geyserWaterTempAddress, inletWaterAddress, outletWaterAddress,\
                                topSurfaceGeyserTempAddress, bottomSurfaceGeyserTempAddress,
                                outsideTempAddress, amb1TempAddress, amb2TempAddress, \
                                };  // This enumeration is used to assign the indices to names for better readibility
const int numOfChamberTempSensors = 8;  // Look at array below for size
double climaticChamberTempArray[numOfChamberTempSensors] = {};  // This global variable will store the instantanious temperature values obtained from the climatic chamber test station
const DeviceAddress climaticChamberTempReg[numOfChamberTempSensors] =    {
                                                        {}, // No address for this since it is a thermistor reading
                                                        {0x28, 0xA7, 0xB3, 0x79, 0xA2, 0x00, 0x03, 0xA6},   // Inlet water temperature sensor ROM address
                                                        {0x28, 0x50, 0x33, 0x79, 0xA2, 0x00, 0x03, 0x9A},   // Outlet water temperature sensor ROM address
                                                        // {0x28, 0x23, 0xE9, 0x79, 0xA2, 0x00, 0x03, 0xB8},   // Source water temperature sensor ROM address
                                                        {0x28, 0xFF, 0x64, 0x19, 0xCE, 0x3B, 0xF0, 0x30},   // Top surface temperature of geyser 
                                                        {0x28, 0xFF, 0x64, 0x19, 0xCF, 0xA4, 0x35, 0xB5},   // Bottom surface temperature of geyser 
                                                        {0x28, 0x70, 0x93, 0x79, 0xA2, 0x00, 0x03, 0x1F},   // Lab ambient temperature sensor ROM address
                                                        {0x28, 0x7F, 0x24, 0x4D, 0x22, 0x20, 0x01, 0x7C},   // Chamber ambient 1 temperature sensor ROM address
                                                        {0x28, 0xFF, 0x9F, 0xB6, 0xA1, 0x16, 0x05, 0x2C}    // Chamber ambient 2 temperature sensor ROM address
                                                    };   // Extra surface temp sensor address --> 0x28, 0xFF, 0x64, 0x19, 0xCF, 0xA4, 0xD7, 0xE0

const DeviceAddress boilerProfileTempReg[boilerProfileBusNumber][maxSensorsPerBus]  = // This 2D array is used to store the temperature sensor 64-bit ROM addresses
                                                    {   // TO-DO: 
                                                        {   
                                                            // Sensor region 0
                                                            {0x28, 0x1B, 0x75, 0x75, 0xD0, 0x01, 0x3C, 0xEB},     // Sensor (0,0)                                               
                                                            {0x28, 0x75, 0x95, 0x75, 0xD0, 0x01, 0x3C, 0xE1},     // Sensor (0,1)
                                                            {0x28, 0xE6, 0x44, 0x75, 0xD0, 0x01, 0x3C, 0x9A},     // Sensor (0,2)
                                                            {0x28, 0x6D, 0x74, 0x75, 0xD0, 0x01, 0x3C, 0x0C},     // Sensor (0,3)
                                                            {0x28, 0x38, 0xCC, 0x75, 0xD0, 0x01, 0x3C, 0xB8},     // Sensor (0,4)
                                                            {0x28, 0x77, 0x1B, 0x75, 0xD0, 0x01, 0x3C, 0xE6},     // Sensor (0,5)
                                                            {0x28, 0x92, 0x7D, 0x75, 0xD0, 0x01, 0x3C, 0xA9},     // Sensor (0,6)
                                                            {0x28, 0xF3, 0x8A, 0x75, 0xD0, 0x01, 0x3C, 0xAA},     // Sensor (0,7)
                                                            {0x28, 0x57, 0x54, 0x75, 0xD0, 0x01, 0x3C, 0xD6}      // Sensor (0,8)
                                                        },
                                                            // Sensor region 1
                                                        {   {0x28, 0xDD, 0xBA, 0x75, 0xD0, 0x01, 0x3C, 0x8B},     // Sensor (1,0)
                                                            {0x28, 0xEB, 0x35, 0x75, 0xD0, 0x01, 0x3C, 0x70},     // Sensor (1,1)                                               
                                                            {0x28, 0x92, 0x6E, 0x75, 0xD0, 0x01, 0x3C, 0x9B},     // Sensor (1,2)
                                                            {0x28, 0xA1, 0xC7, 0x75, 0xD0, 0x01, 0x3C, 0xEF},     // Sensor (1,3)
                                                            {0x28, 0xD1, 0x80, 0x75, 0xD0, 0x01, 0x3C, 0xCF},     // Sensor (1,4)
                                                            {0x28, 0x46, 0x8E, 0x75, 0xD0, 0x01, 0x3C, 0x59},     // Sensor (1,5)
                                                            {0x28, 0x68, 0x00, 0x75, 0xD0, 0x01, 0x3C, 0x95},     // Sensor (1,6)
                                                            {0x28, 0x7E, 0x4D, 0x75, 0xD0, 0x01, 0x3C, 0x79},     // Sensor (1,7)
                                                            {0x28, 0xBD, 0xCC, 0x75, 0xD0, 0x01, 0x3C, 0xB9}      // Sensor (1,8)
                                                        },
                                                        {   // Sensor region 2
                                                            {0x28, 0xEE, 0x81, 0x75, 0xD0, 0x01, 0x3C, 0xCB},     // Sensor (2,0)
                                                            {0x28, 0xB7, 0x7A, 0x75, 0xD0, 0x01, 0x3C, 0xA5},     // Sensor (2,1)                                               
                                                            {0x28, 0x56, 0x62, 0x75, 0xD0, 0x01, 0x3C, 0xF9},     // Sensor (2,2)
                                                            {0x28, 0xBD, 0x3B, 0x75, 0xD0, 0x01, 0x3C, 0x4E},     // Sensor (2,3)
                                                            {0x28, 0xCC, 0x42, 0x75, 0xD0, 0x01, 0x3C, 0x7F},     // Sensor (2,4)
                                                            {0x28, 0x7A, 0x8C, 0x75, 0xD0, 0x01, 0x3C, 0x4A},     // Sensor (2,5)
                                                            {0x28, 0x7A, 0x3A, 0x75, 0xD0, 0x01, 0x3C, 0x99},     // Sensor (2,6)
                                                            {0x28, 0x3C, 0x6D, 0x75, 0xD0, 0x01, 0x3C, 0x9A},     // Sensor (2,7)
                                                            {0x28, 0x21, 0x56, 0x75, 0xD0, 0x01, 0x3C, 0x7F}      // Sensor (2,8)
                                                        },   
                                                            // Sensor region 3
                                                        {   {0x28, 0x19, 0x44, 0x75, 0xD0, 0x01, 0x3C, 0xCC},     // Sensor (3,0)
                                                            {0x28, 0x73, 0x05, 0x75, 0xD0, 0x01, 0x3C, 0xE4},     // Sensor (3,1)                                               
                                                            {0x28, 0xA5, 0x07, 0x75, 0xD0, 0x01, 0x3C, 0x11},     // Sensor (3,2)
                                                            {0x28, 0x7A, 0x04, 0x75, 0xD0, 0x01, 0x3C, 0xBF},     // Sensor (3,3)
                                                            {0x28, 0x71, 0x71, 0x75, 0xD0, 0x01, 0x3C, 0xF8},     // Sensor (3,4)
                                                            {0x28, 0x48, 0x97, 0x75, 0xD0, 0x01, 0x3C, 0xC5},     // Sensor (3,5)
                                                            {0x28, 0x80, 0x1F, 0x75, 0xD0, 0x01, 0x3C, 0x0E},     // Sensor (3,6)
                                                            {0x28, 0x9E, 0xD9, 0x75, 0xD0, 0x01, 0x3C, 0xF8},     // Sensor (3,7)
                                                            {0x28, 0x42, 0x45, 0x75, 0xD0, 0x01, 0x3C, 0xD7}      // Sensor (3,8)
                                                        },
                                                            // Sensor region 4
                                                        {   {0x28, 0x42, 0x87, 0x75, 0xD0, 0x01, 0x3C, 0x76},     // Sensor (4,0)
                                                            {0x28, 0x77, 0x4D, 0x75, 0xD0, 0x01, 0x3C, 0xEF},     // Sensor (4,1)                                               
                                                            {0x28, 0x38, 0x21, 0x75, 0xD0, 0x01, 0x3C, 0x8E},     // Sensor (4,2)
                                                            {},     // N/A (No sensor there)
                                                            {},     // N/A (No sensor there)
                                                            {},     // N/A (No sensor there)
                                                            {0x28, 0x4A, 0x7C, 0x75, 0xD0, 0x01, 0x3C, 0x01},     // Sensor (4,6)
                                                            {0x28, 0xA1, 0x8F, 0x75, 0xD0, 0x01, 0x3C, 0x38},     // Sensor (4,7)
                                                            {0x28, 0x03, 0x56, 0x75, 0xD0, 0x01, 0x3C, 0xA7}      // Sensor (4,8)
                                                        },  
                                                            // Sensor region 5
                                                        {   {0x28, 0x57, 0x84, 0x75, 0xD0, 0x01, 0x3C, 0x88},     // Sensor (5,0)
                                                            {0x28, 0x65, 0x35, 0x75, 0xD0, 0x01, 0x3C, 0x89},     // Sensor (5,1)                                               
                                                            {0x28, 0xC6, 0x88, 0x75, 0xD0, 0x01, 0x3C, 0x2F},     // Sensor (5,2)
                                                            {0x28, 0x98, 0x1C, 0x75, 0xD0, 0x01, 0x3C, 0xBA},     // Sensor (5,3)
                                                            {0x28, 0xDD, 0xE2, 0x75, 0xD0, 0x01, 0x3C, 0x20},     // Sensor (5,4)
                                                            {0x28, 0x92, 0x55, 0x75, 0xD0, 0x01, 0x3C, 0x6F},     // Sensor (5,5)
                                                            {0x28, 0x2B, 0x9F, 0x75, 0xD0, 0x01, 0x3C, 0x61},     // Sensor (5,6)
                                                            {0x28, 0xED, 0x61, 0x75, 0xD0, 0x01, 0x3C, 0x48},     // Sensor (5,7)
                                                            {}      // N/A (No sensor connected here)
                                                        },  
                                                            // Sensor region 6
                                                        {   {0x28, 0x3F, 0xF6, 0x75, 0xD0, 0x01, 0x3C, 0x04},     // Sensor (6,0)
                                                            {0x28, 0xA1, 0x3B, 0x75, 0xD0, 0x01, 0x3C, 0x68},     // Sensor (6,1)                                               
                                                            {0x28, 0x5A, 0xB8, 0x75, 0xD0, 0x01, 0x3C, 0x67},     // Sensor (6,2)
                                                            {0x28, 0xFA, 0xCD, 0x75, 0xD0, 0x01, 0x3C, 0x84},     // Sensor (6,3)
                                                            {0x28, 0x6B, 0x75, 0x75, 0xD0, 0x01, 0x3C, 0x73},     // Sensor (6,4)
                                                            {0x28, 0xD3, 0x63, 0x75, 0xD0, 0x01, 0x3C, 0x35},     // Sensor (6,5)
                                                            {0x28, 0xEC, 0xD9, 0x75, 0xD0, 0x01, 0x3C, 0x0E},     // Sensor (6,6)
                                                            {0x28, 0x21, 0x4C, 0x75, 0xD0, 0x01, 0x3C, 0xBE},     // Sensor (6,7)
                                                            {}      // N/A (No sensor connected here)
                                                        },
                                                            // Sensor region 7
                                                        {   {0x28, 0x76, 0xA4, 0x75, 0xD0, 0x01, 0x3C, 0xF1},     // Sensor (7,0)
                                                            {0x28, 0xEB, 0x51, 0x75, 0xD0, 0x01, 0x3C, 0x7E},     // Sensor (7,1)                                                
                                                            {0x28, 0xBB, 0xC9, 0x75, 0xD0, 0x01, 0x3C, 0xD9},     // Sensor (7,2)
                                                            {0x28, 0x71, 0xC0, 0x75, 0xD0, 0x01, 0x3C, 0x7A},     // Sensor (7,3)
                                                            {0x28, 0xA0, 0x0D, 0x75, 0xD0, 0x01, 0x3C, 0x47},     // Sensor (7,4)
                                                            {0x28, 0xF9, 0x64, 0x75, 0xD0, 0x01, 0x3C, 0x1D},     // Sensor (7,5)
                                                            {0x28, 0xF1, 0x59, 0x75, 0xD0, 0x01, 0x3C, 0xD4},     // Sensor (7,6)
                                                            {0x28, 0x3D, 0xFE, 0x75, 0xD0, 0x01, 0x3C, 0x54},     // Sensor (7,7)
                                                            {}      // N/A (No sensor connected here)
                                                        }
                                                    };

#endif