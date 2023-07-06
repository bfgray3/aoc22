FROM gcc:13.1

ARG GO_TARBALL=go1.20.5.linux-amd64.tar.gz

RUN : \
  && apt-get update \
  && DEBIAN_FRONTEND=noninteractive apt-get install --yes --no-install-recommends jq r-base python3-venv \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/* \
  && :

RUN : \
  && curl -OL https://golang.org/dl/$GO_TARBALL \
  && tar -C /usr/local -xvf $GO_TARBALL \
  && rm $GO_TARBALL \
  && :

ENV PATH=$PATH:/usr/local/go/bin

WORKDIR aoc

COPY requirements.txt .

ENV PATH=/venv/bin:$PATH

RUN : \
  && python3 -m venv /venv \
  && pip --no-cache-dir install -r requirements.txt \
  && :

ENTRYPOINT ["./test.sh"]
