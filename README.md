# Geyser Test Station

Software and firmware for an instrumented test bench for domestic electric water heaters — *geysers*, in South African English. The station runs controlled experiments on a full-size storage geyser: it regulates the thermal environment around the tank, feeds it inlet water at a chosen temperature and flow rate, switches element power on schedules that mimic real household usage, and logs a detailed picture of what the tank does in response — including the internal water temperature profile measured by 66 sensors inside the tank.

## System overview

```
  Windows PC
  ┌───────────────────────────────────────────────┐
  │  Control UI (WinForms)  ·  geyserTestStationAPI  │
  └───────────────┬───────────────────────────────┘
                  │ USB serial, 115200 baud
                  ▼
  ┌───────────────────────────────┐    Serial1     ┌─────────────────────────────┐
  │  DAQ controller (Arduino Due) │◄──────────────►│  Inlet water controller     │
  │  Geyser_Data_Acquisition_     │                │  (Nano 33 IoT)              │
  │  Controller                   │                │  InletWaterControl          │
  └───────────────────────────────┘                └─────────────────────────────┘
   measures: tank temperature profile,              regulates inlet water temperature
   power, flow, chamber & ambient temps             via a freezer, a heated buffer tank,
   controls: chamber climate, element power,        and a servo-driven mixing valve
   outlet valve, water-draw & power schedules
   logs to: SD card (CSV) + serial stream
```

Two microcontrollers do the real-time work; the PC side is a thin control and monitoring layer that talks to the Due over a simple line-based serial protocol.

## Components

### `Geyser_Data_Acquisition_Controller/` — main DAQ and control firmware (Arduino Due, PlatformIO)

The heart of the station. Responsibilities:

- **Measurement** — DS18B20 temperature sensors on 8 OneWire buses (6–9 sensors each) profile the water temperature inside the tank, plus sensors for the geyser surface, chamber, lab ambient, and inlet/outlet water. An ADS1115 samples element current and voltage for true AC power measurement; hall-effect and municipal flow meters measure water draw; an NTC thermistor reads the thermostat pocket.
- **Environment control** — bang-bang/PID control of the test chamber air temperature using heating fans, circulation fans, and venting, so the geyser can be tested at a chosen ambient temperature.
- **Experiment execution** — schedules (up to 10 alarms each) for water-draw events and element power availability, emulating household usage patterns and load shedding. An electric ball valve actuates outlet draws; latching relays switch element power.
- **Logging** — samples all channels on a configurable period (default 5 s), timestamps via DS3231 RTC, writes CSV to SD card, and streams the same rows to the PC. `dataCollection.json` documents the intended JSON shape of a data record.
- **Safety** — emergency-stop interrupt that shuts down all actuators.

Build and flash with [PlatformIO](https://platformio.org/): `pio run -t upload` from the project directory. An SSD1306/SH1106 OLED shows live status.

### `InletWaterControl/` — inlet water conditioning firmware (Arduino Nano 33 IoT, PlatformIO)

Slave controller that delivers inlet water at a requested temperature. It blends cold water (chilled in a freezer coil) and warm water (from a small heated buffer tank) with a servo-driven mixing valve, closing the loop on an inline DS18B20. Setpoints arrive from the Due over Serial1 or from a PC over USB; a rotary encoder and OLED provide a small on-device menu. WiFi/MQTT reporting is scaffolded via WiFiNINA (credentials go in `src/wifiDetails.h` — placeholders are committed, fill in your own).

### `geyserTestStationAPI/` — C# class library (.NET Framework)

Thin PC-side API over the serial protocol: opens the COM port and exposes typed `Get*`/`Set*` methods (flow rate, power usage, bus temperature vectors, valve angles, experiment parameters, element power availability, …). Referenced by both PC front-ends below.

### `Geyser DAQ Control User Interface/` — WinForms control panel

Desktop UI for running the station interactively: connect/disconnect the serial port, start/stop/reset the system, set sampling time and temperature/flow setpoints, enter water and power schedules, and watch the live data stream.

### `InterfaceScript/` — C# console scratchpad

Minimal console program that imports `geyserTestStationAPI` for scripted or ad-hoc interaction with the station — handy for testing single commands without the UI.

## Serial protocol

All PC↔Due communication is newline-terminated ASCII at 115200 baud. Commands are colon-delimited:

```
get:<index>              e.g. get:0  → flow rate,  get:2 → lab temperature
set:<index>:<args>       e.g. set:0:<direction>:<step> → step the outlet valve
gr:<index>:<value>       response to a get
```

The command indices are defined in `GetCommandsIndex`/`SetCommandsIndex` on each side (see `GeyserDaqController.h` and `geyserInterfaceLibrary.cs`; note the two `SetCommandsIndex` enums have drifted apart and don't agree past index 0). The Due forwards inlet-related commands to the Nano over Serial1 using the same scheme.

## Repository layout

| Directory | What it is |
|---|---|
| `Geyser_Data_Acquisition_Controller/` | Main DAQ/control firmware (Arduino Due) |
| `InletWaterControl/` | Inlet water temperature conditioning firmware (Nano 33 IoT) |
| `geyserTestStationAPI/` | C# serial API library used by the PC tools |
| `Geyser DAQ Control User Interface/` | WinForms control panel |
| `InterfaceScript/` | Console test harness for the API library |

## Publications

The test station and the data it produced underpin these peer-reviewed papers:

- van Schalkwyk, P. D., Engelbrecht, J. A. A., & Booysen, M. J. (2022). *Thermal stratification and temperature variation in horizontal electric water heaters: A characterisation platform*. **Energies**, 15(8), 2840. [doi:10.3390/en15082840](https://doi.org/10.3390/en15082840) — describes this test bench itself.
- van Schalkwyk, P. D., Engelbrecht, J. A. A., & Booysen, M. J. (2024). *Dataset for the characterisation of thermal stratification in horizontally configured electric water heaters*. **Data in Brief**, 53, 110082. [doi:10.1016/j.dib.2024.110082](https://doi.org/10.1016/j.dib.2024.110082) — the published measurement dataset captured with this station.
- van Schalkwyk, P. D., Engelbrecht, J. A. A., Meyer, J. P., & Booysen, M. J. (2024). *A state-space heating and cooling model for thermal stratification in horizontally configured electric hot water storage cylinders*. **Applied Thermal Engineering**, 245, 122851. [doi:10.1016/j.applthermaleng.2024.122851](https://doi.org/10.1016/j.applthermaleng.2024.122851)
- van Schalkwyk, P. D., Meyer, J. P., Engelbrecht, J. A. A., & Booysen, M. J. (2025). *Numerical modelling of thermal stratification scenarios in horizontal electric hot water storage tanks*. **Applied Thermal Engineering**, 258, 124716. [doi:10.1016/j.applthermaleng.2024.124716](https://doi.org/10.1016/j.applthermaleng.2024.124716)

## Related repositories

- [Hot-Water-Storage-Tank-Simulator](https://github.com/daniel-van-schalkwyk/Hot-Water-Storage-Tank-Simulator) — simulation counterpart to the physical bench
- [InletWaterControl](https://github.com/daniel-van-schalkwyk/InletWaterControl) — public standalone copy of the inlet controller firmware
