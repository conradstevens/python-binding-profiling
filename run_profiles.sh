#!/bin/bash

NUM_TRIALS=1000
FIBONACCI_NUMBER=1000
BURNER_TRIALS=200


cd python/pypy/
source pypy_venv/bin/activate
python save_results.py \
  --num-trials $NUM_TRIALS \
  --fibonacci-number $FIBONACCI_NUMBER \
  --burner-trials $BURNER_TRIALS
deactivate
cd ../..

uv run main.py \
  --num-trials $NUM_TRIALS \
  --fibonacci-number $FIBONACCI_NUMBER \
  --burner-trials $BURNER_TRIALS