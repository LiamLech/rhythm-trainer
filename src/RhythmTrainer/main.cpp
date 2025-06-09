#include <iostream>
#include <thread>
#include <chrono>
#include <limits>
#include "Metronome.h"

// ���͒l�����؂���֐�
int getValidInput(const std::string& prompt, int min, int max) {
	int value;
	while (true) {
		std::cout << prompt;
		std::cin >> value;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "�����ȓ��͂ł��B���l����͂��Ă��������B\n";
		}
		else if (value < min || value > max) {
			std::cout << "�l��" << min << " ���� " << max << " �̊Ԃœ��͂��Ă��������B\n";
		}
		else {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return value;
		}
	}
}

// ���ꂪ�L�����`�F�b�N
int getValidDenominator() {
	int denom;
	while (true) {
		std::cout << "���q�L������͂��Ă��������i���� - 2, 4, 8, 16�̂����ꂩ�j�F";
		std::cin >> denom;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "�����ȓ��͂ł��B���l����͂��Ă�������\n";
		}
		else if (denom == 2 || denom == 4 || denom == 8 || denom == 16) {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return denom;
		}
		else {
			std::cout << "����� 2, 4, 8, 16�̂����ꂩ����͂��Ă��������B\n";
		}
	}
}

int main() {
	std::cout << "=== ���Y���g���[�i�[ ===\n\n";

	// ���[�U�[����̓��͂��擾
	int bpm = getValidInput("BPM����͂��Ă��������i60-200�j�F", 60, 200);
	int numerator = getValidInput("���q�L������͂��Ă��������i���q 1-12�j�F", 1, 12);
	int denominator = getValidDenominator();
	int duration = getValidInput("�Đ����Ԃ���͂��Ă��������i�b 0-�����j�F", 0, 300);

	//// �f�o�b�O: ���͒l�̊m�F
	//std::cout << "\n=== �f�o�b�O��� ===\n";
	//std::cout << "���͂��ꂽBPM: " << bpm << "\n";
	//std::cout << "���͂��ꂽ���q: " << numerator << "\n";
	//std::cout << "���͂��ꂽ����: " << denominator << "\n";
	//std::cout << "==================\n\n";

	// ���g���m�[�����쐬�E�J�n
	Metronome metronome(bpm, numerator, denominator);

	std::cout << "\n�ݒ芮���I\n";
	std::cout << "BPM: " << metronome.getBPM() << "\n";
	std::cout << "���q: " << metronome.getNumerator() << "/" << metronome.getDenominator() << "\n";
	std::cout << "�Đ�����: " << duration << "�b\n\n";

	metronome.start();

	// �w�莞�Ԃ������s 
	if (duration == 0) {
		std::cout << "�����Đ����[�h�B�����L�[�������ƒ�~���܂��c�c\n";
		std::cin.get();
	}
	else {
		std::this_thread::sleep_for(std::chrono::seconds(duration));
	}

	metronome.stop();

	std::cout << "\n�Đ������I�����l�ł����B\n";
	std::cout << "�����L�[�������ďI���c�c";
	std::cin.get();

	return 0;
}

// Email privacy test 
