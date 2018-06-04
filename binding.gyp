{
  "targets": [
    {
      "target_name": "linux-perf",
      "sources": [
        "linux-perf.cc",
        "linux-perf-listener.cc",
      ],
      "include_dirs": ["<!(node -e \"require('nan')\")"],
    }
  ]
}
