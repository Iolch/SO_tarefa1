#include <iostream>
#include <ctime>
#include <chrono>
#include <unistd.h>
#include <stdlib.h>

int main(){

    /**
     * 0 - primeiro filho
     * 1 - segundo filho
     * 2 - primeiro neto
     * 3 - segundo neto
     */
    pid_t pid[4] = {-1, -1, -1, -1};
    std::time_t births[5];
    std::time_t current_time;

    births[0] = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << "Father was born at "  << std::ctime(&births[0]) << std::endl;

    sleep(14); // pai tem 14 anos, entao tem o primeiro filho
    
    pid[0] = fork(); // pai tendo o primeiro filho
    
    if(pid[0]<0){
        current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::cout << "error creating first child process"<< std::endl;
        exit (-1);
    }

    if(pid[0] > 0){ /* if it is the father */

        sleep(2); // pai tem 14+2=16 anos, entao tem o segundo filho

        pid[1] = fork(); // pai tendo o segundo filho

        if(pid[1]<0){
            std::cout << "error creating second child process" << std::endl;
            exit (-1);
        }

        if(pid[1]>0){ /* if it is the father */

            sleep(44); // o pai tem 14+2+44=60 anos entao morre

            current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::cout << "Father was born at " << std::ctime(&births[0]) <<"and died at " << std::ctime(&current_time) << "They lived for " << difftime(current_time, births[0]) << " seconds."<< std::endl << std::endl;

            exit (0);
        }

        if(pid[1] == 0){ /* if it is the second son */

            births[2] = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::cout << "Second son was born at " << std::ctime(&births[2]) << std::endl;

            sleep(14); // o pai tem 14+2+14=30 anos, entao tem o segundo neto. o segundo filho tem 14 anos

            pid[3] = fork(); // pai tendo segundo neto

            if(pid[3]<0){
                std::cout << "error creating second grandson process" << std::endl;
                exit (-1);
            }

            if(pid[3]>0){ /* if it is the second son */

                sleep(16); // o segundo filho tem 14+16=30 anos, entao morre

                current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                std::cout << "Second son was born at " << std::ctime(&births[2]) << "and died at " << std::ctime(&current_time) << "They lived for " << difftime(current_time, births[2]) << " seconds."<< std::endl << std::endl;
                exit (0);
            }
            if(pid[3]==0){ /* if it is the second grandson */

                births[4] = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                std::cout << "Second grandson was born at " << std::ctime(&births[4]) << std::endl;

                sleep(18); // o segundo neto tem 18 anos, entao morre

                current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                std::cout << "Second grandson was born at "<< std::ctime(&births[4]) <<"and died at " << std::ctime(&current_time) << "They lived for " << difftime(current_time, births[4]) << " seconds."<< std::endl << std::endl;

                exit (0);
            }
        }
    }
    if(pid[0] == 0){ /* if it is the first son */

        births[1] = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::cout << "First son was born at " << std::ctime(&births[1]) << std::endl;

        sleep(12); // o pai tem 14+12=26 anos, entao tem o primeiro neto. o primeiro filho tem 12 anos

        pid[2] = fork(); // pai tendo primeiro neto

        if(pid[2]<0){
            std::cout << "error creating first grandson process" << std::endl;
        }

        if(pid[2]>0){ /* if it is the first son */

            sleep(18); // o segundo filho tem 12+18=30 anos, entao morre

            current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::cout << "First son was born at "<< std::ctime(&births[1]) << "and died at " << std::ctime(&current_time) <<"They lived for " << difftime(current_time, births[1]) << " seconds."<< std::endl << std::endl;

            exit (0);
        }
        if(pid[2]==0){ /* if it is the first grandson */

            births[3] = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::cout << "First grandson was born at " << std::ctime(&births[3]) << std::endl;

            sleep(12); // o primeiro neto tem 12 anos, entao morre

            current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::cout << "First grandson was born at "<< std::ctime(&births[3]) << "and died at " << std::ctime(&current_time) << "They lived for " << difftime(current_time, births[3]) << " seconds."<< std::endl << std::endl;


            exit (0);
        }
    }
}