#!/bin/bash

if [ "$(echo 'mkvjahr9vdqe' | sed -E 's/[0-9]/Z/')" != "$(./esub '[0-9]' 'Z' 'mkvjahr9vdqe')" ]; then
  echo "Test 1 failed"
  exit 1
fi
if [ "$(echo 'aaabbbccc' | sed -E 's/ab//')" != "$(./esub 'ab' '' 'aaabbbccc')" ]; then
  echo "Test 2 failed"
  exit 1
fi