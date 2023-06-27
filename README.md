## overview

the image and tests support the following languages:

* Bash
* C++
* Go
* Python
* R

## usage

1. write solutions in files named `<DD>/{a,b}/main.{sh,cpp,go,py,R}`. each program/script should output the answer (and only the answer) to stdout.
2. build the image for testing with `make build`.
3. test all solutions in the above languages with `make test`.
4. once there is a correct solution for a given day/part, add it to [answers.json](answers.json).
