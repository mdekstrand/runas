FROM centos:centos7
MAINTAINER Michael Ekstrand <michael@elehack.net>

ADD yum-ops.sh /root/yum-ops.sh
RUN /bin/sh /root/yum-ops.sh
ADD Makefile runas.c build.sh /root/runas/
WORKDIR /root/runas
CMD ./build.sh
