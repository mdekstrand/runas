#!/bin/sh

make runas || exit 2
if [ -d /out ]; then
    cp runas /out
fi
