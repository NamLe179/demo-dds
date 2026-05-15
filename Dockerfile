# FROM ubuntu:24.04

# ENV DEBIAN_FRONTEND=noninteractive

# RUN apt-get update && apt-get install -y --no-install-recommends \
#     build-essential \
#     cmake \
#     ninja-build \
#     git \
#     pkg-config \
#     ca-certificates \
#     qt6-base-dev \
#     libasio-dev \
#     libtinyxml2-dev \
#     libssl-dev \
#     libzstd-dev \
#     libfoonathan-memory-dev \
#     && rm -rf /var/lib/apt/lists/*

# ARG FASTDDS_TAG=v3.5.0

# RUN git clone --branch ${FASTDDS_TAG} --depth 1 https://github.com/eProsima/Fast-DDS.git /tmp/Fast-DDS && \
#     cmake -S /tmp/Fast-DDS -B /tmp/Fast-DDS/build -G Ninja \
#       -DCMAKE_BUILD_TYPE=Release \
#       -DCMAKE_INSTALL_PREFIX=/opt/fastdds \
#       -DTHIRDPARTY=ON \
#       -DFASTDDS_STATISTICS=ON \
#       -DBUILD_TESTING=OFF && \
#     cmake --build /tmp/Fast-DDS/build --target install -j"$(nproc)" && \
#     rm -rf /tmp/Fast-DDS

# WORKDIR /src
# COPY . .

# RUN cmake -S . -B build -G Ninja \
#       -DCMAKE_BUILD_TYPE=Release \
#       -DCMAKE_PREFIX_PATH=/opt/fastdds && \
#     cmake --build build --target dds_publisher dds_subscriber -j"$(nproc)"

# RUN cp /src/build/dds_publisher /usr/local/bin/dds_publisher && \
#     cp /src/build/dds_subscriber /usr/local/bin/dds_subscriber

# RUN mkdir -p /etc/fastdds && \
#     cp /src/config/fastdds_statistics_profiles.xml /etc/fastdds/fastdds_statistics_profiles.xml

# ENV FASTDDS_DEFAULT_PROFILES_FILE=/etc/fastdds/fastdds_statistics_profiles.xml
# ENV LD_LIBRARY_PATH=/opt/fastdds/lib

# WORKDIR /app
# CMD ["dds_subscriber", "--domain", "0"]


# ==========================================
# STAGE 1: Môi trường Build (Biên dịch C++)
# ==========================================
FROM ubuntu:24.04 AS builder

ENV DEBIAN_FRONTEND=noninteractive

# Chỉ cài CMake, build-essential và thư viện phát triển cốt lõi của Qt (Qt5 Core)
# Không cài các thành phần GUI để tiết kiệm thời gian build
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    qtbase5-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy RTI SDK và License
COPY rti_sdk /opt/rti_sdk

# Thiết lập NDDSHOME (giống hệt logic CMake của bạn)
ENV NDDSHOME=/opt/rti_sdk

# Copy toàn bộ mã nguồn
COPY . .

# Build project
RUN mkdir -p build && cd build && \
    cmake .. && \
    make -j$(nproc)

# ==========================================
# STAGE 2: Môi trường Runtime siêu nhẹ
# ==========================================
FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

# CHỈ cài thư viện chạy Qt Core (không chứa GUI), giúp Image cực kỳ nhẹ
RUN apt-get update && apt-get install -y \
    libqt5core5a \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy thư viện RTI và License
COPY --from=builder /opt/rti_sdk/lib/x64Linux4gcc8.5.0 /opt/rti_sdk/lib/x64Linux4gcc8.5.0
COPY --from=builder /opt/rti_sdk/rti_license.dat /opt/rti_sdk/rti_license.dat

# Copy 2 file chạy đích danh theo cấu hình CMakeLists.txt
COPY --from=builder /app/build/dds_publisher /app/dds_publisher
COPY --from=builder /app/build/dds_subscriber /app/dds_subscriber

# Biến môi trường hệ thống
ENV RTI_LICENSE_FILE=/opt/rti_sdk/rti_license.dat
ENV LD_LIBRARY_PATH=/opt/rti_sdk/lib/x64Linux4gcc8.5.0:$LD_LIBRARY_PATH

CMD ["bash"]