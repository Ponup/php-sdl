FROM debian:11

ARG TARGET_PHP_VERSION=8.1

RUN apt-get update
RUN apt-get install -y make build-essential wget
RUN apt-get install -y lsb-release apt-transport-https ca-certificates 
RUN wget -O /etc/apt/trusted.gpg.d/php.gpg https://packages.sury.org/php/apt.gpg
RUN echo "deb https://packages.sury.org/php/ $(lsb_release -sc) main" | tee /etc/apt/sources.list.d/php.list
RUN apt-get update
RUN apt-get install -y php${TARGET_PHP_VERSION}-dev
RUN apt-get install -y libsdl2-dev
RUN apt-get install -y xvfb
COPY . /opt/php-sdl
WORKDIR /opt/php-sdl
RUN phpize
RUN ./configure
RUN make
RUN make install
RUN echo "extension=sdl.so" >> /etc/php/${TARGET_PHP_VERSION}/cli/php.ini

ENTRYPOINT ["/opt/php-sdl/docker-entrypoint.sh"]

