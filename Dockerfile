FROM emscripten/emsdk:latest

# Build arguments
ARG SDL_VERSION=3

# Environment variables for runtime configuration
ENV SDL_VERSION=${SDL_VERSION}
ENV BUILD_OUTPUT=html
ENV SERVE_PORT=8080

# Pre-fetch SDL port to speed up first builds
RUN emcc --use-port=sdl${SDL_VERSION} --check

# Create directories
RUN mkdir -p /app/src /app/build /app/output

# Copy demo source code
COPY src/ /app/src/

# Copy entrypoint script
COPY scripts/entrypoint.sh /app/entrypoint.sh
RUN chmod +x /app/entrypoint.sh

WORKDIR /app

# Expose port for emrun web server
EXPOSE 8080

ENTRYPOINT ["/app/entrypoint.sh"]

# Default command: build the project
CMD ["build"]
