#ifndef TASK_HPP
#define TASK_HPP

#include <iostream>
#include <string>
#include <sstream>
#include "../fileHandling/IO.hpp"

enum class Action {
	ENCRYPT,
	DECRYPT
};

struct Task {
	std::string filePath;
	std::fstream f_stream;
	Action action;

	Task(std::fstream&& stream, Action act, std::string filePath) : f_stream(std::move(stream)), action(act), filePath(filePath) { }
	
	// serialize: converting an object's data into a byte stream for storage or transmission
	std::string toString() {
		std::ostringstream oss;
		oss << filePath << "," << (action == Action::ENCRYPT ? "ENCRYPT" : "DECRYPT");

		return oss.str();
	}

	// deserialize: reconstructing the object from the byte stream
	static Task fromString(const std::string& taskData) {
		std::istringstream iss(taskData);
		std::string filePath;
		std::string actionStr;

		if (std::getline(iss, filePath, ',') && std::getline(iss, actionStr)) {
			Action action = (actionStr == "ENCRYPT" ? Action::ENCRYPT : Action::DECRYPT);

			IO io(filePath);
			std::fstream f_stream = std::move(io.getFileStream());
			if (f_stream.is_open()) {
				return Task(std::move(f_stream), action, filePath);
			}
			else {
				throw std::runtime_error("Failed to open file: " + filePath);
			}
		}
		else {
			throw std::runtime_error("Invalid task data format");
		}
	}
};


#endif