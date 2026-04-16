FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    ninja-build \
    git \
    pkg-config \
    ca-certificates \
    qt6-base-dev \
    libasio-dev \
    libtinyxml2-dev \
    libssl-dev \
    libzstd-dev \
    libfoonathan-memory-dev \
    && rm -rf /var/lib/apt/lists/*

ARG FASTDDS_TAG=v3.5.0

RUN git clone --branch ${FASTDDS_TAG} --depth 1 https://github.com/eProsima/Fast-DDS.git /tmp/Fast-DDS && \
    cmake -S /tmp/Fast-DDS -B /tmp/Fast-DDS/build -G Ninja \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/opt/fastdds \
      -DTHIRDPARTY=ON \
      -DFASTDDS_STATISTICS=ON \
      -DBUILD_TESTING=OFF && \
    cmake --build /tmp/Fast-DDS/build --target install -j"$(nproc)" && \
    rm -rf /tmp/Fast-DDS

WORKDIR /src
COPY . .

RUN cmake -S . -B build -G Ninja \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_PREFIX_PATH=/opt/fastdds && \
    cmake --build build --target dds_publisher dds_subscriber -j"$(nproc)"

RUN cp /src/build/dds_publisher /usr/local/bin/dds_publisher && \
    cp /src/build/dds_subscriber /usr/local/bin/dds_subscriber

RUN mkdir -p /etc/fastdds && \
    cp /src/config/fastdds_statistics_profiles.xml /etc/fastdds/fastdds_statistics_profiles.xml

ENV FASTDDS_DEFAULT_PROFILES_FILE=/etc/fastdds/fastdds_statistics_profiles.xml
ENV LD_LIBRARY_PATH=/opt/fastdds/lib

WORKDIR /app
CMD ["dds_subscriber", "--domain", "0"]
