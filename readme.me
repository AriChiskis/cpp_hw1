# Vacuum Cleaner Simulation Project

This project simulates the operation of an automated vacuum cleaner (like an iRobot) as it cleans a virtual house. The simulation mimics the behavior of a relatively simple robotic cleaner that navigates through a house, cleans dirt, and manages its battery life intelligently.

## Project Overview

### Simulation Logic

The vacuum cleaner in this simulation exhibits the following behaviors:
- **Random Navigation**: The robot moves randomly through the house but avoids walls and can recognize clean versus dirty areas.
- **Dynamic Mapping**: As it moves, the robot builds a map of the house based on its travels. This map helps in navigation, especially when returning to the docking station to recharge.
- **Energy Management**: If the robot determines that its battery is too low to continue and return safely to the docking station, it will navigate back to recharge.
- **Cleaning**: Upon encountering a dirty square, the robot will clean it thoroughly before moving on. If a square is already clean, it moves on to explore another direction.

### Simulation Output

At the end of a cleaning session, the robot generates a report detailing its activities. This report is saved in the `Output` directory. The report includes:
- **Steps History**: A sequence of all actions taken by the robot, including movements and stays.
- **Total Steps**: The count of all actions taken during the session.
- **Remaining Dirt**: The amount of dirt left in the house.
- **Battery Status**: The remaining battery percentage at the end of the session.
- **Mission Status**: Indicates whether the cleaning mission was successful (all dirt cleaned and robot returned to docking station).

#### Example of Output
Steps History:
NORTH STAY SOUTH NORTH NORTH STAY SOUTH EAST STAY STAY EAST STAY STAY STAY EAST STAY STAY STAY STAY WEST ...  ... ... ...
Total Steps: 100
Remaining Dirt: 28
Battery Status: 25
Mission Status: Failed

### Simulation Input

The robot reads its initial layout from a text file located in the `Inputs` directory. This file includes:
- **House Layout**: Represented as a grid where `W` denotes walls, numbers represent dirt levels (1 to 9), and `D` indicates the location of the docking station.
- **Max Battery**: The maximum battery capacity of the robot.
- **Max Mission Steps**: The maximum number of steps the robot can take before it must consider returning to the dock.

#### Example of House Layout and Settings

WWWWWW
W1234W
W1239W
W1234W
W1234W
WD234W
WWWWWW
Max Battery: 50
Max Mission Steps: 100


## Classes and Components

- **UML*
  - In the UML directory , we have the sketch of all the details of how the classes are acting with erach other
### Abstract Base Classes

#### IEnvironment

- **IEnvironment.hpp**
  - An abstract base class intended to provide common interface methods for various components of the project.
  - Currently empty, it serves as a foundational class for future extensibility and functionality enhancements.
  - Inherited by `IHouse`, `ISensor`, and `ICleaner`.

### Specific Implementations and Components

#### House Components

- **IHouse.hpp**
  - An abstract class derived from `IEnvironment`. It defines the interface for interacting with a house layout, such as getting the dirt level and checking for walls.
- **House.cpp / House.hpp**
  - Concrete class that implements the `IHouse` interface, managing the details of the house layout including walls, dirt levels, and the docking station.

#### Vacuum Cleaner Components

- **ICleaner.hpp**
  - An abstract class derived from `IEnvironment`, outlining the essential functionalities for a vacuum cleaner, such as moving and cleaning operations.

- **VacuumCleaner.cpp / VacuumCleaner.hpp**
  - Implements the `ICleaner` interface, encapsulating the logic for the vacuum cleaner’s movement and cleaning operations, interfacing with sensors to navigate and clean effectively.

#### Sensor Components

- **ISensor.hpp**
  - An abstract class derived from `IEnvironment` that provides a common interface for all sensors within the project, including functionalities like sensor updates and environmental checks.

- **HouseSensor.cpp / HouseSensor.hpp**
  - An abstract class inheriting from `ISensor`, providing common functionalities used by more specific sensors within the project.

- **WallSensor.cpp / WallSensor.hpp**
  - Inherits from `HouseSensor` and specializes in detecting walls to prevent collisions.

- **DirtSensor.cpp / DirtSensor.hpp**
  - Inherits from `HouseSensor`, measuring the dirt level at the vacuum cleaner’s current location.

- **BatterySensor.cpp / BatterySensor.hpp**
  - Inherits directly from `ISensor`, not `HouseSensor`, monitoring the vacuum cleaner's battery level and calculating remaining operational steps.

### Dynamic Map

- **DynamicMap.cpp / DynamicMap.hpp**
  - Manages a conceptual map that updates dynamically as the vacuum cleaner explores. It simulates the vacuum cleaner's environment with the docking station as the origin (0,0) and has no prior knowledge of the house structure.

### Cleaning Algorithm

- **CleaningAlgorithm.cpp / CleaningAlgorithm.hpp**
  - This class implements the cleaning algorithm, coordinating the vacuum cleaner's actions based on inputs from sensors and managing its navigation on the dynamic map. It encapsulates the logic necessary to simulate the vacuum cleaner’s operations as if exploring an unknown environment.


### Direction Enum

The `Direction` defining the possible movement directions for the vacuum cleaner within the house layout.
#### Overview of the Direction Enum

The `Direction` enum is defined as follows:

```cpp
enum Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST,
    STAY
};

### Building the Project

```bash
mkdir -p build
cd build
cmake ..
make
mv myrobot ../myrobot #it moves it to the main directory so it will be more comfortable to run :)


### Running the Simulation

The main executable for this project is `myrobot`, which reads an input file specifying the layout of the house and configuration settings for the vacuum cleaner.

#### How to Run

To start the simulation, navigate to the directory containing the executable and run the following command:

```bash
./myrobot Inputs/house_layout.txt
