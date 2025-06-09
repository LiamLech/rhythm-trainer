#include <iostream>
#include <thread>
#include <chrono>
#include <limits>
#include "Metronome.h"

// 入力値を検証する関数
int getValidInput(const std::string& prompt, int min, int max) {
	int value;
	while (true) {
		std::cout << prompt;
		std::cin >> value;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "無効な入力です。数値を入力してください。\n";
		}
		else if (value < min || value > max) {
			std::cout << "値は" << min << " から " << max << " の間で入力してください。\n";
		}
		else {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return value;
		}
	}
}

// 分母が有効かチェック
int getValidDenominator() {
	int denom;
	while (true) {
		std::cout << "拍子記号を入力してください（分母 - 2, 4, 8, 16のいずれか）：";
		std::cin >> denom;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "無効な入力です。数値を入力してください\n";
		}
		else if (denom == 2 || denom == 4 || denom == 8 || denom == 16) {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return denom;
		}
		else {
			std::cout << "分母は 2, 4, 8, 16のいずれかを入力してください。\n";
		}
	}
}

int main() {
	std::cout << "=== リズムトレーナー ===\n\n";

	// ユーザーからの入力を取得
	int bpm = getValidInput("BPMを入力してください（60-200）：", 60, 200);
	int numerator = getValidInput("拍子記号を入力してください（分子 1-12）：", 1, 12);
	int denominator = getValidDenominator();
	int duration = getValidInput("再生時間を入力してください（秒 0-無限）：", 0, 300);

	//// デバッグ: 入力値の確認
	//std::cout << "\n=== デバッグ情報 ===\n";
	//std::cout << "入力されたBPM: " << bpm << "\n";
	//std::cout << "入力された分子: " << numerator << "\n";
	//std::cout << "入力された分母: " << denominator << "\n";
	//std::cout << "==================\n\n";

	// メトロノームを作成・開始
	Metronome metronome(bpm, numerator, denominator);

	std::cout << "\n設定完了！\n";
	std::cout << "BPM: " << metronome.getBPM() << "\n";
	std::cout << "拍子: " << metronome.getNumerator() << "/" << metronome.getDenominator() << "\n";
	std::cout << "再生時間: " << duration << "秒\n\n";

	metronome.start();

	// 指定時間だけ実行 
	if (duration == 0) {
		std::cout << "無限再生モード。何かキーを押すと停止します……\n";
		std::cin.get();
	}
	else {
		std::this_thread::sleep_for(std::chrono::seconds(duration));
	}

	metronome.stop();

	std::cout << "\n再生完了！お疲れ様でした。\n";
	std::cout << "何かキーを押して終了……";
	std::cin.get();

	return 0;
}

// Email privacy test 
