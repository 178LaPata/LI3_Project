FROM ubuntu:22.04
RUN apt-get -y update
RUN apt-get -y install git
RUN apt install gcc make libglib2.0-dev libgtk2.0-dev valgrind \
    libncurses-dev libncurses6 libncursesw6 libreadline8 \ 
    libreadline-dev -y

RUN mkdir /li3/
COPY . /li3/