FROM ubuntu:18.04
RUN apt-get update
RUN apt-get -y install clang-8
RUN apt-get -y install cmake
RUN apt-get -y install python3
RUN apt-get -y install python3-venv python3-pip
RUN apt-get -y install valgrind
WORKDIR /cpp-demo
RUN pip3 install conan
COPY . .
RUN conan install . -if build/ --build=missing -pr conan-profiles/docker_linux_x86_64
RUN conan build . -bf build
CMD valgrind ./build/bin/docker-setup-cpp