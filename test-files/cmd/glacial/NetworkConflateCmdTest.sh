#!/bin/bash
set -e

mkdir -p $HOOT_HOME/tmp/
mkdir -p test-output/cmd/NetworkConflateCmdTest

HOOT_OPTS="-D uuid.helper.repeatable=true -D writer.include.debug.tags=true"

hoot conflate -D hash.seed.zero=true --warn -C ReferenceConflation.conf -C NetworkAlgorithm.conf \
 $HOOT_OPTS \
 test-files/DcGisRoads.osm test-files/DcTigerRoads.osm \
 test-output/cmd/NetworkConflateCmdTest/output.osm

hoot diff test-output/cmd/NetworkConflateCmdTest/output.osm \
          test-files/cmd/glacial/NetworkConflateCmdTest/output.osm || \
     diff test-output/cmd/NetworkConflateCmdTest/output.osm \
          test-files/cmd/glacial/NetworkConflateCmdTest/output.osm

# Check to make sure we don't bomb out on empty files
hoot conflate -D hash.seed.zero=true --warn -C ReferenceConflation.conf -C NetworkAlgorithm.conf \
 $HOOT_OPTS test-files/Empty.osm test-files/Empty.osm tmp/dum.osm

hoot diff test-files/Empty.osm tmp/dum.osm || cat tmp/dum.osm
