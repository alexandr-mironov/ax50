FROM ubuntu:18.04

ENV DEBIAN_FRONTEND=noninteractive
ENV FORCE_UNSAFE_CONFIGURE=1

# 18.04 EOL — write sources.list explicitly
RUN echo "deb http://archive.ubuntu.com/ubuntu bionic main restricted universe multiverse" > /etc/apt/sources.list && \
    echo "deb http://archive.ubuntu.com/ubuntu bionic-updates main restricted universe multiverse" >> /etc/apt/sources.list && \
    echo "deb http://archive.ubuntu.com/ubuntu bionic-security main restricted universe multiverse" >> /etc/apt/sources.list

RUN apt-get update && apt-get install -y \
    build-essential \
    ccache \
    file \
    gawk \
    gettext \
    git \
    libncurses5-dev \
    libssl-dev \
    python2.7 \
    python3 \
    subversion \
    unzip \
    wget \
    zlib1g-dev \
    rsync \
    openssl \
    quilt \
    xsltproc \
    && rm -rf /var/lib/apt/lists/*

# Symlink python2
RUN ln -sf /usr/bin/python2.7 /usr/bin/python && \
    ln -sf /usr/bin/python2.7 /usr/bin/python2

# Build as non-root (OpenWrt requirement)
RUN useradd -m builder
USER builder
WORKDIR /build
