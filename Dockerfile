FROM emscripten/emsdk:5.0.0

# Build arguments
ARG SDL_VERSION=2

# Environment variables for runtime configuration
ENV SDL_VERSION=${SDL_VERSION}
ENV BUILD_OUTPUT=html
ENV SERVE_PORT=8080

# Pre-fetch SDL port to speed up first builds
RUN emcc --use-port=sdl${SDL_VERSION} --check

# Copy entrypoint script and setup directories
COPY scripts/entrypoint.sh /app/entrypoint.sh
RUN mkdir -p /app/src /app/build /app/output && chmod +x /app/entrypoint.sh

# Copy demo source code
COPY src/ /app/src/

WORKDIR /app

# Expose port for emrun web server
EXPOSE 8080

ENTRYPOINT ["/app/entrypoint.sh"]

# Default command: build the project
CMD ["build"]
