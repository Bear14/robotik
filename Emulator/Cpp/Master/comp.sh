#!/bin/bash


g++ -I /home/fabian/Install/boost/boost_1_66_0 $1 -o $2 /home/fabian/Install/boost/lib/libboost_system.a /home/fabian/Install/boost/lib/libboost_thread.a -pthread

