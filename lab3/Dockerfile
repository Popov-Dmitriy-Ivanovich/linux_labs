FROM ubuntu:jammy AS builder

WORKDIR /build
COPY . .

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        g++ make 
RUN make

CMD ["./do.sh"]