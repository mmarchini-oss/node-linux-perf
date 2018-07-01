# node-linux-perf

Library to replace V8's `--perf-basic-prof` flag, with the ability to toggle
creation of Linux `perf` map files during runtime.

## Build Status

| Version | v6.x                    | v8.x                    | v9.x                    | v10.x                     | master                        | v8-canary                        |
|---------|-------------------------|-------------------------|-------------------------|---------------------------|-------------------------------|----------------------------------|
| **Trusty**  | [![v6.x badge][v6-badge]][travis] | [![v8.x badge][v8-badge]][travis] | [![v9.x badge][v9-badge]][travis] | [![v10.x badge][v10-badge]][travis] | [![master badge][master-badge]][travis] | [![v8-canary badge][canary-badge]][travis] |

[travis]: https://travis-ci.org/nodejs/llnode
[v6-badge]: https://img.shields.io/badge/build-unsupported-lightgrey.svg
[v8-badge]: https://img.shields.io/badge/build-unsupported-lightgrey.svg
[v9-badge]: https://img.shields.io/badge/build-unsupported-lightgrey.svg
[v10-badge]: https://travis-matrix-badges.herokuapp.com/repos/nodejs/llnode/branches/master/1?use_travis_com=true
[master-badge]: https://travis-matrix-badges.herokuapp.com/repos/nodejs/llnode/branches/master/2?use_travis_com=true
[canary-badge]: https://travis-matrix-badges.herokuapp.com/repos/nodejs/llnode/branches/master/3?use_travis_com=true

## Installation

```bash
$ npm install linux-perf
```

## Usage

```javascript
const linuxPerf = require('linux-perf');

// Generated a /tmp/perf-PID.map file and updates it when necessary
linuxPerf.start();

// **YOUR CODE HERE**

// Stops writing to /tmp/perf-PID.map
linuxPerf.stop();
```

## API

### `start(): bool`

Generates a `/tmp/perf-PID.map` file and updates it when necessary (for example,
when new functions are declared). If a `/tmp/perf-PID.map` file already exists,
its content will be erased, and a new file will be generated.

**Return**: `true` if the file was generated successfully, `false` otherwise.

### `stop(): bool`

Stops writing to `/tmp/perf-PID.map`. The content written on the file is
preserved.

**Return**: `true` if it was able to stop writting to the file, `false`
  otherwise.
