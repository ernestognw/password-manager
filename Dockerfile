FROM ubuntu:16.04


COPY src /src
WORKDIR /src
RUN make
