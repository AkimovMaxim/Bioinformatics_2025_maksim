#!/bin/bash

paste - - < hw8/4/fin | awk '$2 ~ /777/ {print $1; print $2}' >>  fout
