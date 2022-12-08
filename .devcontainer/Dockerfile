FROM ros:foxy

ENV ROS_DISTRO foxy

# install utils
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
  bash-completion \
  build-essential \
  cmake \
  gdb \
  git \
  pylint3 \
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
  python3-venv

# install protobuf libs:
RUN mkdir protobuf && cd protobuf && \
    wget "https://github.com/protocolbuffers/protobuf/releases/download/v21.7/protobuf-cpp-3.21.7.tar.gz"  && \
    tar -xvzf protobuf-cpp-3.21.7.tar.gz --no-same-owner

# compile protobuf libs:
RUN cd protobuf/protobuf-3.21.7 && \
    cmake -Dprotobuf_BUILD_TESTS=OFF . &&\
    make && \
    make install

# install fprime depenedencies:
RUN rm -rf /var/lib/apt/lists/* \
    && python3 -m venv /tmp/fprime-venv \
    && . /tmp/fprime-venv/bin/activate \
    && python3 -m pip install -U --upgrade pip setuptools setuptools_scm wheel argcomplete \
    && printf '\n[ -d "%s" ] && . %s/bin/activate\n' /tmp/fprime-venv /tmp/fprime-venv >> ~/.bashrc \
    && echo 'eval "$(register-python-argcomplete fprime-cli)"' >> ~/.bashrc

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

# installing fprime requirements
RUN mkdir fprime && git clone https://github.com/nasa/fprime.git fprime
RUN . /tmp/fprime-venv/bin/activate && python3 -m pip install -U -r fprime/requirements.txt

RUN wget -q https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb
RUN apt-get update
RUN apt-get install -y ./google-chrome-stable_current_amd64.deb

RUN echo "source /opt/ros/foxy/setup.bash" >> /home/$USERNAME/.bashrc