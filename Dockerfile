# Multi-stage build for Railway deployment
FROM ubuntu:22.04 AS builder

# Install build dependencies
RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    make \
    libboost-all-dev \
    libasio-dev \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy your project files
COPY CMakeLists.txt .
COPY include/ include/
COPY src/ src/

# Build using CMake
RUN mkdir build && \
    cd build && \
    cmake .. && \
    make -j$(nproc)

# Production stage
FROM ubuntu:22.04

# Install runtime dependencies only
RUN apt-get update && apt-get install -y \
    libboost-system1.74.0 \
    libboost-filesystem1.74.0 \
    libasio-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy compiled binary and assets
COPY --from=builder /app/build/myweb .
COPY templates/ templates/
COPY static/ static/

# Expose port (Railway will set the PORT env var)
EXPOSE $PORT

# Run the application
CMD ["./myweb"]
