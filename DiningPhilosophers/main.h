#pragma once
#include <windows.h>
#include <iostream>
#include <string>


const int NUM_PHILOSOPHERS = 5;
HANDLE forks[NUM_PHILOSOPHERS];
HANDLE philosophers[NUM_PHILOSOPHERS];
HANDLE waiter;
HANDLE outputMutex;
int eatingTimes[NUM_PHILOSOPHERS];

void print(std::string message);

void eat(int philosopherId);

void think(int philosopherId);

void pickUpFork(HANDLE fork, int philosopherId, std::string side);

void putDownFork(HANDLE fork, int philosopherId, std::string side);

void printEatingTimes();