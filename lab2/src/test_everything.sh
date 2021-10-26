#!/bin/bash
bash build_e1.sh
bash test_clock_time.sh

cd e2
bash build_e2.sh
bash test_gettimeofday_time.sh
cd -

bash e3/strace.sh

bash e4/perf.sh
