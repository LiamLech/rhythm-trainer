#ifndef METRONOME_H
#define METRONOME_H

#include <chrono>
#include <thread>
#include <atomic>

class Metronome {
private:
	int bpm_; // tempo BPM
	int beats_per_measure_; // ���q�i�ꏬ�߂̔����j
	std::atomic<bool> running_; // ���s���
	std::thread metronome_thread_; // ���g���m�[���p�X���b�h

	void metronome_loop(); // ���g���m�[���̃��C�����[�v
	void play_click();

public:
	Metronome(int bpm = 120, int beats_per_measure = 4);
	~Metronome();

	void start(); // �J�n
	void stop(); // ��~
	void set_bpm(int bpm); //BPM�ݒ�
	void set_beats_per_measure(int beats); // ���q�ݒ�

	bool is_running() const; // ���s��Ԏ擾
	int get_bpm() const;
};

#endif // METRONOME_H