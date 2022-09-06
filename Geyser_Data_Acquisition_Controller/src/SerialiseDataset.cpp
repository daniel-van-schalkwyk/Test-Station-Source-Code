#include <Arduino.h>
#include <ArduinoJson.h>

class SerialiseDataset
{
private:
    /* data */
public:

    SerialiseDataset(/* args */);
    ~SerialiseDataset();
};

SerialiseDataset::SerialiseDataset(/* args */)
{


}

static void AddDataToJsonDataset()
{
    DynamicJsonDocument doc(4096);

    JsonObject MetaData = doc.createNestedObject("MetaData");
    MetaData["SamplingRate"] = 5;
    MetaData["OperatorName"] = "Daniel van Schalkwyk";
    MetaData["GeneralInfo"] = "Some text here";

    JsonArray DataCollection = doc.createNestedArray("DataCollection");

    JsonObject DataCollection_0 = DataCollection.createNestedObject();
    DataCollection_0["TimeStamp"] = "2022-01-07T15:51:42";

    JsonObject DataCollection_0_SetParameters = DataCollection_0.createNestedObject("SetParameters");
    DataCollection_0_SetParameters["ChamberSetTemp"] = 0;
    DataCollection_0_SetParameters["GeyserWaterSetTemp"] = 0;
    DataCollection_0_SetParameters["InletWaterSetTemp"] = 0;
    DataCollection_0_SetParameters["DesiredFlowRate"] = 0;

    JsonObject DataCollection_0_RegulationFlags = DataCollection_0.createNestedObject("RegulationFlags");
    DataCollection_0_RegulationFlags["ChamberAirTempReg"] = true;
    DataCollection_0_RegulationFlags["GeyserWaterTempReg"] = false;
    DataCollection_0_RegulationFlags["InletWaterTempReg"] = true;
    DataCollection_0_RegulationFlags["FlowRateReg"] = true;
    DataCollection_0_RegulationFlags["WaterScheduleControl"] = true;
    DataCollection_0_RegulationFlags["PowerScheduleControl"] = false;

    JsonObject DataCollection_0_TestBenchStates = DataCollection_0.createNestedObject("TestBenchStates");
    DataCollection_0_TestBenchStates["ChamberHeatingFans"] = true;
    DataCollection_0_TestBenchStates["ChamberVentingFans"] = false;
    DataCollection_0_TestBenchStates["CirculationFans"] = true;
    DataCollection_0_TestBenchStates["ChamberHeatingElement"] = true;
    DataCollection_0_TestBenchStates["WaterValveState"] = false;
    DataCollection_0_TestBenchStates["GeyserHeatingFlag"] = true;

    JsonObject DataCollection_0_ExternalMeasurements = DataCollection_0.createNestedObject("ExternalMeasurements");
    DataCollection_0_ExternalMeasurements["PowerConsumed"] = 0;
    DataCollection_0_ExternalMeasurements["WaterConsumed"] = 0;
    DataCollection_0_ExternalMeasurements["TotalWaterConsumed"] = 0;
    DataCollection_0_ExternalMeasurements["GeyserWaterThermostatTemp"] = 0;
    DataCollection_0_ExternalMeasurements["InletWaterTemp"] = 0;
    DataCollection_0_ExternalMeasurements["OutletWaterTemp"] = 0;
    DataCollection_0_ExternalMeasurements["TopGeyserSurfaceTemp"] = 0;
    DataCollection_0_ExternalMeasurements["BotGeyserSurfaceTemp"] = 0;
    DataCollection_0_ExternalMeasurements["LabTemp"] = 0;
    DataCollection_0_ExternalMeasurements["MeanChamberTemp"] = 0;

    JsonObject DataCollection_0_InternalTankTemperatures = DataCollection_0.createNestedObject("InternalTankTemperatures");

    JsonArray DataCollection_0_InternalTankTemperatures_Bus0 = DataCollection_0_InternalTankTemperatures.createNestedArray("Bus0");
    DataCollection_0_InternalTankTemperatures_Bus0.add(0);
    DataCollection_0_InternalTankTemperatures_Bus0.add(0);
    DataCollection_0_InternalTankTemperatures_Bus0.add(0);
    DataCollection_0_InternalTankTemperatures_Bus0.add(0);
    DataCollection_0_InternalTankTemperatures_Bus0.add(0);
    DataCollection_0_InternalTankTemperatures_Bus0.add(0);
    DataCollection_0_InternalTankTemperatures_Bus0.add(0);
    DataCollection_0_InternalTankTemperatures_Bus0.add(0);
    DataCollection_0_InternalTankTemperatures_Bus0.add(0);

    JsonArray DataCollection_0_InternalTankTemperatures_Bus1 = DataCollection_0_InternalTankTemperatures.createNestedArray("Bus1");
    DataCollection_0_InternalTankTemperatures_Bus1.add(0);
    DataCollection_0_InternalTankTemperatures_Bus1.add(0);
    DataCollection_0_InternalTankTemperatures_Bus1.add(0);
    DataCollection_0_InternalTankTemperatures_Bus1.add(0);
    DataCollection_0_InternalTankTemperatures_Bus1.add(0);
    DataCollection_0_InternalTankTemperatures_Bus1.add(0);
    DataCollection_0_InternalTankTemperatures_Bus1.add(0);
    DataCollection_0_InternalTankTemperatures_Bus1.add(0);
    DataCollection_0_InternalTankTemperatures_Bus1.add(0);

    JsonArray DataCollection_0_InternalTankTemperatures_Bus2 = DataCollection_0_InternalTankTemperatures.createNestedArray("Bus2");
    DataCollection_0_InternalTankTemperatures_Bus2.add(0);
    DataCollection_0_InternalTankTemperatures_Bus2.add(0);
    DataCollection_0_InternalTankTemperatures_Bus2.add(0);
    DataCollection_0_InternalTankTemperatures_Bus2.add(0);
    DataCollection_0_InternalTankTemperatures_Bus2.add(0);
    DataCollection_0_InternalTankTemperatures_Bus2.add(0);
    DataCollection_0_InternalTankTemperatures_Bus2.add(0);
    DataCollection_0_InternalTankTemperatures_Bus2.add(0);
    DataCollection_0_InternalTankTemperatures_Bus2.add(0);

    JsonArray DataCollection_0_InternalTankTemperatures_Bus3 = DataCollection_0_InternalTankTemperatures.createNestedArray("Bus3");
    DataCollection_0_InternalTankTemperatures_Bus3.add(0);
    DataCollection_0_InternalTankTemperatures_Bus3.add(0);
    DataCollection_0_InternalTankTemperatures_Bus3.add(0);
    DataCollection_0_InternalTankTemperatures_Bus3.add(0);
    DataCollection_0_InternalTankTemperatures_Bus3.add(0);
    DataCollection_0_InternalTankTemperatures_Bus3.add(0);
    DataCollection_0_InternalTankTemperatures_Bus3.add(0);
    DataCollection_0_InternalTankTemperatures_Bus3.add(0);
    DataCollection_0_InternalTankTemperatures_Bus3.add(0);

    JsonArray DataCollection_0_InternalTankTemperatures_Bus4 = DataCollection_0_InternalTankTemperatures.createNestedArray("Bus4");
    DataCollection_0_InternalTankTemperatures_Bus4.add(0);
    DataCollection_0_InternalTankTemperatures_Bus4.add(0);
    DataCollection_0_InternalTankTemperatures_Bus4.add(0);
    DataCollection_0_InternalTankTemperatures_Bus4.add(0);
    DataCollection_0_InternalTankTemperatures_Bus4.add(0);
    DataCollection_0_InternalTankTemperatures_Bus4.add(0);

    JsonArray DataCollection_0_InternalTankTemperatures_Bus5 = DataCollection_0_InternalTankTemperatures.createNestedArray("Bus5");
    DataCollection_0_InternalTankTemperatures_Bus5.add(0);
    DataCollection_0_InternalTankTemperatures_Bus5.add(0);
    DataCollection_0_InternalTankTemperatures_Bus5.add(0);
    DataCollection_0_InternalTankTemperatures_Bus5.add(0);
    DataCollection_0_InternalTankTemperatures_Bus5.add(0);
    DataCollection_0_InternalTankTemperatures_Bus5.add(0);
    DataCollection_0_InternalTankTemperatures_Bus5.add(0);
    DataCollection_0_InternalTankTemperatures_Bus5.add(0);

    JsonArray DataCollection_0_InternalTankTemperatures_Bus6 = DataCollection_0_InternalTankTemperatures.createNestedArray("Bus6");
    DataCollection_0_InternalTankTemperatures_Bus6.add(0);
    DataCollection_0_InternalTankTemperatures_Bus6.add(0);
    DataCollection_0_InternalTankTemperatures_Bus6.add(0);
    DataCollection_0_InternalTankTemperatures_Bus6.add(0);
    DataCollection_0_InternalTankTemperatures_Bus6.add(0);
    DataCollection_0_InternalTankTemperatures_Bus6.add(0);
    DataCollection_0_InternalTankTemperatures_Bus6.add(0);
    DataCollection_0_InternalTankTemperatures_Bus6.add(0);

    JsonArray DataCollection_0_InternalTankTemperatures_Bus7 = DataCollection_0_InternalTankTemperatures.createNestedArray("Bus7");
    DataCollection_0_InternalTankTemperatures_Bus7.add(0);
    DataCollection_0_InternalTankTemperatures_Bus7.add(0);
    DataCollection_0_InternalTankTemperatures_Bus7.add(0);
    DataCollection_0_InternalTankTemperatures_Bus7.add(0);
    DataCollection_0_InternalTankTemperatures_Bus7.add(0);
    DataCollection_0_InternalTankTemperatures_Bus7.add(0);
    DataCollection_0_InternalTankTemperatures_Bus7.add(0);
    DataCollection_0_InternalTankTemperatures_Bus7.add(0);

    JsonArray DataCollection_0_InternalTankTemperatures_Bus8 = DataCollection_0_InternalTankTemperatures.createNestedArray("Bus8");
    DataCollection_0_InternalTankTemperatures_Bus8.add(0);
    DataCollection_0_InternalTankTemperatures_Bus8.add(0);
    DataCollection_0_InternalTankTemperatures_Bus8.add(0);
    DataCollection_0_InternalTankTemperatures_Bus8.add(0);
    DataCollection_0_InternalTankTemperatures_Bus8.add(0);
    DataCollection_0_InternalTankTemperatures_Bus8.add(0);
    DataCollection_0_InternalTankTemperatures_Bus8.add(0);
    DataCollection_0_InternalTankTemperatures_Bus8.add(0);

    JsonObject DataCollection_1 = DataCollection.createNestedObject();
    DataCollection_1["TimeStamp"] = "2022-01-07T15:51:47";

    JsonObject DataCollection_1_SetParameters = DataCollection_1.createNestedObject("SetParameters");
    DataCollection_1_SetParameters["ChamberSetTemp"] = 0;
    DataCollection_1_SetParameters["GeyserWaterSetTemp"] = 0;
    DataCollection_1_SetParameters["InletWaterSetTemp"] = 0;
    DataCollection_1_SetParameters["DesiredFlowRate"] = 0;

    JsonObject DataCollection_1_RegulationFlags = DataCollection_1.createNestedObject("RegulationFlags");
    DataCollection_1_RegulationFlags["ChamberAirTempReg"] = true;
    DataCollection_1_RegulationFlags["GeyserWaterTempReg"] = false;
    DataCollection_1_RegulationFlags["InletWaterTempReg"] = true;
    DataCollection_1_RegulationFlags["FlowRateReg"] = true;
    DataCollection_1_RegulationFlags["WaterScheduleControl"] = true;
    DataCollection_1_RegulationFlags["PowerScheduleControl"] = false;

    JsonObject DataCollection_1_TestBenchStates = DataCollection_1.createNestedObject("TestBenchStates");
    DataCollection_1_TestBenchStates["ChamberHeatingFans"] = true;
    DataCollection_1_TestBenchStates["ChamberVentingFans"] = false;
    DataCollection_1_TestBenchStates["CirculationFans"] = true;
    DataCollection_1_TestBenchStates["ChamberHeatingElement"] = true;
    DataCollection_1_TestBenchStates["WaterValveState"] = false;
    DataCollection_1_TestBenchStates["GeyserHeatingFlag"] = true;

    JsonObject DataCollection_1_ExternalMeasurements = DataCollection_1.createNestedObject("ExternalMeasurements");
    DataCollection_1_ExternalMeasurements["PowerConsumed"] = 0;
    DataCollection_1_ExternalMeasurements["WaterConsumed"] = 0;
    DataCollection_1_ExternalMeasurements["TotalWaterConsumed"] = 0;
    DataCollection_1_ExternalMeasurements["GeyserWaterThermostatTemp"] = 0;
    DataCollection_1_ExternalMeasurements["InletWaterTemp"] = 0;
    DataCollection_1_ExternalMeasurements["OutletWaterTemp"] = 0;
    DataCollection_1_ExternalMeasurements["TopGeyserSurfaceTemp"] = 0;
    DataCollection_1_ExternalMeasurements["BotGeyserSurfaceTemp"] = 0;
    DataCollection_1_ExternalMeasurements["LabTemp"] = 0;
    DataCollection_1_ExternalMeasurements["MeanChamberTemp"] = 0;

    JsonObject DataCollection_1_InternalTankTemperatures = DataCollection_1.createNestedObject("InternalTankTemperatures");

    JsonArray DataCollection_1_InternalTankTemperatures_Bus0 = DataCollection_1_InternalTankTemperatures.createNestedArray("Bus0");
    for (size_t i = 0; i < 9; i++)
    {
        DataCollection_1_InternalTankTemperatures_Bus0.add(0);
    }

    JsonArray DataCollection_1_InternalTankTemperatures_Bus1 = DataCollection_1_InternalTankTemperatures.createNestedArray("Bus1");
    for (size_t i = 0; i < 9; i++)
    {
        DataCollection_1_InternalTankTemperatures_Bus1.add(0);
    }

    JsonArray DataCollection_1_InternalTankTemperatures_Bus2 = DataCollection_1_InternalTankTemperatures.createNestedArray("Bus2");
    for (size_t i = 0; i < 9; i++)
    {
        DataCollection_1_InternalTankTemperatures_Bus2.add(0);
    }

    JsonArray DataCollection_1_InternalTankTemperatures_Bus3 = DataCollection_1_InternalTankTemperatures.createNestedArray("Bus3");
    for (size_t i = 0; i < 9; i++)
    {
        DataCollection_1_InternalTankTemperatures_Bus3.add(0);
    }

    JsonArray DataCollection_1_InternalTankTemperatures_Bus4 = DataCollection_1_InternalTankTemperatures.createNestedArray("Bus4");
    for (size_t i = 0; i < 9; i++)
    {
        if( i != 3 || i != 4 || i != 5 )    // Exclude the inbetween sensors that don't exist
            DataCollection_1_InternalTankTemperatures_Bus4.add(0);
    }

    JsonArray DataCollection_1_InternalTankTemperatures_Bus5 = DataCollection_1_InternalTankTemperatures.createNestedArray("Bus5");
    for (size_t i = 0; i < 8; i++)
    {
        DataCollection_1_InternalTankTemperatures_Bus5.add(0);
    }

    JsonArray DataCollection_1_InternalTankTemperatures_Bus6 = DataCollection_1_InternalTankTemperatures.createNestedArray("Bus6");
    for (size_t i = 0; i < 8; i++)
    {
        DataCollection_1_InternalTankTemperatures_Bus6.add(0);
    }

    JsonArray DataCollection_1_InternalTankTemperatures_Bus7 = DataCollection_1_InternalTankTemperatures.createNestedArray("Bus7");
    for (size_t i = 0; i < 8; i++)
    {
        DataCollection_1_InternalTankTemperatures_Bus7.add(0);
    }

    JsonArray DataCollection_1_InternalTankTemperatures_Bus8 = DataCollection_1_InternalTankTemperatures.createNestedArray("Bus8");
    for (size_t i = 0; i < 8; i++)
    {
        DataCollection_1_InternalTankTemperatures_Bus8.add(0);
    }

// serializeJson(doc, output);
}


