#include <iostream>
#include <thread>
#include <chrono>
#include "Metronome.h"

int main() {
	std::cout << "=== Rhythm Trainer - Basic Metronome Test ===" << std::endl;

	// ���g���m�[���쐬�i120 BPM�A4���q�j
	Metronome metronome(120, 4);

	// �J�n
	metronome.start();

	// 5�b�Ԏ��s
	std::this_thread::sleep_for(std::chrono::seconds(5));

	// ��~
	metronome.stop();

	std::cout << "Test completed. Press Enter to exit..." << std::endl;
	std::cin.get();
	return 0;
}

// Email privacy test 
