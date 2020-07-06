//#include "pch.h"
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include<boost/array.hpp>
#include <ctime>
#include <fstream>
#include <sstream>

unsigned short tcp_port = 1111;

int main(int argc, char* argv[])
{
	boost::array<char, 1024> buffer;
	size_t file_size = 0;
	try
	{
		std::cout << argv[0] << " listen port " << tcp_port << std::endl;
		boost::asio::io_service io_service;
		boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), tcp_port));
		boost::asio::ip::tcp::socket socket(io_service);
		acceptor.accept(socket);
		std::cout << "Connection..." << std::endl;
		std::string path;
		boost::asio::streambuf request_buffer;
		boost::system::error_code error;
		boost::asio::read_until(socket, request_buffer, "*");
		std::istream request_stream(&request_buffer);
		
		request_stream >> path;
		request_stream >> file_size;
		request_stream.read(buffer.c_array(), 2);

		std::cout << path << " size is " << file_size << std::endl;
		std::ofstream output_file(path.c_str(), std::ios_base::out);
		if (!output_file)
		{
			std::cout << "Can't open " << path << std::endl;
			return 1;
		}

		do
		{
			request_stream.read(buffer.c_array(), (std::streamsize)buffer.size());
			output_file.write(buffer.c_array(), request_stream.gcount());
		} while (request_stream.gcount() > 0);

		while(true)
		{
			size_t length = socket.read_some(boost::asio::buffer(buffer), error);
			if (length > 0)
				output_file.write(buffer.c_array(), (std::streamsize)length);
			if (output_file.tellp() == (std::fstream::pos_type)(std::streamsize)file_size)
				break; 
			if (error)
			{
				std::cout << error << std::endl;
				break;
			}
		}
		std::cout << "Successfully received " << output_file.tellp() << " bytes" << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}