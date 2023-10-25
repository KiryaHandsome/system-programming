#include "main.h"




DWORD WINAPI PhilosopherThread(LPVOID param) {
	int philosopherId = (int)param;
	int leftFork = philosopherId;
	int rightFork = (philosopherId + 1) % NUM_PHILOSOPHERS;

	if (philosopherId + 1 == NUM_PHILOSOPHERS) {
		int tmp = leftFork;
		leftFork = rightFork;
		rightFork = tmp;
	}

	while (true) {
		think(philosopherId);

		pickUpFork(forks[rightFork], philosopherId, "right");
		pickUpFork(forks[leftFork], philosopherId, "left");

		eat(philosopherId);

		putDownFork(forks[leftFork], philosopherId, "left");
		putDownFork(forks[rightFork], philosopherId, "right");
	}

	return 0;
}

int main() {
	outputMutex = CreateMutex(NULL, FALSE, NULL);
	for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
		forks[i] = CreateMutex(NULL, FALSE, NULL);
		philosophers[i] = CreateThread(NULL, 0, PhilosopherThread, (LPVOID)i, 0, NULL);
	}

	WaitForMultipleObjects(NUM_PHILOSOPHERS, philosophers, TRUE, 3000);

	for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
		CloseHandle(forks[i]);
		CloseHandle(philosophers[i]);
	}

	printEatingTimes();

	return 0;
}

void print(std::string message)
{
	WaitForSingleObject(outputMutex, INFINITE);
	std::cout << message << "\n";
	ReleaseMutex(outputMutex);
}

void eat(int philosopherId)
{
	print("Philosopher #" + std::to_string(philosopherId) + " is eating...");
	Sleep(300);
	eatingTimes[philosopherId]++;
}

void think(int philosopherId)
{
	print("Philosopher #" + std::to_string(philosopherId) + " is thinking...");
	Sleep(300);
}

void pickUpFork(HANDLE fork, int philosopherId, std::string side)
{
	WaitForSingleObject(fork, INFINITE);
	print("Philosopher #" + std::to_string(philosopherId) + " picked up " + side + " fork.");
}

void putDownFork(HANDLE fork, int philosopherId, std::string side)
{
	ReleaseMutex(fork);
	print("Philosopher #" + std::to_string(philosopherId) + " put down " + side + " fork.");
}

void printEatingTimes()
{
	std::string message = "Eating times: ";
	for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
		message += std::to_string(eatingTimes[i]) + " ";
	}
	print(message);
}
