#!/bin/bash
export "GIT_AUTHOR_DATE=$1"
export "GIT_COMMITTER_DATE=$1"
git add .
git commit -m "$2"
