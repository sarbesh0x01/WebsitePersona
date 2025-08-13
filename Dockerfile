FROM ubuntu:22.04

# Install dependencies
RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    make \
    libboost-all-dev \
    libasio-dev \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy everything
COPY . .

# Build with your existing CMakeLists.txt
RUN mkdir -p build && cd build && cmake .. && cmake --build .

# Expose port (Railway sets the PORT environment variable)
EXPOSE $PORT

# Run your executable
CMD  ./build/myweb
