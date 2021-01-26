#include <iostream>
#include <ctime>
#include <chrono>
#include <unistd.h>

int main(){

    /**
     * 0 - primeiro filho
     * 1 - segundo filho
     * 2 - primeiro neto
     * 3 - segundo neto
     */
    pid_t pid[4] = {-1, -1, -1, -1};
    std::time_t time_time;

    time_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << "father was born at "  << std::ctime(&time_time) << std::endl;

    sleep(14); // pai tem 14 anos, entao tem o primeiro filho
    
    pid[0] = fork(); // pai tendo o primeiro filho
    
    if(pid[0]<0){
        time_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::cout << "error creating first child process"<< std::endl;
        return 1;
    }

    if(pid[0] > 0){ /* if it is the father */

        sleep(2); // pai tem 14+2=16 anos, entao tem o segundo filho

        pid[1] = fork(); // pai tendo o segundo filho

        if(pid[1]<0){
            std::cout << "error creating second child process" << std::endl;
            return 1;
        }

        if(pid[1]>0){ /* if it is the father */

            sleep(44); // o pai tem 14+2+44=60 anos entao morre

            time_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::cout << "father died at " << std::ctime(&time_time) << std::endl;

            return 0;
        }

        if(pid[1] == 0){ /* if it is the second son */

            time_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::cout << "second son was born at " << std::ctime(&time_time) << std::endl;

            sleep(14); // o pai tem 14+2+14=30 anos, entao tem o segundo neto. o segundo filho tem 14 anos

            pid[3] = fork(); // pai tendo segundo neto

            if(pid[3]<0){
                std::cout << "error creating second grandson process" << std::endl;
                return 1;
            }

            if(pid[3]>0){ /* if it is the second son */

                sleep(16); // o segundo filho tem 14+16=30 anos, entao morre

                time_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                std::cout << "second son died at " << std::ctime(&time_time) << std::endl;

                return 0;
            }
            if(pid[3]==0){ /* if it is the second grandson */

                time_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                std::cout << "second grandson was born at " << std::ctime(&time_time) << std::endl;

                sleep(18); // o segundo neto tem 18 anos, entao morre

                time_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                std::cout << "second grandson died at " << std::ctime(&time_time) << std::endl;

                return 0;
            }
        }
    }
    if(pid[0] == 0){ /* if it is the first son */

        time_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::cout << "first son was born at " << std::ctime(&time_time) << std::endl;

        sleep(12); // o pai tem 14+12=26 anos, entao tem o primeiro neto. o primeiro filho tem 12 anos

        pid[2] = fork(); // pai tendo primeiro neto

        if(pid[2]<0){
            std::cout << "error creating first grandson process" << std::endl;
        }

        if(pid[2]>0){ /* if it is the first son */

            sleep(18); // o segundo filho tem 12+18=30 anos, entao morre

            time_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::cout << "first son died at " << std::ctime(&time_time) << std::endl;

            return 0;
        }
        if(pid[2]==0){ /* if it is the first grandson */

            time_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::cout << "first grandson was born at " << std::ctime(&time_time) << std::endl;

            sleep(12); // o primeiro neto tem 12 anos, entao morre

            time_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::cout << "first grandson died at " << std::ctime(&time_time) << std::endl;

            return 0;
        }
    }
    return 0;
}