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
	//int beats_per_measure_; // ���q�i�ꏬ�߂̔����j
	//std::atomic<bool> running_; // ���s���
	//std::thread metronome_thread_; // ���g���m�[���p�X���b�h

	//void metronome_loop(); // ���g���m�[���̃��C�����[�v
	//void play_click();

	int bpm;
	int numerator; // ���q�L���̕��q
	int denominator; // ���q�L���̕���
	std::atomic<bool> running;
	std::thread metronomeThread;
	std::mutex mtx;
	int currentBeat; // ���݂̔�

	void metronomeLoop();
	void playSound(bool isAccent = false);

public:
	//Metronome(int bpm = 120, int beats_per_measure = 4);
	//~Metronome();

	//void start(); // �J�n
	//void stop(); // ��~
	//void set_bpm(int bpm); //BPM�ݒ�
	//void set_beats_per_measure(int beats); // ���q�ݒ�

	//bool is_running() const; // ���s��Ԏ擾
	//int get_bpm() const;

	Metronome(int bpm = 120, int numValue = 4, int denomValue = 4);
	~Metronome();

	void start();
	void stop();
	bool isRunning() const;

	// �V�����Q�b�^�[
	int getBPM() const { return bpm; }
	int getNumerator() const { return numerator; }
	int getDenominator() const { return denominator; }
	int getCurrentBeat() const { return currentBeat; }

	// �V�����Z�b�^�[
	void setBPM(int newBPM);
	void setTimeSignature(int numValue, int denomValue);
};

#endif // METRONOME_H