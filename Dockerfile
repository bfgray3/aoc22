FROM gcc:11.3.0

# apt-get upgrade after update and before install?

# go     TODO

RUN : \
  && apt-get update \
  && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends jq r-base python3-venv \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/* \
  && :

WORKDIR aoc

COPY . .

ENV PATH=/venv/bin:$PATH

RUN : \
  && python3 -m venv /venv \
  && pip --no-cache-dir install -r requirements.txt \
  && :

CMD ./test.sh
