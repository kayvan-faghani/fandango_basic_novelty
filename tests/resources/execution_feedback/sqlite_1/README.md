# How to run

First make sure your environemnt is set up, containing the `fan` command, the `fcc` compiler, and the required `llvm` version to run `fcc`.

Compile everything with FCC:
```sh
make
```

Generate the analysis metadata using `fan`:
```sh
fan "$PWD/build/sqlite_fuzz"
```

If you change the `.c` source files, either fuzzed program or harness, you need to recompile. If only the grammar chage (`.fan` file), you do not need to run either of those, and can simply run Fandango.

Example Fandango usage:

```sh
FANDANGO_COVERAGE_CSV="$PWD/baseline.csv" \
fandango --enable-experimental-module execution fuzz \
  -f specifications/sqlite_grammar.fan \
  --infinite --stop-after-seconds 180 --random-seed 1 \
  --fcc "$PWD/build/sqlite_fuzz"
```

Note that we first, export a path for the output CSV where the benchmarking results will be stored.
