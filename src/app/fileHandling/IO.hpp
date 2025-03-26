
#ifndef IO_HPP
#define IO_HPP

#include <iostream>
#include <fstream>
#include <string>

class IO {
private:
	std::fstream file_stream;

public:
	IO(const std::string& file_path);
	~IO();
	std::fstream getFileStream();

};

#endif