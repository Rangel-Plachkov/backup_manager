FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y \
    build-essential \
    cmake \
    zlib1g-dev \
    && apt-get clean

WORKDIR /workspace

CMD ["/bin/bash"]


