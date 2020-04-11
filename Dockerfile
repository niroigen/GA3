FROM ubuntu:16.04

RUN apt-get update \
	&& apt-get install -y software-properties-common -y \
	&& apt-get -y install cmake -y \
	&& apt-get install -y autoconf automake make libtool pkg-config g++ gcc \
	&& apt-get install git-core -y \
	&& apt-get install libjsoncpp-dev