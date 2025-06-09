#include "Metronome.h"
#include <iostream>
#include <Windows.h> // Beep関数用（Windows専用）

Metronome::Metronome(int bpmValue, int numValue, int denomValue) : bpm(bpmValue), numerator(numValue), denominator(denomValue), running(false), currentBeat(0) {
	/*std::cout << "=== コンストラクタ詳細デバッグ ===\n";
	std::cout << "引数 bpm: " << bpm << "\n";
	std::cout << "引数 numValue: " << numValue << "\n";
	std::cout << "引数 denomValue: " << denomValue << "\n";
	std::cout << "メンバ this->bpm: " << this->bpm << "\n";
	std::cout << "メンバ this->numerator: " << this->numerator << "\n";
	std::cout << "メンバ this->denominator: " << this->denominator << "\n";
	std::cout << "=================================\n";*/
}

Metronome::~Metronome() {
	stop();
}

void Metronome::start() {
	if (running.load()) {
		return; // 既に実行中
	}

	running.store(true);
	currentBeat = 0;
	metronomeThread = std::thread(&Metronome::metronomeLoop, this);
	std::cout << "メトロノーム開始： " << bpm << " BPM, " << numerator << "/" << denominator << "拍子\n";
}

void Metronome::stop() {
	if (!running.load()) {
		return; // すでに停止中
	}

	running.store(false);
	if (metronomeThread.joinable()) {
		metronomeThread.join();
	}
	std::cout << "メトロノーム停止\n";
}

bool Metronome::isRunning() const {
	return running.load();
}

// ゲッター関数の実装（デバッグ付き）
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
		std::cout << "BPM変更" << bpm << "\n";
	}
}

void Metronome::setTimeSignature(int numValue, int denomValue) {
	std::lock_guard<std::mutex> lock(mtx);
	if (numValue > 0 && (denomValue == 2 || denomValue == 4 || denomValue == 8 || denomValue == 16)) {
		numerator = numValue;
		denominator = denomValue;
		currentBeat = 0;
		std::cout << "拍子変更： " << numerator << "/" << denominator << "\n";
	}
}

void Metronome::metronomeLoop() {
	while (running.load()) {
		// スレッドセーフな値の取得
		int currentBPM = 120; // デフォルト値で初期化
		int currentNum = 4; // デフォルト値で初期化
		int currentDenom =4; // デフォルト値で初期化
		{
			std::lock_guard<std::mutex> lock(mtx);
			int currentBPM = bpm;
			int currentNum = numerator;
			int currentDenom = denominator;
		}

		// 一般区の時間を計算（ミリ秒）
		// denominator=4なら4分音符、denominator=8なら八分音符基準
		double beatDuration = (60.0 / currentBPM) * (4.0 / currentDenom) * 1000.0;

		currentBeat = (currentBeat % currentNum) + 1;

		// 一拍目は強拍（アクセント）
		bool isAccent = (currentBeat == 1);
		playSound(isAccent);

		// 画面に現在の拍を表示
		std::cout << "[" << currentBeat << "]";
		if (currentBeat == currentNum) {
			std::cout << "\n"; // 小節の終わりで改行
		}
		else {
			std::cout << " ";
		}
		std::cout.flush();

		// 次の拍まで待機
		auto sleepDuration = std::chrono::milliseconds(static_cast<int>(beatDuration));
		std::this_thread::sleep_for(sleepDuration);
	}

}

void Metronome::playSound(bool isAccent) {
	if (isAccent) {
		// 強拍：高い音で眺め
		Beep(1000, 100);
	}
	else {
		Beep(600, 50);
	}
}


//void Metronome::play_click() {
//	// windows のBeep関数を使用 （簡易的なクリック音）
//	Beep(800, 50); // 800Hz, 50ミリ秒
//}
//
//void Metronome::set_bpm(int bpm) {
//	if (bpm > 0 && bpm <= 300) { // 妥当な範囲チェック
//		bpm_ = bpm;
//		std::cout << "BPM changed to: " << bpm_ << std::endl;
//	}
//}
//
//void Metronome::set_beats_per_measure(int beats) {
//	if (beats > 0 && beats <= 16) { // 妥当な範囲チェック
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