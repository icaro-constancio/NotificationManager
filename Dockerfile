FROM ubuntu:22.04

RUN apt-get update && \
    apt-get install -y build-essential libcurl4-openssl-dev && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . /app

RUN make

CMD ["bash"]