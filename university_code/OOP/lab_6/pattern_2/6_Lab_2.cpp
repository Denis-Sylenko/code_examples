#include "pch.h"
#include <iostream>
#include <string>
#include<vector>
#include<map>
#include <fstream>
using namespace std;

class DataLayer {
public:
	pair<string, string> get_riddle(size_t number) {
		ifstream ridle_stream;
		pair<string, string> riddle_and_answer;
		ridle_stream.open(riddles);
		for (int i = 0; i <= number % 2; ++i) {
			getline(ridle_stream, riddle_and_answer.first);
			getline(ridle_stream, riddle_and_answer.second);
		}
		return riddle_and_answer;
	}

	string get_song(size_t number) {
		ifstream song_stream;
		string song_name;
		song_stream.open(songs);
		for (int i = 0; i <= number%2; ++i) {
			getline(song_stream, song_name);
		}
		return song_name;
	}
private:
	string riddles = "riddles.txt";
	string songs = "songs.txt";
};

class ServiceLayer {
public:

	string predict(const int day) {
		if (day >= 15) {
			return "You'll be happy today!";
		}
		return "You'll be funny today!";
	};

	string advice_song() {
		return "I advice you to listen:" + database.get_song(rand());
	};
	string ask_question() {
		pair<string, string> riddle_and_answer = database.get_riddle(rand());
		cout << "A riddle: " << riddle_and_answer.first << endl;
		string answer;
		cin >> answer;
		if (answer == riddle_and_answer.second) {
			return "Congratulations! You are win!";
		}
		return "No( Correct answer is " + riddle_and_answer.second;
	};
private:
	DataLayer database;
};

class ComunicationInterface {
public:
	void StartCommunication() {
		cout << "Hello! I am robo-gamer-bot! What's your name?" << endl;
		cin >> user_name;
		cout << "Nice to see you, " << user_name << endl;
	}

	void PurposeGames() {
		cout << "I would like to purpose some games to you:" << endl
			<< "Predictor" << endl << "Song_advice" << endl << "Mystery_man"
			<< endl;
		string choise;
		while (true) {
			cout << "Choose your game or exit!" << endl;
			cin >> choise;
			if (choise == "exit")
				break;
			ManageChoise(choise);
		}
	}

	void EndCommunication() {
		cout << "Goodbuy, " << user_name << endl;
	}
private:
	void ManageChoise(const string& choise) {
		if (choise == "Predictor") {
			cout << "Enter your birthday date (only day):";
			int day;
			cin >> day;
			cout << service.predict(day) << endl;
		}
		else if (choise == "Song_advice") {
			cout << service.advice_song() << endl;
		}
		else if (choise == "Mystery_man") {
			cout << service.ask_question() << endl;
		}
		else cout << "We haven't got such game!";
	};
	string user_name;
	ServiceLayer service;
};
int main()
{
	ComunicationInterface robo_game_bot;
	robo_game_bot.StartCommunication();
	robo_game_bot.PurposeGames();
	robo_game_bot.EndCommunication();
}
