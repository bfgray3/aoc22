FROM gcc:13.2

ARG GO_TARBALL=go1.21.4.linux-amd64.tar.gz

RUN : \
  && apt-get update \
  && DEBIAN_FRONTEND=noninteractive apt-get install --yes --no-install-recommends jq r-base python3-venv \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/* \
  && :

WORKDIR aoc

COPY requirements.txt .

ENV PATH=/venv/bin:$PATH

RUN : \
  && python3 -m venv /venv \
  && pip --no-cache-dir install -r requirements.txt \
  && :

ENTRYPOINT ["./test.sh"]
