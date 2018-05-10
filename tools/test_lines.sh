#!/usr/bin/env bash
(find `pwd`/tests/unit/* -name '*.c' -print0 -o -name '*.h' -print0 | xargs -0 cat) | wc -l

