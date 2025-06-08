#ifndef METRONOME_H
#define METRONOME_H

#include <chrono>
#include <thread>
#include <atomic>

class Metronome {
private:
	int bpm_; // tempo BPM
	int beats_per_measure_; // 拍子（一小節の拍数）
	std::atomic<bool> running_; // 実行状態
	std::thread metronome_thread_; // メトロノーム用スレッド

	void metronome_loop(); // メトロノームのメインループ
	void play_click();

public:
	Metronome(int bpm = 120, int beats_per_measure = 4);
	~Metronome();

	void start(); // 開始
	void stop(); // 停止
	void set_bpm(int bpm); //BPM設定
	void set_beats_per_measure(int beats); // 拍子設定

	bool is_running() const; // 実行状態取得
	int get_bpm() const;
};

#endif // METRONOME_H