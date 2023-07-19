## overview

the image and tests support the following languages:

* Bash
* C++
* Go
* Python
* R

## usage

1. write solutions in files named `<DD>/{a,b}/main.{sh,cpp,go,py,R}`.
    1. each program/script should output the answer (and only the answer) to stdout.
    2. each program/script should expect exactly one command line argument, which is the file containing the input data.
2. build the image for testing with `make build`.
3. test all solutions in the above languages with `make test`.
4. test all solutions for a given day/part with `make test path=<dd>/{a,b}/`, e.g. `make test path=05/a/`.
5. once there is a correct solution for a given day/part, add it to [answers.json](answers.json) in a format like the following:

```json
{
  "ans01": {"a": "foo", "b": "bar"},
  "ans02": {"a": "123"}
}
```
