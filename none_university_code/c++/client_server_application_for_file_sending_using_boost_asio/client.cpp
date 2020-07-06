//#include "pch.h"
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include<boost/array.hpp>
#include <ctime>
#include <fstream>
#include <sstream>
using boost::asio::ip::tcp;
int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " <file path>" << std::endl;
		return 1;
	}
	try
	{
		boost::asio::io_service io_service;
		tcp::resolver resolver(io_service);
		tcp::resolver::results_type endpoint = resolver.resolve("127.0.0.1", "1111");
	
		tcp::socket socket(io_service);
		boost::system::error_code error = boost::asio::error::host_not_found;
		boost::asio::connect(socket, endpoint);
	
    	std::cout << "Connected to 127.0.0.1:1111" << std::endl;
		boost::array<char, 1024> buffer;
		std::ifstream source_file(argv[1]);
		if (!source_file)
		{
			std::cout << "Can't open " << argv[1] << std::endl;
			return 1;
		}
		size_t file_size = source_file.tellg();
		source_file.seekg(0);

		boost::asio::streambuf request_bufer;
		std::ostream request_stream(&request_bufer);
		request_stream << argv[1] << "\n" << file_size << "*";

		boost::asio::write(socket, request_bufer);
		std::cout << "Start sending...\n";
		while(true)
		{
			if (source_file.eof() == false)
			{
				source_file.read(buffer.c_array(), (std::streamsize)buffer.size());
				if (source_file.gcount() <= 0)
				{
					std::cout << "read file error " << std::endl;
					return 1;
				}
				boost::asio::write(socket, boost::asio::buffer(buffer.c_array(),
					source_file.gcount()),
					boost::asio::transfer_all(), error);
				if (error)
				{
					std::cout << error << std::endl;
					return 1;
				}
			}
			else
				break;
		}
		std::cout << "File " << argv[1] << " was send successfully.\n";
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}