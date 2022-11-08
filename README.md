# Philosophers @ 42KualaLumpur

In this project, you will learn the basics of threading a process. You will see how to create threads and you will discover mutexes.

<p align="center">
<img width="300" height="300" src="https://user-images.githubusercontent.com/32697686/200514831-a38f5b87-21e6-448c-b5e3-b57e0babb91c.png">
</p>

## About
The **Dining Philosophers Problem** is an example problem often used in concurrent algorithm design to illustrate synchronization issues
and techniques for resolving them. `n philosophers` seated around a circular table with one chopstick between each pair of philosophers.
A philosopher may eat if he can pick up the two chopsticks adjacent to him.
One chopstick may be picked up by any one of its adjacent followers but not both.

## Installation & Usage

### Requirements
The only requirements are:
- GNU make (v3.81)
- GCC (v4.2.1)

### Building the program

1. Download/Clone this repo

        git clone https://github.com/jasonkwm/philo42.git philo
2. `cd` into the root directory and run `make`

        cd philo
        make

### Running the program

After building the source, run `./philo 4 410 200 200` from the project root. The numeric arguments can be changed and is explained below at [Rules](https://github.com/jasonkwm/philo42/new/master?readme=1#rules) section.

![VN20221108_173951 (1)](https://user-images.githubusercontent.com/32697686/200530917-bbb0a0cf-63c6-4050-a89c-8a2b85b59fe6.gif)

## Overview
#### Logic:
- One or more philosophers sit at a round table. There is a large bowl of spaghetti in the middle of the table.
- The philosophers alternatively **eat**, **think**, or **sleep**. \
While they are eating, they are not thinking nor sleeping;\
while thinking, they are not eating nor sleeping;\
and, of course, while sleeping, they are not eating nor thinking.
- There are also forks on the table. There are **as many forks as philosophers**.
- Because serving and eating spaghetti with only one fork is very inconvenient, a philosopher takes their right and their left forks to eat, one in each hand.
- When a philosopher has finished eating, they put their forks back on the table and start sleeping.
Once awake, they start thinking again. The simulation stops when a philosopher dies of starvation.
- Every philosopher needs to eat and should never starve.
- Philosophers should avoid dying!
#### Rules:
- Global variables are forbidden!
- Your(s) program(s) should take the following arguments:
 `"number_of_philosophers" "time_to_die time_to_eat" "time_to_sleep"
"[number_of_times_each_philosopher_must_eat]"`
  - **number_of_philosophers**: The number of philosophers and also the number of forks.
  - **time_to_die** (in milliseconds): If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal
  or the beginning of the simulation, they die.
  - **time_to_eat** (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
  - **time_to_sleep** (in milliseconds): The time a philosopher will spend sleeping.
  - **number_of_times_each_philosopher_must_eat** (optional argument): If all philosophers have eaten at least *number_of_times_each_philosopher_must_eat* times,
  the simulation stops. If not specified, the simulation stops when a philosopher dies.
  - Each philosopher has a number ranging from **1** to **number_of_philosophers**.
  - Philosopher number **1** sits next to philosopher number **number_of_philosophers**.
Any other philosopher number **N** sits between philosopher number **N - 1** and philosopher number **N + 1**.

*Example:* `./philo 3 410 200 200 (2)`
#### About the logs of your program:
- Any state change of a philosopher must be formatted as follows:
  - **timestamp_in_ms X** has taken a fork
  - **timestamp_in_ms X** is eating
  - **timestamp_in_ms X** is sleeping
  - **timestamp_in_ms X** is thinking
  - **timestamp_in_ms X** died \
  
*Replace timestamp_in_ms with the current timestamp in milliseconds
and X with the philosopher number*

- A displayed state message should not be mixed up with another message.
- A message announcing a philosopher died should be displayed no more than 10 ms after the actual death of the philosopher.
- Again, philosophers should avoid dying!

#### Mandatory:
- Each philosopher should be a thread.
- There is one fork between each pair of philosophers. Therefore, if there are several philosophers, each philosopher has a fork on their left side
and a fork on their right side. If there is only one philosopher, there should be only one fork on the table.
- To prevent philosophers from duplicating forks, you should protect the forks state with a mutex for each of them.
