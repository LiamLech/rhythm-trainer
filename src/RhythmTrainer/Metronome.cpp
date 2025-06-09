#include "Metronome.h"
#include <iostream>
#include <Windows.h> // Beep�֐��p�iWindows��p�j

Metronome::Metronome(int bpmValue, int numValue, int denomValue) : bpm(bpmValue), numerator(numValue), denominator(denomValue), running(false), currentBeat(0) {
	/*std::cout << "=== �R���X�g���N�^�ڍ׃f�o�b�O ===\n";
	std::cout << "���� bpm: " << bpm << "\n";
	std::cout << "���� numValue: " << numValue << "\n";
	std::cout << "���� denomValue: " << denomValue << "\n";
	std::cout << "�����o this->bpm: " << this->bpm << "\n";
	std::cout << "�����o this->numerator: " << this->numerator << "\n";
	std::cout << "�����o this->denominator: " << this->denominator << "\n";
	std::cout << "=================================\n";*/
}

Metronome::~Metronome() {
	stop();
}

void Metronome::start() {
	if (running.load()) {
		return; // ���Ɏ��s��
	}

	running.store(true);
	currentBeat = 0;
	metronomeThread = std::thread(&Metronome::metronomeLoop, this);
	std::cout << "���g���m�[���J�n�F " << bpm << " BPM, " << numerator << "/" << denominator << "���q\n";
}

void Metronome::stop() {
	if (!running.load()) {
		return; // ���łɒ�~��
	}

	running.store(false);
	if (metronomeThread.joinable()) {
		metronomeThread.join();
	}
	std::cout << "���g���m�[����~\n";
}

bool Metronome::isRunning() const {
	return running.load();
}

// �Q�b�^�[�֐��̎����i�f�o�b�O�t���j
//int Metronome::getBPM() const {
//	std::cout << "[DEBUG] getBPM() = " << bpm << "\n";
//	return bpm;
//}
//
//int Metronome::getNumerator() const {
//	std::cout << "[DEBUG] getNumerator() = " << numerator << "\n";
//	return numerator;
//}
//
//int Metronome::getDenominator() const {
//	std::cout << "[DEBUG] getDenominator() = " << denominator << "\n";
//	return denominator;
//}

void Metronome::setBPM(int newBPM) {
	std::lock_guard<std::mutex> lock(mtx);
	if (newBPM >= 60 && newBPM <= 200) {
		bpm = newBPM;
		std::cout << "BPM�ύX" << bpm << "\n";
	}
}

void Metronome::setTimeSignature(int numValue, int denomValue) {
	std::lock_guard<std::mutex> lock(mtx);
	if (numValue > 0 && (denomValue == 2 || denomValue == 4 || denomValue == 8 || denomValue == 16)) {
		numerator = numValue;
		denominator = denomValue;
		currentBeat = 0;
		std::cout << "���q�ύX�F " << numerator << "/" << denominator << "\n";
	}
}

void Metronome::metronomeLoop() {
	while (running.load()) {
		// �X���b�h�Z�[�t�Ȓl�̎擾
		int currentBPM = 120; // �f�t�H���g�l�ŏ�����
		int currentNum = 4; // �f�t�H���g�l�ŏ�����
		int currentDenom =4; // �f�t�H���g�l�ŏ�����
		{
			std::lock_guard<std::mutex> lock(mtx);
			int currentBPM = bpm;
			int currentNum = numerator;
			int currentDenom = denominator;
		}

		// ��ʋ�̎��Ԃ��v�Z�i�~���b�j
		// denominator=4�Ȃ�4�������Adenominator=8�Ȃ甪�������
		double beatDuration = (60.0 / currentBPM) * (4.0 / currentDenom) * 1000.0;

		currentBeat = (currentBeat % currentNum) + 1;

		// �ꔏ�ڂ͋����i�A�N�Z���g�j
		bool isAccent = (currentBeat == 1);
		playSound(isAccent);

		// ��ʂɌ��݂̔���\��
		std::cout << "[" << currentBeat << "]";
		if (currentBeat == currentNum) {
			std::cout << "\n"; // ���߂̏I���ŉ��s
		}
		else {
			std::cout << " ";
		}
		std::cout.flush();

		// ���̔��܂őҋ@
		auto sleepDuration = std::chrono::milliseconds(static_cast<int>(beatDuration));
		std::this_thread::sleep_for(sleepDuration);
	}

}

void Metronome::playSound(bool isAccent) {
	if (isAccent) {
		// �����F�������Œ���
		Beep(1000, 100);
	}
	else {
		Beep(600, 50);
	}
}


//void Metronome::play_click() {
//	// windows ��Beep�֐����g�p �i�ȈՓI�ȃN���b�N���j
//	Beep(800, 50); // 800Hz, 50�~���b
//}
//
//void Metronome::set_bpm(int bpm) {
//	if (bpm > 0 && bpm <= 300) { // �Ó��Ȕ͈̓`�F�b�N
//		bpm_ = bpm;
//		std::cout << "BPM changed to: " << bpm_ << std::endl;
//	}
//}
//
//void Metronome::set_beats_per_measure(int beats) {
//	if (beats > 0 && beats <= 16) { // �Ó��Ȕ͈̓`�F�b�N
//		beats_per_measure_ = beats;
//		std::cout << "Beats per measure changed to: " << beats_per_measure_ << std::endl;
//	}
//}
//
//bool Metronome::is_running() const {
//	return running_;
//}
//
//int Metronome::get_bpm() const {
//	return bpm_;
//}