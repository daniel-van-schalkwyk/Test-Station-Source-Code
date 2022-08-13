// #include "GeyserDaqController.h"

class ControlEnvironment
{
    public: // Access modifier
    // Properties

    /**
     @brief  This function is responsible for ensuring that the environment of the EWH unit 
            remains at the desireable parameters and that the geyser schedule is followed.
            Different climatic chamber functions
            1. Ambient Temperature
                1.1. Venting environment when too hot
                1.2. Heating environment when too cold
            2. Geyser internal temperature
                2.1. Switching off element when higher than set point
                2.2. Switching on element when lower than set point 
            3. Schedule for on and off time of the geyser
                3.1. Switch system on according to schedule
                3.2. Swicth system off according to schedule
            4. Control electric ball valve to allow flow of water
                4.1. Open valve to enable flow of water [scheduled or manual]
                4.2. Close vale to disable flow of water [after consumption goal or manual]
            5. Regulate geyser inlet water temperature
                5.1. Send inlet water temperature control parameters to inlet controller
    */
    static void ControlTheEnvironment()
    {
        // if(autoControlFlags[autoControlIndex::geyserPowerControlIndex]) geyserElementPowerAvailable = isInPowerSchedule();
        // if(autoControlFlags[autoControlIndex::chamberTempRegIndex])  controlAmbTemp(); 
        // if(autoControlFlags[autoControlIndex::geyserTempRegIndex])  controlGeyserElement();
        // if(autoControlFlags[autoControlIndex::inletTempRegIndex])  controlGeyserInletTemp();
        // controlWaterFlow();
        // capture_AC_current();
    }

    /**
        @brief  This function is responsible for controlling the power delivered 
                to the element of the geyser. This function is used to check if the geyser element is scheduled to have power, that being said, 
                whether it should respond to the set temperature reading of the water or whether it 
                should remain off.
        @returns A boolean flag indicating whether there is scheduled power availability
    */
    // bool isInPowerSchedule() 
    // {   
    //     bool geyserElementPowerAvailable = false;
    //     for(int i = 0; i < numberOfRequestedPowerSchedules; i++)
    //     {
    //         uint8_t scheduledDurationHours = geyserPowerSchedules[i].duration_ / 60;
    //         uint8_t scheduledDurationMin = geyserPowerSchedules[i].duration_ % 60;
    //         // If the current time is at the start of the "Power available" period
    //         if(geyserPowerSchedules[i].activeAlarm_ && !geyserPowerSchedules[i].running_\
    //         && geyserPowerSchedules[i].hour_ == (uint8_t)currentLoopTime.hour_\
    //         && geyserPowerSchedules[i].minute_ == (uint8_t)currentLoopTime.minute_ && !geyserPowerSchedules[i].elapsed_)
    //         {
    //         geyserPowerSchedules[i].elapsed_ = false;
    //         geyserPowerSchedules[i].running_ = true;
    //         geyserElementPowerAvailable = true;
    //         }
    //         // Else if it is in the scheduled "Power available" period
    //         else if(geyserPowerSchedules[i].running_ && !geyserPowerSchedules[i].elapsed_)
    //         {
    //         // Check if the "Power available" period has elapsed
    //         if(currentLoopTime.hour_ - geyserPowerSchedules[i].hour_ == scheduledDurationHours\
    //             && currentLoopTime.minute_ - geyserPowerSchedules[i].minute_ == scheduledDurationMin)
    //         {
    //             geyserPowerSchedules[i].elapsed_ = true;
    //             geyserPowerSchedules[i].running_ = false;
    //             geyserElementPowerAvailable = false;
    //         }
    //         }
    //     }
    //     return geyserElementPowerAvailable;
    // }
};

