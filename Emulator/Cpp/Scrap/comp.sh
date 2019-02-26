#!/bin/bash


g++ -I /home/torben/Install/boost/boost_1_66_0 $1 -o $2 /home/torben/Install/boost/lib/libboost_system.a /home/torben/Install/boost/lib/libboost_thread.a -pthread

