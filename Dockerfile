FROM ros:humble

ENV ROS_DISTRO humble

# install utils
RUN apt-get update && DEBIAN_FRONTEND=noninteractive  && apt-get install -y  --no-install-recommends\
    protobuf-compiler \
    autoconf \
    automake \
    libtool \
    make \
    g++ \
    unzip \
    libprotobuf-dev \
    wget \
    openssh-server \
    curl \
    gnupg \
    git \
    build-essential \
    cmake \
    gdb-multiarch \
    default-jre \
    python3 \
    python3-setuptools \
    python3-pip \
    python3-venv \
    ros-${ROS_DISTRO}-rosbridge-suite \
    && rm -rf /var/lib/apt/lists/*

# install protobuf libs:
RUN mkdir protobuf && cd protobuf && \
    wget "https://github.com/protocolbuffers/protobuf/releases/download/v21.7/protobuf-cpp-3.21.7.tar.gz"  && \
    tar -xvzf protobuf-cpp-3.21.7.tar.gz --no-same-owner

# compile protobuf libs:
RUN cd protobuf/protobuf-3.21.7 && \
    cmake -Dprotobuf_BUILD_TESTS=OFF . &&\
    make && \
    make install

# install fprime:
RUN apt-get update && \
    python3 -m venv /tmp/fprime-venv &&\
    . /tmp/fprime-venv/bin/activate &&\
    python3 -m pip install -U --upgrade pip setuptools==58.2.0 setuptools_scm wheel argcomplete &&\
    printf '\n[ -d "%s" ] && . %s/bin/activate\n' /tmp/fprime-venv /tmp/fprime-venv >> ~/.bashrc &&\
    echo 'eval "$(register-python-argcomplete fprime-cli)"' >> ~/.bashrc

# defining working directory
WORKDIR /workspaces/ros2_fprime_bridge

# copying workspaces to the docker
COPY common/ common/

#compiling fprime workspace
COPY fprime_ws/ fprime_ws/
RUN  git clone https://github.com/nasa/fprime.git /app/fprime && \
     cd /app/fprime && \
     git reset --hard a56426adbb888ce4f5a8c6a2be3071a25b11da16
RUN  . /tmp/fprime-venv/bin/activate && python3 -m pip install -U -r /app/fprime/requirements.txt
RUN  rm -rf fprime_ws/spring/build-artifacts fprime_ws/spring/build-fprime-automatic-native

COPY examples/ examples/

RUN  . /tmp/fprime-venv/bin/activate && \
     cd fprime_ws/spring && \
     fprime-util generate && \
     fprime-util build 

# compiling ros workspace
COPY ros_ws/ ros_ws/
RUN  rm -rf ros_ws/build/ ros_ws/log/ ros_ws/install/
RUN  . /opt/ros/${ROS_DISTRO}/setup.sh && \
     cd ros_ws && \
     colcon build

# sourcing ROS and F'
RUN echo "source /opt/ros/${ROS_DISTRO}/setup.bash" >> /home/$USERNAME/.bashrc
RUN echo "source /tmp/fprime-venv/bin/activate" >> /home/$USERNAME/.bashrc 

CMD ["bash"]