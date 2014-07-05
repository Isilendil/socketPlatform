cmake_minimum_required(VERSION 2.8)
PROJECT(SERVERLIBRARYMAIN)
INCLUDE_DIRECTORIES(/usr/include/python2.7)
LINK_DIRECTORIES(/usr/lib64/ ./)
ADD_EXECUTABLE(ServerlibraryMain Serverlibrary.cpp Server.cpp)
TARGET_LINK_LIBRARIES(ServerlibraryMain libpython2.7.so liblibrary.so)

