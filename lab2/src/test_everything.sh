#!/bin/bash

# clock - done
# bash build_e1.sh
# bash test_clock_time.sh

# gettimeofday - done
# cd e2
# bash build_e2.sh
# bash test_gettimeofday_time.sh
# cd -

# only eigen:
cd e2
bash build_e2.sh
bash test_gettimeofday_time_only_eigen.sh
cd -

# strace - done
# bash e3/strace.sh

# perf
bash e4/perf.sh
