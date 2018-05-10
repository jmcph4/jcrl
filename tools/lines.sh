#!/usr/bin/env bash
root=`pwd`
src_lines=`$root/tools/src_lines.sh`
test_lines=`$root/tools/test_lines.sh`
total=$((src_lines + test_lines))
echo $total

