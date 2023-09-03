FROM ros:hubmle

ENV ROS_DISTRO hubmle

# install utils
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
  bash-completion \
  build-essential \
  cmake \
  gdb \
  git \
  python3-argcomplete \
  python3-pip \
  nano \
  wget \
  curl \
  autoconf \
  automake \
  libtool \
  make \
  g++ \
  unzip \
  libprotobuf-dev \
  protobuf-compiler \ 
  openssh-server \
  gnupg \
  gdb-multiarch \
  default-jre \
  python3 \
  python3-setuptools \
  python3-pip \
  python3-venv && \
  ros-${ROS_DISTRO}-rosbridge-suite \
  rm -rf /var/lib/apt/lists/*

# install protobuf libs:
RUN mkdir protobuf && cd protobuf && \
    wget "https://github.com/protocolbuffers/protobuf/releases/download/v21.7/protobuf-cpp-3.21.7.tar.gz"  && \
    tar -xvzf protobuf-cpp-3.21.7.tar.gz --no-same-owner

# compile protobuf libs:
RUN cd protobuf/protobuf-3.21.7 && \
    cmake -Dprotobuf_BUILD_TESTS=OFF . &&\
    make && \
    make install

ARG USERNAME=dev
ARG USER_UID=1000
ARG USER_GID=$USER_UID

# create a non-root user
RUN groupadd --gid $USER_GID $USERNAME \
  && useradd -s /bin/bash --uid $USER_UID --gid $USER_GID -m $USERNAME \
  # [Optional] Add sudo support for the non-root user
  && apt-get update \
  && apt-get install -y sudo \
  && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME\
  && chmod 0440 /etc/sudoers.d/$USERNAME \
  # Cleanup
  && rm -rf /var/lib/apt/lists/* \
  && echo "source /usr/share/bash-completion/completions/git" >> /home/$USERNAME/.bashrc

# define workspace
WORKDIR /app

# install fprime depenedencies:
RUN python3 -m pip install -U --upgrade pip setuptools==58.2.0 setuptools_scm wheel argcomplete \
    && echo 'eval "$(register-python-argcomplete fprime-cli)"' >> ~/.bashrc

# installing fprime requirements
RUN python3 -m pip install --ignore-installed PyYAML
RUN mkdir fprime && git clone https://github.com/nasa/fprime.git fprime && \
    cd fprime && \
    git reset --hard a56426adbb888ce4f5a8c6a2be3071a25b11da16
RUN python3 -m pip install -U -r fprime/requirements.txt

RUN echo "source /opt/ros/${ROS_DISTRO}}/setup.bash" >> /home/$USERNAME/.bashrc
RUN chown -R $USERNAME:$USERNAME /app/fprime