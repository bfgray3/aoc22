## usage

to run day 1 part b, for example, run:

```bash
make day=01 part=b
./01/b/aocmain ./01/input.txt
```

automatically build and test all c++ solutions with

```bash
./test
```

do the above in docker with

```bash
docker build . -t aoc22  # just a single-stage build
docker run --rm aoc22:latest
```

solutions in other languages have no automated tests but can be run with

```bash
go run main.go
python3 main.py
Rscript main.R
bash main.sh
```
