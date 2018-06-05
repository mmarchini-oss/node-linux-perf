# node-linux-perf

Library to replace V8's `--perf-basic-prof` flag, with the ability to toggle the
creation of Linux `perf` map files during runtime.

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
