#include <iostream>
#include <ctime>
#include <chrono>
#include <unistd.h>
#include <stdlib.h>

int main(){

    pid_t pid[4] = {-1, -1, -1, -1};
    std::time_t births[5];
    std::time_t current_time;

    births[0] = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << "Father born at "  << std::ctime(&births[0]) << std::endl;

    sleep(14);
    
    pid[0] = fork();
    
    if(pid[0]<0){
        current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::cout << "Error creating first child process"<< std::endl;
        exit(-1);
    }

    if(pid[0] > 0){

        sleep(2);

        pid[1] = fork();

        if(pid[1]<0){
            std::cout << "Error creating second child process" << std::endl;
            exit (-1);
        }

        if(pid[1]>0){

            sleep(44);

            current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::cout << "Father was born at " << std::ctime(&births[0]) << "He died at " << std::ctime(&current_time) << "He lived for " << difftime(current_time, births[0]) << " seconds" << std::endl << std::endl;

            exit(0);
        }

        if(pid[1] == 0){

            births[2] = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::cout << "Second son born at " << std::ctime(&births[2]) << std::endl;

            sleep(14);

            pid[3] = fork();

            if(pid[3]<0){
                std::cout << "Error creating second grandson process" << std::endl;
                exit(-1);
            }

            if(pid[3]>0){

                sleep(16);

                current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                std::cout << "Second son was born at " << std::ctime(&births[2]) << "He died at " << std::ctime(&current_time) << "He lived for " << difftime(current_time, births[2]) << " seconds" << std::endl << std::endl;

                exit (0);
            }
            
            if(pid[3]==0){

                births[4] = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                std::cout << "Second grandson born at " << std::ctime(&births[4]) << std::endl;

                sleep(18);

                current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                std::cout << "Second grandson was born at "<< std::ctime(&births[4]) <<"He died at " << std::ctime(&current_time) << "He lived for " << difftime(current_time, births[4]) << " seconds" << std::endl << std::endl;

                exit (0);
            }
        }
    }
    if(pid[0] == 0){

        births[1] = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::cout << "First son born at " << std::ctime(&births[1]) << std::endl;

        sleep(12);

        pid[2] = fork();

        if(pid[2]<0){
            std::cout << "Error creating first grandson process" << std::endl;
            exit(-1);
        }

        if(pid[2]>0){

            sleep(18);

            current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::cout << "First son was born at "<< std::ctime(&births[1]) << "He died at " << std::ctime(&current_time) <<"He lived for " << difftime(current_time, births[1]) << " seconds" << std::endl << std::endl;

            exit(0);
        }

        if(pid[2]==0){

            births[3] = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::cout << "First grandson born at " << std::ctime(&births[3]) << std::endl;

            sleep(12);

            current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::cout << "First grandson was born at "<< std::ctime(&births[3]) << "He died at " << std::ctime(&current_time) << "He lived for " << difftime(current_time, births[3]) << " seconds" << std::endl << std::endl;

            exit(0);
        }
    }
}