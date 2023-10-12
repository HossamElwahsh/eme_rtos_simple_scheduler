# Simple time based OS scheduler
### EUI / EME - SEITech Solutions - Class 3
### RTOS
#### Author: Hossam Elwahsh (1055)

## Brief
> This project aims to deliver an SOS (Simple Operating System Scheduler) which will manage the scheduling of some tasks. 
> 
> The project will resemble RTOS non-preemptive tasks with priorities.
> 
> For the delivery, it will be tested on 3 LEDs which will toggle at different periods.
> 
> - 🔴 RED LED 1: every 1 second 
> - 🟡 YELLOW LED: every 2 seconds
> - 🔴 RED LED 2: every 5 seconds


## Quick Links
> - `Showcase Video`
    >     👉 [Youtube](https://youtu.be/LMloCQ683_k)
> - ---
> ### Technical
> - `IDE1` 👉 `STM32Cube 1.4.0`
> - `IDE2` 👉 `CLION 2023.2`
> - `Board` 👉 `Panda Rev1 - STM32F103C8T6`

### Important Files

```
project_root:.
│   README.md
│
├───cmake-build-debug
│   └───<cmake debug files...>
│
├───Core
│   ├───Inc                         // header files
│   │       main.h                  // main header     
│   │       sos_interface.h         // sos prototypes
│   │       sos_private.h           // sos private types & configs
│   │       sos_tasks_interface.h   // sos tasks prototypes
│   │       sos_tasks_private.h     // sos tasks private types & configs
│   │       std.h                   // standard header file
│   │
│   ├───Src                     // .c files
│   │       main.c              // main program
│   │       sos_program.c       // sos implementation
│   │       sos_tasks_program.c // sos tasks functions
│   │       stm32f1xx_it.c      // updates systick_handler to notify sos with tick events
│   │
│
├───Debug
│   └───<STM32 Debug Files...>



```