#include <iostream>
#include <thread>
#include <chrono>
#include "Metronome.h"

int main() {
	std::cout << "=== Rhythm Trainer - Basic Metronome Test ===" << std::endl;

	// メトロノーム作成（120 BPM、4拍子）
	Metronome metronome(120, 4);

	// 開始
	metronome.start();

	// 5秒間実行
	std::this_thread::sleep_for(std::chrono::seconds(5));

	// 停止
	metronome.stop();

	std::cout << "Test completed. Press Enter to exit..." << std::endl;
	std::cin.get();
	return 0;
}

// Email privacy test 
