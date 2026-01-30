# cse498 Build System

Docker environment for C++ development with Emscripten and SDL2.

## Quick Start


### Make Commands

| Command | Description |
|---------|-------------|
| `make build` | Build project, output to `./output` |
| `make test` | Build and run tests |
| `make serve` | Build and start emrun web server |
| `make dev` | Interactive development shell |

### Docker Compose Usage
```bash
# Build the demo
docker compose run --rm build

# Build and serve with web server
docker compose up serve
# Open http://localhost:8080

# Interactive shell
docker compose run --rm dev
```

## Configuration

### Environment Variables

| Variable | Default | Description |
|----------|---------|-------------|
| `SDL_VERSION` | `2` | SDL version (2 or 3) |
| `BUILD_OUTPUT` | `html` | Output format: `html` or `js` |
| `SERVE_PORT` | `8080` | emrun server port |

### Direct Docker Usage

```bash
# Build image
docker build -t cse498-companyb-project .

# Build project
docker run --rm \
  -v $(pwd)/src:/app/src:ro \
  -v $(pwd)/output:/app/output \
  cse498-companyb-project build

# Build and serve
docker run --rm -p 8080:8080 \
  -v $(pwd)/src:/app/src:ro \
  -v $(pwd)/output:/app/output \
  cse498-companyb-project serve

# Build with SDL2
docker run --rm -e SDL_VERSION=2 \
  -v $(pwd)/src:/app/src:ro \
  -v $(pwd)/output:/app/output \
  cse498-companyb-project build

# Interactive shell
docker run -it --rm \
  -v $(pwd)/src:/app/src \
  -v $(pwd)/output:/app/output \
  cse498-companyb-project shell
```


## Writing Src

Add source files to `./src` and update `CMakeLists.txt`:

```cmake
file(GLOB SOURCES "*.cpp" "*.c")
add_executable(index ${SOURCES})
```

## Adding ports in CMakeLists.txt:

```cmake
target_link_options(index PRIVATE --use-port=sdl3 --use-port=sdl2_image)
```
