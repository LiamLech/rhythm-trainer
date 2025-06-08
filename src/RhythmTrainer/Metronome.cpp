#include "Metronome.h"
#include <iostream>
#include <Windows.h> // Beep�֐��p�iWindows��p�j

Metronome::Metronome(int bpm, int beats_per_measure) : bpm_(bpm), beats_per_measure_(beats_per_measure), running_(false) {
	std::cout << "Metronome created: " << bpm_ << " BPM, " << beats_per_measure_ << "/4 time" << std::endl;
}

Metronome::~Metronome() {
	stop(); // �f�X�g���N�^�Ŋm���ɒ�~
}

void Metronome::start() {
	if (running_) {
		std::cout << "Metronome is always running!" << std::endl;
		return;
	}

	running_ = true;
	std::cout << "Metronome started at " << bpm_ << " BPM" << std::endl;

	// �ʃX���b�h�Ń��g���m�[�������s
	metronome_thread_ = std::thread(&Metronome::metronome_loop, this);
}

void Metronome::stop() {
	if (!running_) {
		return;
	}

	running_ = false;
	std::cout << "Metronome stopped" << std::endl;

	// �X���b�h�̏I����҂�
	if (metronome_thread_.joinable()) {
		metronome_thread_.join();
	}
}

void Metronome::metronome_loop() {
	int beat_count = 0;

	// �ꔏ�̎��Ԃ��v�Z�i�~���b�j
	auto beat_duration = std::chrono::milliseconds(60000 / bpm_);
	auto next_beat = std::chrono::steady_clock::now();

	while (running_) {
		next_beat += beat_duration;

		//�N���b�N�����Đ�
		play_click();
		beat_count++;

		// �����\���i�ꏬ�߂��ƂɃ��Z�b�g�j
		std::cout << "Beat " << (beat_count % beats_per_measure_) + 1 << "/" << beats_per_measure_ << std::endl;

		// ���̔��܂őҋ@
		std::this_thread::sleep_until(next_beat);
	}
}

void Metronome::play_click() {
	// windows ��Beep�֐����g�p �i�ȈՓI�ȃN���b�N���j
	Beep(800, 50); // 800Hz, 50�~���b
}

void Metronome::set_bpm(int bpm) {
	if (bpm > 0 && bpm <= 300) { // �Ó��Ȕ͈̓`�F�b�N
		bpm_ = bpm;
		std::cout << "BPM changed to: " << bpm_ << std::endl;
	}
}

void Metronome::set_beats_per_measure(int beats) {
	if (beats > 0 && beats <= 16) { // �Ó��Ȕ͈̓`�F�b�N
		beats_per_measure_ = beats;
		std::cout << "Beats per measure changed to: " << beats_per_measure_ << std::endl;
	}
}

bool Metronome::is_running() const {
	return running_;
}

int Metronome::get_bpm() const {
	return bpm_;
}