#include "Metronome.h"
#include <iostream>
#include <Windows.h> // Beep関数用（Windows専用）

Metronome::Metronome(int bpm, int beats_per_measure) : bpm_(bpm), beats_per_measure_(beats_per_measure), running_(false) {
	std::cout << "Metronome created: " << bpm_ << " BPM, " << beats_per_measure_ << "/4 time" << std::endl;
}

Metronome::~Metronome() {
	stop(); // デストラクタで確実に停止
}

void Metronome::start() {
	if (running_) {
		std::cout << "Metronome is always running!" << std::endl;
		return;
	}

	running_ = true;
	std::cout << "Metronome started at " << bpm_ << " BPM" << std::endl;

	// 別スレッドでメトロノームを実行
	metronome_thread_ = std::thread(&Metronome::metronome_loop, this);
}

void Metronome::stop() {
	if (!running_) {
		return;
	}

	running_ = false;
	std::cout << "Metronome stopped" << std::endl;

	// スレッドの終了を待つ
	if (metronome_thread_.joinable()) {
		metronome_thread_.join();
	}
}

void Metronome::metronome_loop() {
	int beat_count = 0;

	// 一拍の時間を計算（ミリ秒）
	auto beat_duration = std::chrono::milliseconds(60000 / bpm_);
	auto next_beat = std::chrono::steady_clock::now();

	while (running_) {
		next_beat += beat_duration;

		//クリック音を再生
		play_click();
		beat_count++;

		// 拍数表示（一小節ごとにリセット）
		std::cout << "Beat " << (beat_count % beats_per_measure_) + 1 << "/" << beats_per_measure_ << std::endl;

		// 次の拍まで待機
		std::this_thread::sleep_until(next_beat);
	}
}

void Metronome::play_click() {
	// windows のBeep関数を使用 （簡易的なクリック音）
	Beep(800, 50); // 800Hz, 50ミリ秒
}

void Metronome::set_bpm(int bpm) {
	if (bpm > 0 && bpm <= 300) { // 妥当な範囲チェック
		bpm_ = bpm;
		std::cout << "BPM changed to: " << bpm_ << std::endl;
	}
}

void Metronome::set_beats_per_measure(int beats) {
	if (beats > 0 && beats <= 16) { // 妥当な範囲チェック
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