#ifndef METRONOME_H
#define METRONOME_H

#pragma once

#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>

class Metronome {
private:
	//int bpm_; // tempo BPM
	//int beats_per_measure_; // 拍子（一小節の拍数）
	//std::atomic<bool> running_; // 実行状態
	//std::thread metronome_thread_; // メトロノーム用スレッド

	//void metronome_loop(); // メトロノームのメインループ
	//void play_click();

	int bpm;
	int numerator; // 拍子記号の分子
	int denominator; // 拍子記号の分母
	std::atomic<bool> running;
	std::thread metronomeThread;
	std::mutex mtx;
	int currentBeat; // 現在の拍

	void metronomeLoop();
	void playSound(bool isAccent = false);

public:
	//Metronome(int bpm = 120, int beats_per_measure = 4);
	//~Metronome();

	//void start(); // 開始
	//void stop(); // 停止
	//void set_bpm(int bpm); //BPM設定
	//void set_beats_per_measure(int beats); // 拍子設定

	//bool is_running() const; // 実行状態取得
	//int get_bpm() const;

	Metronome(int bpm = 120, int numValue = 4, int denomValue = 4);
	~Metronome();

	void start();
	void stop();
	bool isRunning() const;

	// 新しいゲッター
	int getBPM() const { return bpm; }
	int getNumerator() const { return numerator; }
	int getDenominator() const { return denominator; }
	int getCurrentBeat() const { return currentBeat; }

	// 新しいセッター
	void setBPM(int newBPM);
	void setTimeSignature(int numValue, int denomValue);
};

#endif // METRONOME_H