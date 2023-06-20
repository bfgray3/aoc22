FROM gcc:11.3.0

# apt-get upgrade after update and before install?

RUN : \
  && apt-get update \
  && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends jq \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/* \
  && :

WORKDIR aoc

COPY . .

CMD ./test.sh
