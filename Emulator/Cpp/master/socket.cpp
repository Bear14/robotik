//
// Created by torben on 24/02/19.
//

#ifndef SOCKET
#define SOCKET

#include <boost/asio.hpp>
#include <thread>
#include <iostream>
#include "string.h"


#define IPADDRESS "127.0.0.1" // "192.168.1.64"
//#define UDP_PORT 5005

using boost::asio::ip::udp;
using boost::asio::ip::address;

void Sender(char *in,int udpPort) {


    std::string send = (std::string) in;
    boost::asio::io_service io_service;
    udp::socket socket(io_service);
    udp::endpoint remote_endpoint = udp::endpoint(address::from_string(IPADDRESS), udpPort);
    socket.open(udp::v4());

    boost::system::error_code err;
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    auto sent = socket.send_to(boost::asio::buffer(send), remote_endpoint, 0, err);
    socket.close();
    std::cout << "Sent Payload --- " << send << "--" << sent << "\n";
}

void sendWithDelay(char *input,int udpPort){
    //std::this_thread::sleep_for(std::chrono::milliseconds(200));
    Sender(input,udpPort);
}

#endif