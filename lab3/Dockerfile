FROM docker.io/library/ubuntu:22.04@sha256:0bced47fffa3361afa981854fcabcd4577cd43cebbb808cea2b1f33a3dd7f508
LABEL name="lab3"
RUN apt-get update && apt-get install -y wget  \
    lsb-release  \
    software-properties-common  \
    gnupg  \
    make
RUN wget https://apt.llvm.org/llvm.sh && chmod u+x llvm.sh && ./llvm.sh 19
RUN apt-get install -y     libomp-19-dev