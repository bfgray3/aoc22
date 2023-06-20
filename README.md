## usage

automatically build and test all solutions in Bash, C++, Go, Python, and R with

```bash
./test
```

do the above in docker with

```bash
docker build . -t aoc22  # just a single-stage build
docker run --rm aoc22:latest
```
